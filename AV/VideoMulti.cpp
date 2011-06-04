#include "StdAfx.h"
#include "VideoMulti.h"


CVideoMulti::CVideoMulti(HWND hwnd)
{
	m_hwnd = hwnd;
	m_pSence = new CMultiScene();
	m_pSence->CreateDevice(hwnd);
	m_pMultiAllocotar = new CMultiAllocotar(m_pSence);
}


CVideoMulti::~CVideoMulti(void)
{
}



HRESULT CVideoMulti::AddMultiFileSource()
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
		DWORD_PTR userId;
		hr = m_pMultiAllocotar->Attach(m_pVRM,D3DFMT_A8R8G8B8,&userId);
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

