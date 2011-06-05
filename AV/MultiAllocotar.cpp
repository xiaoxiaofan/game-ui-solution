#include "StdAfx.h"
#include "MultiAllocotar.h"


CMultiAllocotar::CMultiAllocotar(CMultiScene * scene)
	: m_refCount(1)
	, m_pScene(scene)
{

}


CMultiAllocotar::~CMultiAllocotar(void)
{
	
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
	
	VideoSource* pSrc = NULL;
	hr = GetVideoSourceInfo(dwUserID,&pSrc);
	if (FAILED(hr)||!pSrc)
	{
		return hr;
	}

	if ( !(pSrc->m_lpIVMRSurfAllocNotify))
	{
		return E_FAIL;
	}
	
	CAutoLock Lock(&m_ObjectLock);
	pSrc->m_surfaces.resize(*lpNumBuffers);

	hr = pSrc->m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, &pSrc->m_surfaces.at(0));
	
	return hr;

}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::TerminateDevice( /* [in] */ DWORD_PTR dwID )
{
	HRESULT hr = S_OK;
	VideoSource* pSrc = NULL;
	hr = GetVideoSourceInfo(dwID,&pSrc);
	if (FAILED(hr))
	{
		return E_FAIL;
	}
	CAutoLock Lock(&m_ObjectLock);
	pSrc->DeleteSurfaces();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::GetSurface( /* [in] */ DWORD_PTR dwUserID, /* [in] */ DWORD SurfaceIndex, /* [in] */ DWORD SurfaceFlags, /* [out] */ IDirect3DSurface9 **lplpSurface )
{
	if( lplpSurface == NULL )
	{
		return E_POINTER;
	}

	HRESULT hr = S_OK;
	VideoSource* pSrc = NULL;
	hr = GetVideoSourceInfo(dwUserID,&pSrc);
	if(FAILED(hr))
	{
		return hr;
	}

	if (SurfaceIndex >= pSrc->m_surfaces.size() ) 
	{
		return E_FAIL;
	}

	CAutoLock Lock(&m_ObjectLock);

	*lplpSurface = pSrc->m_surfaces[SurfaceIndex];
	(*lplpSurface)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::AdviseNotify( /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify )
{
	return S_OK;
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
			
	SmartPtr<IDirect3DTexture9> texture = NULL;
	FAIL_RET( lpPresInfo->lpSurf->GetContainer( __uuidof(IDirect3DTexture9), (LPVOID*) & texture ) );    
			
    m_pScene->SetTexture(texture);
	m_pScene->DrawScene();

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

HRESULT CMultiAllocotar::Attach( IBaseFilter* pVMRFilter,D3DFORMAT format,DWORD_PTR* pdwID )
{
	if( pVMRFilter == NULL )
	{
		return E_FAIL;
	}

	HRESULT hr = S_OK;

	VideoSource *videoSource = new VideoSource();
	videoSource->m_dwID = (DWORD_PTR)&videoSource;

	SmartPtr<IVMRSurfaceAllocatorNotify9> lpIVMRSurfAllocNotify = NULL;

	FAIL_RET( pVMRFilter->QueryInterface(IID_IVMRSurfaceAllocatorNotify9, reinterpret_cast<void**>(&lpIVMRSurfAllocNotify)));

	*pdwID = (DWORD_PTR)&videoSource;

	FAIL_RET( lpIVMRSurfAllocNotify->AdviseSurfaceAllocator( *pdwID,this) );
	
	CAutoLock Lock(&m_ObjectLock);

	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	SmartPtr<IDirect3D9> p3D = NULL;
	m_pScene->Get3DDevice(&pDevice);
	pDevice->GetDirect3D(&p3D);

	HMONITOR hMonitor = p3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );
	hr = lpIVMRSurfAllocNotify->SetD3DDevice( pDevice, hMonitor );

	videoSource->m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;
	m_pVideoSources.push_back(videoSource);
	return hr;
}

HRESULT CMultiAllocotar::GetVideoSourceInfo( DWORD_PTR dwID,VideoSource **ppSource )
{
	if ( !dwID )
	{
		return VFW_E_NOT_FOUND;
	}
	VideoSource *pSrc = NULL;
	pSrc = reinterpret_cast<VideoSource *>(dwID);
	if( !pSrc )
	{
		return VFW_E_NOT_FOUND;
	}
	*ppSource = pSrc;

	return S_OK;
}


CMultiAllocotar::VideoSource::VideoSource()
	: m_lpIVMRSurfAllocNotify(NULL)
{

}

CMultiAllocotar::VideoSource::~VideoSource()
{

}


void CMultiAllocotar::VideoSource::DeleteSurfaces()
{
	CAutoLock Lock(&m_ObjectLock);

	for( size_t i = 0; i < m_surfaces.size(); ++i ) 
	{
		m_surfaces[i] = NULL;
	}
}

HRESULT CMultiAllocotar::VideoSource::AllocateSurfaceBuffer( DWORD dwN )
{
	return S_OK;
}


