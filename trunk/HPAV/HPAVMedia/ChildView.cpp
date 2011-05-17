
// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "HPAVMedia.h"
#include "ChildView.h"
#include "AVBase/AVDefine.h"
#include "AVBase/CamerCapture.h"
#include "AVBase/MediaCapture.h"
#include <process.h>
#include "live.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{

}

CChildView::~CChildView()
{
	
	
	if (m_pCamCaptrue)
	{
		m_pCamCaptrue->StopRecord();
		delete m_pCamCaptrue;
		m_pCamCaptrue = NULL;
	}
	if (m_pAVPalyer)
	{
		delete m_pAVPalyer;
		m_pAVPalyer = NULL;
	}
	if(m_avCap)
	{
		m_avCap->StopRecordToAVI();
	}
	_endthreadex(theadHandle);

}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_CAPTURE, &CChildView::OnCapture)
	ON_COMMAND(ID_RECORD, &CChildView::OnRecord)
	ON_COMMAND(ID_COMPOSE, &CChildView::OnCompose)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	
	// 不要为绘制消息而调用 CWnd::OnPaint()
}



void CChildView::OnCapture()
{
	
	unsigned threadId;
	theadHandle = _beginthreadex(NULL,0,ServerConnect,NULL,0,&threadId);


	VIDEC_SetScreenPos(0,440,250,400,300);
	VIDEC_SetScreenWndCount(0,2);                    //设置合成的视频位置
	VIDEC_SetScreenWndPos(0,0,0,0,200,300);
	VIDEC_SetScreenWndPos(0,1,200,0,200,300);

	
	CPlayChanEmptyHandle* playEmptyHandle = new CPlayChanEmptyHandle(); 
	m_pAVPalyer = new CAVPlayer(*playEmptyHandle); 
	m_pAVPalyer->Create(GetSafeHwnd());                  //创建player
	IMXEC_PlayChan* playChan = m_pAVPalyer->GetPlayChan();
//	playChan->SetSynFlag(1);
	CCapChanPlayHandle* capChanPlayHandle = new CCapChanPlayHandle(*playChan);
	IMXEC_CapChanCallback* capChan = new IMXEC_CapChanCallback();
	m_pCamCaptrue = new CCamerCapture(*capChanPlayHandle);       // 创建捕获摄像头对象
	m_pCamCaptrue->Create(GetSafeHwnd());
	LBVideoSet videoSet;
	videoSet.nBitrate = 768;
	videoSet.nBitrateControlType = 0;
	videoSet.nFrameRate = 30;
	videoSet.nResolution = 5;
	videoSet.nVideoCodec = 2;
	videoSet.nVideoDev = 0;
	m_pCamCaptrue->OpenVideo(&videoSet);         //打开摄像头
	/*
	int i = -1;
		i = m_pCamCaptrue->OpenAudio(-1,(X_AUDIO_CODEC_ID)X_AUDIO_CODEC_G7221_14_24);
		m_pCamCaptrue->SetVolume(100);*/
	
	IMXEC_CapChanDev *cap = m_pCamCaptrue->GetCapChanDev();
	int i = -1;
	X_AUDIO_CODEC_ID code = (X_AUDIO_CODEC_ID)X_AUDIO_CODEC_G7221_14_24;
	cap->OpenAudio(i,code);

	cap->SetVolume(10);
	cap->SetForceEncodeAudio(1);
	if (cap->IsAudioOpen(i,code))
	{
		MessageBox(_T("success"));
	}
	
	m_pCamCaptrue->SetForceEncodeVideo(1);
	m_pCamCaptrue->SetVideoWindowPos(NULL,20,20,300,200,SWP_SHOWWINDOW | SWP_NOACTIVATE);
	m_pCamCaptrue->SetScreenWnd(0,0,0);

	m_pAVPalyer->ReceiveVideo(true);      //player 从摄像头接收数据
	m_pAVPalyer->SetWindowPos(NULL, 340, 20, 300, 200, SWP_SHOWWINDOW | SWP_NOACTIVATE);
	m_pAVPalyer->SetScreenWnd(0,1,0);

	/*
	CAVPlayer* avPalyer = new CAVPlayer(*playEmptyHandle); 
		avPalyer->Create(GetSafeHwnd());
		IMXEC_PlayChan* playChan1 = avPalyer->GetPlayChan();
		CCapChanPlayHandle* capChanPlayHandle1 = new CCapChanPlayHandle(*playChan1);*/
	IMXEC_CapChanCallback* capHandle = new IMXEC_CapChanCallback();
//	CMediaCapture* avMediaCap = new CMediaCapture(*capHandle);
//	avMediaCap->Create(GetSafeHwnd());

	//打开媒体文件
//	avMediaCap->OpenMediaVideo("C:\\Wildlife.wmv",1,384,0,(VIDEC_CODEC_TYPE)10);
//	avCap->OpenVideoDev(0,0,400,300,30,384,0,(VIDEC_CODEC_TYPE)10,1, 1);
//	avMediaCap->SetVideoWindowPos(NULL,20,250,400,300,SWP_SHOWWINDOW | SWP_NOACTIVATE);
//	avMediaCap->SetForceEncodeVideo(1);
//	avMediaCap->SetScreenWnd(0,1,0);
	/*
	avPalyer->ReceiveVideo(true);
		avPalyer->SetWindowPos(NULL,440,250,400,300,SWP_SHOWWINDOW | SWP_NOACTIVATE);*/
	
	m_avCap = new CAVCapture(*capHandle);
	m_avCap->Create(GetSafeHwnd());           //打开合成视频
	m_avCap->OpenVideoDev(0,0,400,300,30,384,0,(VIDEC_CODEC_TYPE)10,1,1);
	m_avCap->SetVideoWindowPos(NULL,440,250,400,300,SWP_SHOWWINDOW | SWP_NOACTIVATE);
//	avCap->ShowVideoInputWnd();

}


void CChildView::OnRecord()
{
	m_pCamCaptrue->StartRecord();
}


void CChildView::OnCompose()
{
    m_avCap->StartRecordToAVI("C:\\comp.avi",1);
}
