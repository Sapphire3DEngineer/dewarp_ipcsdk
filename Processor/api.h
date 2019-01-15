#pragma once

#define PROCESSOR_API __declspec(dllexport)

enum ProcessingErrorCode
{
	PROCESSING_SUCCESS = 0,
	PROCESSING_ERROR_GENERAL = 1,
	PROCESSING_ERROR_BADIMAGE = 2,
	PROCESSING_ERROR_GPUMEMORYOUT = 3,
	PROCESSING_ERROR_BIGIMAGE = 4,
};

extern "C" ProcessingErrorCode PROCESSOR_API IPC_StartUp();
extern "C" ProcessingErrorCode PROCESSOR_API IPC_CleanUp();

extern "C" int PROCESSOR_API IPC_Login(const int* pParameters);
extern "C" ProcessingErrorCode PROCESSOR_API IPC_Logout(int id);

extern "C" int PROCESSOR_API IPC_ClientPlay(int id, HWND hwnd);

extern "C" ProcessingErrorCode PROCESSOR_API IPC_ClientRefreshWnd(int id);
extern "C" ProcessingErrorCode PROCESSOR_API IPC_ClientSetWnd(int id, HWND hwnd);
