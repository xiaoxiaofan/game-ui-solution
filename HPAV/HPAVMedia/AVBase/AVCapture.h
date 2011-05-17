#pragma once
#include <imxec/IMXEC_MediaChannel.h>
#include <kbase/CritSec.h>
#include <audec/AUDEC_CodecID.h>
#include "AVRecord.h"
#include "AVLocalNotify.h"
#include "../ClientSocket.h"

class CAVCapture 
	: public CAVLocalNotify
	, public CAVRecordNotify
{
public:
	CAVCapture(IMXEC_CapChanCallback& capChanHandle);
	~CAVCapture(void);
	
	int Create(HWND hwnd,int nOnlyPreview = 0);
	void Destroy(void);
	
	int OpenVideoDev(int nScreenIndex,int nScreenType,int nWidth,int nHeight,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub,int nQSub);
	//����Ƶͨ��
	//nDevID:��Ƶ�ɼ��豸�ţ�-2�Ӳɼ����вɼ���Ƶ��>=-1�������вɼ���Ƶ
	//CodecType:��������
	int OpenAudio(int nDevID, X_AUDIO_CODEC_ID CodecType);
	//�ر���Ƶͨ��
	void CloseVideo(void);
	//�ر���Ƶͨ��
	void CloseAudio(void);
	void Close(void);

public:
	//�̳���CAVLocalNotify
	virtual bool HasVideoAdjustWnd(void);
	virtual void ShowAdjustVideoWnd(void);
	virtual bool HasVideoInputWnd(void);
	virtual void ShowVideoInputWnd(void);
	virtual HWND GetVideoHWnd(void);

	virtual void SetInvert(int nInvert);
	virtual int  GetInvert(void);

	virtual bool HasVideoCapture(void);
	virtual void SetScreenWnd(int nScreenIndex, int nWndIndex, int nFullScreen);
	virtual int  GetVideoWidth(void);
	virtual int  GetVideoHeight(void);
	virtual int  SetForceEncodeAudio(int nForceEncodeAudio);
	virtual int  SetForceEncodeVideo(int nForceEncodeVideo);
	virtual bool SetVideoWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags);
	
	virtual int  SetVolume(int nVolume);
	virtual int  GetAudioLevel(void);
	virtual int  GetVideoPacketStatistics(unsigned long& ulTotalPackets, unsigned long& ulLostPackets, double& AvgPacketLossRate, double& CurPacketLossRate, int& nBitrate);
	virtual int  GetAudioPacketStatistics(unsigned long& ulTotalPackets, unsigned long& ulLostPackets, double& AvgPacketLossRate, double& CurPacketLossRate, int& nBitrate);

	virtual unsigned long GetAudioID(void);
	virtual unsigned long GetVideoID(void);

	virtual bool CaptureToBMPFile(const char*cszFile);
	virtual int  SetVideoParam(int nBrightness=128, int nContrast=64, int nSaturation=64, int nHue=0, int nGamma=100, int nSharpen=0, int iRed=100, int iGreen=100, int iBlue=100);

	//ͼ��ȥ��
	virtual void SetDenoise(int nDenoise);
	virtual	int  GetDenoise(void);

	virtual bool IsVideoDevOpen(void);
	virtual	bool IsAudioOpen(int nDevID);


	virtual bool StartRecordToAVI(const char*cszPathName,int nStandardFormat);
	virtual void StopRecordToAVI(void);
	virtual void RequestKeyFrame(void);


	IMXEC_CapChanDev*                GetCapChanDev();
protected:
	IMXEC_CapChanDev*	             m_pCapChanDev;
	IMXEC_CapChanCallback&           m_capChanHandle; 
	CAVRecord*						 m_pAVRecord;		
	KCritSec			             m_csAVRecord;
	int							     m_nVideoWidth;
	int								 m_nVideoHeight;
	int								 m_nForceEncodeVideo;
	int							     m_nForceEncodeAudio;
	int					             m_nFrameRate;
	int					             m_nBitrate;
	int					             m_nBitrateControlType;
	VIDEC_CODEC_TYPE	             m_VideoCodecType;
	int					             m_nSub;
	int					             m_nQSub;

private:
	
};

class CCapChanPlayHandle : public IMXEC_CapChanCallback
{
public:
	CCapChanPlayHandle(IMXEC_PlayChan& player);
	~CCapChanPlayHandle();

	//��Ƶ���ݻص�����
	virtual void OnIMXEC_CapChanCallbackAudioData(unsigned char*pData,int nLen,bool&bLoop){};
	virtual void OnIMXEC_CapChanCallbackAudioSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp){};
	//��Ƶ���ݻص�����
	//nKeyFrame,0:�ǹؼ�֡ 1:�ؼ�֡
	virtual void OnIMXEC_CapChanCallbackVideoData(unsigned char*pData,int nLen,int nKeyFrame);

private:
	 //CClientSocket*      m_pClientSocket;    
	IMXEC_PlayChan&     m_player; 
};



class CPlayChanEmptyHandle : public IMXEC_PlayChanCallback
{
public:
	CPlayChanEmptyHandle(){};
	~CPlayChanEmptyHandle(){};

	//��Ƶ���ݻص�����
	virtual void OnIMXEC_PlayChanCallbackAudChanData(unsigned char*pData,int nLen,bool&bLoop){};
	virtual void OnIMXEC_PlayChanCallbackAudioSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp){};
	//��Ƶ���ݻص�����
	//nKeyFrame,0:�ǹؼ�֡ 1:�ؼ�֡
	virtual void OnIMXEC_PlayChanCallbackVidChanData(unsigned char*pData,int nLen,int nKeyFrame,int& nFlagDontDecode){};

	virtual void OnIMXEC_PlayChanCallbackRemoteSnapJPG(const char*cszPathName){};
};