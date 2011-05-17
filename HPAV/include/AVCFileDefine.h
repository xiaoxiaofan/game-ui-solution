#ifndef	__AVC_DEFINE_H__
#define __AVC_DEFINE_H__

// ֡����
enum{

		AVC_FRAME_TYPE_TIME	= 0,					//ʱ��֡
		AVC_FRAME_TYPE_START,						//��ʼ֡
		AVC_FRAME_TYPE_STOP	,						//����֡
		AVC_FRAME_TYPE_VIDEO,						//��Ƶ��
		AVC_FRAME_TYPE_AUDIO,						//��Ƶ��
		AVC_FRAME_TYPE_WB,							//�װ���
		AVC_FRAME_TYPE_SCREEN,						//��Ļ��
		AVC_FRAME_TYPE_TEXT	,						//�ı���
		AVC_FRAME_TYPE_USER_LIST,					//�û��б���		/avcon6.0������Ա��Ϣ
		AVC_FRAME_TYPE_AVTM	,						//��Ƶ������		/avcon6.0ģ����Ϣ
		AVC_FRAME_TYPE_AVTM_DATA,					//��Ƶ����������	/avcon6.0������Ϣ
		AVC_FRAME_TYPE_VIDEO_WND_POS,				//��Ƶ��������
		AVC_FRAME_TYPE_VIDEO_WND_NAME,				//��Ƶ��������
		AVC_FRAME_TYPE_AVTM_MID_SHOW,				//��Ƶ���������м䴰�ڵ���ʾ������
		AVC_FRAME_TYPE_MCU_LIST,					//MCU�б���,		/avcon6.0���������Ϣ
		AVC_FRAME_TYPE_CONFERENCE,					//������Ϣ,			/avcon6.0���鷿����Ϣ
		AVC_FRAME_TYPE_MY_USER,						//�Լ���Ϣ	
		AVC_VERSION,								//�汾��			/avcon6.0�汾��Ϣ
		AVC_FRAME_TYPE_SCREEN_INFO,					//��ض���Ļ״̬֡
		AVC_FRAME_TYPE_BEGIN_TIME,					//���¼����ʼʱ��֡
		AVC_FRAME_TYPE_DOCSHARE,					//�ĵ�������
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
	*��¼��ʽ�� 
	*	char[0-3]	��������n���Ի���						sizeof(int)��4 B
	*   char[4-7]	��ѡ�еĶԻ����SessionID				sizeof(unsigned long)��4 B
	*   char[8-11]	������ʾ����							sizeof(int)��4 B
	*   char[12...]	����									...
	*				(a)	SessionID							sizeof(unsigned long)��4 B
	*				(b)	UserName�ĳ���						sizeof(int)��4 B
	*				(c)	UserName							strlen(UserName)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT						50
	/*******************************************************************************
	*��¼��ʽ�� 
	*   char[0-3]	������ʾ����							sizeof(int)��4 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT_DISPLAY_TYPE		51
	/*******************************************************************************
	*��¼��ʽ�� 
	*	char[0-15]	����pos									sizeof(RECT)��16 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT_POS					52
	/*******************************************************************************
	*��¼��ʽ�� 
	*	char[0-3]	��ѡ�еĶԻ����SessionID				sizeof(unsigned long)��4 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CONTAINER_VIDEOCHAT_SEL					53
	/*******************************************************************************
	*��¼��ʽ�� 
	*	char[0-3]	SessionID								sizeof(int)��4 B
	*   char[4-7]	UserName�ĳ���							sizeof(int)��4 B
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
	*��¼��ʽ�� 
	*   char[0-3]	���л�����								sizeof(int)��4 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_VIDEO_MGR_POS							71
	//{
		#define VIDEO_AND_VIDEO_DISPLAY_A	1				//������Ƶ(�Է�)
		#define VIDEO_AND_VIDEO_DISPLAY_AB	2				//������Ƶ(�Է�+�Լ�)
		#define VIDEO_AND_VIDEO_DISPLAY_BA	3				//������Ƶ(�Լ�+�Է�)
		#define VIDEO_AND_VIDEO_DISPLAY_AC	4				//������Ƶ(�Է�+����)
		#define VIDEO_AND_VIDEO_DISPLAY_CA	5				//������Ƶ(����+�Է�)
		#define VIDEO_AND_VIDEO_DISPLAY_ABC	6				//������Ƶ(�Է�+�Լ�+����)
		#define VIDEO_AND_VIDEO_DISPLAY_CAB	7				//������Ƶ(����+�Է�+�Լ�)
		#define VIDEO_AND_VIDEO_DISPLAY_BCA	8				//������Ƶ(�Լ�+����+�Է�)
	//}
	#define AVIM_FRAME_TYPE_VIDEO									72
	#define AVIM_FRAME_TYPE_AUDIO									73
	/*******************************************************************************
	*��¼��ʽ�� 
	*	char[0...]	TitleName								strlen(TitleName)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_VIDEO_WND_NAME							74
	#define AVIM_FRAME_TYPE_FILEVIDEO								75
	#define AVIM_FRAME_TYPE_FILEAUDIO								76
	/*******************************************************************************
	*��¼��ʽ�� 
	*	char[0...]	TitleName								strlen(TitleName)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_FILEVIDEO_NAME							77	
//}	

//AVIMChatPlayer
//{
	/*******************************************************************************
	*��¼��ʽ�� 
	*char[0-3]		cszTime�ĳ���							sizeof(int)��4 B
	*char[3...]		cszTime									strlen(cszTime)+1 B
	*char[n-n+3]	cszUserName�ĳ���						sizeof(int)��4 B
	*char[n+3...]	cszUserName								strlen(cszUserName)+1 B
    *char[m-m+3]	cszMessage�ĳ���						sizeof(int)��4 B
	*char[m+3...]	cszMessage								strlen(cszMessage)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_CHAT_TEXT			81		//�ı���(�����ı���)
//}


//AVIMPlayer
//{
	/*******************************************************************************
	*��¼��ʽ�� 
	*char[0-3]		cszTime�ĳ���							sizeof(int)��4 B
	*char[4...]		cszTime									strlen(cszTime)+1 B
    *char[n-n+3]	cszMessage�ĳ���						sizeof(int)��4 B
	*char[n+3...]	cszMessage								strlen(cszMessage)+1 B
	********************************************************************************/
	#define AVIM_FRAME_TYPE_STATE_TEXT			91		//�ı���(״̬����)
//}

// AVC�ļ��ṹ
typedef struct tag_AVC_FILE_HEADER
{
	unsigned long		version		;		//�汾��
	unsigned long		flag		;		//��ʶ��
	char				password[16];		//����
}AVC_FILE_HEADER, *PAVC_FILE_HEADER;

// ����֡����
typedef struct tag_AVC_DATA_FRAME
{
	char				frame_type	;		//֡����
	char				key_frame	;		//�ؼ�֡
	unsigned short		sequence	;		//�Ự����
	unsigned long		session_id	;		//�Ự��ʶ
	int					channel		;		//ͨ��
	unsigned long		timestamp	;		//ʱ���
	long				data_length	;		//���ݳ���
}AVC_DATA_FRAME,*PAVC_DATA_FRAME;

// ʱ��֡
typedef struct tag_AVC_TIME_FRAME
{
	unsigned long		timestamp	;		//ʱ���
	unsigned long		position	;		//ָ������֡λ��
}AVC_TIME_FRAME,*PAVC_TIME_FRAME;


// ��������ͷ����
typedef struct tag_AVC_INDEX_HEADER
{
	char				index[4]	;		//������־:'INDX'
	char				frame_type	;		//֡����
	unsigned short		sequence	;		//�Ự����
	unsigned long		session_id	;		//�Ự��ʶ
	int					channel		;		//ͨ��
	unsigned long		start_time	;		//�����Ŀ�ʼʱ��
	unsigned long		stop_time	;		//�����Ľ���ʱ��
	long				data_length	;		//�����������ݳ���
}AVC_INDEX_HEADER, *PAVC_INDEX_HEADER;

// ��������
typedef struct tag_AVC_INDEX_DATA
{
	unsigned long		pos			;		//λ��
	unsigned long		timestamp	;		//ʱ���
	char				key_frame	;		//�Ƿ�ؼ�֡
}AVC_INDEX_DATA, *PAVC_INDEX_DATA;

#define RECOVER_EVENT_FILENOTEXIT	1
#define RECOVER_EVENT_NOTAVCFILE	2
#define RECOVER_EVENT_POSITION	3
#define RECOVER_EVENT_ANALYING	4
#define RECOVER_EVENT_RECOVERING	5
#define RECOVER_EVENT_COMPLITE	6
#define RECOVER_EVENT_NORMALAVC	7

#endif
