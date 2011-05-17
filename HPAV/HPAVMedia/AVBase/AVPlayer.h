#pragma once
#include <imxec/IMXEC_MediaChannel.h>
#include <kbase/CritSec.h>
#include <netec/NETEC.h>


class CAVPlayer
{
public:
	CAVPlayer(IMXEC_PlayChanCallback& playChanHandle);
	~CAVPlayer(void);

	int Create(HWND hwnd);

	void Close();

	int Open(unsigned long nAudChanID,unsigned long nVidChanID,std::string strPeerNodeID,std::string strPeerNATIP,
		std::string strPeerLocalIP,unsigned short nPeerLocalPort,std::string strPeerMCUID,std::string strPeerMCUIP,unsigned short nPeerMCUPort,int nForceUseMCU=0);


	HWND GetVideoHwnd(void);
	void SetWindowPos(HWND hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags);

    virtual void ReceiveAudio(bool bRecv = true);
	virtual void ReceiveVideo(bool bRecv = true);
	virtual void SetScreenWnd(int nScreenIndex, int nWndIndex, int nFullScreen);

	IMXEC_PlayChan*             GetPlayChan();


	

private:
	IMXEC_PlayChan*					m_pPlayChan;
	IMXEC_PlayChanCallback&			m_playChanHandle;
	HWND							m_Hwnd;
	bool							m_bRecvVideo;
};
