#include "stdafx.h"
#include "AVPlayer.h"
#include <kbase/AutoLock.h>
#include <KRTL32/Func.h>
#include <kbase/Utils.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CAVPlayer::CAVPlayer(IMXEC_PlayChanCallback& playChanHandle)
	: m_pPlayChan(NULL)
	, m_playChanHandle(playChanHandle)
	, m_bRecvVideo(false) 
{

}

CAVPlayer::~CAVPlayer(void)
{
	Close();
}

void CAVPlayer::Close()
{
	if (m_pPlayChan)
	{
		m_pPlayChan->Close();
		delete m_pPlayChan;
		m_pPlayChan = NULL;
	}
}

int CAVPlayer::Open(unsigned long nAudChanID,unsigned long nVidChanID,std::string strPeerNodeID,std::string strPeerNATIP,
					  std::string strPeerLocalIP,unsigned short nPeerLocalPort,std::string strPeerMCUID,std::string strPeerMCUIP,unsigned short nPeerMCUPort,int nForceUseMCU)
{
	return 0;
}

int CAVPlayer::Create( HWND hwnd )
{
	m_Hwnd = hwnd;
	int nResult = -1;
	if (m_pPlayChan)
	{
		m_pPlayChan->Close();
		delete m_pPlayChan;
		m_pPlayChan = NULL;
	}

	m_pPlayChan = IMXEC_PlayChan::Create(m_playChanHandle);
	nResult = m_pPlayChan->Open(hwnd);
	return nResult;
}

IMXEC_PlayChan* CAVPlayer::GetPlayChan()
{
	return m_pPlayChan;
}

HWND CAVPlayer::GetVideoHwnd( void )
{
	return m_Hwnd;
}

void CAVPlayer::ReceiveAudio( bool bRecv /*= true*/ )
{

}

void CAVPlayer::ReceiveVideo( bool bRecv /*= true*/ )
{
	if (m_pPlayChan)
	{
		m_bRecvVideo = bRecv;
		m_pPlayChan->EnableVideo(bRecv);
		if (bRecv)
		{
			m_pPlayChan->StartVideo();
		}
	}
}

void CAVPlayer::SetWindowPos( HWND hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags )
{
	if (m_pPlayChan)
	{
		m_pPlayChan->SetWindowPos(hWndInsertAfter,X,Y,cx,cy,uFlags);
	}
}

void CAVPlayer::SetScreenWnd( int nScreenIndex, int nWndIndex, int nFullScreen )
{
	if (m_pPlayChan)
	{
		m_pPlayChan->SetScreenWnd(nScreenIndex, nWndIndex, nFullScreen);
	}
}


