#include "StdAfx.h"
#include "MultiAllocotar.h"


CMultiAllocotar::CMultiAllocotar(HRESULT& hr, HWND wnd, IDirect3D9* d3d, IDirect3DDevice9* d3dd)
	: m_refCount(1)
	, m_D3D(d3d)
	, m_D3DDev(d3dd)
	, m_window(wnd)
{
	CAutoLock Lock(&m_ObjectLock);
	hr = E_FAIL;

	if( IsWindow( wnd ) == FALSE )
	{
		hr = E_INVALIDARG;
		return;
	}

	if( m_D3D == NULL )
	{
		//ASSERT( d3dd ==  NULL ); 

		m_D3D.Attach( Direct3DCreate9(D3D_SDK_VERSION) );
		if (m_D3D == NULL) {
			hr = E_FAIL;
			return;
		}
	}

	if( m_D3DDev == NULL )
	{
		hr = CreateDevice();
	}
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

	m_D3DDev->GetDeviceCaps( &d3dcaps );
	if( d3dcaps.TextureCaps & D3DPTEXTURECAPS_POW2 )
	{
		while( dwWidth < lpAllocInfo->dwWidth )
			dwWidth = dwWidth << 1;
		while( dwHeight < lpAllocInfo->dwHeight )
			dwHeight = dwHeight << 1;

		fTU = (float)(lpAllocInfo->dwWidth) / (float)(dwWidth);
		fTV = (float)(lpAllocInfo->dwHeight) / (float)(dwHeight);
		m_scene.SetSrcRect( fTU, fTV );
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

		// is surface YUV ?
		if (lpAllocInfo->Format > '0000') 
		{           
			D3DDISPLAYMODE dm; 
			m_D3DDev->GetDisplayMode(NULL,  & dm );

			// create the private texture
			m_D3DDev->CreateTexture(lpAllocInfo->dwWidth, lpAllocInfo->dwHeight,
				1, 
				D3DUSAGE_RENDERTARGET, 
				dm.Format, 
				D3DPOOL_DEFAULT /* default pool - usually video memory */, 
				& m_privateTexture, NULL );
		}


		lpAllocInfo->dwFlags &= ~VMR9AllocFlag_TextureSurface;
		lpAllocInfo->dwFlags |= VMR9AllocFlag_OffscreenSurface;

		m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, & m_surfaces.at(0));
	}

	return m_scene.Init(m_D3DDev);
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

	HRESULT hr;

	m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;

	HMONITOR hMonitor = m_D3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );
	m_lpIVMRSurfAllocNotify->SetD3DDevice( m_D3DDev, hMonitor );

	return hr;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::StartPresenting( /* [in] */ DWORD_PTR dwUserID )
{
	CAutoLock Lock(&m_ObjectLock);

	ASSERT( m_D3DDev );
	if( m_D3DDev == NULL )
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::StopPresenting( /* [in] */ DWORD_PTR dwUserID )
{
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::PresentImage( /* [in] */ DWORD_PTR dwUserID, /* [in] */ VMR9PresentationInfo *lpPresInfo )
{
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
		if (m_D3DDev->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) 
		{
			DeleteSurfaces();
			CreateDevice();

			HMONITOR hMonitor = m_D3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );

			m_lpIVMRSurfAllocNotify->ChangeD3DDevice( m_D3DDev, hMonitor ) ;

		}

		hr = S_OK;
	}

	return hr;
}

HRESULT CMultiAllocotar::CreateDevice()
{
	HRESULT hr;
	m_D3DDev = NULL;
	D3DDISPLAYMODE dm;

	hr = m_D3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Windowed = TRUE;
	pp.hDeviceWindow = m_window;
	pp.SwapEffect = D3DSWAPEFFECT_COPY;
	pp.BackBufferFormat = dm.Format;

	FAIL_RET( m_D3D->CreateDevice(  D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_window,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | 
		D3DCREATE_MULTITHREADED,
		&pp,
		&m_D3DDev) );

	m_renderTarget = NULL; 
	return m_D3DDev->GetRenderTarget( 0, & m_renderTarget );
}

void CMultiAllocotar::DeleteSurfaces()
{
	CAutoLock Lock(&m_ObjectLock);

	// clear out the private texture
	m_privateTexture = NULL;

	for( size_t i = 0; i < m_surfaces.size(); ++i ) 
	{
		m_surfaces[i] = NULL;
	}
}

bool CMultiAllocotar::NeedToHandleDisplayChange()
{
	if( ! m_lpIVMRSurfAllocNotify )
	{
		return false;
	}

	D3DDEVICE_CREATION_PARAMETERS Parameters;
	if( FAILED( m_D3DDev->GetCreationParameters(&Parameters) ) )
	{
		ASSERT( false );
		return false;
	}

	HMONITOR currentMonitor = m_D3D->GetAdapterMonitor( Parameters.AdapterOrdinal );

	HMONITOR hMonitor = m_D3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );

	return hMonitor != currentMonitor;

}

HRESULT CMultiAllocotar::PresentHelper( VMR9PresentationInfo *lpPresInfo )
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

	m_D3DDev->SetRenderTarget( 0, m_renderTarget );
	// if we created a  private texture
	// blt the decoded image onto the texture.
	if( m_privateTexture != NULL )
	{   
		SmartPtr<IDirect3DSurface9> surface;
		FAIL_RET( m_privateTexture->GetSurfaceLevel( 0 , & surface ) );

		// copy the full surface onto the texture's surface
		FAIL_RET( m_D3DDev->StretchRect( lpPresInfo->lpSurf, NULL,
			surface, NULL,
			D3DTEXF_NONE ) );

		FAIL_RET( m_scene.DrawScene(m_D3DDev, m_privateTexture ) );
	}
	else // this is the case where we have got the textures allocated by VMR
		// all we need to do is to get them from the surface
	{
		SmartPtr<IDirect3DTexture9> texture;
		FAIL_RET( lpPresInfo->lpSurf->GetContainer( __uuidof(IDirect3DTexture9), (LPVOID*) & texture ) );    
		FAIL_RET( m_scene.DrawScene(m_D3DDev, texture ) );
	}

	FAIL_RET( m_D3DDev->Present( NULL, NULL, NULL, NULL ) );
	return hr;
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
