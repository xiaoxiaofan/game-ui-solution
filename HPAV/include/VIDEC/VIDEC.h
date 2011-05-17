//VIDEC.h
#ifndef __VIDEC_H__
#define __VIDEC_H__

#include <winsock2.h>
#include <windows.h>

#include "VIDEC_Export.h"
#include "VIDEC_CodecDef.h"

//���Ի���Ƶ�⣬������ʹ��VIDEC֮ǰ����
#define VIDEC_INIT_FLAG_AH2K					0x00000002
#define VIDEC_INIT_FLAG_AH400					0x00000004
#define VIDEC_INIT_FLAG_HARDWARE_DECODER		0x00000008	
#define VIDEC_INIT_FALG_ONLY_USB_CAMERA			0x00000010


#define VIDEC_INIT_FLAG_ALL			(VIDEC_INIT_FLAG_AH2K|VIDEC_INIT_FLAG_AH400)

VIDEC_API int VIDEC_Init(unsigned long ulFlag=VIDEC_INIT_FLAG_ALL,int nUsedByProductType=0);
//��ֹ��Ƶ�⣬������ʹ����VIDEC֮�����
VIDEC_API void VIDEC_Terminate(void);

#define VIDEC_NETWORK_INTERNET			0			//������
#define VIDEC_NETWORK_LAN				1			//������
#define VIDEC_NETWORK_PRIVATE			2			//ר��
#define VIDEC_NETWORK_SATELLITE			3			//������
#define VIDEC_NETWORK_CDMA				4			//CDMA

#define VIDEC_BITRATE_CONTROL_VBR		0			//�ɱ�����
#define VIDEC_BITRATE_CONTROL_CBR		1			//�㶨����
#define VIDEC_BITRATE_CONTROL_CQP		2			//�̶�����
#define VIDEC_BITRATE_CONTROL_QUALITY	0x80000000	//�Ƿ���������

VIDEC_API int GetBitrateControlTypeByNetworkType(int nNetworkType);
//��������ȡ����
//nQuality,ͼ��������0��64,1:128,2:256,3:384,4:512,5:768,6:1024,7:1536,8:2048,9:4096:10:6144
//szName,������Ӧ������
//nMaxCount,szName�Ĵ�С
//ʧ�ܷ���-1����ʾ��Ч����
//�ɹ�����ȡ�������Ƶĳ���
VIDEC_API int GetQualityCount(void);
VIDEC_API int GetNameByQuality(int nQuality,char*szName,int nMaxCount);

VIDEC_API int GetCodecInfo(int&nQuality,int&nBitrate,int&nQMin,int&nQMax,VIDEC_CODEC_TYPE&CodecType,bool bRTP);
VIDEC_API int GetCodecInfo(int&nQuality,int&nBitrateControlType,int&nBitrate,int&nQMin,int&nQMax,VIDEC_CODEC_TYPE&CodecType,bool bRTP);
VIDEC_API int GetCodecInfoWithBitrate(int& nBitrateControlType,int nBitrate,int&nQMin,int&nQMax,VIDEC_CODEC_TYPE&CodecType,bool bRTP);

VIDEC_API int GetFrameRateCount(void);
VIDEC_API int GetFrameRateByIndex(int nIndex);
VIDEC_API int GetFrameRateDefaultIndex(void);

class VIDEC_API VIDEC_Image
{
public:
	VIDEC_Image(void){};
	virtual~VIDEC_Image(void){};
public:
	virtual void AddRef(void)=0;
	virtual void Release(void)=0;
	virtual void*GetData(void)=0;
	virtual int GetDataLen(void)=0;
	virtual int GetWidth(void)=0;
	virtual int GetHeight(void)=0;
	virtual int GetFrameRate(void)=0;

	static VIDEC_Image*Create(unsigned char*pData,int nLen,int nWidth,int nHeight,int nFrameRate=30);
};

class VIDEC_API VIDEC_ImageSink;
class VIDEC_API VIDEC_ImageSource
{
public:
	VIDEC_ImageSource(void){};
	virtual~VIDEC_ImageSource(void){};
public:
	virtual int AddImageSink(VIDEC_ImageSink*pImageSink)=0;
	virtual void RemoveImageSink(VIDEC_ImageSink*pImageSink)=0;
};


class VIDEC_API VIDEC_ImageSink
{
public:
	VIDEC_ImageSink(void){};
	virtual~VIDEC_ImageSink(void){};
public:
	virtual void OnAttachedToImageSource(VIDEC_ImageSource*pImageSource)=0;
	virtual void OnDetachedFromImageSource(VIDEC_ImageSource*pImageSource)=0;
	//pData:IYUV��ʽ������,Y+U+V
	virtual void OnReceivedImage(VIDEC_Image*pImage)=0;
	//pResultList[i]==0,û�ж��������ڶ�
	virtual void OnReceivedMotionDetect(int*pResultList,int nResultCount){};
	virtual void OnReceivedAudioSamples(short*pSamples,int nSamples,int nSampleRate){};
};


class VIDEC_API VIDEC_StreamSink;
class VIDEC_API VIDEC_StreamSource
{
public:
	VIDEC_StreamSource(void){};
	virtual~VIDEC_StreamSource(void){};
public:
	virtual int AddStreamSink(VIDEC_StreamSink*pStreamSink)=0;
	virtual void RemoveStreamSink(VIDEC_StreamSink*pStreamSink)=0;
};

class VIDEC_API VIDEC_StreamSink
{
public:
	VIDEC_StreamSink(void){};
	virtual~VIDEC_StreamSink(void){};
public:
	virtual void OnAttachedToStreamSource(VIDEC_StreamSource*pStreamSource)=0;
	virtual void OnDetachedFromStreamSource(VIDEC_StreamSource*pStreamSource)=0;
	virtual void OnReceivedStreamData(VIDEC_StreamSource*pStreamSource,unsigned char*pData,int nLen,bool bKeyFrame=false,int nWidth=0,int nHeight=0,int nHeaderLen=0)=0;
	virtual void OnReceivedSubStreamData(VIDEC_StreamSource*pStreamSource,unsigned char*pData,int nLen,bool bKeyFrame=false,int nWidth=0,int nHeight=0,int nHeaderLen=0){};
	virtual void OnReceivedAudioStreamData(VIDEC_StreamSource*pStreamSource,unsigned char*pData,int nLen){};
};

//ȡ����ֵ��Χ
VIDEC_API int VIDEC_GetBrightessRange(int&nMin,int&nMax);
//ȡ����ֵ��ȱʡֵ
VIDEC_API int VIDEC_GetDefaultBrightness(void);

//ȡ�Աȶȷ�Χ
VIDEC_API int VIDEC_GetContrastRange(int&nMin,int&nMax);
//ȡ�Աȶȵ�ȱʡֵ
VIDEC_API int VIDEC_GetDefaultContrast(void);

//ȡ���Ͷȷ�Χ
VIDEC_API int VIDEC_GetSaturationRange(int&nMin,int&nMax);
//ȡ���Ͷȵ�ȱʡֵ
VIDEC_API int VIDEC_GetDefaultSaturation(void);

//ȡɫ����Χ
VIDEC_API int VIDEC_GetHueRange(int&nMin,int&nMax);
//ȡɫ����ȱʡֵ
VIDEC_API int VIDEC_GetDefaultHue(void);

//ȡ٤��Χ
VIDEC_API int VIDEC_GetGammaRange(int&nMin,int&nMax);
//ȡ٤���ȱʡֵ
VIDEC_API int VIDEC_GetDefaultGamma(void);

//ȡ�񻯷�Χ
VIDEC_API int VIDEC_GetSharpenRange(int&nMin,int&nMax);
//ȡ�񻯵�ȱʡֵ
VIDEC_API int VIDEC_GetDefaultSharpen(void);



#define VIDEC_OSD_ALIGN_TOP_LEFT			0	//�����Ͻ�
#define VIDEC_OSD_ALIGN_BOTOM_LEFT			1	//�����½�
#define VIDEC_OSD_ALIGN_TOP_CENTER			2	//�����м�
#define VIDEC_OSD_ALIGN_BOTTOM_CENTER		3	//�����м�
#define VIDEC_OSD_ALIGN_TOP_RIGHT			4	//�����Ͻ�
#define VIDEC_OSD_ALIGN_BOTTOM_RIGHT		5	//�����½�

class VIDEC_API VIDEC_CapDev
	: public VIDEC_ImageSource
{
public:
	VIDEC_CapDev(void){};
	virtual~VIDEC_CapDev(void){};
public:
	virtual void Close(void)=0;

	virtual void SetInvert(int nInvert)=0;
	virtual int GetInvert(void)=0;
	virtual void SetDenoise(int nDenoise)=0;
	virtual int GetDenoise(void)=0;

	//�������ڲ���������
	virtual int SetupMask(RECT *RectList, int iRectCount){return -1;};
	//ֹͣ����
	virtual int StopMask(void){return -1;};
	virtual int StartMotionDetect(void){return -1;};
	virtual int StopMotionDetect(void){return -1;};
	virtual int SetupMotionDetect(int iGrade/*�����ȵȼ�0-6*/,RECT *RectList, int iRectCount){return -1;};
 	
	//��ʾOSD
	virtual void EnableOSD(bool bEnable)=0;
	//�Ƿ���ʾOSD 
	virtual bool IsOSDEnable(void)=0;
	//����OSD 
	virtual void SetOSDText(const char*cszText,int nAlign=VIDEC_OSD_ALIGN_TOP_LEFT)=0;//Align==0 TOP_LEFT 1:BOTOM_LEFT,2:TOP_CENTER,3:BOTTOM_CENTER,4:TOP_RIGHT,5:BOTTOM_RIGHT
	//����OSD����,�ֵ���ɫ�ͱ���ɫ
	virtual void SetOSDFont(LOGFONTA logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255))=0;
};


//��Ƶ��ʾ����
class VIDEC_API VIDEC_Wnd
	: public VIDEC_ImageSink
{
public:
	VIDEC_Wnd(void){};
	virtual~VIDEC_Wnd(void){};
public:
	//����ʾ����
	//hWndParent����ʾ���ڵĸ����ھ��
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Open(HWND hWndParent,bool bLocal=false,unsigned long*lpnVidFrameTimestamp=NULL,unsigned long*lpnAudFrameTimestamp=NULL)=0;
	//�ر���ʾ����
	virtual void Close(void)=0;

	//ȡ��Ƶ���
	virtual int GetVideoWidth(void)=0;
	//ȡ��Ƶ�߶�
	virtual int GetVideoHeight(void)=0;

	//ȡ��Ƶ����
	virtual HWND GetWnd(void)=0;
	//same as CWnd::IsWindowVisible
	virtual bool IsWindowVisible(void)=0;
	//same as CWnd::SetWindowPos
	virtual bool SetWindowPos(HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT nFlags)=0; 

	//���ֵ�ǰͼ��BMP�ļ�
	virtual bool CaptureToBMPFile(const char*cszFile)=0;

	virtual double GetAverageFPS(void)=0;

	virtual void SetSynFlag(int nSynFlag)=0;

	virtual bool HasVideo(void)=0;

	static VIDEC_Wnd*Create(void);

	//������Ƶ����
	virtual int SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/)=0;
	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;
	//����ͼ����ʾģʽ
#define VIDEC_IMAGE_DISPLAY_MODE_AUTO	0
#define VIDEC_IMAGE_DISPLAY_MODE_MANUAL	1
	virtual int SetImageDisplayMode(int nMode=VIDEC_IMAGE_DISPLAY_MODE_AUTO)=0;
	virtual int GetImageDisplayMode(void)=0;

	/******************************************************************************
	* SetScreenWnd
	*����������������Ļ����λ��
	*���룺	nScreenIndex	-��Ļ��
			nWndIndex		-���ں�
			nFullScreen		-�Ƿ�ȫ����ʾ��0����ͨ��ʾ����0��ȫ����ʾ��
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void SetScreenWnd(int nScreenIndex,int nWndIndex,int nFullScreen)=0;

	virtual void EnablePreview(int nPreview)=0;
	virtual int GetSupportPreview(void)=0;
	virtual void Reset(void)=0;

	virtual VIDEC_Image*GetImage(void)=0;

	static VIDEC_Wnd*CreateLocalVideo(void);
};

class VIDEC_API VIDEC_CapChan;
class VIDEC_CapChanCallback
{
public:
	VIDEC_CapChanCallback(void){};
	virtual~VIDEC_CapChanCallback(void){};
public:
	//nSkipFlag,1:������֡��ѹ����0:ѹ����ǰ֡
	virtual void OnVIDEC_CapChanCallbackPreEncode(VIDEC_CapChan*pCapChan,int&nSkipFlag)=0;
};

//��Ƶ�ɼ�ͨ����֧��ѹ������֡�ķ�ʽ���
class VIDEC_API VIDEC_CapChan
	: public VIDEC_ImageSink
	, public VIDEC_StreamSource
{
public:
	VIDEC_CapChan(void){};
	virtual~VIDEC_CapChan(void){};
public:
	//�򿪲ɼ�ͨ��ѹ��ͨ��
	//nQuality,ͼ��������0:32,1��64,2:128,3:256,4:384,5:512,6:768,7:1024,8:1536,9:2048,10:4096:11:6144
	//CodecType����Ƶ����
	//nScaleType:�������ͣ�0:same,1:1/4,2:1/16
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Open(int nQuality,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nScaleType)=0;
	//�رղɼ�ͨ��ѹ��ͨ��
	virtual void Close(void)=0;
	//������ѹ��ͨ��
	//nQuality,ͼ��������0:32,1��64,2:128,3:256,4:384,5:512,6:768,7:1024,8:1536,9:2048,10:4096:11:6144
	//CodecType����Ƶ����
	//nScaleType:�������ͣ�0:same,1:1/4,2:1/16
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Reset(int nQuality,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nScaleType)=0;
	//����ؼ�֡
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int RequestKeyFrame(void)=0;

	static VIDEC_CapChan*Create(VIDEC_CapChanCallback&rCallback);
};

//��Ƶ����ͨ����֧�ֽ�ѹ������֡�ķ�ʽ�����
class VIDEC_API VIDEC_PlayChan
	: public VIDEC_ImageSource
	, public VIDEC_StreamSink
{
public:
	VIDEC_PlayChan(void){};
	virtual~VIDEC_PlayChan(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;
	virtual int GetAverageKBPS(void)=0;

	static VIDEC_PlayChan*Create(void);
};


//��Ƶ����ͨ��RTP��֧�ֽ�ѹ��
class VIDEC_API VIDEC_PlayChanRTP
	: public VIDEC_ImageSource
	, public VIDEC_StreamSource
{
public:
	VIDEC_PlayChanRTP(void){};
	virtual~VIDEC_PlayChanRTP(void){};
public:
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Open(int nPayloadType,VIDEC_CODEC_TYPE CodecType)=0;
	virtual void Close(void)=0;
	virtual void OnRecvdRTPPacket(unsigned char*pRTPPacketData,int nRTPPacketLen)=0;

	static VIDEC_PlayChanRTP*Create(void);
};


class VIDEC_API VIDEC_CapChanRTP;
class VIDEC_CapChanRTPCallback
{
public:
	VIDEC_CapChanRTPCallback(void){}
	virtual~VIDEC_CapChanRTPCallback(void){};
public:
	virtual void OnVIDEC_CapChanRTPCallbackPacketData(VIDEC_CapChanRTP*pCapChanRTP,const void*pPacketData,int nPacketLen)=0;
};

//��Ƶ�ɼ�ͨ��RTP��֧��ѹ��
class VIDEC_API VIDEC_CapChanRTP
	: public VIDEC_ImageSink
	, public VIDEC_StreamSource
{
public:
	VIDEC_CapChanRTP(void){};
	virtual~VIDEC_CapChanRTP(void){};
public:
	//�򿪲ɼ�ͨ��ѹ��ͨ��
	//nPayloadType:RTP�ĸ�������
	//nWidth,ͼ����
	//nHeight,ͼ��߶�
	//nFrameRate,֡�ʣ�1-30
	//nBitrate,��Ƶ������32,64,128,256,384,512,768,1024,1536,2048,4096:6144
	//CodecType����Ƶ����
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Open(int nPayloadType,int nWidth,int nHeight,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE CodecType)=0;
	//�رղɼ�ͨ��ѹ��ͨ��
	virtual void Close(void)=0;
	//����ؼ�֡
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int RequestKeyFrame(void)=0;

	static VIDEC_CapChanRTP*Create(VIDEC_CapChanRTPCallback&rCallback);
};

typedef enum VIDEC_DEV_TYPE
{
	VIDEC_DEV_SD=0,
	VIDEC_DEV_VGA,
	VIDEC_DEV_HD,
}VIDEC_DEV_TYPE;

VIDEC_API int VIDEC_GetDevCount(void);
VIDEC_API int VIDEC_GetDevName(int nDevID,char*szName,int nMaxCount);
VIDEC_API int VIDEC_GetDevType(int nDevID,VIDEC_DEV_TYPE&nDevType);
VIDEC_API void* VIDEC_GetDevHandle(int nDevID);

VIDEC_API int VIDEC_SetScreenPos(int nScreenIndex,int x,int y,int cx,int cy);
VIDEC_API int VIDEC_SetScreenWndCount(int nScreenIndex,int nWndCount);
VIDEC_API int VIDEC_SetScreenWndPos(int nScreenIndex,int nWndIndex,int x,int y,int cx,int cy);


class VIDEC_API VIDEC_MPScreen
	: public VIDEC_ImageSource
{
public:
	VIDEC_MPScreen(void){};
	virtual~VIDEC_MPScreen(void){};
public:
	virtual int Open(int nWidth,int nHeight,int nFrameRate)=0;
	virtual void Close(void)=0;
	virtual int SetScreenIndex(int nScreenIndex)=0;

	static VIDEC_MPScreen*Create(void);
};

VIDEC_API void GetBitrateRange(int nWidth,int nHeight,int&nQualityMin,int&nQualityMax);

VIDEC_API int GetSupportDXVA(void);

#endif