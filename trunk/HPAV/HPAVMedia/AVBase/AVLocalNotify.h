#pragma once
class CAVLocalNotify
{
public:
	CAVLocalNotify(void){};
	virtual ~CAVLocalNotify(void){};

	virtual bool HasVideoAdjustWnd(void) = 0;
	virtual void ShowAdjustVideoWnd(void) = 0;
	virtual bool HasVideoInputWnd(void) = 0;
	virtual void ShowVideoInputWnd(void) = 0;
	virtual HWND GetVideoHWnd(void) = 0;

	virtual void SetInvert(int nInvert) = 0;
	virtual int  GetInvert(void) = 0;

	virtual bool SetVideoWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags) = 0;

	virtual bool HasVideoCapture(void) = 0;
	virtual void SetScreenWnd(int nScreenIndex, int nWndIndex, int nFullScreen) = 0;
	virtual int  GetVideoWidth(void) = 0;
	virtual int  GetVideoHeight(void) = 0;
	virtual int  SetForceEncodeAudio(int nForceEncodeAudio) = 0;
	virtual int  SetForceEncodeVideo(int nForceEncodeVideo) = 0;
	virtual int  SetVolume(int nVolume) = 0;
	virtual int  GetAudioLevel(void) = 0;
	virtual int  GetVideoPacketStatistics(unsigned long& ulTotalPackets, unsigned long& ulLostPackets, double& AvgPacketLossRate, double& CurPacketLossRate, int& nBitrate) = 0;
	virtual int  GetAudioPacketStatistics(unsigned long& ulTotalPackets, unsigned long& ulLostPackets, double& AvgPacketLossRate, double& CurPacketLossRate, int& nBitrate) = 0;

	virtual unsigned long GetAudioID(void) = 0;
	virtual unsigned long GetVideoID(void) = 0;

	virtual bool CaptureToBMPFile(const char*cszFile) = 0;
	virtual int  SetVideoParam(int nBrightness=128, int nContrast=64, int nSaturation=64, int nHue=0, int nGamma=100, int nSharpen=0, int iRed=100, int iGreen=100, int iBlue=100) = 0;

	//ÕºœÒ»•‘Î
 	virtual void SetDenoise(int nDenoise) = 0;
	virtual	int  GetDenoise(void) = 0;
	
	virtual bool IsVideoDevOpen(void) = 0;
	virtual	bool IsAudioOpen(int nDevID) = 0;
};


class CMediaLocalNotify
{
public:
	CMediaLocalNotify(void){};
	virtual ~CMediaLocalNotify(void){};

	virtual HWND GetVideoHWnd(void) = 0;
	virtual int GetVideoWidth(void) = 0;
	virtual int GetVideoHeight(void) = 0;
	
	virtual void SetScreenWnd(int nScreenIndex, int nWndIndex, int nFullScreen) = 0;
	virtual int SetVolume(int nVolume)=0;
	virtual int GetAudioLevel(void) = 0;

	virtual unsigned long GetDuration(void)=0;
	virtual unsigned long GetPosition(void)=0;

	virtual void Seek(unsigned long ulSeconds)=0;
	virtual void Pause(void)=0;
	virtual void Play(void)=0;
	virtual void SetMute(bool bMute=true)=0;
};