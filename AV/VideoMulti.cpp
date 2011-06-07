#include "StdAfx.h"
#include "VideoMulti.h"
#include <dshowutil.h>


CVideoMulti::CVideoMulti(HWND hwnd)
{
	m_hwnd = hwnd;
	m_pSence = new CMultiScene();
	m_pSence->CreateDevice(hwnd);
	StartRenderThread();
}


CVideoMulti::~CVideoMulti(void)
{
}



HRESULT CVideoMulti::AddMultiFileSource(DWORD_PTR& userId,LPRECT pRect)
{
	SmartPtr<IVMRFilterConfig9> filterConfig;

	BSTR path = GetMoviePath();
	if( ! path )
	{
		return E_FAIL;
	}

	HRESULT hr = S_OK;

	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC, IID_IGraphBuilder, (void**)&m_pGraph);

	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void**)&m_pVRM);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pVRM->QueryInterface(IID_IVMRFilterConfig9, reinterpret_cast<void**>(&filterConfig));
	}

	if (SUCCEEDED(hr))
	{
		hr = filterConfig->SetRenderingMode( VMR9Mode_Renderless );

	}

	if (SUCCEEDED(hr))
	{
		hr = filterConfig->SetNumberOfStreams(2);

	}

	if (SUCCEEDED(hr))
	{
		hr = m_pSence->AddVideoSource(m_pVRM,userId);
		m_pVSIDs.push_back(userId);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pGraph->AddFilter(m_pVRM, L"Video Mixing Renderer 9");
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pGraph->QueryInterface(IID_IMediaControl, reinterpret_cast<void**>(&m_pMediaControl));
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pGraph->RenderFile( path, NULL );
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pMediaControl->Run();
	}

	SysFreeString(path);
	//SaveGraphFile(m_pGraph,L"C:\\VideoMulti.grf");
	return hr;
}


BSTR CVideoMulti::GetMoviePath()
{
	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	TCHAR  szBuffer[MAX_PATH];
	szBuffer[0] = NULL;

	static const TCHAR szFilter[]  
	= TEXT("Video Files (.ASF, .AVI, .MPG, .MPEG, .VOB, .QT, .WMV)\0*.ASF;*.AVI;*.MPG;*.MPEG;*.VOB;*.QT;*.WMV\0") \
		TEXT("All Files (*.*)\0*.*\0\0");
	ofn.lStructSize         = sizeof(OPENFILENAME);
	ofn.hwndOwner           = NULL;
	ofn.hInstance           = NULL;
	ofn.lpstrFilter         = szFilter;
	ofn.nFilterIndex        = 1;
	ofn.lpstrCustomFilter   = NULL;
	ofn.nMaxCustFilter      = 0;
	ofn.lpstrFile           = szBuffer;
	ofn.nMaxFile            = MAX_PATH;
	ofn.lpstrFileTitle      = NULL;
	ofn.nMaxFileTitle       = 0;
	ofn.lpstrInitialDir     = NULL;
	ofn.lpstrTitle          = TEXT("Select a video file to play...");
	ofn.Flags               = OFN_HIDEREADONLY;
	ofn.nFileOffset         = 0;
	ofn.nFileExtension      = 0;
	ofn.lpstrDefExt         = TEXT("AVI");
	ofn.lCustData           = 0L;
	ofn.lpfnHook            = NULL;
	ofn.lpTemplateName  = NULL; 

	if (GetOpenFileName (&ofn))  // user specified a file
	{
		return SysAllocString( szBuffer );
	}

	return NULL;
}

void CVideoMulti::StartRenderThread()
{
	HANDLE hThread = NULL;
	DWORD tid = NULL;
	hThread = CreateThread( NULL,
		NULL,
		RenderThreadProc_, 
		this, 
		NULL, 
		&tid);

}

DWORD WINAPI CVideoMulti::RenderThreadProc_( LPVOID lpParameter )
{
	CVideoMulti* This = (CVideoMulti*)lpParameter;
	while(true)
	{
		This->m_pSence->DrawScene();
		Sleep(1);
	}
}

void CVideoMulti::SetPosition( DWORD_PTR dwID,int x,int y,int cx,int cy )
{
	m_pSence->SetPosition(dwID,x,y,cx,cy);
}

