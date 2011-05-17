//VIDEC_AH2KDev.h
#ifndef __VIDEC_AH2KDEV_H__
#define __VIDEC_AH2KDEV_H__

#include "VIDEC.h"

//AH2K�ɼ�Դ
class VIDEC_API VIDEC_AH2KDev
	: public VIDEC_CapDev
	, public VIDEC_StreamSource
{
public:
	VIDEC_AH2KDev(void){}
	virtual~VIDEC_AH2KDev(void){};
public:
	//���豸
	//nDevID�豸�ţ���0��ʼ
	//nWidth,ͼ����
	//nHeight,ͼ��߶�
	//nFrameRate,֡�ʣ�1-30
	//bInterlaced,�Ƿ����ɨ��
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Open(int nDevID,int nWidth,int nHeight,int nFrameRate,bool bDenoise=true)=0;
	//�ر�����
	virtual void Close(void)=0;
	//�����豸
	//nDevID�豸�ţ���0��ʼ
	//nWidth,ͼ����
	//nHeight,ͼ��߶�
	//nFrameRate,֡�ʣ�1-30
	//bInterlaced,�Ƿ����ɨ��
	//�ɹ�����0��ʧ�ܷ���-1
	virtual int Reset(int nDevID,int nWidth,int nHeight,int nFrameRate,bool bDenoise=true)=0;

	virtual int SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/)=0;
 	
	virtual int StartVideoStream(int nBitrate,int nBitrateControlType,int qmin,int qmax)=0;
	virtual int RequestKeyFrame(void)=0;
	virtual int StopVideoStream(void)=0;

	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;
 
	//�����ӿ�
	static VIDEC_AH2KDev*Create(void);

	//ȡ�豸����
	static int GetDevCount(void);
	//ȡ�豸����
	static int GetDevName(unsigned int nDevIndex,char*szName,int nMaxCount);
	static int GetDevType(unsigned int nDevIndex,VIDEC_DEV_TYPE&nDevType);
	static bool HasAudioInput(unsigned int nDevIndex);
	static bool SupportHardwareEncoding(unsigned int nDevIndex);


	//�г��ɲü��ĸ�ʽ�ĸ���
	static int GetFormatCount(void);
	//ȡ��ʽ����
	static int GetFormatName(int nIndex,char*szName,int nMaxCount);
	//ȡ��ʽ��С
	static int GetFormatSize(int nIndex,int&nWidth,int&nHeight);
	//example
	//int nCount=VIDEC_AH2KDev::GetFormatCount();
	//for (int i=0;i<nCount;i++)
	//{
	//	char szName[128];
	//	VIDEC_AH2KDev::GetFormatName(i,szName,127);
	//	int nWidth=0;
	//	int nHeight=0;
	//	VIDEC_AH2KDev::GetFormatSize(i,nWidth,nHeight);
	//}
};

#endif