// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "cProcessor.h"

extern cProcessor* g_pProcessor;
TCHAR g_szModuleFolder[MAX_PATH] = { 0, };

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		TCHAR szModule[MAX_PATH];
		GetModuleFileName(hModule, szModule, MAX_PATH);
		TCHAR szDrive[_MAX_DRIVE];
		TCHAR szDir[_MAX_DIR];
		_tsplitpath_s(szModule, szDrive, _MAX_DRIVE, szDir, _MAX_DIR, NULL, 0, NULL, 0);
		_stprintf_s(g_szModuleFolder, "%s%s", szDrive, szDir);
		string sLogFilename = "Processor.log";

		g_pFileLog = new FileLog();
		g_pFileLog->Initialize(FileLog::LOG_DEBUG, (g_szModuleFolder + sLogFilename).c_str());

		g_pProcessor = new cProcessor();
		break;
	}
	case DLL_PROCESS_DETACH:
	{

		SafeDelete(&g_pProcessor);

		if (g_pFileLog)
		{
			g_pFileLog->Log(FileLog::LOG_INFO, _T("DllMain: Screen encoder unloaded"));
			delete g_pFileLog;
			g_pFileLog = NULL;
		}

#ifdef _DEBUG
		_CrtDumpMemoryLeaks();
#endif

		break;

	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

