// VedioScreen.cpp : 实现文件
//

#include "stdafx.h"
#include "Vedio.h"
#include "VedioScreen.h"


// VedioScreen

#include <WindowsX.h>
#include <Vfw.h>
#include <MMSystem.h>
#pragma comment (lib,"vfw32.lib")
#pragma comment (lib,"winmm.lib")
#include <cmath>
using namespace std;

#define  FULLSCREEN 1
#define  AREASCREEN 2
#define  WNDSCREEN  3

BOOL IsStopThread = FALSE;

IMPLEMENT_DYNAMIC(VedioScreen, CWnd)

VedioScreen::VedioScreen(CString strFilePath,CString strFileName,int nRate,CPoint Point1,CPoint Point2,int nFlag,HWND GetCurHwnd)
{
	m_strFileName = strFileName;
	m_strFilePath = strFilePath;
	m_nRate = nRate;
	m_P1 = Point1;
	m_P2 = Point2;
	opts[0]= &m_pCompressOption; 
	m_nFrames = 0;
	m_IsStop = FALSE;
	m_nFlag = nFlag;
	m_WndHwnd = GetCurHwnd;
}

VedioScreen::~VedioScreen()
{

}


BEGIN_MESSAGE_MAP(VedioScreen, CWnd)
END_MESSAGE_MAP()



// VedioScreen 消息处理程序

BOOL VedioScreen::StopVedio()
{
	/*-------------------------------------------------------------------------*/
	IsStopThread = TRUE;
	WaitForMultipleObjects(1,&ThreadFun,FALSE,INFINITE);
	if (NULL != ThreadFun)
	{
		if (NULL != pData)
		{
			delete pData;
			pData = NULL;
		}
		CloseHandle(ThreadFun);
		IsStopThread = FALSE;
		return TRUE;
	}
	/*-------------------------------------------------------------------------*/
	return TRUE;
}

DWORD WINAPI VedioScreen::VedioFun(LPVOID lp)
{
	
	CRect   crRect;
	CRect   rectWnd;
	CPoint  Point;
	HICON   phicon;

	CDC     memDC;
	CDC*    pDeskDC;
	BITMAP bitmap;
	CBitmap cbBmp;
	/*-------------------------------------------------------------------------*/

	AVISTREAMINFO  m_StrHdr;                 //定义一个avi 流信息结构体
	PAVIFILE       m_pFile;                  //定义一个avi 流文件
	PAVISTREAM     m_ps;                     //定义一个avi流
	PAVISTREAM     m_pComStream;             //定义一个avi流
	HRESULT        m_hr;
	AVICOMPRESSOPTIONS  m_pCompressOption;
	AVICOMPRESSOPTIONS FAR * opts[1]; 
	opts[0]= &m_pCompressOption;
	AVIFileInit(); //初始化AVI格式流媒体

	/*-------------------------------------------------------------------------*/

	PVedioData lpVedio = (PVedioData)lp;

	/*-------------------------------------------------------------------------*/
	int nX1Start;
	int nY1End;
	int nX2Start;
	int nY2End;

	/*-------------------------------------------------------------------------*/

	if ( NULL == lpVedio->WndHwnd )
	{
		nX1Start  = lpVedio -> p1.x;
		nY1End    = lpVedio -> p1.y;
		nX2Start  = lpVedio -> p2.x - lpVedio -> p1.x + 3;
		nY2End    = lpVedio -> p2.y - lpVedio -> p1.y + 3;
	}else
	{
		if (::GetWindowRect(lpVedio->WndHwnd,&rectWnd))
		{
			nX1Start = rectWnd.left;
			nY1End   = rectWnd.top;
			nX2Start = rectWnd.right - rectWnd.left;
			nY2End   = rectWnd.bottom - rectWnd.top;
		}
	}
	/*-------------------------------------------------------------------------*/
	switch (lpVedio->nFlag)
	{
	case FULLSCREEN:
		{
			pDeskDC = GetDesktopWindow()->GetDC();
			GetDesktopWindow()->GetClientRect(crRect);
			memDC.CreateCompatibleDC(pDeskDC);
			cbBmp.CreateCompatibleBitmap(pDeskDC,crRect.Width(),crRect.Height());
			memDC.SelectObject(&cbBmp);
			cbBmp.GetBitmap(&bitmap);
		}
		break;
	case AREASCREEN:
		{
			/*-------------------------------------------------------------------------*/

			//初始化位图信息
			pDeskDC = GetDesktopWindow()->GetDC();
			memDC.CreateCompatibleDC(pDeskDC);
			cbBmp.CreateCompatibleBitmap(pDeskDC,nX2Start,nY2End);
			memDC.SelectObject(&cbBmp);
			cbBmp.GetBitmap(&bitmap);

			/*-------------------------------------------------------------------------*/
		}
		break;
	case WNDSCREEN:
		{
			//初始化位图信息
			pDeskDC = GetDesktopWindow()->GetDC();
			memDC.CreateCompatibleDC(pDeskDC);
			cbBmp.CreateCompatibleBitmap(pDeskDC,nX2Start,nY2End);
			memDC.SelectObject(&cbBmp);
			cbBmp.GetBitmap(&bitmap);
		}
		break;
	default:
		break;
	}

	/*-------------------------------------------------------------------------*/

	while (1)
	{
		/*-------------------------------------------------------------------------*/

		switch (lpVedio->nFlag)
		{
		case FULLSCREEN:
			{
				memDC.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,pDeskDC,0,0,SRCCOPY);
			}
			break;
		case AREASCREEN:
			{
				memDC.BitBlt(0,0,nX2Start,nY2End,pDeskDC,nX1Start,nY1End,SRCCOPY);
			}
			break;
		case WNDSCREEN:
			{
				memDC.BitBlt(0,0,nX2Start,nY2End,pDeskDC,nX1Start,nY1End,SRCCOPY);
			}
			break;
		default:
			break;
		}
		/*-------------------------------------------------------------------------*/

		GetCursorPos(&Point);
		phicon = (HICON)GetCursor();
		memDC.DrawIcon(Point,phicon);

		/*-------------------------------------------------------------------------*/

		DWORD dwSize = bitmap.bmWidthBytes*bitmap.bmHeight;
		BYTE* lpData = new BYTE[dwSize];
		int nPanelSize  = 0;									//记录调色板大小
		if(bitmap.bmBitsPixel<16)							//判断是否为真彩色位图
		{
			nPanelSize = (int)pow((double)2,(double)bitmap.bmBitsPixel*sizeof(RGBQUAD));
		}

		/*-------------------------------------------------------------------------*/

		BITMAPINFOHEADER *pBInfo = new BITMAPINFOHEADER;
		pBInfo->biBitCount       = bitmap.bmBitsPixel;
		pBInfo->biClrImportant   = 0;
		pBInfo->biCompression    = 0;
		pBInfo->biHeight         = bitmap.bmHeight;
		pBInfo->biPlanes         = bitmap.bmPlanes;
		pBInfo->biSize           = sizeof(BITMAPINFOHEADER);
		pBInfo->biSizeImage      = bitmap.bmWidthBytes*bitmap.bmHeight;
		pBInfo->biWidth          = bitmap.bmWidth;
		pBInfo->biXPelsPerMeter  = 0;
		pBInfo->biYPelsPerMeter  = 0;
		BITMAPINFO bInfo;
		bInfo.bmiHeader = *pBInfo;
		GetDIBits(memDC.m_hDC,cbBmp,0,pBInfo->biHeight,lpData,&bInfo,DIB_RGB_COLORS);

		/*-------------------------------------------------------------------------*/

		if (lpVedio->nFrames == 0)
		{
			if(lpVedio->strFilePath.Right(1) != "\\")
			{
				lpVedio->strFilePath = lpVedio->strFilePath + "\\";
			}
			AVIFileOpen(&m_pFile,lpVedio->strFilePath+lpVedio->strFileName+_T(".avi"),OF_WRITE|OF_CREATE,NULL);
			memset(&m_StrHdr, 0, sizeof(m_StrHdr));
			m_StrHdr.fccType    = streamtypeVIDEO;
			m_StrHdr.fccHandler = 0;
			m_StrHdr.dwScale    = 1;
			m_StrHdr.dwRate     = lpVedio->nRate;
			m_StrHdr.dwSuggestedBufferSize = pBInfo->biSizeImage;
			SetRect(&m_StrHdr.rcFrame,0,0,pBInfo->biWidth,pBInfo->biHeight);
			m_hr= AVIFileCreateStream(m_pFile,&m_ps,&m_StrHdr);

			//设置压缩格式
			opts[0]->fccType = streamtypeVIDEO;
			opts[0]->fccHandler = mmioStringToFOURCC("MSVC", 0);
			opts[0]->dwQuality = 7500;
			opts[0]->dwBytesPerSecond = 0;
			opts[0]->dwFlags = AVICOMPRESSF_VALID || AVICOMPRESSF_KEYFRAMES;
			opts[0]->lpFormat = 0;
			opts[0]->cbFormat = 0;
			opts[0]->dwInterleaveEvery = 0;
			m_hr=AVIMakeCompressedStream(&m_pComStream,m_ps,&m_pCompressOption,NULL); 
			m_hr=AVIStreamSetFormat(m_pComStream,0,pBInfo,sizeof(BITMAPINFOHEADER));
		}
		m_hr= AVIStreamWrite(m_pComStream,lpVedio->nFrames ,1,(LPBYTE)lpData,
			pBInfo->biSizeImage,AVIIF_KEYFRAME,NULL,NULL);
		lpVedio->nFrames++;

		delete []lpData;
		delete pBInfo ;

		/*-------------------------------------------------------------------------*/

		if (IsStopThread == TRUE)
		{	
			AVIStreamClose(m_pComStream);
			AVIStreamClose(m_ps);
			if (NULL != m_pFile)
			{
				AVIFileRelease(m_pFile);
			}
			AVIFileExit();
			lpVedio->nFrames = 0;
			::MessageBox(NULL,_T("关闭文件成功"),_T("关闭提示"),MB_OK);
			break;
		}
		Sleep(100);

	}
	ExitThread(GetCurrentThreadId());
	return 0;
}
void VedioScreen::StartVedio()
{
	pData = new VedioData;
	pData->strFilePath = m_strFilePath;
	pData->strFileName = m_strFileName;
	pData->nFrames = m_nFrames;
	pData->nRate = m_nRate;
	pData->p1 = m_P1;
	pData->p2 = m_P2;
	pData->nFlag = m_nFlag;
	pData->WndHwnd = m_WndHwnd;

	ThreadFun = CreateThread(NULL,0,VedioFun,pData,0,0);
	if (NULL == ThreadFun )
	{
		MessageBox(_T("线程创建失败"));
		ExitProcess(0);
	} 
}


void VedioScreen::PauseVedio()
{
	SuspendThread(ThreadFun); //挂起线程的执行
}


void VedioScreen::UnPauseVedio()
{
	ResumeThread(ThreadFun); //恢复线程的执行
}
