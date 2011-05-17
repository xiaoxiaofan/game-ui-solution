//VIDEC_AH400Dev.h
#ifndef __VIDEC_AH400DEV_H__
#define __VIDEC_AH400DEV_H__

#include "VIDEC.h"



//AH400�ɼ�Դ
class VIDEC_API VIDEC_AH400Dev
	: public VIDEC_CapDev
	, public VIDEC_StreamSource
{
public:
	VIDEC_AH400Dev(void){}
	virtual~VIDEC_AH400Dev(void){};
public:
	//���豸
	//nDevID�豸�ţ���0��ʼ
	//nWidth,ͼ����
	//nHeight,ͼ��߶�
	//nFrameRate,֡�ʣ�1-30
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Open(int nDevID,int nWidth,int nHeight,int nFrameRate)=0;
	//�ر�����
	virtual void Close(void)=0;
	//�����豸
	//nDevID�豸�ţ���0��ʼ
	//nWidth,ͼ����
	//nHeight,ͼ��߶�
	//nFrameRate,֡�ʣ�1-30
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Reset(int nDevID,int nWidth,int nHeight,int nFrameRate)=0;

	virtual int StartVideoStream(int nBitrate,int nQuant,int qmin,int qmax,int nKeyFrameInterval,bool bEnableSub=false,int nSubScaleType=1,int nSubBitrate=0,int nSubQuant=0,int nSubQMin=0,int nSubQMax=0)=0;
	virtual int StopVideoStream(void)=0;
	virtual int RequestKeyFrame(void)=0;
	virtual int RequestSubKeyFrame(void)=0;

	virtual int SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/)=0;
 
	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;

	//�����ӿ�
	static VIDEC_AH400Dev*Create(void);

	//ȡ�豸����
	static int GetDevCount(void);
	//ȡ�豸����
	static int GetDevName(unsigned int nDevIndex,char*szName,int nMaxCount);


	//�г��ɲü��ĸ�ʽ�ĸ���
	static int GetFormatCount(void);
	//ȡ��ʽ����
	static int GetFormatName(int nIndex,char*szName,int nMaxCount);
	//ȡ��ʽ��С
	static int GetFormatSize(int nIndex,int&nWidth,int&nHeight);
	//example
	//int nCount=VIDEC_AH400Dev::GetFormatCount();
	//for (int i=0;i<nCount;i++)
	//{
	//	char szName[128];
	//	VIDEC_AH400Dev::GetFormatName(i,szName,127);
	//	int nWidth=0;
	//	int nHeight=0;
	//	VIDEC_AH400Dev::GetFormatSize(i,nWidth,nHeight);
	//}
};


#endif
