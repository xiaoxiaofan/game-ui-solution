#include "StdAfx.h"
#include "MultiAllocotar.h"


CMultiAllocotar::CMultiAllocotar(CMultiScene& scene)
	: m_refCount(1)
	, m_scene(scene)
{

}


CMultiAllocotar::~CMultiAllocotar(void)
{
	
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::InitializeDevice( /* [in] */ DWORD_PTR dwUserID, /* [in] */ VMR9AllocationInfo *lpAllocInfo, /* [out][in] */ DWORD *lpNumBuffers )
{
	if( lpNumBuffers == NULL )
	{
		return E_POINTER;
	}
	
	HRESULT hr = S_OK;
	
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

	pSrc->DeleteSurfaces();
	pSrc->m_surfaces.resize(*lpNumBuffers);

	hr = pSrc->m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, &pSrc->m_surfaces.at(0));

	//DeleteSurfaces();
	//m_surfaces.resize(*lpNumBuffers);
//	hr = pSrc->m_lpIVMRSurfAllocNotify->AllocateSurfaceHelper(lpAllocInfo, lpNumBuffers, &m_surfaces.at(0));

	D3DCAPS9 d3dcaps;
	DWORD dwWidth = 1;
	DWORD dwHeight = 1;
	float fTU = 1.f;
	float fTV = 1.f;

	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	m_scene.Get3DDevice(&pDevice);

	ZeroMemory( &d3dcaps, sizeof(D3DCAPS9));
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

	hr = pDevice->CreateTexture(dwWidth,                // width
		dwHeight,                                      // height
		1,                                            // levels
		D3DUSAGE_RENDERTARGET,                       //D3DUSAGE_DYNAMIC,//D3DUSAGE_RENDERTARGET,// usage
		lpAllocInfo->Format,                                     // format
		D3DPOOL_DEFAULT  ,                         // we are not going to get into surface bits, so we do not need managed
		&(pSrc->m_pTexture),
		NULL);

    SmartPtr<IDirect3DSurface9> pSurface = NULL;
	hr = pSrc->m_pTexture->GetSurfaceLevel(0,&pSurface);

	hr = pDevice->ColorFill(pSurface,NULL,D3DCOLOR_ARGB(0x00,0x00,0x00,0x00));

	m_scene.AddVideoID(dwUserID);
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::TerminateDevice( /* [in] */ DWORD_PTR dwID )
{
	
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

	/*
	if (SurfaceIndex >= m_surfaces.size() ) 
		{
			return E_FAIL;
		}*/
	

	CAutoLock Lock(&m_ObjectLock);

	*lplpSurface = pSrc->m_surfaces[SurfaceIndex];
	(*lplpSurface)->AddRef();

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::AdviseNotify( /* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify )
{
	CAutoLock Lock(&m_ObjectLock);

	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	SmartPtr<IDirect3D9> p3D = NULL;
	m_scene.Get3DDevice(&pDevice);
	pDevice->GetDirect3D(&p3D);

	HMONITOR hMonitor = p3D->GetAdapterMonitor( D3DADAPTER_DEFAULT );
	lpIVMRSurfAllocNotify->SetD3DDevice( pDevice, hMonitor );

	return S_OK;
}

HRESULT STDMETHODCALLTYPE CMultiAllocotar::StartPresenting( /* [in] */ DWORD_PTR dwUserID )
{
	CAutoLock Lock(&m_ObjectLock);
	SmartPtr<IDirect3DDevice9> pDevice = NULL;
	m_scene.Get3DDevice(&pDevice);
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
			
	//SmartPtr<IDirect3DDevice9> pDevice = NULL;
	//m_scene.Get3DDevice(&pDevice);

	//SmartPtr<IDirect3DTexture9> texture = NULL;
	//FAIL_RET( lpPresInfo->lpSurf->GetContainer( __uuidof(IDirect3DTexture9), (LPVOID*) & texture ) );    
			
    //m_scene.SetTexture(texture);
	//m_pScene->DrawScene();

	VideoSource* pSrc = NULL;

	hr = GetVideoSourceInfo(dwUserID,&pSrc);

	SmartPtr<IDirect3DDevice9>       pSampleDevice       = NULL;
	SmartPtr<IDirect3DSurface9>      pTexturePrivSurf    = NULL;

	hr = lpPresInfo->lpSurf->GetDevice(&pSampleDevice);
	hr = pSrc->m_pTexture->GetSurfaceLevel(0,&pTexturePrivSurf);

	hr = pSampleDevice->StretchRect(lpPresInfo->lpSurf, 
		0, 
		pTexturePrivSurf,
		0,
		D3DTEXF_NONE);

	m_scene.SetTexture(pSrc->m_pTexture);
	//m_scene.DrawScene();
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

HRESULT CMultiAllocotar::Attach( IBaseFilter* pVMRFilter,D3DFORMAT format,DWORD_PTR& pdwID )
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

	pdwID = (DWORD_PTR)videoSource;

	//*pdwID = (DWORD_PTR)&lpIVMRSurfAllocNotify;
	FAIL_RET( lpIVMRSurfAllocNotify->AdviseSurfaceAllocator( pdwID,this) );
	
	
	FAIL_RET( AdviseNotify(lpIVMRSurfAllocNotify) );


	videoSource->m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;

	
	m_pVideoSources.push_back(videoSource);

	//videoSource->m_lpIVMRSurfAllocNotify = lpIVMRSurfAllocNotify;
	//m_pVideoSources.push_back(videoSource);
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




void CMultiAllocotar::GetTexture( DWORD_PTR videoId,IDirect3DTexture9 **ppTexture )
{
	/*
	std::list<VideoSource>::iterator begin,it,end;
		begin = m_pVideoSources.begin();
		end = m_pVideoSources.end();*/
	
	HRESULT hr = S_OK;
	VideoSource* pSrc = NULL;
	hr = GetVideoSourceInfo(videoId,&pSrc);

	*ppTexture = pSrc->m_pTexture;

}


HRESULT CMultiAllocotar::SetRect(DWORD_PTR dwID,NORMALIZEDRECT & newnrect)
{
	 HRESULT hr = S_OK;

	 VideoSource* pSrc = NULL;
	 hr = GetVideoSourceInfo(dwID,&pSrc);

	 if (FAILED(hr))
	 {
		 return hr;
	 }

    // coordinates in composition space [-1,1]x[1,-1]
    float cl; // left
    float ct; // top
    float cr; // right
    float cb; // bottom

    memcpy( (void*)(&pSrc->m_rect), (const void*)(&newnrect), sizeof(NORMALIZEDRECT));

    // update composition space coordinates
    // comp_space_x = 2. * norm_space_x - 1.;
    // comp_space_x = 1. - 2. * norm_space_y;
    cl = 2.f * newnrect.left - 1.f;
    cr = 2.f * newnrect.right - 1.f;
    ct = 1.f - 2.f * newnrect.top;
    cb = 1.f - 2.f * newnrect.bottom;

	/*cl = m_nrDst.left ;
    cr = m_nrDst.right ;
    ct = m_nrDst.top;
    cb = m_nrDst.bottom;*/

    pSrc->m_vertices[0].position.x = cl;
    pSrc->m_vertices[0].position.y = ct;
    pSrc->m_vertices[0].position.z = 0.0f; 

    pSrc->m_vertices[1].position.x = cl;
    pSrc->m_vertices[1].position.y = cb;
    pSrc->m_vertices[1].position.z = 0.0f; 

    pSrc->m_vertices[2].position.x = cr;
    pSrc->m_vertices[2].position.y = ct;
    pSrc->m_vertices[2].position.z = 0.0f;

    pSrc->m_vertices[3].position.x = cr;
    pSrc->m_vertices[3].position.y = cb;
    pSrc->m_vertices[3].position.z = 0.0f;

    return S_OK;
}


