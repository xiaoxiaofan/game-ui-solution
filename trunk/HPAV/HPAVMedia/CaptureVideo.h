// CCaptureVideo视频捕捉类头文件
/////////////////////////////////////////////////////////////////////
#if !defined(AFX_CAPTUREVIDEO_H__F5345AA4_A39F_4B07_B843_3D87C4287AA0__INCLUDED_)
#define AFX_CAPTUREVIDEO_H__F5345AA4_A39F_4B07_B843_3D87C4287AA0__INCLUDED_
/////////////////////////////////////////////////////////////////////
// CaptureVideo.h : header file
/////////////////////////////////////////////////////////////////////
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <atlbase.h>
#include <windows.h>
#include <qedit.h>
#include <dshow.h>
#ifndef SAFE_RELEASE
#define SAFE_RELEASE( x )if ( NULL != x ){x->Release();x = NULL;}
#endif
class CSampleGrabberCB;
class CCaptureVideo : public CWnd 
{
	friend class CSampleGrabberCB;
public:
	void GrabOneFrame(BOOL bGrab);
	HRESULT Init(int iDeviceID,HWND hWnd);
	HRESULT ReInit(int iDeviceID, HWND hWnd);
	int EnumDevices(HWND hList);
	CCaptureVideo();
	virtual ~CCaptureVideo();
	HRESULT	CaptureImagesToAVI(CString inFileName);//捕获保存视频
private:
	IBaseFilter *pMux;//捕获视频为AVI文件

	HWND m_hWnd;
	IGraphBuilder *m_pGB;
	ICaptureGraphBuilder2* m_pCapture;
	IBaseFilter* m_pBF;
	IMediaControl* m_pMC;
	IVideoWindow* m_pVW;
	ISampleGrabber* m_pGrabber;
protected:
	void FreeMediaType(AM_MEDIA_TYPE& mt);
	bool BindFilter(int deviceId, IBaseFilter **pFilter);
	void ResizeVideoWindow();
	HRESULT SetupVideoWindow();
	HRESULT InitCaptureGraphBuilder();
};
#endif // !defined(AFX_CAPTUREVIDEO_H__F5345AA4_A39F_4B07_B843_3D87C4287AA0__INCLUDED_)
