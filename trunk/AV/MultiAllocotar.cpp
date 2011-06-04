#include "StdAfx.h"
#include "MultiAllocotar.h"


CMultiAllocotar::CMultiAllocotar(CMultiScene * scene)
	: m_refCount(1)
	, m_pScene(scene)
{
	
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	
	HWND hwnd;
	m_pScene->GetWindow(hwnd);
	D3DDISPLAYMODE dm;
    d3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Windowed = TRUE;
	pp.hDeviceWindow = hwnd;
	pp.SwapEffect = D3DSWAPEFFECT_COPY;
	pp.BackBufferFormat = dm.Format;

    d3d->CreateDevice(  D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | 
		D3DCREATE_MULTITHREADED,
		&pp,
		&device);
	m_renderTarget = NULL;

	//device->GetRenderTarget(0,&m_renderTarget);
}


CMultiAllocotar::~CMultiAllocotar(void)
{
	DeleteSurfaces();
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::InitializeDevice( /* [in] */ DWORD_PTR dwUserID, /* [in] */ VMR9AllocationInfo *lpAllocInfo, /* [out][in] */ DWORD *lpNumBuffers )
{
	D3DCAPS9 d3dcaps;
	DWORD dwWidth = 1;
	DWORD dwHeight = 1;
	float fTU = 1.f;
	float fTV = 1.f;
	
	if( lpNumBuffers == NULL )
	{
		return E_POINTER;
	}
	
	if( m_lpIVMRSurfAllocNotify == NULL )
	{
		return E_FAIL;
	}
	
	HRESULT hr = S_OK;
	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	m_pScene->Get3DDevice(&pDevice);
	pDevice->GetDeviceCaps(&d3dcaps);
	if( d3dcaps.TextureCaps & D3DPTEXTURECAPS_POW2 )
	{
		while( dwWidth < lpAllocInfo->dwWidth )
			dwWidth = dwWidth << 1;
		while( dwHeight < lpAllocInfo->dwHeight )
			dwHeight = dwHeight << 1;
	
		fTU = (float)(lpAllocInfo->dwWidth) / (float)(dwWidth);
		fTV = (float)(lpAllocInfo->dwHeight) / (float)(dwHeight);
			
		lpAllocInfo->dwWidth = dwWidth;
		lpAllocInfo->dwHeight = dwHeight;
	}
	
	lpAllocInfo->dwFlags |= VMR9AllocFlag_TextureSurface;
	
	DeleteSurfaces();
	m_surfaces.resize(*lpNumBuffers);
	
	hr = m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, & m_surfaces.at(0) );
	
	return hr;
/*

	D3DCAPS9 d3dcaps;
	DWORD dwWidth = 1;
	DWORD dwHeight = 1;
	float fTU = 1.f;
	float fTV = 1.f;

	if( lpNumBuffers == NULL )
	{
		return E_POINTER;
	}

	if( m_lpIVMRSurfAllocNotify == NULL )
	{
		return E_FAIL;
	}

	HRESULT hr = S_OK;

	device->GetDeviceCaps( &d3dcaps );
	if( d3dcaps.TextureCaps & D3DPTEXTURECAPS_POW2 )
	{
		while( dwWidth < lpAllocInfo->dwWidth )
			dwWidth = dwWidth << 1;
		while( dwHeight < lpAllocInfo->dwHeight )
			dwHeight = dwHeight << 1;

		fTU = (float)(lpAllocInfo->dwWidth) / (float)(dwWidth);
		fTV = (float)(lpAllocInfo->dwHeight) / (float)(dwHeight);
		m_sence.SetSrcRect( fTU, fTV );
		lpAllocInfo->dwWidth = dwWidth;
		lpAllocInfo->dwHeight = dwHeight;
	}

	// NOTE:
	// we need to make sure that we create textures because
	// surfaces can not be textured onto a primitive.
	lpAllocInfo->dwFlags |= VMR9AllocFlag_TextureSurface;

	DeleteSurfaces();
	m_surfaces.resize(*lpNumBuffers);
	hr = m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, & m_surfaces.at(0) );

	// If we couldn't create a texture surface and 
	// the format is not an alpha format,
	// then we probably cannot create a texture.
	// So what we need to do is create a private texture
	// and copy the decoded images onto it.
	if(FAILED(hr) && !(lpAllocInfo->dwFlags & VMR9AllocFlag_3DRenderTarget))
	{
		DeleteSurfaces();           
	}

	return m_sence.Init(device);*/

}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::TerminateDevice( /* [in] */ DWORD_PTR dwID )
{
	DeleteSurfaces();
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::GetSurface( /* [in] */ DWORD_PTR dwUserID, /* [in] */ DWORD SurfaceIndex, /* [in] */ DWORD SurfaceFlags, /* [out] */ IDirect3DSurface9 **lplpSurface )
{
	if( lplpSurface == NULL )
	{
		return E_POINTER;
	}

	if (SurfaceIndex >= m_surfaces.size() ) 
	{
		return E_FAIL;
	}

	CAutoLock Lock(&m_ObjectLock);

	*lplpSurface = m_surfaces[SurfaceIndex];
	(*lplpSurface)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::AdviseNotify( /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify )
{
	CAutoLock Lock(&m_ObjectLock);

	HRESULT hr = S_OK;

	m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;

	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	SmartPtr<IDirect3D9> p3D = NULL;
	m_pScene->Get3DDevice(&pDevice);
	pDevice->GetDirect3D(&p3D);
	pDevice->GetRenderTarget(0,&m_renderTarget);
	HMONITOR hMonitor = p3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );
	hr = m_lpIVMRSurfAllocNotify->SetD3DDevice( pDevice, hMonitor );

	return hr;

	/*
	CAutoLock Lock(&m_ObjectLock);
	
		HRESULT hr;
	
		m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;
	
		HMONITOR hMonitor = d3d->GetAdapterMonitor( D3DADAPTER_DEFAULT );
		FAIL_RET( m_lpIVMRSurfAllocNotify->SetD3DDevice( device, hMonitor ) );
		return hr;*/
	
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::StartPresenting( /* [in] */ DWORD_PTR dwUserID )
{
	CAutoLock Lock(&m_ObjectLock);
	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	m_pScene->Get3DDevice(&pDevice);
	ASSERT( pDevice );
	if( pDevice == NULL )
	{
		return E_FAIL;
	}

	return S_OK;	
	/*
	CAutoLock Lock(&m_ObjectLock);
	
		ASSERT( d3d );
		if( device == NULL )
		{
			return E_FAIL;
		}
	
		return S_OK;*/
	
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::StopPresenting( /* [in] */ DWORD_PTR dwUserID )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::PresentImage( /* [in] */ DWORD_PTR dwUserID, /* [in] */ VMR9PresentationInfo *lpPresInfo )
{
	HRESULT hr;
	CAutoLock Lock(&m_ObjectLock);
			
	if( lpPresInfo == NULL )
	{
		return E_POINTER;
	}
	else if( lpPresInfo->lpSurf == NULL )
	{
		return E_POINTER;
	}
			
	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	m_pScene->Get3DDevice(&pDevice);
			
	IDirect3DDevice9*       pSampleDevice       = NULL;
	hr = lpPresInfo->lpSurf->GetDevice( &pSampleDevice );
			
	pDevice->SetRenderTarget(0,m_renderTarget);
			
	SmartPtr<IDirect3DTexture9> texture;
	FAIL_RET( lpPresInfo->lpSurf->GetContainer( __uuidof(IDirect3DTexture9), (LPVOID*) & texture ) );    
			
    m_pScene->SetTexture(texture);
	m_pScene->DrawScene();
	//m_sence.DrawScene(device,texture);
	return hr;

	/*
	HRESULT hr;
		CAutoLock Lock(&m_ObjectLock);
	
		// if we are in the middle of the display change
		if( NeedToHandleDisplayChange() )
		{
			// NOTE: this piece of code is left as a user exercise.  
			// The D3DDevice here needs to be switched
			// to the device that is using another adapter
		}
	
		hr = PresentHelper( lpPresInfo );
	
		// IMPORTANT: device can be lost when user changes the resolution
		// or when (s)he presses Ctrl + Alt + Delete.
		// We need to restore our video memory after that
		if( hr == D3DERR_DEVICELOST)
		{
			if (device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) 
			{
				DeleteSurfaces();
				FAIL_RET( CreateDevice() );
	
				HMONITOR hMonitor = d3d->GetAdapterMonitor( D3DADAPTER_DEFAULT );
	
				FAIL_RET( m_lpIVMRSurfAllocNotify->ChangeD3DDevice( device, hMonitor ) );
	
			}
	
			hr = S_OK;
		}
	
		return hr;*/
	
}

HRESULT CMultiAllocotar::CreateDevice()
{
	HRESULT hr;
	d3d = NULL;
	D3DDISPLAYMODE dm;

	HWND hwnd;
	m_pScene->GetWindow(hwnd);
	hr = d3d->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Windowed = TRUE;
	pp.hDeviceWindow = hwnd;
	pp.SwapEffect = D3DSWAPEFFECT_COPY;
	pp.BackBufferFormat = dm.Format;

	FAIL_RET( d3d->CreateDevice(  D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | 
		D3DCREATE_MULTITHREADED,
		&pp,
		&device) );

	m_renderTarget = NULL; 
	return device->GetRenderTarget( 0, & m_renderTarget );
}

HRESULT CMultiAllocotar::PresentHelper(VMR9PresentationInfo *lpPresInfo)
{
	// parameter validation
	if( lpPresInfo == NULL )
	{
		return E_POINTER;
	}
	else if( lpPresInfo->lpSurf == NULL )
	{
		return E_POINTER;
	}

	CAutoLock Lock(&m_ObjectLock);
	HRESULT hr;

//	device->SetRenderTarget( 0, m_renderTarget );
	
	SmartPtr<IDirect3DTexture9> texture;
	FAIL_RET( lpPresInfo->lpSurf->GetContainer( __uuidof(IDirect3DTexture9), (LPVOID*) & texture ) );    
	FAIL_RET( m_sence.DrawScene(device, texture ) );
	

	FAIL_RET( device->Present( NULL, NULL, NULL, NULL ) );

	return hr;
}

bool CMultiAllocotar::NeedToHandleDisplayChange()
{
	if( ! m_lpIVMRSurfAllocNotify )
	{
		return false;
	}

	D3DDEVICE_CREATION_PARAMETERS Parameters;
	if( FAILED( device->GetCreationParameters(&Parameters) ) )
	{
		ASSERT( false );
		return false;
	}

	HMONITOR currentMonitor = d3d->GetAdapterMonitor( Parameters.AdapterOrdinal );

	HMONITOR hMonitor = d3d->GetAdapterMonitor( D3DADAPTER_DEFAULT );

	return hMonitor != currentMonitor;


}


void CMultiAllocotar::DeleteSurfaces()
{
	CAutoLock Lock(&m_ObjectLock);

	for( size_t i = 0; i < m_surfaces.size(); ++i ) 
	{
		m_surfaces[i] = NULL;
	}
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::QueryInterface( REFIID riid, void** ppvObject )
{
	HRESULT hr = E_NOINTERFACE;

	if( ppvObject == NULL ) {
		hr = E_POINTER;
	} 
	else if( riid == IID_IVMRSurfaceAllocator9 ) {
		*ppvObject = static_cast<IVMRSurfaceAllocator9*>( this );
		AddRef();
		hr = S_OK;
	} 
	else if( riid == IID_IVMRImagePresenter9 ) {
		*ppvObject = static_cast<IVMRImagePresenter9*>( this );
		AddRef();
		hr = S_OK;
	} 
	else if( riid == IID_IUnknown ) {
		*ppvObject = 
			static_cast<IUnknown*>( 
			static_cast<IVMRSurfaceAllocator9*>( this ) );
		AddRef();
		hr = S_OK;    
	}

	return hr;
}

ULONG STDMETHODCALLTYPE CMultiAllocotar::AddRef()
{
	return InterlockedIncrement(& m_refCount);
}

ULONG STDMETHODCALLTYPE CMultiAllocotar::Release()
{
	ULONG ret = InterlockedDecrement(& m_refCount);
	if( ret == 0 )
	{
		delete this;
	}

	return ret;
}

HRESULT CMultiAllocotar::Attach( IBaseFilter* pVMRFilter,D3DFORMAT format,DWORD_PTR* pdwID )
{
	if( pVMRFilter == NULL )
	{
		return E_FAIL;
	}

	HRESULT hr = S_OK;

	SmartPtr<IVMRSurfaceAllocatorNotify9> lpIVMRSurfAllocNotify;
	FAIL_RET( pVMRFilter->QueryInterface(IID_IVMRSurfaceAllocatorNotify9, reinterpret_cast<void**>(&lpIVMRSurfAllocNotify)) );

	if( FAILED( hr ) )
	{
		lpIVMRSurfAllocNotify = NULL;
		return hr;
	}
	*pdwID = (DWORD_PTR)&lpIVMRSurfAllocNotify;

	FAIL_RET( lpIVMRSurfAllocNotify->AdviseSurfaceAllocator( *pdwID,this) );
	FAIL_RET( AdviseNotify(lpIVMRSurfAllocNotify) );
}
