#include "stdafx.h"
#include "AVCapture.h"
#include <kbase/AutoLock.h>
#include "imxec/IMXEC_MediaChannel.h"
#include <winbase.h>
#include <atlstr.h>

#include "live.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAVCapture::CAVCapture(IMXEC_CapChanCallback& capChanHandle)
	:m_capChanHandle(capChanHandle)
	,m_pCapChanDev(NULL)
	,m_nForceEncodeVideo(0)
	,m_nForceEncodeAudio(0)
	,m_pAVRecord(NULL)
{

}

CAVCapture::~CAVCapture( void )
{
	Destroy();
}


void CAVCapture::Destroy( void )
{
    if( m_pCapChanDev )
	{
		m_pCapChanDev->CloseVideoDev();
		m_pCapChanDev->CloseAudio();
		m_pCapChanDev->Close();
		delete m_pCapChanDev;
		m_pCapChanDev = NULL;
	}
}

void CAVCapture::CloseVideo( void )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->CloseVideoDev();
	}
}

int CAVCapture::OpenAudio( int nDevID, X_AUDIO_CODEC_ID CodecType )
{
	if (m_pCapChanDev == NULL)
	{
		return -1;
	}
	int nResult = m_pCapChanDev->OpenAudio(nDevID, CodecType);
	return nResult;
}

void CAVCapture::CloseAudio( void )
{
	if (m_pCapChanDev)
	{
		OutputDebugString(_T("CAVCapture::CloseAudio()\n"));
		m_pCapChanDev->CloseAudio();
	}
}

void CAVCapture::Close( void )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->CloseAudio();
		m_pCapChanDev->CloseVideoDev();
	}
}

int CAVCapture::Create( HWND hwnd,int nOnlyPreview /*= 0*/ )
{
	int nResult = -1;
	if (m_pCapChanDev)
	{
		m_pCapChanDev->Close();
		delete m_pCapChanDev;
		m_pCapChanDev = NULL;
	}

	m_pCapChanDev = IMXEC_CapChanDev::Create(m_capChanHandle);
	nResult = m_pCapChanDev->Open(hwnd,nOnlyPreview);
	return nResult;
}



bool CAVCapture::SetVideoWindowPos( HWND hWndInsertAfter,int X,int Y,int cx,int cy,UINT uFlags )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->SetWindowPos(hWndInsertAfter,X,Y,cx,cy,uFlags);
	}
	return false;
}

int CAVCapture::SetForceEncodeVideo( int nForceEncodeVideo )
{
	if (m_pCapChanDev == NULL)
	{
		return -1;
	}

	if (nForceEncodeVideo == 0)
	{
		m_nForceEncodeVideo = 0;
	}
	else
	{
		m_nForceEncodeVideo += nForceEncodeVideo;


		if (m_nForceEncodeVideo > 0)
		{
			nForceEncodeVideo = 1;
		}
		else
		{
			nForceEncodeVideo = 0;
		}
	}

	return m_pCapChanDev->SetForceEncodeVideo(nForceEncodeVideo);
}

int CAVCapture::SetForceEncodeAudio( int nForceEncodeAudio )
{
	if (m_pCapChanDev == NULL)
	{
		return -1;
	}

	if (nForceEncodeAudio == 0)
	{
		m_nForceEncodeAudio = 0;
	}
	else
	{
		m_nForceEncodeAudio += nForceEncodeAudio;
		if (m_nForceEncodeAudio > 0)
		{
			nForceEncodeAudio = 1;
		}
		else
		{
			nForceEncodeAudio = 0;
		}
	}

	return m_pCapChanDev->SetForceEncodeAudio(nForceEncodeAudio);
}

bool CAVCapture::HasVideoAdjustWnd( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->HasVideoAdjustWnd();
	}
	return false;
}

void CAVCapture::ShowAdjustVideoWnd( void )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->ShowAdjustVideoWnd(); //ÊÓÆµÊôÐÔ 
	}
}

bool CAVCapture::HasVideoInputWnd( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->HasVideoInputWnd();
	}
	return false;
}

void CAVCapture::ShowVideoInputWnd( void )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->ShowVideoInputWnd();
	}
}

HWND CAVCapture::GetVideoHWnd( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetVideoWnd();
	}
	return NULL;
}

void CAVCapture::SetInvert( int nInvert )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->SetInvert(nInvert);
	}
}

int CAVCapture::GetInvert( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetInvert();
	}
	return 0;
}

bool CAVCapture::HasVideoCapture( void )
{
	if (m_pCapChanDev)
	{
		return true;
	}
	return false;
}

void CAVCapture::SetScreenWnd( int nScreenIndex, int nWndIndex, int nFullScreen )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->SetScreenWnd(nScreenIndex, nWndIndex, nFullScreen);
	}
}

int CAVCapture::GetVideoWidth( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetVideoWidth();
	}
	return 0;
}

int CAVCapture::GetVideoHeight( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetVideoHeight();
	}
	return 0;
}

int CAVCapture::GetAudioLevel( void )
{
	int nLevel = 0;
	if (m_pCapChanDev)
	{
		m_pCapChanDev->GetLevel(nLevel);
	}
	return nLevel;
}

int CAVCapture::SetVolume( int nVolume )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->SetVolume(nVolume);
	}
	return -1;
}

int CAVCapture::GetVideoPacketStatistics( unsigned long& ulTotalPackets, unsigned long& ulLostPackets, double& AvgPacketLossRate, double& CurPacketLossRate, int& nBitrate )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetVideoPacketStatistics(ulTotalPackets, ulLostPackets, AvgPacketLossRate, CurPacketLossRate, nBitrate);
	}
	return -1;
}

int CAVCapture::GetAudioPacketStatistics( unsigned long& ulTotalPackets, unsigned long& ulLostPackets, double& AvgPacketLossRate, double& CurPacketLossRate, int& nBitrate )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetAudioPacketStatistics(ulTotalPackets, ulLostPackets, AvgPacketLossRate, CurPacketLossRate, nBitrate);
	}
	return -1;
}

unsigned long CAVCapture::GetAudioID( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetAudioID();
	}
	return 0;
}

unsigned long CAVCapture::GetVideoID( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetVideoID();
	}
	return 0;
}

bool CAVCapture::CaptureToBMPFile( const char*cszFile )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->CaptureToBMPFile(cszFile);
	}
	return false;
}

int CAVCapture::SetVideoParam( int nBrightness/*=128*/, int nContrast/*=64*/, int nSaturation/*=64*/, int nHue/*=0*/, int nGamma/*=100*/, int nSharpen/*=0*/, int iRed/*=100*/, int iGreen/*=100*/, int iBlue/*=100*/ )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->SetVideoGammaRGB(iRed, iGreen, iBlue);
		return m_pCapChanDev->SetVideoParam(nBrightness, nContrast, nSaturation, nHue, nGamma, nSharpen);
	}
	return -1;
}

void CAVCapture::SetDenoise( int nDenoise )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->SetDenoise(nDenoise);
	}
}

int CAVCapture::GetDenoise( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->GetDenoise();
	}
	return 0;
}

bool CAVCapture::IsVideoDevOpen( void )
{
	if (m_pCapChanDev)
	{
		return m_pCapChanDev->IsVideoDevOpen();
	}
	return false;
}

bool CAVCapture::IsAudioOpen(int nDevID)
{
	if (m_pCapChanDev)
	{
		X_AUDIO_CODEC_ID code = (X_AUDIO_CODEC_ID)X_AUDIO_CODEC_G7221_14_24;
		return m_pCapChanDev->IsAudioOpen(nDevID,code);
	}
	return false;
}

int CAVCapture::OpenVideoDev( int nScreenIndex,int nScreenType,int nWidth,int nHeight,int nFrameRate,int nBitrate,int nBitrateControlType,VIDEC_CODEC_TYPE CodecType,int nSub,int nQSub )
{
	int nResult = -1;
	if (m_pCapChanDev)
	{
		nResult = m_pCapChanDev->OpenVideoDev(nScreenIndex,nScreenType,nWidth,nHeight,nFrameRate,nBitrate,nBitrateControlType,CodecType,nSub,nQSub);
	}
	return nResult;
}



bool CAVCapture::StartRecordToAVI( const char*cszPathName,int nStandardFormat )
{
	int nResult = -1;
	if (m_pCapChanDev)
	{
		nResult = m_pCapChanDev->StartRecordToAVI(cszPathName, nStandardFormat);
	}
	return nResult == 0;
}

void CAVCapture::StopRecordToAVI( void )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->StopRecordToAVI();
	}
}

void CAVCapture::RequestKeyFrame( void )
{
	if (m_pCapChanDev)
	{
		m_pCapChanDev->RequestKeyFrame();
	}
}

IMXEC_CapChanDev* CAVCapture::GetCapChanDev()
{
	return m_pCapChanDev;
}


CCapChanPlayHandle::CCapChanPlayHandle( IMXEC_PlayChan& player )
	: m_player(player)
{
	/*
	m_pClientSocket = new CClientSocket(player);
		m_pClientSocket->Create();
		BOOL connected = m_pClientSocket->Connect(_T("127.0.0.1"),14000);
		if (!connected)
		{
			AfxMessageBox(_T("fail"));
		}*/
	
}

CCapChanPlayHandle::~CCapChanPlayHandle()
{
	/*
	if (m_pClientSocket)
		{
			delete m_pClientSocket;
			m_pClientSocket = NULL;
		}
		*/
		

	
}

void CCapChanPlayHandle::OnIMXEC_CapChanCallbackVideoData( unsigned char*pData,int nLen,int nKeyFrame )
{
	//m_pClientSocket->Send(pData,nLen);
	//m_player.PlayVideoData(pData,nLen);
	SetLiveData(pData,nLen);
}


