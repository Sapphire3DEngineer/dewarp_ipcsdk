#include "stdafx.h"
#include "api.h"
#include "cProcessor.h"

extern cProcessor* g_pProcessor;

ProcessingErrorCode PROCESSOR_API IPC_StartUp()
{
	g_pProcessor->Startup();
	return PROCESSING_SUCCESS;
}
ProcessingErrorCode PROCESSOR_API IPC_CleanUp()
{
	g_pProcessor->Cleanup();
	return PROCESSING_SUCCESS;
}

int PROCESSOR_API IPC_Login(const int* pParameters)
{
	return g_pProcessor->Login(pParameters);
}
ProcessingErrorCode PROCESSOR_API IPC_Logout(int id)
{
	g_pProcessor->Logout(id);
	return PROCESSING_SUCCESS;
}
int PROCESSOR_API IPC_ClientPlay(int id, HWND hwnd)
{
	return g_pProcessor->ClientPlay(id, hwnd);
}
ProcessingErrorCode PROCESSOR_API IPC_ClientRefreshWnd(int id)
{
	if(g_pProcessor->ClientRefreshWnd(id)==0) return PROCESSING_SUCCESS;
	return PROCESSING_ERROR_GENERAL;
}
ProcessingErrorCode PROCESSOR_API IPC_ClientSetWnd(int id, HWND hwnd)
{
	if (g_pProcessor->ClientSEtWnd(id, hwnd) == 0) return PROCESSING_SUCCESS;
	return PROCESSING_ERROR_GENERAL;
}