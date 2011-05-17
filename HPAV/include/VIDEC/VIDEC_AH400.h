//VIDEC_AH400.h
#ifndef __VIDEC_AH400_H__
#define __VIDEC_AH400_H__

#include "VIDEC.h"

class VIDEC_AH400Callback
{
public:
	VIDEC_AH400Callback(void){};
	virtual~VIDEC_AH400Callback(void){};
public:
	virtual void OnVIDEC_AH400CallbackImage(VIDEC_Image*pImage)=0;
	virtual void OnVIDEC_AH400CallbackVideoStreamData(unsigned char*pData,int nLen,int nKeyFrame,int nWidth,int nHeight)=0;
	virtual void OnVIDEC_AH400CallbackVideoSubStreamData(unsigned char*pData,int nLen,int nKeyFrame,int nWidth,int nHeight)=0;
	virtual void OnVIDEC_AH400CallbackAudioStreamData(unsigned char*pData,int nLen)=0;
	virtual void OnVIDEC_AH400CallbackMotionDetected(int*pResultList,int nResultCount)=0;//pResultList[i]==0,û�ж��������ڶ�
};

class VIDEC_AH400
{
public:
	VIDEC_AH400(void){};
	virtual~VIDEC_AH400(void){};
public:
	virtual void Close(void)=0;
	//nSubScaleType:��С������,0:SameSize 1:1/4 2:1/8
	virtual int StartVideoStream(int nBitrate,int nQuant,int qmin,int qmax,int nKeyFrameInterval,bool bEnableSub=false,int nSubScaleType=1,int nSubBitrate=0,int nSubQuant=0,int nSubQMin=0,int nSubQMax=0)=0;
	virtual int StopVideoStream(void)=0;
	virtual int RequestKeyFrame(void)=0;
	virtual int RequestSubKeyFrame(void)=0;

	//�������ڲ���������
	virtual int SetupMask(RECT *RectList, int iRectCount)=0;
	//ֹͣ����
	virtual int StopMask(void)=0;

	virtual void EnableOSD(bool bEnable)=0;
	virtual void SetOSDText(void)=0;

	virtual int StartMotionDetect(void)=0;
	virtual int StopMotionDetect(void)=0;
	virtual int SetupMotionDetect(int iGrade/*�����ȵȼ�0-6*/,RECT *RectList, int iRectCount)=0;

	virtual int SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/)=0;
 
	static int Init(void);
	static void Terminate(void);

	static int GetDevCount(void);
	static int GetDevName(int nDevID,char*szName,int nMaxCount);
	static void*GetDevHandle(int nDevID);

	static VIDEC_AH400*Create(VIDEC_AH400Callback&rCallback,int nDevID,int nWidth,int nHeight,int nFrameRate,bool bAutoFrameRate);
};


#endif