#ifndef	__AVC_DEFINE_H__
#define __AVC_DEFINE_H__

// 帧类型
enum{

		AVC_FRAME_TYPE_TIME	= 0,					//时间帧
		AVC_FRAME_TYPE_START,						//开始帧
		AVC_FRAME_TYPE_STOP	,						//结束帧
		AVC_FRAME_TYPE_VIDEO,						//视频流
		AVC_FRAME_TYPE_AUDIO,						//音频流
		AVC_FRAME_TYPE_WB,							//白板流
		AVC_FRAME_TYPE_SCREEN,						//屏幕流
		AVC_FRAME_TYPE_TEXT	,						//文本流
		AVC_FRAME_TYPE_USER_LIST,					//用户列表流		/avcon6.0会议人员信息
		AVC_FRAME_TYPE_AVTM	,						//视频窗口流		/avcon6.0模板信息
		AVC_FRAME_TYPE_AVTM_DATA,					//视频窗口数据流	/avcon6.0窗口信息
		AVC_FRAME_TYPE_VIDEO_WND_POS,				//视频窗口数据
		AVC_FRAME_TYPE_VIDEO_WND_NAME,				//视频窗口姓名
		AVC_FRAME_TYPE_AVTM_MID_SHOW,				//视频窗口排列中间窗口的显示和隐藏
		AVC_FRAME_TYPE_MCU_LIST,					//MCU列表流,		/avcon6.0会议分组信息
		AVC_FRAME_TYPE_CONFERENCE,					//会议信息,			/avcon6.0会议房间信息
		AVC_FRAME_TYPE_MY_USER,						//自己信息	
		AVC_VERSION,								//版本号			/avcon6.0版本信息
		AVC_FRAME_TYPE_SCREEN_INFO,					//监控端屏幕状态帧
		AVC_FRAME_TYPE_BEGIN_TIME,					//监控录像起始时间帧
		AVC_FRAME_TYPE_DOCSHARE,					//文档共享流
};

typedef struct tag_AVC_SCREEN_INFO
{
	UINT	screen_number;
	UINT	screen_ulSessionID[16];
	char	screen_name[16][17];
	bool	screen_active[16];
}AVC_SCREEN_INFO,*PAVC_SCREEN_INFO;

typedef struct tag_AVC_BEGIN_TIME
{
	UINT	session_id;
	UINT	year;
	UINT	month;
	UINT	day;
	UINT	hour;
	UINT	minute;
	UINT	second;
}AVC_BEGIN_TIME,*PAVC_BEGIN_TIME;

//AVIMContainerPlayer
//{
	/*******************************************************************************
	*记录格式： 
	*	char[0-3]	容器包含n个对话框						sizeof(int)或4 B
	*   char[4-7]	被选中的对话框的SessionID				sizeof(unsigned long)或4 B
	*   char[8-11]	容器显示类型							sizeof(int)或4 B
	*   char[12...]	数据									...
	*				(a)	SessionID							sizeof(unsigned long)或4 B
	*				(b)	UserName的长度						sizeof(int)或4 B
	*				(c)	UserName							strlen(UserName)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT						50
	/*******************************************************************************
	*记录格式： 
	*   char[0-3]	容器显示类型							sizeof(int)或4 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT_DISPLAY_TYPE		51
	/*******************************************************************************
	*记录格式： 
	*	char[0-15]	容器pos									sizeof(RECT)或16 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT_POS					52
	/*******************************************************************************
	*记录格式： 
	*	char[0-3]	被选中的对话框的SessionID				sizeof(unsigned long)或4 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT_SEL					53
	/*******************************************************************************
	*记录格式： 
	*	char[0-3]	SessionID								sizeof(int)或4 B
	*   char[4-7]	UserName的长度							sizeof(int)或4 B
	*	char[8...]	UserName								strlen(UserName)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT_NAME				54

	#define AVIM_FRAME_TYPE_CONTAINER_WB							61
	#define AVIM_FRAME_TYPE_CONTAINER_WB_DISPLAY_TYPE				62
	#define AVIM_FRAME_TYPE_CONTAINER_WB_POS						63
	#define AVIM_FRAME_TYPE_CONTAINER_WB_SEL						64
	#define AVIM_FRAME_TYPE_CONTAINER_WB_NAME						65
//}	

//AVIMVideoPlayer
//{
	/*******************************************************************************
	*记录格式： 
	*   char[0-3]	画中画类型								sizeof(int)或4 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_VIDEO_MGR_POS							71
	//{
		#define VIDEO_AND_VIDEO_DISPLAY_A	1				//单个视频(对方)
		#define VIDEO_AND_VIDEO_DISPLAY_AB	2				//两个视频(对方+自己)
		#define VIDEO_AND_VIDEO_DISPLAY_BA	3				//两个视频(自己+对方)
		#define VIDEO_AND_VIDEO_DISPLAY_AC	4				//两个视频(对方+共享)
		#define VIDEO_AND_VIDEO_DISPLAY_CA	5				//两个视频(共享+对方)
		#define VIDEO_AND_VIDEO_DISPLAY_ABC	6				//三个视频(对方+自己+共享)
		#define VIDEO_AND_VIDEO_DISPLAY_CAB	7				//三个视频(共享+对方+自己)
		#define VIDEO_AND_VIDEO_DISPLAY_BCA	8				//三个视频(自己+共享+对方)
	//}
	#define AVIM_FRAME_TYPE_VIDEO									72
	#define AVIM_FRAME_TYPE_AUDIO									73
	/*******************************************************************************
	*记录格式： 
	*	char[0...]	TitleName								strlen(TitleName)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_VIDEO_WND_NAME							74
	#define AVIM_FRAME_TYPE_FILEVIDEO								75
	#define AVIM_FRAME_TYPE_FILEAUDIO								76
	/*******************************************************************************
	*记录格式： 
	*	char[0...]	TitleName								strlen(TitleName)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_FILEVIDEO_NAME							77	
//}	

//AVIMChatPlayer
//{
	/*******************************************************************************
	*记录格式： 
	*char[0-3]		cszTime的长度							sizeof(int)或4 B
	*char[3...]		cszTime									strlen(cszTime)+1 B
	*char[n-n+3]	cszUserName的长度						sizeof(int)或4 B
	*char[n+3...]	cszUserName								strlen(cszUserName)+1 B
    *char[m-m+3]	cszMessage的长度						sizeof(int)或4 B
	*char[m+3...]	cszMessage								strlen(cszMessage)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CHAT_TEXT			81		//文本流(聊天文本流)
//}


//AVIMPlayer
//{
	/*******************************************************************************
	*记录格式： 
	*char[0-3]		cszTime的长度							sizeof(int)或4 B
	*char[4...]		cszTime									strlen(cszTime)+1 B
    *char[n-n+3]	cszMessage的长度						sizeof(int)或4 B
	*char[n+3...]	cszMessage								strlen(cszMessage)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_STATE_TEXT			91		//文本流(状态条流)
//}

// AVC文件结构
typedef struct tag_AVC_FILE_HEADER
{
	unsigned long		version		;		//版本号
	unsigned long		flag		;		//标识符
	char				password[16];		//密码
}AVC_FILE_HEADER, *PAVC_FILE_HEADER;

// 数据帧定义
typedef struct tag_AVC_DATA_FRAME
{
	char				frame_type	;		//帧类型
	char				key_frame	;		//关键帧
	unsigned short		sequence	;		//会话次数
	unsigned long		session_id	;		//会话标识
	int					channel		;		//通道
	unsigned long		timestamp	;		//时间戳
	long				data_length	;		//数据长度
}AVC_DATA_FRAME,*PAVC_DATA_FRAME;

// 时间帧
typedef struct tag_AVC_TIME_FRAME
{
	unsigned long		timestamp	;		//时间戳
	unsigned long		position	;		//指向数据帧位置
}AVC_TIME_FRAME,*PAVC_TIME_FRAME;


// 索引数据头定义
typedef struct tag_AVC_INDEX_HEADER
{
	char				index[4]	;		//索引标志:'INDX'
	char				frame_type	;		//帧类型
	unsigned short		sequence	;		//会话次数
	unsigned long		session_id	;		//会话标识
	int					channel		;		//通道
	unsigned long		start_time	;		//本流的开始时间
	unsigned long		stop_time	;		//本流的结束时间
	long				data_length	;		//本段索引数据长度
}AVC_INDEX_HEADER, *PAVC_INDEX_HEADER;

// 索引定义
typedef struct tag_AVC_INDEX_DATA
{
	unsigned long		pos			;		//位置
	unsigned long		timestamp	;		//时间戳
	char				key_frame	;		//是否关键帧
}AVC_INDEX_DATA, *PAVC_INDEX_DATA;

#define RECOVER_EVENT_FILENOTEXIT	1
#define RECOVER_EVENT_NOTAVCFILE	2
#define RECOVER_EVENT_POSITION	3
#define RECOVER_EVENT_ANALYING	4
#define RECOVER_EVENT_RECOVERING	5
#define RECOVER_EVENT_COMPLITE	6
#define RECOVER_EVENT_NORMALAVC	7

#endif
