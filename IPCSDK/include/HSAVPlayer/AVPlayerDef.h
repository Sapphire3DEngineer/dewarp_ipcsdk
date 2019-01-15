#ifndef __AV_PLAYER_DEF_H__
#define __AV_PLAYER_DEF_H__

typedef struct _AV_STREAM_INFO
{
	unsigned short	videoCoder;		//视频编码方式
	unsigned short	audioCoder;		//音频编码方式
	unsigned short	frameRate;		//帧率
	unsigned short	bitRate;			//比特率
	unsigned short	nWidth;			// 视频宽
	unsigned short	nHeight;			// 视频高
	unsigned short	frameType;		// H264帧类型 见下面定义
	unsigned short     isKeyFrame;		//是否为关键帧
	unsigned short	type;			//数据类型，0 视频， 1 音频  2码流头信息
	unsigned short	res;			//低字节为插入视频类型 0:当显示缓冲满时等待缓冲有空闲再插入,4:当显示缓冲满时直接丢弃.高字节为解码器读取每一帧源数据的方式 0x1200:通过ff_read_frame来读取每一帧
	long			nStamp;			// 时标信息，单位毫秒
}AV_STREAM_INFO;

typedef struct _AV_STREAM_INFO_EX
{
	unsigned short	videoCoder;		//视频编码方式
	unsigned short	audioCoder;		//音频编码方式
	unsigned short	frameRate;		//帧率
	unsigned short	videoBitRate;			//比特率
	unsigned short	nWidth;			// 视频宽
	unsigned short	nHeight;			// 视频高
	unsigned short	frameType;		// H264帧类型 见下面定义
	unsigned short     isKeyFrame;		//是否为关键帧
	unsigned short	type;			//数据类型，0 视频， 1 音频  2码流头信息
	unsigned int	res;			//低字节为插入视频类型 0:当显示缓冲满时等待缓冲有空闲再插入,4:当显示缓冲满时直接丢弃.高字节为解码器读取每一帧源数据的方式 0x1200:通过ff_read_frame来读取每一帧
	int			nStamp;			// 时标信息，单位毫秒
	unsigned short audioBitRate;    //音频码率
	unsigned short sampleRate;      //音频采样率
	unsigned short channels;        //音频声道数
}AV_STREAM_INFO_EX;
//解码后数据回调
typedef struct _AV_FRAME_INFO
{ 
	long nWidth;	 // 画面宽，单位为像素，如果是音频数据则为0
	long nHeight;	// 画面高，单位为像素，如果是音频数据则为0
	long nStamp;	 // 时标信息，单位毫秒
	long nType;		//数据类型，见下表
	long nFrameRate;// 编码时产生的图像帧率
}AV_FRAME_INFO; 

//回调函数申明

//设备消息回调函数
typedef void(CALLBACK *HsAVMessageCallBack)(HANDLE handle, long msgType,  void*lpStruct, void *lpContext);

//视频数据回调函数
typedef void ( CALLBACK* HsAVDataCallBack )( HANDLE handle, char* pBuf, long nSize, AV_FRAME_INFO* pBufInfo, void *lpContext  );

//视频显示回调函数
typedef void ( CALLBACK* HsDrawCallback )( HANDLE hHandle, HDC hDC, void *lpContext );

//解码回调函数
typedef void ( CALLBACK * HsDecodeCallBack ) ( HANDLE hHandle, char * py, char*pu, char*pv,int ystride,int uvstride, AV_FRAME_INFO * pFrameInfo, void* lpContext  );

//FRAME_INFO.avType
enum AV_Stream_Type
{
	AV_STREAM_VIDEO = 0,
	AV_STREAM_AUDIO,
	AV_STREAM_HEADER,
};


//FRAME_INFO.nalType
#define H264_NAL_TYPE_SLICE      1
#define H264_NAL_TYPE_IDR        5
#define H264_NAL_TYPE_SEI        6
#define H264_NAL_TYPE_SPS        7
#define H264_NAL_TYPE_PPS        8
//#define NAL_TYPE_SEQ_END    9
//#define NAL_TYPE_STREAM_END 10

//FRAME_INFO.videoCoder
#ifndef HS_VIDEO_CODER_H264
#define HS_VIDEO_CODER_H264				96
#define HS_VIDEO_CODER_MJPEG				26
#define HS_VIDEO_CODER_MPEG4				99
#endif

//FRAME_INFO.audioCoder
#define HS_AUDIO_CODER_G711_A				0x01  /* 64kbps G.711 A, see RFC3551.txt  4.5.14 PCMA */
#define HS_AUDIO_CODER_G711_U				0x02  /* 64kbps G.711 U, see RFC3551.txt  4.5.14 PCMU */
#define HS_AUDIO_CODER_G726_16KBPS			0x04  /* 16kbps G.726, see RFC3551.txt  4.5.4 G726-16 */
#define HS_AUDIO_CODER__G726_24KBPS			0x05  /* 24kbps G.726, see RFC3551.txt  4.5.4 G726-24 */
#define HS_AUDIO_CODER_G726_32KBPS			0x06  /* 32kbps G.726, see RFC3551.txt  4.5.4 G726-32 */
#define HS_AUDIO_CODER_G726_40KBPS			0x07  /* 40kbps G.726, see RFC3551.txt  4.5.4 G726-40 */
#define HS_AUDIO_CODER_PCM                  0x13
#define HS_AUDIO_CODER_ADPCM                0x14
#define HS_AUDIO_CODER_AAC                  0x20
enum HsCaptureType
{
	HS_CAPTURE_JPEG = 0,//默认
	HS_CAPTURE_BMP
};

/*************************** 消息 ********************************/
//状态消息
enum HS_MSG_TYPE
{
	//录像状态void*lpStruct = char*filename
	HS_MSG_RECORD_BEGIN = 0x100,			//第一帧数据写入时回调产生此消息
	HS_MSG_RECORD_WRITE_ERROR,			//录像异常错误,写文件失败
	HS_MSG_RECORD_FORMAT_CHANGED,	//音视频格式,分辨率,帧率发生改变,内部已经停止录像,如果仍需要录像则需要重新调用开始录像, 一般此消息在视频重连后发生
	HS_MSG_RECORD_PACKET_FINISH	,		//录象打包完成,内部已经调用停止录像,外部直接再调用开始录像即可
	
	//另外一份录像文件,可用于专门录制报警录像void*lpStruct = char*filename
	HS_MSG_RECORD_BEGIN_ANOTHER,				//同上
	HS_MSG_RECORD_WRITE_ERROR_ANOTHER,		//同上
	HS_MSG_RECORD_FORMAT_CHANGED_ANOTHER,	//同上
	HS_MSG_RECORD_PACKET_FINISH_ANOTHER,		//同上
	//播放使用
	HS_MSG_REPLAY_FINISHED = 0X400,		//文件回放结束
};

#endif




