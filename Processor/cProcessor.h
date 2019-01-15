#pragma once

#include "HSAGRAccess\HSAGRAccess.h"
#include "HSAGRAccess\HsNetStructDef.h"
#include <map>

class cProcessor
{
public:
	cProcessor();
	~cProcessor();
	void Startup();
	void Cleanup();
	int Login(const int* pParameters);
	void Logout(int id);
	int ClientPlay(int id, HWND hwnd);
	int ClientRefreshWnd(int id);
	int ClientSEtWnd(int id, HWND hwnd);
	static void CALLBACK NetMessageCallBack(int nLoginId, long msgType, void *pMsgData, void *pUser);
	static void CALLBACK NetAVDataCallBack(int nRealPlayId, char* pBuf, long nSize, HS_STREAM_INFO* pBufInfo, void *pUser);
	static void CALLBACK NetDecodeCallBack(int nRealPlayId, char *py, char *pu, char *pv, int ystride, int uvstride, HS_FRAME_INFO *pFrameInfo, void *pUser);
	HS_CLIENTINFO m_channelInfo;
	int m_nLoginID;
	int m_nRealPlayId;

	map<int, HS_CLIENTINFO> m_clientmap;
	CritSec m_CS;
};

