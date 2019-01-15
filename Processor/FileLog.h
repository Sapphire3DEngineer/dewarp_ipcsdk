#pragma once

#include "Lock.h"
#include <tchar.h>
#include <string>
#include <iostream>
#include "targetver.h"
#include <fstream>
#include <sstream>
using namespace std;
class FileLog
{

public:

	enum FileLogLevel
	{
		LOG_NONE,
		LOG_ERROR,
		LOG_WARNING,
		LOG_INFO,
		LOG_DEBUG,
		LOG_TRACE,
	};

	FileLog() :
		m_nLogLevel(LOG_INFO),
		m_hLogFile(INVALID_HANDLE_VALUE),
		m_nPrevPrefixLen(0),
		m_nMsgRepeatCount(0),
		m_nPrevLogLevel(LOG_TRACE)
	{
	}

	~FileLog()
	{
		clear();
	}

	void Initialize(FileLogLevel nLogLevel, const TCHAR* pszLogFileName)
	{

		AutoLock autoLock(m_CS);

		clear();
		m_nLogLevel = nLogLevel;

		for (int i = 0; i < 10; ++i)
		{
			m_hLogFile = CreateFile(pszLogFileName, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (m_hLogFile != INVALID_HANDLE_VALUE)
			{
				break;
			}
			else
			{
				Sleep(1000);
			}
		}

		if (m_hLogFile == INVALID_HANDLE_VALUE)
		{
			printf("Unable to open log file %s, error %d\n", pszLogFileName, GetLastError());
			return;
		}

		if (sizeof(TCHAR) == 2)
		{
			LockFile(m_hLogFile, 0, 0, 2, 0);
			LARGE_INTEGER nFileSize = { 0, };
			if (GetFileSizeEx(m_hLogFile, &nFileSize))
			{
				if (nFileSize.QuadPart == 0)
				{
					const unsigned char cUniMark[] = { 0xFF, 0xFE };
					DWORD dwWritten = 0;
					WriteFile(m_hLogFile, cUniMark, sizeof(cUniMark), &dwWritten, NULL);
				}
				else
				{
					LARGE_INTEGER nNewPos = { 0, };
					SetFilePointerEx(m_hLogFile, nFileSize, &nNewPos, FILE_BEGIN);
				}
			}
			UnlockFile(m_hLogFile, 0, 0, 2, 0);
		}

		m_PrevBuf[0] = 0;

	}

	FileLogLevel GetLogLevel()
	{
		AutoLock autoLock(m_CS);
		return m_nLogLevel;
	}

	void SetLogLevel(FileLogLevel nLogLevel)
	{
		AutoLock autoLock(m_CS);
		m_nLogLevel = nLogLevel;
	}

	void Log(FileLogLevel nLevel, const TCHAR* pszFormat, ...)
	{

		if (m_hLogFile == INVALID_HANDLE_VALUE) return;
		if (nLevel > m_nLogLevel) return;

		AutoLock autoLock(m_CS);

		va_list args;
		va_start(args, pszFormat);
		log(nLevel, pszFormat, args);
		va_end(args);

	}

	void Log(FileLogLevel nLevel, int nBufferLen, const char* pBuffer)
	{

		if (m_hLogFile == INVALID_HANDLE_VALUE) return;
		if (nLevel > m_nLogLevel) return;

		AutoLock autoLock(m_CS);

		DWORD dwWritten = 0;
		LockFile(m_hLogFile, 0, 0, 2, 0);
		SetFilePointer(m_hLogFile, 0, 0, FILE_END);
		WriteFile(m_hLogFile, pBuffer, nBufferLen, &dwWritten, NULL);
		UnlockFile(m_hLogFile, 0, 0, 2, 0);

		OutputDebugStringA(pBuffer);

	}

	void FFlog(int level, char* line)
	{

		if (m_hLogFile == INVALID_HANDLE_VALUE) return;
		if (m_nLogLevel < LOG_DEBUG) return;

		AutoLock autoLock(m_CS);

		size_t nLen = strlen(line);
		while (nLen > 0 && (line[nLen - 1] == '\r' || line[nLen - 1] == '\n'))
		{
			line[--nLen] = 0;
		}
		string s = line;
		if (s.length() == 0) return;

		string ws(s.begin(), s.end());
		stringstream wss;
		wss << "FF(" << level << "): " << ws;
		log(LOG_DEBUG, wss.str().c_str(), NULL);

		return;

	}

protected:

	void log(FileLogLevel nLevel, const TCHAR* pszFormat, va_list args)
	{
		SYSTEMTIME t;
		::GetLocalTime(&t);
		_stprintf_s(m_Buf, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d [%d] %s "), t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, GetCurrentThreadId(), levelToString(nLevel));
		//_stprintf(m_Buf, _T("%02d:%02d:%02d.%03d "), t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
		size_t nPrefixLen = 24;// _tcslen(m_Buf);
		size_t nLen = _tcslen(m_Buf);

		if (args == NULL)
		{
			_tcscpy_s(m_Buf + nLen, _countof(m_Buf) - nLen, pszFormat);
		}
		else
		{
			_vstprintf_s(m_Buf + nLen, _countof(m_Buf) - nLen, pszFormat, args);
		}

		nLen = _tcslen(m_Buf);
		m_Buf[nLen++] = _T('\r');
		m_Buf[nLen++] = _T('\n');
		m_Buf[nLen] = 0;

		if (_tcscmp(m_PrevBuf + m_nPrevPrefixLen, m_Buf + nPrefixLen) == 0)
		{
			++m_nMsgRepeatCount;
		}
		else
		{

			DWORD dwWritten = 0;

			LockFile(m_hLogFile, 0, 0, 2, 0);
			SetFilePointer(m_hLogFile, 0, 0, FILE_END);
			if (m_nMsgRepeatCount >= 1)
			{
				_stprintf_s(m_PrevBuf, _T("%04d-%02d-%02d %02d:%02d:%02d.%03d %s previous message repeated %d times\r\n"), t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds, levelToString(m_nPrevLogLevel), m_nMsgRepeatCount);
				WriteFile(m_hLogFile, m_PrevBuf, (DWORD)(_tcslen(m_PrevBuf) * sizeof(TCHAR)), &dwWritten, NULL);
				OutputDebugString(m_PrevBuf);
				m_nMsgRepeatCount = 0;
			}

			WriteFile(m_hLogFile, m_Buf, (DWORD)(nLen * sizeof(TCHAR)), &dwWritten, NULL);
			UnlockFile(m_hLogFile, 0, 0, 2, 0);

			OutputDebugString(m_Buf);

			_tcscpy_s(m_PrevBuf, m_Buf);
			m_nPrevPrefixLen = nPrefixLen;
			m_nPrevLogLevel = nLevel;

		}

	}

	void clear()
	{
		if (m_hLogFile != INVALID_HANDLE_VALUE)
		{
			FlushFileBuffers(m_hLogFile);
			CloseHandle(m_hLogFile);
			m_hLogFile = INVALID_HANDLE_VALUE;
		}
	}

	TCHAR* levelToString(FileLogLevel nLevel)
	{
		switch (nLevel)
		{
		case LOG_ERROR:
			return _T("ERROR");
			break;
		case LOG_WARNING:
			return _T("WARN ");
			break;
		case LOG_INFO:
			return _T("INFO ");
			break;
		case LOG_DEBUG:
			return _T("DEBUG");
			break;
		case LOG_TRACE:
			return _T("TRACE");
			break;
		}
		return _T("     ");
	}

	CritSec m_CS;
	FileLogLevel m_nLogLevel;
	HANDLE m_hLogFile;
	TCHAR m_Buf[10240];
	TCHAR m_PrevBuf[10240];
	size_t m_nPrevPrefixLen;
	FileLogLevel m_nPrevLogLevel;
	int m_nMsgRepeatCount;

};

