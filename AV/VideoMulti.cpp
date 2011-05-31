#include "StdAfx.h"
#include "VideoMulti.h"
#include "MultiAllocotar.h"

DWORD_PTR                       g_userId = 0xACDCACDC;

CVideoMulti::CVideoMulti(HWND hwnd)
{
	m_hwnd = hwnd;
	CreateDevice();
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
		hr = SetAllocatorPresenter( m_pVRM);
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

HRESULT CVideoMulti::SetAllocatorPresenter( IBaseFilter *filter)
{
	if( filter == NULL )
	{
		return E_FAIL;
	}

	HRESULT hr = S_OK;

	SmartPtr<IVMRSurfaceAllocatorNotify9> lpIVMRSurfAllocNotify;
	FAIL_RET( filter->QueryInterface(IID_IVMRSurfaceAllocatorNotify9, reinterpret_cast<void**>(&lpIVMRSurfAllocNotify)) );

	// create our surface allocator
	m_pMultiAllocator.Attach(new CMultiAllocotar(m_hwnd ,m_pD3D,m_pDirect3DDevice));
	if( FAILED( hr ) )
	{
		m_pMultiAllocator = NULL;
		return hr;
	}

	// let the allocator and the notify know about each other
	FAIL_RET( lpIVMRSurfAllocNotify->AdviseSurfaceAllocator( g_userId, m_pMultiAllocator ) );
	FAIL_RET( m_pMultiAllocator->AdviseNotify(lpIVMRSurfAllocNotify) );

	m_pMultiAllocators.push_back(m_pMultiAllocator);
	return hr;
}

HRESULT CVideoMulti::CreateDevice()
{
	HRESULT hr;

	m_pD3D = NULL;
	m_pD3D.Attach(Direct3DCreate9(D3D_SDK_VERSION));

	m_pDirect3DDevice = NULL;
	D3DDISPLAYMODE dm;

	hr = m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Windowed = TRUE;
	pp.hDeviceWindow = m_hwnd;
	pp.SwapEffect = D3DSWAPEFFECT_COPY;
	pp.BackBufferFormat = dm.Format;

	FAIL_RET( m_pD3D->CreateDevice(  D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | 
		D3DCREATE_MULTITHREADED,
		&pp,
		&m_pDirect3DDevice) );

	
	return S_OK;
}