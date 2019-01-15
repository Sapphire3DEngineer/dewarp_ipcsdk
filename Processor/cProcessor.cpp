#include "stdafx.h"
#include "cProcessor.h"

cProcessor* g_pProcessor = NULL;

cProcessor::cProcessor()
{
}


cProcessor::~cProcessor()
{
}


void cProcessor::Startup()
{
	HS_NET_Startup();
	HS_NET_SetMessageCallBack(cProcessor::NetMessageCallBack, this);
}


void cProcessor::Cleanup()
{
}
void CALLBACK cProcessor::NetMessageCallBack(int nLoginId, long msgType, void *pMsgData, void *pUser)
{

}
void CALLBACK cProcessor::NetAVDataCallBack(int nRealPlayId, char* pBuf, long nSize, HS_STREAM_INFO* pBufInfo, void *pUser)
{

}
void CALLBACK cProcessor::NetDecodeCallBack(int nRealPlayId, char *py, char *pu, char *pv, int ystride, int uvstride, HS_FRAME_INFO *pFrameInfo, void *pUser)
{
	g_pFileLog->Log(FileLog::LOG_DEBUG, "ystride = %d, uvstrid=%d", ystride, uvstride);
}
int cProcessor::ClientPlay(int id, HWND hwnd)
{
	AutoLock lock(m_CS);

	if (m_clientmap.find(id) == m_clientmap.end()) return -1;

	HS_CLIENTINFO clientInfo = m_clientmap[id];
	clientInfo.hwnd = hwnd;

	int playid = HS_NET_RealPlayStart(id, &clientInfo, cProcessor::NetAVDataCallBack, NULL);

	if (id != -1)
	{
		HS_NET_ClientSetDecodeCallBack(playid, cProcessor::NetDecodeCallBack, NULL);
	}

	return id;
}
int cProcessor::Login(const int* pParameters)
{
	AutoLock lock(m_CS);


	memcpy(&m_channelInfo, pParameters, sizeof(HS_CLIENTINFO));

	g_pFileLog->Log(FileLog::LOG_DEBUG, "%s %s %s", m_channelInfo.host, m_channelInfo.username, m_channelInfo.password);
	m_nLoginID = HS_NET_Login(&m_channelInfo);

	if (m_nLoginID > 0)
	{
		m_clientmap[m_nLoginID] = m_channelInfo;
	}
	else m_nLoginID = -1;
	return m_nLoginID;
}
void cProcessor::Logout(int id)
{
	AutoLock lock(m_CS);

	HS_NET_Logout(id);
	m_nLoginID = -1;
}
int cProcessor::ClientRefreshWnd(int id)
{
	AutoLock lock(m_CS);

	return HS_NET_ClientRefreshWnd(id);
}
int cProcessor::ClientSEtWnd(int id, HWND hwnd)
{
	AutoLock lock(m_CS);

	return HS_NET_ClientSetWnd(id, hwnd);
}