//IMXEC_MediaChannel.h
#ifndef __IMXEC_MEDIACHANNEL_H__
#define __IMXEC_MEDIACHANNEL_H__

#include <IMXEC/IMXEC_Export.h>
#include <IMXEC/IMXEC_Call.h>
#include <VIDEC/VIDEC.h>
#include <AUDEC/AUDEC_CodecID.h>
#include <NETEC/NETEC.h>

class IMXEC_CapChanCallback
{
public:
	IMXEC_CapChanCallback(void){};
	virtual~IMXEC_CapChanCallback(void){};
public:
	//��Ƶ���ݻص�����
	virtual void OnIMXEC_CapChanCallbackAudioData(unsigned char*pData,int nLen,bool&bLoop){};
	virtual void OnIMXEC_CapChanCallbackAudioSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp){};
	//��Ƶ���ݻص�����
	//nKeyFrame,0:�ǹؼ�֡ 1:�ؼ�֡
	virtual void OnIMXEC_CapChanCallbackVideoData(unsigned char*pData,int nLen,int nKeyFrame){};
	virtual void OnIMXEC_CapChanCallbackMotionDetected(int*pResultList,int nResultCount){};//pResultList[i]==0,û�ж��������ڶ�

	virtual void OnIMXEC_CapChanCallbackFilePositionChanged(unsigned long ulSeconds){};
	virtual void OnIMXEC_CapChanCallbackFilePause(void){};
	virtual void OnIMXEC_CapChanCallbackFilePlay(void){};
	virtual void OnIMXEC_CapChanCallbackFileEnd(void){};
	virtual void OnIMXEC_CapChanCallbackRecvdCtrlData(void*pData,int nLen){};

	virtual void OnIMXEC_CapChanCallbackAudioIDChanged(unsigned long nAudioID){};
	virtual void OnIMXEC_CapChanCallbackVideoDevOpen(void){};
};

class IMXEC_API IMXEC_CapChanDev
{
public:
	IMXEC_CapChanDev(void){};
	virtual~IMXEC_CapChanDev(void){};
public:
	//��ͨ��
	virtual int Open(HWND hwndParent,int nOnlyPreview)=0;
	//�ر�ͨ��
	virtual void Close(void)=0;

	virtual void EnablePreview(int nPreview)=0;

	//ȡ��Ƶ����
	virtual HWND GetVideoWnd(void)=0;
	//ȡ��Ƶ���
	virtual int GetVideoWidth(void)=0;
	//ȡ��Ƶ�߶�
	virtual int GetVideoHeight(void)=0;

	//same as CWnd::IsWindowVisible
	virtual bool IsWindowVisible(void)=0;
	//same as CWnd::SetWindowPos
	virtual bool SetWindowPos(HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT nFlags)=0; 
	//���ֵ�ǰͼ��BMP�ļ�
	virtual bool CaptureToBMPFile(const char*cszFile)=0;


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

	//��������
	virtual int SetVolume(int nVolume)=0;
	//ȡ��ǰ��ֵ
	virtual int GetLevel(int&nLevel)=0;

	virtual unsigned long GetAudioID(void)=0;
	virtual unsigned long GetVideoID(void)=0;

	//����Ƶ�豸
	virtual int OpenVideoDev(int nDevID,int nWidth,int nHeight,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub=0,int nQSub=0)=0;
	virtual int OpenVideoDev(int x,int y,int cx,int cy,int nBitCount,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub=0,int nQSub=0)=0;
	virtual int OpenVideoDev(const char*cszMediaFile,int nLoop,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub=0,int nQSub=0)=0;
	//nScreenType[0:������Ƶ���,1:��Ļģ�������ϣ�����+Զ��+�װ�+�����ĵ���]
	virtual int OpenVideoDev(int nScreenIndex,int nScreenType,int nWidth,int nHeight,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub,int nQSub)=0;
	virtual int OpenVideoDev(const char*cszServerIP,const char*cszIPCameraType,const char*cszUserID,const char*cszPassword,int nWidth,int nHeight,int nFrameRate,int nBitrate,int nBitrateControlType,int nSub,int nQSub)=0;

	/******************************************************************************
	* IsVideoDevOpen
	*��������ȡ�Ƿ��Ѿ�����Ƶ�豸
	*���룺��
	*�����	��
	*����ֵ��Ϊtrueʱ�Ѿ�����Ƶ�豸������û�д�
	*****************************************************************************/
	virtual bool IsVideoDevOpen(void)=0;

	//�ر���Ƶ�豸
	virtual void CloseVideoDev(void)=0;
 	
	/******************************************************************************
	* SetForceEncodeVideo
	*�����������Ƿ�ǿ��ѹ����Ƶ��¼��ʱ���߱��ػ��ز���ʱ������Ϊ��0������ʱ��������Ϊ0���Խ�ʡ��Դ��
	*���룺nForceEncodeVideo	-�Ƿ�ǿ��ѹ����Ƶ��0:���˽��յ�ʱ��ѹ����Ƶ,��0���κ�ʱ��ѹ����Ƶ��
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int SetForceEncodeVideo(int nForceEncodeVideo)=0;

	/******************************************************************************
	* RequestKeyFrame
	*����������ؼ�֡
	*���룺��
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void RequestKeyFrame(void)=0;

	virtual void SetInvert(int nInvert)=0;
	virtual int GetInvert(void)=0;
	virtual void SetDenoise(int nDenoise)=0;
	virtual int GetDenoise(void)=0;

	//�������ڲ���������
	virtual int SetupMask(RECT *RectList, int iRectCount)=0;
	//ֹͣ����
	virtual int StopMask(void)=0;
	virtual int StartMotionDetect(void)=0;
	virtual int StopMotionDetect(void)=0;
	virtual int SetupMotionDetect(int iGrade/*�����ȵȼ�0-6*/,RECT *RectList, int iRectCount)=0;
	virtual bool GetMotionImageSize(int&nWidth,int&nHeight)=0;
 	
	/******************************************************************************
	* EnableOSD
	*�����������Ƿ���ʾOSD
	*���룺	bEnable			-�Ƿ���ʾOSD,Ϊtrueʱ��ʾ��������ʾ
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void EnableOSD(bool bEnable)=0;

	/******************************************************************************
	* IsOSDEnable
	*��������ȡ�Ƿ���ʾOSD
	*���룺��
	*�������
	*����ֵ��Ϊtrueʱ��ʾ��������ʾ
	*****************************************************************************/
	virtual bool IsOSDEnable(void)=0;

	/******************************************************************************
	* SetOSDText
	*����������OSD���ı�
	*���룺	cszText			-Ҫ��ʾ���ı�
			nAlign			-���뷽ʽ���ο�VIDEC.h�е�VIDEC_OSD_ALIGN_TOP_LEFT�Ķ���
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void SetOSDText(const char*cszText,int nAlign=VIDEC_OSD_ALIGN_TOP_LEFT)=0;//Align==0 TOP_LEFT 1:BOTOM_LEFT,2:TOP_CENTER,3:BOTTOM_CENTER,4:TOP_RIGHT,5:BOTTOM_RIGHT

	/******************************************************************************
	* SetOSDFont
	*����������OSD������
	*���룺	logfont			-OSD������
			crText			-OSD���ı�����ɫ
			crBk			-OSD���ı��ı�����ɫ
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void SetOSDFont(LOGFONTA logfont,COLORREF crText=RGB(0,0,255),COLORREF crBk=RGB(255,255,255))=0;
	//������Ƶ����
	virtual int SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/,bool bSharpenLocalOnly=true)=0;
	
	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;
	
	virtual bool HasVideoAdjustWnd(void)=0;
	virtual void ShowAdjustVideoWnd(void)=0;
	virtual void ShowVideoInputWnd(void)=0;
	virtual bool HasVideoInputWnd(void)=0;
	virtual int TVTunerPutChannel(long lChannel)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*��������ȡ��Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
			nBitrate			-������bps��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetVideoPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	//����Ƶͨ��
	//nDevID:��Ƶ�ɼ��豸�ţ�-2�Ӳɼ����вɼ���Ƶ��>=-1�������вɼ���Ƶ
	//CodecType:��������
	virtual int OpenAudio(int nDevID,X_AUDIO_CODEC_ID CodecType)=0;

	/******************************************************************************
	* IsAudioOpen
	*��������ȡ�Ƿ��Ѿ�����Ƶ
	*���룺��
	*�����	nDevID		-��Ƶ�ɼ��豸�ţ�-2�Ӳɼ����вɼ���Ƶ��>=-1�������вɼ���Ƶ
			CodecType	-��������
	*����ֵ��Ϊtrueʱ�Ѿ�����Ƶ������û�д�
	*****************************************************************************/
	virtual bool IsAudioOpen(int&nDevID,X_AUDIO_CODEC_ID&CodecType)=0;

	//�ر���Ƶͨ��
	virtual void CloseAudio(void)=0;
 	
	/******************************************************************************
	* SetForceEncodeAudio
	*�����������Ƿ�ǿ��ѹ����Ƶ��¼��ʱ���߱��ػ��ز���ʱ������Ϊ��0������ʱ��������Ϊ0���Խ�ʡ��Դ��
	*���룺nForceEncodeAudio	-�Ƿ�ǿ��ѹ����Ƶ��0:���˽��յ�ʱ��ѹ����Ƶ,��0���κ�ʱ��ѹ����Ƶ��
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int SetForceEncodeAudio(int nForceEncodeAudio)=0;

	/******************************************************************************
	* GetAudioPacketStatistics
	*��������ȡ��Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
			nBitrate			-������bps��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetAudioPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	virtual unsigned long GetDuration(void)=0;
	virtual unsigned long GetPosition(void)=0;
	virtual void Seek(unsigned long ulSeconds)=0;
	virtual void Pause(void)=0;
	virtual void Play(void)=0;
	virtual void SetMute(bool bMute=true)=0;

	/******************************************************************************
	* StartRecordToAVI
	*��������ʼ����¼��
	*���룺	cszPathName			-¼���ļ�����
			nStandardFormat		-�Ƿ�¼�Ƴɱ�׼�ļ���ʽ
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int StartRecordToAVI(const char*cszPathName,int nStandardFormat=1)=0;
	
	/******************************************************************************
	* StopRecordToAVI
	*������ֹͣ����¼��
	*���룺��
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void StopRecordToAVI(void)=0;

	/******************************************************************************
	* SendPTZ
	*����������PTZ��������̨�������
	*���룺	nPTZAction		-��̨����
			nSpeed			-�������ٶ�
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int SendPTZ (PTZ_ACTION nPTZAction,int nSpeed)=0;

	virtual VIDEC_Image*GetImage(void)=0;

	static IMXEC_CapChanDev*Create(IMXEC_CapChanCallback&rCallback);

	//ȡ�豸����
	static int GetDevCount(void);
	//ȡ�豸����
	static int GetDevName(int nDevID,char*szName,int nMaxCount);
	
	//ȡ�豸����
	static int GetDevType(int nDevID,VIDEC_DEV_TYPE&nDevType);

	//�г���ʽ�ĸ���
	static int GetFormatCount(VIDEC_DEV_TYPE nDevType);
	//ȡ��ʽ����
	static int GetFormatName(VIDEC_DEV_TYPE nDevType,int nIndex,char*szName,int nMaxCount);
	//ȡ��ʽ��С
	static int GetFormatSize(VIDEC_DEV_TYPE nDevType,int nIndex,int&nWidth,int&nHeight);
	//�ж���Ƶ�豸�Ƿ�����Ƶ����
	static bool HasAudioInput(int nDevID);

	static void EnableAudioSend(bool bEnable);
	static bool IsEnableAudioSend(void);
	static void EnableVideoSend(bool bEnable);
	static bool IsEnableVideoSend(void);

	static unsigned long GetTotalBytes(void);
	static int GetBitrate(void);
	static void ClearTotalBytes(void);
};


class IMXEC_PlayChanCallback
{
public:
	IMXEC_PlayChanCallback(void){};
	virtual~IMXEC_PlayChanCallback(void){};
public:
	//��Ƶ���ݻص�����
	virtual void OnIMXEC_PlayChanCallbackAudChanData(unsigned char*pData,int nLen,bool&bLoop)=0;
	virtual void OnIMXEC_PlayChanCallbackAudioSamples(const short*pSamples,int nSamples,int nSampleRate,int nTimestamp)=0;
	//��Ƶ���ݻص�����
	//nKeyFrame,0:�ǹؼ�֡ 1:�ؼ�֡
	virtual void OnIMXEC_PlayChanCallbackVidChanData(unsigned char*pData,int nLen,int nKeyFrame,int& nFlagDontDecode)=0;

	virtual void OnIMXEC_PlayChanCallbackRemoteSnapJPG(const char*cszPathName){};
};

class IMXEC_API IMXEC_PlayChan
{
public:
	IMXEC_PlayChan(void){};
	virtual~IMXEC_PlayChan(void){};
public:
	virtual int Open(HWND hwndParent,unsigned long nAudChanID,unsigned long nVidChanID,const char*cszPeerNodeID,const char*cszPeerNATIP,unsigned short nPeerNATPort,const char*cszPeerLocalIP,unsigned short nPeerLocalPort,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort,int nForceUseMCU=0)=0;

	/******************************************************************************
	* Open
	*�������򿪱��ز���
	*���룺	hwndParent		-��Ƶ�����ھ��
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int Open(HWND hwndParent)=0;

	virtual void Close(void)=0;

	//ȡ��Ƶ����
	virtual HWND GetVideoWnd(void)=0;
	//ȡ��Ƶ���
	virtual int GetVideoWidth(void)=0;
	//ȡ��Ƶ�߶�
	virtual int GetVideoHeight(void)=0;

	//same as CWnd::IsWindowVisible
	virtual bool IsWindowVisible(void)=0;
	//same as CWnd::SetWindowPos
	virtual bool SetWindowPos(HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT nFlags)=0; 
	//���ֵ�ǰͼ��BMP�ļ�
	virtual bool CaptureToBMPFile(const char*cszFile)=0;

	//������Ƶ����
	virtual int SetVideoParam(int nBrightness=128/*����ֵ0-255*/, int nContrast=64/*�Աȶ�0-127*/, int nSaturation=64/*���Ͷ�0-127*/, int nHue=0/*ɫ��0-255*/,int nGamma=100/*٤��1-400*/,int nSharpen=0/*��0-127*/)=0;

	//int nGammaR[1-400 100]
	//int nGammaG[1-400 100]
	//int nGammaB[1-400 100]
	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;

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

	virtual int SetVolume(int nVolume)=0;
	virtual int GetLevel(int&nLevel)=0;

	virtual int StartAudio(void)=0;
	virtual int EnableAudio(int nEnable/*0:�����գ�1:����*/)=0;
	virtual int SetAudioID(unsigned long nAudioID)=0;
	virtual int StopAudio(void)=0;
	virtual int StartVideo(void)=0;
	virtual int EnableVideo(int nEnable/*0:�����գ�1:����*/)=0;
	virtual int StopVideo(void)=0;
	virtual int SetAudioCast(bool bAudioCast)=0;
	virtual int SetVideoCast(bool bVideoCast)=0;

	/******************************************************************************
	* RequestKeyFrame
	*����������ؼ�֡
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int RequestKeyFrame(void)=0;

	/******************************************************************************
	* SetFrameRateControlMode
	*����������֡�ʿ���ģʽ
	*���룺	nMode			-֡�ʿ���ģʽ
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int SetFrameRateControlMode(FRAME_RATE_CONTROL_MODE nMode)=0;

	/******************************************************************************
	* SetFrameTypeControlMode
	*����������֡���Ϳ���ģʽ
	*���룺	nMode			-֡���Ϳ���ģʽ
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int SetFrameTypeControlMode(FRAME_TYPE_CONTROL_MODE nMode)=0;

	/******************************************************************************
	* GetAudioPacketStatistics
	*��������ȡ��Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
			nBitrate			-������bps��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetAudioPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	/******************************************************************************
	* GetVideoPacketStatistics
	*��������ȡ��Ƶ�İ���ͳ������
	*���룺	��
	*����� ulTotalPackets		-�ܹ������˶��ٸ���
			ulLostPackets		-�ܹ������˶��ٸ���
			AvgPacketLossRate	-ƽ��������
			CurPacketLossRate	-��ǰ������
			nBitrate			-������bps��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int GetVideoPacketStatistics(unsigned long&ulTotalPackets,unsigned long&ulLostPackets,double&AvgPacketLossRate,double&CurPacketLossRate,int&nBitrate)=0;

	/******************************************************************************
	* PlayAudioData
	*������������Ƶ����
	*���룺	pData			-����ָ��
			nLen			-���ݳ���
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int PlayAudioData(const void*pData,int nLen)=0;

	/******************************************************************************
	* PlayVideoData
	*������������Ƶ����
	*���룺	pData			-����ָ��
			nLen			-���ݳ���
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int PlayVideoData(const void*pData,int nLen)=0;

	/******************************************************************************
	* StartRecordToAVI
	*��������ʼ����¼��
	*���룺	cszPathName			-¼���ļ�����
			nStandardFormat		-�Ƿ�¼�Ƴɱ�׼�ļ���ʽ
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int StartRecordToAVI(const char*cszPathName,int nStandardFormat=1)=0;
	
	/******************************************************************************
	* StopRecordToAVI
	*������ֹͣ����¼��
	*���룺��
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void StopRecordToAVI(void)=0;

	/******************************************************************************
	* SendCtrlData
	*���������Ϳ�������
	*���룺	pData			-��������
			nLen			-�������ݳ���
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void SendCtrlData(void*pData,int nLen)=0;

	/******************************************************************************
	* SetSynFlag
	*������������Ƶ��Ƶͬ�����
	*���룺	nSynFlag		-��Ƶ��Ƶͬ����ǡ�0����Ƶ��Ƶ��ͬ������0����Ƶ��Ƶͬ����
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void SetSynFlag(int nSynFlag)=0;

	virtual void SetImage(VIDEC_Image*pImage)=0;


	static IMXEC_PlayChan*Create(IMXEC_PlayChanCallback&rCallback);

	static unsigned long GetTotalBytes(void);
	static int GetBitrate(void);
	static void ClearTotalBytes(void);
	static void SetForcibleReceiving(bool bForcible);
	static bool GetForcibleReceiving(void);
};

#endif
