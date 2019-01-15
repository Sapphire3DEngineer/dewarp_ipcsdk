#ifndef __HS_AGRACCESS_H__
#define __HS_AGRACCESS_H__

#include "HsNetStructDef.h"


#if defined __BUILD_DLL		/* build dll */
	#define NET_DLLAPI	 __declspec(dllexport)
#elif defined __BUILD_LIB	/* static library */
	#define NET_DLLAPI
#else						/* use dll */
	#define NET_DLLAPI	__declspec(dllimport)
#endif

#define FUN_CALL __stdcall

#ifdef __cplusplus
extern "C"
{
#endif
/******************************************************************/


//Initialization function
NET_DLLAPI int  FUN_CALL HS_NET_Startup();

//Release resources function
NET_DLLAPI void FUN_CALL HS_NET_Cleanup();

//Set connect timeout function
NET_DLLAPI void FUN_CALL HS_NET_SetWaitTime(int nWaitTime, int nTryNum, int nTryInterval);

//Message callback function
typedef void(CALLBACK *fNetMessageCallBack)(int nLoginId, long msgType, void *pMsgData, void *pUser);
NET_DLLAPI void FUN_CALL HS_NET_SetMessageCallBack(fNetMessageCallBack cbMessageCallBack, void *pUser);

//Login and Logout function
NET_DLLAPI int FUN_CALL HS_NET_Login(HS_CLIENTINFO *pChaninfo);
NET_DLLAPI int FUN_CALL HS_NET_Logout(int nLoginId);

// 搜索设备信息
typedef void (CALLBACK* fSearchDeviceCallback)(long msgType/*HS_SEARCH_TYPE*/, void *pMsgData/*HS_STREAM_INFO*/, void *pUser);
NET_DLLAPI int FUN_CALL HS_NET_StartSearchDevice(fSearchDeviceCallback SearchDeviceCallback,void *pUser);
NET_DLLAPI int FUN_CALL HS_NET_StopSearchDevice();


//live view
typedef void (CALLBACK* fNetAVDataCallBack)(int nRealPlayId, char* pBuf, long nSize, HS_STREAM_INFO* pBufInfo, void *pUser);
NET_DLLAPI int FUN_CALL HS_NET_RealPlayStart(int nLoginId, HS_CLIENTINFO *pChaninfo, fNetAVDataCallBack dataFun, void *pUser);
NET_DLLAPI int FUN_CALL HS_NET_RealPlayStop(int nRealPlayId);

/*********************************Local Operator Interface************************************/
//window handle and refresh window
NET_DLLAPI int FUN_CALL HS_NET_ClientSetWnd(int nRealPlayId, HWND hWnd);
NET_DLLAPI int FUN_CALL HS_NET_ClientRefreshWnd(int nRealPlayId);

//stream information 
NET_DLLAPI int FUN_CALL HS_NET_ClientGetStreamInfo(int nRealPlayId, unsigned long *pBitRate, unsigned long *pFrameRate, unsigned long *pWidth, unsigned long *pHeight);

//play audio if live view has audio stream
NET_DLLAPI int FUN_CALL HS_NET_ClientPlayAudioStart(int nRealPlayId);
NET_DLLAPI int FUN_CALL HS_NET_ClientPlayAudioStop(int nRealPlayId);

//capture a picture
NET_DLLAPI int FUN_CALL HS_NET_ClientCapturePicture(int nRealPlayId, const char* filename, HsNetCaptureType type = HS_NET_CAPTURE_JPEG);

//record
NET_DLLAPI int FUN_CALL HS_NET_ClientStartRecord(int nRealPlayId, const char* filename, DWORD dwDurationSeconds=0);
NET_DLLAPI int FUN_CALL HS_NET_ClientStopRecord(int nRealPlayId);

//record another
NET_DLLAPI int FUN_CALL HS_NET_ClientStartRecord_Another(int nRealPlayId, const char* filename, DWORD dwDurationSeconds=0);
NET_DLLAPI int FUN_CALL HS_NET_ClientStopRecord_Another(int nRealPlayId);

//draw handle callback function
typedef void (CALLBACK* fNetDrawCallback)(int nRealPlayId, HDC hDC, void *pUser);
NET_DLLAPI int FUN_CALL HS_NET_ClientSetDrawCallback(int nRealPlayId, fNetDrawCallback dawFun, void *pUser);

//yuv420 data callback function
typedef void (CALLBACK * fNetDecodeCallBack)(int nRealPlayId, char *py, char *pu, char *pv, int ystride, int uvstride, HS_FRAME_INFO *pFrameInfo, void *pUser);
NET_DLLAPI int FUN_CALL HS_NET_ClientSetDecodeCallBack( int nRealPlayId, fNetDecodeCallBack decfun, void *pUser);

//cache frames before playing
NET_DLLAPI int FUN_CALL HS_NET_ClientSetRestoreFrame(int nRealPlayId, UINT frame);

//digital larger image. range:[(0,0), (image width, image height)]. when PRC is NULL, revert to its original state
NET_DLLAPI int FUN_CALL HS_NET_ClientShowRect(int nRealPlayId, RECT *pRc);
//********************************************************************************

/*********************************Remote configure interface************************************/
//image property
NET_DLLAPI int FUN_CALL HS_NET_GetImageProperty(int nLoginId, HS_IMAGE_PROPERTY *imageprty);
NET_DLLAPI int FUN_CALL HS_NET_SetImageProperty(int nLoginId, HS_IMAGE_PROPERTY *pImageprty);

//user configure
NET_DLLAPI int FUN_CALL HS_NET_UserConfig(int nLoginId, HS_USER_INFOR *pUserInfo, HS_USER_CONFIG_TYPE configType);
NET_DLLAPI int FUN_CALL HS_NET_GetUserInfo(int nLoginId, HS_USER_INFOR userInfo[], int bufNum, int *nCount);

//Motion detection
NET_DLLAPI int FUN_CALL HS_NET_GetMDInfo(int nLoginId, HS_MOTIONDETECTION_EX_PROPERTY* pMDInfo);
NET_DLLAPI int FUN_CALL HS_NET_SetMDInfo(int nLoginId, HS_MOTIONDETECTION_EX_PROPERTY* pMDInfo);

//Video cover
NET_DLLAPI int FUN_CALL HS_NET_GetVideoCover(int nLoginId, HS_VIDEOCOVER_PROPERTY* pVCInfo);
NET_DLLAPI int FUN_CALL HS_NET_SetVideoCover(int nLoginId, HS_VIDEOCOVER_PROPERTY* pVCInfo);

//Encoding scope
NET_DLLAPI int FUN_CALL HS_NET_GetEncodingScope(int nLoginId, HS_ENCODING_SCOPE *encscope);

//Encoding property
NET_DLLAPI int FUN_CALL HS_NET_SetEncodingProperty(int nLoginId, HS_ENCODING_PROPERTY clientParam[], int bufNum);
NET_DLLAPI int FUN_CALL HS_NET_GetEncodingProperty(int nLoginId, int nStreamType, HS_ENCODING_PROPERTY clientParam[], int bufNum, int *nCount);

//Network property
NET_DLLAPI int FUN_CALL HS_NET_SetNetParam(int nLoginId, HS_NET_PROPERTY *pNetInfo);
NET_DLLAPI int FUN_CALL HS_NET_GetNetParam(int nLoginId, HS_NET_PROPERTY *pNetInfo);

//Time parameter
NET_DLLAPI int FUN_CALL HS_NET_SetTimeParam(int nLoginId, HS_TIME_INFO *timeInfo);
NET_DLLAPI int FUN_CALL HS_NET_GetTimeParam(int nLoginId, HS_TIME_INFO *timeInfo);

//device upgrade
NET_DLLAPI int FUN_CALL HS_NET_Upgrade(int nLoginId, const char* filename);

//reboot、reset
NET_DLLAPI int FUN_CALL HS_NET_Reboot(int nLoginId);
NET_DLLAPI int FUN_CALL HS_NET_Reset(int nLoginId);

//log info
NET_DLLAPI int FUN_CALL HS_NET_GetLogFile(int nLoginId, HS_LOG_GREP_INFO *loggrepinfo, HS_LOG_EVENT_INFO logeventinfo[], int bufNum, int *nCount);

//smtp、ftp、ddns、p2p
NET_DLLAPI int FUN_CALL HS_NET_GetSmtp(int nLoginId, HS_SMTP_PROPERTY *smtpprty);
NET_DLLAPI int FUN_CALL HS_NET_SetSmtp(int nLoginId, HS_SMTP_PROPERTY *smtpprty);

NET_DLLAPI int FUN_CALL HS_NET_GetFtp(int nLoginId, HS_FTP_PROPERTY *ftpprty);
NET_DLLAPI int FUN_CALL HS_NET_SetFtp(int nLoginId, HS_FTP_PROPERTY *ftpprty);

NET_DLLAPI int FUN_CALL HS_NET_GetDDNS(int nLoginId, HS_DDNSSERVER_PROPERTY *ddnsprty);
NET_DLLAPI int FUN_CALL HS_NET_SetDDNS(int nLoginId, HS_DDNSSERVER_PROPERTY *ddnsprty);

NET_DLLAPI int FUN_CALL HS_NET_GetP2P(int nLoginId, HS_P2P_PROPERTY *p2pprty);
NET_DLLAPI int FUN_CALL HS_NET_SetP2P(int nLoginId, HS_P2P_PROPERTY *p2pprty);
NET_DLLAPI int FUN_CALL HS_NET_GetP2PInfo(int nLoginId, HS_P2P_INFO *p2pinfo);

//OSD property
NET_DLLAPI int FUN_CALL HS_NET_GetOSD(int nLoginId, HS_DISPLAY_PROPERTY *displayprty);
NET_DLLAPI int FUN_CALL HS_NET_SetOSD(int nLoginId, HS_DISPLAY_PROPERTY *displayprty);

//Audio property
NET_DLLAPI int FUN_CALL HS_NET_GetAudio(int nLoginId, HS_AUDIO_PROPERTY *adprty);
NET_DLLAPI int FUN_CALL HS_NET_SetAudio(int nLoginId, HS_AUDIO_PROPERTY *adprty);

//device information
NET_DLLAPI int FUN_CALL HS_NET_GetDeviceInfo(int nLoginId, HS_DEV_INFO *devinfo);
NET_DLLAPI int FUN_CALL HS_NET_SetDeviceInfo(int nLoginId, HS_DEV_INFO *devinfo);

//schedul reboot
NET_DLLAPI int FUN_CALL HS_NET_GetTimeReboot(int nLoginId, HS_SYSREBOOT_PROPERTY *sysreboot);
NET_DLLAPI int FUN_CALL HS_NET_SetTimeReboot(int nLoginId, HS_SYSREBOOT_PROPERTY *sysreboot);

//protocol configure
NET_DLLAPI int FUN_CALL HS_NET_GetAgreementProperty(int nLoginId, int agrType, HS_AGREEMENT_PROPERTY agreementPrty[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL HS_NET_SetAgreementProperty(int nLoginId, HS_AGREEMENT_PROPERTY agreementPrty[], int bufNum);

//Alarm configure
NET_DLLAPI int FUN_CALL HS_NET_GetAlarmScopeV2(int nLoginId, HS_ALARM_SCOPE_V2 *pAlarmScope);
NET_DLLAPI int FUN_CALL HS_NET_GetAlarmPropertyV2(int nLoginId, HS_ALARM_PROPERTY_V2 *pAlarmPrty);
NET_DLLAPI int FUN_CALL HS_NET_SetAlarmPropertyV2(int nLoginId, HS_ALARM_PROPERTY_V2 *pAlarmPrty);

//update by 2016.05.10
//search record file
NET_DLLAPI int FUN_CALL HS_NET_SearchRecordFile(int nLoginId, HS_PLAYBACK_GREP_INFO *pGrepInfo, HS_PLAYBACK_FILE_INFO fileInfo[], int bufNum, int *nCount);

//record download
NET_DLLAPI int FUN_CALL HS_NET_DownloadRecordFileStart(int nLoginId, HS_PLAYBACK_FILE_INFO *pFileInfo, const char* filename);
NET_DLLAPI int FUN_CALL HS_NET_DownloadRecordFileStop(int nDownloadId);

//record playback
NET_DLLAPI int FUN_CALL HS_NET_PlayBackStart(int nLoginId, HS_CLIENTINFO *pChaninfo, HS_PLAYBACK_FILE_INFO *pFileInfo, fNetAVDataCallBack dataFun = NULL, void *pUser=NULL);
NET_DLLAPI int FUN_CALL HS_NET_PlayBackStop(int nPlayBackId);

NET_DLLAPI int FUN_CALL HS_NET_PlayBackPause(int nPlayBackId, int lpause);
NET_DLLAPI int FUN_CALL HS_NET_PlayBackSpeed(int nPlayBackId, unsigned char fspeed);
NET_DLLAPI int FUN_CALL HS_NET_PlayBackSeek(int nPlayBackId, int lseek);
NET_DLLAPI int FUN_CALL HS_NET_PlayBackByFrame(int nPlayBackId);
		   
//PTZ
NET_DLLAPI int FUN_CALL HS_NET_PTZCtrl(int nLoginId, HS_PTZ_OPTION *ptzopt);
		   
NET_DLLAPI int FUN_CALL HS_NET_GetPTZProperty(int nLoginId, HS_PTZ_PROPERTY *ptzopt);
NET_DLLAPI int FUN_CALL HS_NET_SetPTZProperty(int nLoginId, HS_PTZ_PROPERTY *ptzopt);
		   
NET_DLLAPI int FUN_CALL HS_NET_GetPresetPointProperty(int nLoginId, int nChannel, UCHAR ucIndex, HS_PRESET_POINT_PROPERTY presetPrty[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL HS_NET_SetPresetPointProperty(int nLoginId, HS_PRESET_POINT_PROPERTY presetPrty[], int bufNum);
		   
NET_DLLAPI int FUN_CALL HS_NET_GetCruisePointProperty(int nLoginId, int nChannel, UCHAR ucCruiseLineIndex, UCHAR ucCruisePointIndex, HS_CRUISE_POINT_PROPERTY cruisePrty[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL HS_NET_SetCruisePointProperty(int nLoginId, HS_CRUISE_POINT_PROPERTY cruisePrty[], int bufNum);
		   
NET_DLLAPI int FUN_CALL HS_NET_GetCruiseLineProperty(int nLoginId, int nChannel, UCHAR ucIndex, HS_CRUISE_LINE_PROPERTY cruisePrty[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL HS_NET_SetCruiseLineProperty(int nLoginId, HS_CRUISE_LINE_PROPERTY cruisePrty[], int bufNum);
		   
NET_DLLAPI int FUN_CALL HS_NET_GetSerialProperty(int nLoginId, int nChannel, HS_PTZ_SERIAL_PROPERTY serialPrty[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL HS_NET_SetSerialProperty(int nLoginId, HS_PTZ_SERIAL_PROPERTY serialPrty[], int bufNum);
		   
NET_DLLAPI int FUN_CALL HS_NET_GetPTZInfo(int nLoginId, int nChannel, HS_PTZ_INFO ptzInfo[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL HS_NET_SetPTZInfo(int nLoginId, HS_PTZ_INFO ptzInfo[], int bufNum);
		   
//Storage Config
NET_DLLAPI int FUN_CALL  HS_NET_GetStorageProperty(int nLoginId, int nChannel, int storageType, unsigned char storageId, HS_STORAGE_PROPERTY storagePrty[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL  HS_NET_SetStorageProperty(int nLoginId, HS_STORAGE_PROPERTY storagePrty[], int bufNum);

NET_DLLAPI int FUN_CALL  HS_NET_StorageOption(int nLoginId, HS_STORAGE_OPTION *storageOpt);
		   
NET_DLLAPI int FUN_CALL  HS_NET_GetStorageInfo(int nLoginId, int nChannel, int storageType, unsigned char storageId, HS_STORAGE_INFO storageInfo[], int bufNum, int *nCount);
		   
//Record config
NET_DLLAPI int FUN_CALL  HS_NET_GetRegularRecordProperty(int nLoginHandle, HS_NVR_REGULAR_RECORD_PROPERTY *pRglRecordPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetRegularRecordProperty(int nLoginHandle, HS_NVR_REGULAR_RECORD_PROPERTY *pRglRecordPrty);
		   
//Snap config
NET_DLLAPI int FUN_CALL  HS_NET_GetRegularSnapProperty(int nLoginId, HS_NVR_REGULAR_SNAP_PROPERTY *pRglSnapPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetRegularSnapProperty(int nLoginId, HS_NVR_REGULAR_SNAP_PROPERTY *pRglSnapPrty);

//Region of Interest
NET_DLLAPI int FUN_CALL  HS_NET_GetROIProperty(int nLoginId, HS_ROI_PROPERTY *pROIPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetROIProperty(int nLoginId, HS_ROI_PROPERTY *pROIPrty);

//Lens distortion correction
NET_DLLAPI int FUN_CALL  HS_NET_GetLDCProperty(int nLoginId, HS_LDC_PROPERTY *pLDCPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetLDCProperty(int nLoginId, HS_LDC_PROPERTY *pLDCPrty);

//output video 
NET_DLLAPI int FUN_CALL  HS_NET_GetVideoOutputProperty(int nLoginId, HS_VIDEO_OUTPUT_PROPERTY *pVideoOutputPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetVideoOutputProperty(int nLoginId, HS_VIDEO_OUTPUT_PROPERTY *pVideoOutputPrty);

//System Control
NET_DLLAPI int FUN_CALL  HS_NET_GetCommonSysProperty(int nLoginId, int nChannel, HS_COMMON_SYS_PROPERTY *pSysPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetCommonSysProperty(int nLoginId, int nChannel, HS_COMMON_SYS_PROPERTY *pSysPrty);

//cloud
NET_DLLAPI int FUN_CALL  HS_NET_GetCloudBindInfo(int nLoginId, int nChannel, HS_CLOUD_BRAND_TYPE bindType, HS_CLOUD_BIND_INFO *pCloudBindInfo);
NET_DLLAPI int FUN_CALL  HS_NET_SetCloudBindInfo(int nLoginId, int nChannel, HS_CLOUD_BIND_INFO *pCloudBindInfo);
NET_DLLAPI int FUN_CALL  HS_NET_GetCloudStateInfo(int nLoginId, int nChannel, HS_CLOUD_STATE_INFO *pCloudStateInfo);

//import export file
NET_DLLAPI int FUN_CALL  HS_NET_ImportFileStart(int nLoginId, const char* filename, HS_FILE_PROPERTY *pFilePrty);
NET_DLLAPI int FUN_CALL  HS_NET_ImportFileStop(int nLoginId);
NET_DLLAPI int FUN_CALL  HS_NET_ExportFileStart(int nLoginId, const char* filename, HS_FILE_PROPERTY *pFilePrty);
NET_DLLAPI int FUN_CALL  HS_NET_ExportFileStop(int nLoginId);

//wifi
NET_DLLAPI int FUN_CALL  HS_NET_GetWifiList(int nLoginId, int nChannel, HS_WIFI_INFO wifiInfo[], int bufNum, int *nCount);
NET_DLLAPI int FUN_CALL  HS_NET_WifiOperate(int nLoginId, HS_WIFI_OPERATE_TYPE operateType, HS_WIFI_INFO *pWifiInfo);

//Daylight Saving Time
NET_DLLAPI int FUN_CALL  HS_NET_GetDstProperty(int nLoginId, HS_DST_PROPERTY *pDstPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetDstProperty(int nLoginId, HS_DST_PROPERTY *pDstPrty);

//Automatic maintenance configuration
NET_DLLAPI int FUN_CALL  HS_NET_GetSystemRebootExProperty(int nLoginId, HS_SYSREBOOT_EX_PROPERTY *pSysRebootExPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetSystemRebootExProperty(int nLoginId, HS_SYSREBOOT_EX_PROPERTY *pSysRebootExPrty);

//IO
NET_DLLAPI int FUN_CALL  HS_NET_GetIoProperty(int nLoginId, HS_IO_PROPERTY *pIoPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetIoProperty(int nLoginId, HS_IO_PROPERTY *pIoPrty);

//fish eye
NET_DLLAPI int FUN_CALL  HS_NET_GetFishEyeProperty(int nLoginId, HS_FISH_EYE_PROPERTY *pFishEyePrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetFishEyeProperty(int nLoginId, HS_FISH_EYE_PROPERTY *pFishEyePrty);

//Suitable Encoding Param
NET_DLLAPI int FUN_CALL  HS_NET_GetSuitableEncodingProperty(int nLoginId, HS_SUITABLE_ENCODING_PROPERTY *pSuitableEncodingPrty);

//Exception Events
NET_DLLAPI int FUN_CALL  HS_NET_GetABNormalEventProperty(int nLoginId, HS_ABNORMAL_EVENT_PROPERTY *pABNormalEventPrty);
NET_DLLAPI int FUN_CALL  HS_NET_SetABNormalEventProperty(int nLoginId, HS_ABNORMAL_EVENT_PROPERTY *pABNormalEventPrty);

#ifdef __cplusplus
}
#endif
#endif


