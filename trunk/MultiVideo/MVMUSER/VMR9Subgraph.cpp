//------------------------------------------------------------------------------
// File: VMR9Subgraph.cpp
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "VMR9Subgraph.h"
#include "d3dx9tex.h"

HRESULT SaveGraphFile(IGraphBuilder *pGraph, WCHAR *wszPath) 
{
	const WCHAR wszStreamName[] = L"ActiveMovieGraph"; 
	HRESULT hr;
	
	IStorage *pStorage = NULL;
	hr = StgCreateDocfile(
	wszPath,
	STGM_CREATE | STGM_TRANSACTED | STGM_READWRITE | STGM_SHARE_EXCLUSIVE,
	0, &pStorage);
	if(FAILED(hr)) 
	{
		return hr;
	}

	IStream *pStream;
	hr = pStorage->CreateStream(
	wszStreamName,
	STGM_WRITE | STGM_CREATE | STGM_SHARE_EXCLUSIVE,
	0, 0, &pStream);
	if (FAILED(hr)) 
	{
		pStorage->Release(); 
		return hr;
	}
	
	IPersistStream *pPersist = NULL;
	pGraph->QueryInterface(IID_IPersistStream, (void**)&pPersist);
	hr = pPersist->Save(pStream, TRUE);
	pStream->Release();
	pPersist->Release();
	if (SUCCEEDED(hr)) 
	{
		hr = pStorage->Commit(STGC_DEFAULT);
	}
	pStorage->Release();
	return hr;
}


/******************************Public*Routine******************************\
* CVMR9Subgraph
*
* constructor
\**************************************************************************/

CVMR9Subgraph::CVMR9Subgraph()
    : m_dwID( NULL)
	,m_GraphType(Un_Known)
	,m_DeviceId( NULL)
	,m_pGraph(NULL)
    ,m_pMc(NULL)
    ,m_pMs(NULL)
	,m_pCapGraph(NULL)
	,m_pCapMc(NULL)
	,m_ConnectProc(NULL)
{
	
}

/******************************Public*Routine******************************\
* CVMR9Subgraph
*
* destructor
\**************************************************************************/
CVMR9Subgraph::~CVMR9Subgraph()
{
	CMediaHelper help;
	help.DestroyGraph(m_pGraph);
	help.DestroyGraph(m_pCapGraph);
    RELEASE(m_pMc);			// media control
    RELEASE(m_pMs);			// media seeking
	RELEASE(m_pGraph);		// filter graph
	RELEASE(m_pCapMc);
	RELEASE(m_pCapGraph);
	m_ConnectProc = 0;
		
}
/******************************Public*Routine******************************\
* BuildAndRender
*
* 位图源
\**************************************************************************/
HRESULT CVMR9Subgraph::BuildAndRender(UINT id,UINT imgtp,LPRECT rcSrc,DWORD ColorKey, IMultiVMR9Wizard* pWizard )
{
	HRESULT hr = S_OK;
	if(!pWizard)return E_FAIL;
	if(m_pGraph)			return E_FAIL;

    IVMRFilterConfig9		* pConfig = 0;
    IGraphBuilder			* pGb= 0;
	IDirect3DSurface9		* pTexturePrivSurf    = NULL;
	IDirect3DTexture9		* pTexture = 0;
	IBaseFilter				* pVMR9 = 0;
	VMR9AllocationInfo info;
	info.dwFlags = VMR9AllocFlag_OffscreenSurface;
	info.dwHeight = rcSrc->bottom - rcSrc->top;
	info.dwWidth =	rcSrc->bottom - rcSrc->left;
	info.Format = (D3DFORMAT)imgtp;
	info.MinBuffers = 1;
	info.Pool = D3DPOOL_SYSTEMMEM;
	info.szAspectRatio.cx = 0;//rcDest->right - rcDest->left;
	info.szAspectRatio.cy =0;// rcDest->bottom - rcDest->top;
	info.szNativeSize.cy = rcSrc->right - rcSrc->left;
	info.szNativeSize.cy = rcSrc->bottom - rcSrc->top;



   // USES_CONVERSION;
	m_GraphType = Image_DIB;
	try
	{
		// create graph
		hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
			IID_IFilterGraph, (void**)&(m_pGraph) );
		
		if( FAILED(hr))throw hr;
	
		if(!m_pGraph)
			throw E_OUTOFMEMORY;
		

		// create and add VMR9
		hr = CoCreateInstance( CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER,
			IID_IBaseFilter, (void**)&(pVMR9) );
		if( FAILED(hr))throw hr;

		hr = m_pGraph->AddFilter( pVMR9, L"VMR9");
		if( FAILED(hr))throw hr;

		// configure VMR9
		hr = pVMR9->QueryInterface( IID_IVMRFilterConfig9, (void**)&(pConfig) );
		if( FAILED(hr))throw hr;

	    
		// if wizard is provided, set VMR to the renderless code and attach to the wizard
		if( pWizard )
		{
			// set VMR to the renderless mode
			hr = pConfig->SetRenderingMode( VMR9Mode_Renderless );
			if( FAILED(hr))throw hr;


			hr = pWizard->Attach( pVMR9, D3DFMT_A8R8G8B8,& m_dwID);
			if( FAILED(hr))throw hr;

			DWORD num = 1;
			hr = pWizard->InitializeDevice(m_dwID,&info,&num);
			if( FAILED(hr))throw hr;
			hr = pWizard->GetTexture(m_dwID,&pTexture);
			if( FAILED(hr))throw hr;

			hr = pTexture->GetSurfaceLevel(0,&pTexturePrivSurf);
			if( FAILED(hr))throw hr;
			
			//CDC::GetCurrentBitmap(imgtp	
			hr =  D3DXLoadSurfaceFromResource( pTexturePrivSurf,
											NULL,
											0,
											GetModuleHandle(NULL),
											MAKEINTRESOURCE(id),
											rcSrc,
											D3DX_DEFAULT,
											ColorKey,
											0
											);

			if( FAILED(hr))throw hr;
			if(!pTexturePrivSurf)throw E_OUTOFMEMORY;
			
		}
		
		// try to render media source
		hr = m_pGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb) );
		if( FAILED(hr))throw hr;

	//	pWizard->InitializeDevice();

		// ok, all is rendered, now get MediaControl, MediaSeeking and continue
		hr = m_pGraph->QueryInterface( IID_IMediaControl, (void**)&(m_pMc) );
		if( FAILED(hr))throw hr;

		hr = m_pGraph->QueryInterface( IID_IMediaSeeking, (void**)&(m_pMs) );
		if( FAILED(hr))throw hr;


	}
	catch(HRESULT hr1)
	{
		pWizard->Detach( m_dwID );
		hr = hr1;
	}
	RELEASE(pVMR9);
	RELEASE(pConfig );
	RELEASE(pGb );
	RELEASE(pTexturePrivSurf );
	RELEASE(pTexture );
	//AddCaptureFilter(pWizard);
    return hr;
}
HRESULT CVMR9Subgraph::BuildAndRender(LPCVOID pSrcMemory,UINT imgtp,long bmWidthBytes,LPRECT rcSrc,DWORD ColorKey,IMultiVMR9Wizard* pWizard)
{
	HRESULT hr = S_OK;
	if(!pWizard)return E_FAIL;
	if(m_pGraph)			return E_FAIL;

    IVMRFilterConfig9		* pConfig = 0;
    IGraphBuilder			* pGb= 0;
	IDirect3DSurface9		* pTexturePrivSurf    = NULL;
	IDirect3DTexture9		* pTexture = 0;
	IBaseFilter				* pVMR9 = 0;
	VMR9AllocationInfo info;
	info.dwFlags = VMR9AllocFlag_OffscreenSurface;
	info.dwHeight = rcSrc->bottom - rcSrc->top;
	info.dwWidth =	rcSrc->bottom - rcSrc->left;
	info.Format = (D3DFORMAT)imgtp;
	info.MinBuffers = 1;
	info.Pool = D3DPOOL_SYSTEMMEM;
	info.szAspectRatio.cx = 0;//rcDest->right - rcDest->left;
	info.szAspectRatio.cy =0;// rcDest->bottom - rcDest->top;
	info.szNativeSize.cy = rcSrc->right - rcSrc->left;
	info.szNativeSize.cy = rcSrc->bottom - rcSrc->top;

    if( !pSrcMemory )
    {
        return E_POINTER;
    }

   // USES_CONVERSION;
	m_GraphType = Image_DIB;
	try
	{
		// create graph
		hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
			IID_IFilterGraph, (void**)&(m_pGraph) );
		
		if( FAILED(hr))throw hr;
	
		if(!m_pGraph)
			throw E_OUTOFMEMORY;
		

		// create and add VMR9
		hr = CoCreateInstance( CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER,
			IID_IBaseFilter, (void**)&(pVMR9) );
		if( FAILED(hr))throw hr;

		hr = m_pGraph->AddFilter( pVMR9, L"VMR9");
		if( FAILED(hr))throw hr;

		// configure VMR9
		hr = pVMR9->QueryInterface( IID_IVMRFilterConfig9, (void**)&(pConfig) );
		if( FAILED(hr))throw hr;

	    
		// if wizard is provided, set VMR to the renderless code and attach to the wizard
		if( pWizard )
		{
			// set VMR to the renderless mode
			hr = pConfig->SetRenderingMode( VMR9Mode_Renderless );
			if( FAILED(hr))throw hr;


			hr = pWizard->Attach( pVMR9, D3DFMT_A8R8G8B8,& m_dwID);
			if( FAILED(hr))throw hr;

			DWORD num = 1;
			hr = pWizard->InitializeDevice(m_dwID,&info,&num);
			if( FAILED(hr))throw hr;
			hr = pWizard->GetTexture(m_dwID,&pTexture);
			if( FAILED(hr))throw hr;

			hr = pTexture->GetSurfaceLevel(0,&pTexturePrivSurf);
			if( FAILED(hr))throw hr;
			
			//CDC::GetCurrentBitmap(imgtp	
			hr = D3DXLoadSurfaceFromMemory( pTexturePrivSurf,
											NULL,
											0,
											pSrcMemory,
											(D3DFORMAT)imgtp,
											bmWidthBytes,
											0,
											rcSrc,
											D3DX_DEFAULT,
											ColorKey
											);

			if( FAILED(hr))throw hr;
			if(!pTexturePrivSurf)throw E_OUTOFMEMORY;
			
		}
		
		// try to render media source
		hr = m_pGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb) );
		if( FAILED(hr))throw hr;

	//	pWizard->InitializeDevice();

		// ok, all is rendered, now get MediaControl, MediaSeeking and continue
		hr = m_pGraph->QueryInterface( IID_IMediaControl, (void**)&(m_pMc) );
		if( FAILED(hr))throw hr;

		hr = m_pGraph->QueryInterface( IID_IMediaSeeking, (void**)&(m_pMs) );
		if( FAILED(hr))throw hr;

	}
	catch(HRESULT hr1)
	{
		pWizard->Detach( m_dwID );
		hr = hr1;
	}
	RELEASE(pVMR9);
	RELEASE(pConfig );
	RELEASE(pGb );
	RELEASE(pTexturePrivSurf );
	RELEASE(pTexture );
	//AddCaptureFilter(pWizard);
    return hr;
}
/******************************Public*Routine******************************\
* BuildAndRender
*
* 视频文件源
\**************************************************************************/
HRESULT CVMR9Subgraph::BuildAndRender( LPCWSTR lpPath , IMultiVMR9Wizard* pWizard ,SourceConnectProc ConnectProc)
{
    HRESULT hr = S_OK;
	if(!pWizard)return E_FAIL;
	if(m_pGraph)			return E_FAIL;
	m_ConnectProc = ConnectProc;
    if( !lpPath )
    {
        return E_POINTER;
    }
	IBaseFilter				* pVMR9 = 0;
	IBaseFilter				* pFileScr  = 0;
	IVMRFilterConfig9		* pConfig = 0;
    IGraphBuilder			* pGb = 0;
	ICaptureGraphBuilder2	* pBuild = NULL;
	IBaseFilter *pAviSplit = NULL;
	IPin*pPin = 0;

    USES_CONVERSION;
	m_GraphType = Media_File;
	try
	{
    // first, check that file exists
		if( INVALID_FILE_ATTRIBUTES == GetFileAttributes( lpPath))throw VFW_E_NOT_FOUND;

		// create graph
		hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
			IID_IFilterGraph, (void**)&(m_pGraph) );
		if( FAILED(hr))throw hr;
		
		// create and add VMR9
		hr = CoCreateInstance( CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC_SERVER,
			IID_IBaseFilter, (void**)&(pVMR9) );
		if( FAILED(hr))throw hr;


		hr = m_pGraph->AddFilter( pVMR9, L"VMR9");
		if( FAILED(hr))throw hr;

		// configure VMR9
		hr = pVMR9->QueryInterface( IID_IVMRFilterConfig9, (void**)&(pConfig) );
		if( FAILED(hr))throw hr;
		
		
	    
		// if wizard is provided, set VMR to the renderless code and attach to the wizard
		if( pWizard )
		{
			// set VMR to the renderless mode
			hr = pConfig->SetRenderingMode( VMR9Mode_Renderless );
			if( FAILED(hr))throw hr;
			
			hr = pWizard->Attach( pVMR9, D3DFMT_UNKNOWN,&m_dwID );
			if( FAILED(hr))throw hr;

		}

		// try to render media source
		hr = m_pGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb) );
		if( FAILED(hr))throw hr;

		hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&pBuild);		
		if( FAILED(hr))throw hr;if(!pBuild)throw  E_OUTOFMEMORY;
	
		//--
		hr = pBuild->SetFiltergraph(pGb);
		if( FAILED(hr))throw hr;


		hr = pGb->AddSourceFilter( lpPath, L"Source", &pFileScr);
		if( FAILED(hr))throw hr;


		
		if(m_ConnectProc) {
			hr = m_ConnectProc(m_dwID,m_pGraph,pFileScr,pVMR9);
			if( FAILED(hr))throw hr;
		}else
		{
			hr = CoCreateInstance(CLSID_AviSplitter, 0, CLSCTX_INPROC_SERVER,IID_IBaseFilter, reinterpret_cast<void**>(&pAviSplit));
			if( FAILED(hr))throw hr;
			hr = m_pGraph->AddFilter(pAviSplit, L"AVI Splitter");
			if( FAILED(hr))throw hr;

			hr =	pBuild->RenderStream(0, 0,pFileScr,pAviSplit,pVMR9);
			if( FAILED(hr))throw hr;

		}
	

		// ok, all is rendered, now get MediaControl, MediaSeeking and continue
		hr = m_pGraph->QueryInterface( IID_IMediaControl, (void**)&(m_pMc) );
		if( FAILED(hr))throw hr;

		hr = m_pGraph->QueryInterface( IID_IMediaSeeking, (void**)&(m_pMs) );
		if( FAILED(hr))throw hr;
	}
	catch(HRESULT hr1)
	{
		pWizard->Detach( m_dwID );
		hr = hr1;
	}
	RELEASE(pConfig);
	RELEASE(pGb);
	RELEASE(pVMR9);
	RELEASE(pFileScr);
	RELEASE(pAviSplit);
	RELEASE(pBuild);
	RELEASE(pPin);

	//AddCaptureFilter(pWizard);
    return hr;
}
/******************************Public*Routine******************************\
* BuildAndRender
*
* 采集卡源
\**************************************************************************/
HRESULT CVMR9Subgraph::BuildAndRender(IBaseFilter* pCap , GUID VidType ,UINT Width,UINT Height,int nFPS,IMultiVMR9Wizard* pWizard ,BOOL bUsingColorSpace,SourceConnectProc ConnectProc)
{
    HRESULT hr = S_OK;
	if(!pWizard)return E_FAIL;
	if(!pCap)return E_FAIL;
	if(m_pGraph)			return E_FAIL;
    IVMRFilterConfig9	*	pConfig = NULL;
	IGraphBuilder		*	pGb= NULL;
	IBaseFilter			*	pColorSpace = 0;
	IBaseFilter				* pVMR9 = 0;

	ICaptureGraphBuilder2 * pBuild = NULL;
	//IBaseFilter* pCap = NULL;
	IPin * pPin = NULL;
	IAMStreamConfig *pStrCfig = 0;
	AM_MEDIA_TYPE * mmt = 0;
	//m_DeviceId = DeviceId;
	m_GraphType = Capture_Device;
		
	m_ConnectProc = ConnectProc;
	CMediaHelper Helper;
    // create graph
	try
	{
		hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
			IID_IFilterGraph, (void**)&(m_pGraph) );
		if( FAILED(hr))throw hr;if(!m_pGraph)throw  E_OUTOFMEMORY;
		//--
		hr = m_pGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb) );
		if( FAILED(hr))throw hr;if(!pGb)throw  E_OUTOFMEMORY;
		//--
		hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&pBuild);		
		if( FAILED(hr))throw hr;if(!pBuild)throw  E_OUTOFMEMORY;
	
		//--
		hr =pBuild->SetFiltergraph(pGb);
		if( FAILED(hr))throw hr;
		//--
		// create and add VMR9
		hr = CoCreateInstance( CLSID_VideoMixingRenderer9, NULL, CLSCTX_INPROC,
			IID_IBaseFilter, (void**)&(pVMR9) );
		if( FAILED(hr))throw hr;if(! pVMR9)throw  E_OUTOFMEMORY;
		//--
		hr = m_pGraph->AddFilter( pVMR9, L"VMR9");
		if( FAILED(hr))throw hr;

		//--
		hr = pVMR9->QueryInterface( IID_IVMRFilterConfig9, (void**)&(pConfig) );
		if( FAILED(hr))throw hr;
		//--
		// set VMR to the renderless mode
		hr = pConfig->SetRenderingMode(  VMR9Mode_Renderless );
				//--
		hr = pWizard->Attach( pVMR9,D3DFMT_UNKNOWN, &m_dwID );
		if( FAILED(hr))throw hr;

		if(bUsingColorSpace){
			hr = CoCreateInstance( CLSID_Colour, NULL, CLSCTX_INPROC,
				IID_IBaseFilter, (void**)&(pColorSpace) );
			if( FAILED(hr))throw hr;if( !pColorSpace)throw  E_OUTOFMEMORY;
			//--
			hr = m_pGraph->AddFilter( pColorSpace, L"ColorSpace");
			if( FAILED(hr))throw hr;
		}

		
		////连接采集卡
		//hr = Helper.GetVidCapDevice(DeviceId,&pCap);
		//if( FAILED(hr))throw hr;
		//if(!pCap)throw  E_OUTOFMEMORY;
		hr = m_pGraph->AddFilter(pCap,L"Capture");
		if( FAILED(hr))throw hr;
		if(m_ConnectProc) {
			hr = m_ConnectProc(m_dwID,m_pGraph,pCap,pVMR9);
		}
		else{//使用默认连接方法
			hr = pBuild->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Interleaved,pCap,IID_IAMStreamConfig,(void **)&pStrCfig);
			if( FAILED( hr) ){
				hr = pBuild->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,pCap,IID_IAMStreamConfig,(void **)&pStrCfig);
				if (FAILED(hr ))throw hr;	
			}
			
				hr = pStrCfig->GetFormat(&mmt);
				if(mmt->formattype  == FORMAT_VideoInfo){
				if (FAILED(hr ))throw hr;	
				if(!mmt) throw E_OUTOFMEMORY;
				VIDEOINFO *pvi = (VIDEOINFO *) mmt->pbFormat;
				pvi->AvgTimePerFrame = UNITS/nFPS;
				pvi->bmiHeader.biWidth = Width;
				pvi->bmiHeader.biHeight = Height;
				mmt->subtype = VidType;
		//		hr=pStrCfig->SetFormat(mmt);   //重新设置参数
				
				if( FAILED(hr))throw hr;
			}
			/*hr = pBuild->FindPin( pCap, PINDIR_OUTPUT, &PIN_CATEGORY_CAPTURE,&MEDIATYPE_Interleaved, TRUE, 0, &pPin);
			if( FAILED(hr)){
				hr = pBuild->FindPin( pCap, PINDIR_OUTPUT, &PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video, TRUE, 0, &pPin); 
				if (FAILED(hr ))throw hr;
			}
			if(!pPin) throw E_OUTOFMEMORY;*/
			hr = pBuild->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Interleaved,pCap,pColorSpace,pVMR9);
			if( FAILED(hr)){
				hr = pBuild->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,pCap,pColorSpace,pVMR9);
				if (FAILED(hr ))throw hr;
			}
		}
		if( FAILED(hr))throw hr;

		
		// ok, all is rendered, now get MediaControl, MediaSeeking and continue
		hr = m_pGraph->QueryInterface( IID_IMediaControl, (void**)&(m_pMc) );
		if( FAILED(hr))throw hr;

		hr = m_pGraph->QueryInterface( IID_IMediaSeeking, (void**)&(m_pMs) );
		if( FAILED(hr))throw hr;



	}
	catch(HRESULT hr1)
	{
		pWizard->Detach( m_dwID );
		hr = hr1;
	}

	RELEASE( pConfig );
	RELEASE( pGb );
	RELEASE( pColorSpace );
	RELEASE( pBuild  );
	RELEASE( pStrCfig );
	RELEASE( pVMR9);
	Helper.DeleteMediaType(mmt);
	return hr;
}
HRESULT CVMR9Subgraph::AddCaptureFilter(LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName ,IMultiVMR9Wizard* pWizard )
{
	HRESULT hr = S_OK;
    IGraphBuilder*  pGb = 0;
	ICaptureGraphBuilder2 * pBuild = 0;
	IBaseFilter* pStreamFt = 0;
	IBaseFilter* pAudFt = 0;
	IBaseFilter* pAudCom = 0;//音频压缩
	IBaseFilter* pVidCom = 0;//视频压缩
	IBaseFilter* pAviMux = 0;
	IFileSinkFilter	*pSink  = 0;//file
	IConfigAviMux *pConfigMux = NULL;
	CMediaHelper Helper;
	if(m_pCapGraph) 
	hr = DelCaptureFilter();
	if(FAILED(hr) || m_pCapGraph)
		return E_INVALIDARG;
	try
	{
  
		// create graph
		hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
			IID_IFilterGraph, (void**)&(m_pCapGraph) );
		if( FAILED(hr))throw hr;

		hr = m_pCapGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb) );
		if( FAILED(hr))throw hr;

		hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&pBuild);		
		if( FAILED(hr))throw hr;

		hr =pBuild->SetFiltergraph(pGb);
		if( FAILED(hr))throw hr;

		//连接输出流filter/////////////////////////////////////////
		//
		//  filter			--->	|-------|
		//							|AVI MUX|	---->	Avi File
		//	sound device	--->	|-------|
		//
		///////////////////////////////////////////////////////////
		hr = pWizard->InitializeOutStream(m_dwID);
		if( FAILED(hr)) throw hr;
		hr = pWizard->GetOutStreamFilter(m_dwID,&pStreamFt);
		if( FAILED(hr)) throw hr;
		if(pStreamFt == 0) throw E_INVALIDARG;
		hr = m_pCapGraph->AddFilter( pStreamFt, L"OutFilter");
		if( FAILED(hr))throw hr;

		//create AVI MUX Filter

		hr = pBuild->SetOutputFileName(&MEDIASUBTYPE_Avi,lpPath, &pAviMux, &pSink); 
		if( FAILED(hr) || !pAviMux) throw hr;
		if(pszVidComName){//视频压缩
			hr = Helper.GetVidCompression(pszVidComName,&pVidCom);
			if( SUCCEEDED(hr) && pVidCom){
				hr = m_pCapGraph->AddFilter(pVidCom,L"VidCom");
				if( FAILED(hr) ) throw hr;
			}
		}
		if( lpszAudDevice){//音频采集
			hr = Helper.GetAudCapDevice(lpszAudDevice,&pAudFt);
			if( FAILED(hr) || !pAudFt) throw hr;
			hr = m_pCapGraph->AddFilter(pAudFt,L"AudFt");
			if( FAILED(hr) ) throw hr;
			if(pszAudComName){
				hr = Helper.GetAudCompression(pszAudComName,&pAudCom);
				if( FAILED(hr) || !pAudCom) throw hr;
				hr = m_pCapGraph->AddFilter(pAudCom,L"AudCom");
				if( FAILED(hr) ) throw hr;
			}
		}		
		
		//开始连接
		hr = pBuild->RenderStream(0, &MEDIATYPE_Video,pStreamFt,pVidCom,pAviMux);

		if( FAILED(hr) ) throw hr;
		if(pAudFt){
			pBuild->RenderStream(0,0,pAudFt,pAudCom,pAviMux);
			if( FAILED(hr) ) throw hr;
			hr = pAviMux->QueryInterface(IID_IConfigAviMux, (void**)&pConfigMux);
			if( SUCCEEDED(hr)) {
				pConfigMux->SetMasterStream(1);
			}
		}
		/*IConfigInterleaving *pInterleave = NULL;
		hr = pAviMux->QueryInterface(IID_IConfigInterleaving, (void**)&pInterleave);
		if (SUCCEEDED(hr))
		{
			pInterleave->put_Mode(INTERLEAVE_CAPTURE);
			pInterleave->Release();
		}*/
		//连接完成

		hr = CheckConnection(pStreamFt);
		if( FAILED(hr))throw hr;

		////   Done   /////////////////////////////////////////////

		// ok, all is rendered, now get MediaControl
		hr = m_pCapGraph->QueryInterface( IID_IMediaControl, (void**)&(m_pCapMc) );
		if( FAILED(hr))throw hr;


	}
	catch(HRESULT hr1)
	{
		hr = hr1;
	}
	RELEASE(pStreamFt);
	RELEASE(pGb);
	RELEASE(pBuild);
	RELEASE(pConfigMux);
	RELEASE(pAudFt);
	RELEASE(pAudCom );
	RELEASE(pVidCom );
	RELEASE(pAviMux );
	RELEASE(pSink);
   

    return hr;

	
}
HRESULT CVMR9Subgraph::DelCaptureFilter()
{	
	CMediaHelper help;
	HRESULT hr = help.DestroyGraph(m_pCapGraph);
	if(FAILED(hr))return hr;
	RELEASE(m_pCapMc);
	RELEASE(m_pCapGraph);	
	return hr;
}
/******************************Public*Routine******************************\
* CheckOutConnection
\**************************************************************************/
HRESULT CVMR9Subgraph::CheckConnection(IBaseFilter* ft)
{
	HRESULT hr = S_OK;
    bool bConnected = false;

    IEnumPins*pEnum = 0;
	IPin* pPin = 0;

    if( !ft )
        return E_UNEXPECTED;
	
		hr = ft->EnumPins( &pEnum );
		if( FAILED(hr))
			return hr;

		hr = pEnum->Next( 1, &pPin, NULL);
		while( SUCCEEDED(hr) && pPin)
		{
			IPin* pConnectedPin = 0;
			hr = pPin->ConnectedTo( &pConnectedPin );
			
			if( SUCCEEDED(hr) && pConnectedPin )
			{
				bConnected = true;
				RELEASE(pConnectedPin);
				break;
			}
			RELEASE(pPin);
			RELEASE(pConnectedPin);
			hr = pEnum->Next( 1, &pPin, NULL);
		}// while

		hr = (true == bConnected) ? S_OK : E_FAIL;
	
	RELEASE(pEnum);
	RELEASE(pPin);
    return hr;
}

/******************************Public*Routine******************************\
* StartCapture
\**************************************************************************/
HRESULT CVMR9Subgraph::StartCapture()
{
	HRESULT hr = S_OK;

    if( !m_pCapMc )
    {
        return E_UNEXPECTED;
    }
    hr = m_pCapMc->Run();

    return hr;
}
/******************************Public*Routine******************************\
* StartStop
\**************************************************************************/
HRESULT CVMR9Subgraph::StopCapture()
{
	HRESULT hr = S_OK;

    if( !m_pCapMc )
    {
        return S_OK;
    }
	
	hr = m_pCapMc->Stop();

    return hr;
}
/******************************Public*Routine******************************\
* Run
\**************************************************************************/
HRESULT CVMR9Subgraph::Run()
{
    HRESULT hr = S_OK;

    if( !m_pMc )
    {
        return E_UNEXPECTED;
    }
	LONGLONG  llCur= 0; LONGLONG  llDur = 0;
	hr = GetTimes(llCur,  llDur);
	if(llCur == llDur)
		SetTime(0);
    hr = m_pMc->Run();

    return hr;
}

/******************************Public*Routine******************************\
* Pause
\**************************************************************************/
HRESULT CVMR9Subgraph::Pause()
{
    HRESULT hr = S_OK;

    if( !m_pMc )
    {
        return E_UNEXPECTED;
    }
    hr = m_pMc->Pause();

    return hr;
}
/******************************Public*Routine******************************\
* StopWhenReady
\**************************************************************************/
HRESULT CVMR9Subgraph::StopWhenReady() 
{
	 HRESULT hr = S_OK;
	  if( !m_pMc )
		{
        return E_UNEXPECTED;
		}
		hr = m_pMc->StopWhenReady();

    return hr;
}
/******************************Public*Routine******************************\
* Stop
\**************************************************************************/
HRESULT CVMR9Subgraph::Stop()
{
    HRESULT hr = S_OK;
    OAFilterState state;

    if( !m_pMc )
    {
        return E_UNEXPECTED;
    }

    hr = m_pMc->Stop();
    state = State_Running;

    while( State_Stopped != state && SUCCEEDED(hr))
    {
        hr = m_pMc->GetState(100, &state);
        Sleep(100);
    }

    return hr;
}

/******************************Public*Routine******************************\
* GetState
*
* Returns OAFilterState from IMediaControl of the graph
*
* Return values: errors from the filter graph and wizard
\**************************************************************************/
OAFilterState CVMR9Subgraph::GetState()
{
    OAFilterState state = State_Stopped;
    if( m_pMc )
    {
        HRESULT hr = m_pMc->GetState( 20, &state );
    }
    return state;
}

/******************************Public*Routine******************************\
* SetTime
*
*
\**************************************************************************/
HRESULT CVMR9Subgraph::SetTime( LONGLONG llCur,LONGLONG llDur)
{
    HRESULT hr = S_OK;
   // LONGLONG llDur = 0L;

    if( !m_pMs )
        return E_FAIL;

    hr = m_pMs->SetPositions(   &llCur, AM_SEEKING_AbsolutePositioning, 
								&llDur, (llDur == 0)? AM_SEEKING_NoPositioning:AM_SEEKING_AbsolutePositioning);
	
	
    return hr;
}
/******************************Public*Routine******************************\
* GetVideoLen
*
*
\**************************************************************************/
HRESULT CVMR9Subgraph::GetVideoLen( LONGLONG &llLen)
{
    HRESULT hr = S_OK;
   // LONGLONG llDur = 0L;

    if( !m_pMs )
        return E_FAIL;

    hr = m_pMs->GetDuration (&llLen );

    return hr;
}
/******************************Public*Routine******************************\
* StopAt
*
*
\**************************************************************************/
HRESULT CVMR9Subgraph::StopAt( LONGLONG llDur)
{
    HRESULT hr = S_OK;
   // LONGLONG llDur = 0L;

    if( !m_pMs )
        return E_FAIL;

    hr = m_pMs->SetPositions(   0, AM_SEEKING_NoPositioning, 
								&llDur, (llDur == 0)? AM_SEEKING_NoPositioning:AM_SEEKING_AbsolutePositioning);

    return hr;
}
//HRESULT  CVMR9Subgraph::GetDIB(  long *pBufferSize,LPVOID pDIBImage)
//{
//	IBasicVideo * pBV = 0;
//	HRESULT hr = m_pVMR->QueryInterface(IID_IBasicVideo, (void**)&pBV);
//	if(FAILED(hr)) return hr;
//	m_pVMR->
//}
/******************************Public*Routine******************************\
* GetTimes
*
\**************************************************************************/
HRESULT CVMR9Subgraph::GetTimes( LONGLONG& llCur, LONGLONG& llDur)
{
    HRESULT hr = S_OK;
    if( !m_pMs )
        return E_FAIL;

    hr = m_pMs->GetPositions( &llCur, &llDur );
    return hr;
}
HRESULT CVMR9Subgraph::SetTimeFormat( const GUID *pFormat)
{
	if(!m_pMs) return E_NOTIMPL;
	if(!pFormat) return E_POINTER;
    HRESULT hr = m_pMs->IsFormatSupported(pFormat);
	if(hr!=S_OK) return hr;
	return m_pMs->SetTimeFormat(pFormat);

}
HRESULT CVMR9Subgraph::GetTimeFormat( GUID *pFormat)
{
	if(!m_pMs) return E_NOTIMPL;
	if(!pFormat) return E_POINTER;
	return m_pMs->GetTimeFormat(pFormat);
}



///******************************Public*Routine******************************\
//* DestroyGraph
//*
//* Stops the graph, destroys and removes all the filters 
//*
//\**************************************************************************/
//HRESULT CVMR9Subgraph::DestroyGraph(IFilterGraph * pGraph)
//{
//    HRESULT hr = S_OK;
//    OAFilterState state;
//
//    if( !pGraph )return S_OK;
//
//    FILTER_INFO fi;
//    IMediaControl* pMc= NULL;
//    IEnumFilters* pEnum= NULL;
//    IBaseFilter*  pFilter= NULL;
//	IBaseFilter*  pOutFilter = NULL;	
//    // 1. stop the graph
//	try
//	{
//		hr = pGraph->QueryInterface( IID_IMediaControl, (void**)&(pMc) );
//		if( FAILED(hr)) throw hr;
//		pMc->Stop();
//		do
//		{
//			hr = pMc->GetState(100, &state);
//		} while( S_OK == hr && State_Stopped != state );
//
//		hr = pGraph->EnumFilters( &(pEnum) );
//		if( FAILED(hr))throw hr;
//	
//		// tear off
//		hr = pEnum->Next(1, &(pFilter), NULL);
//		while( S_OK == hr && pFilter )
//		{
//			hr = DisconnectPins( pFilter );
//			RELEASE(pFilter);
//			hr = pEnum->Next(1, &(pFilter), NULL);
//		}
//		// remove filters
//		hr = pEnum->Reset();
//		hr = pEnum->Next(1, &(pFilter), NULL);
//		while( S_OK == hr && pFilter )
//		{
//			hr = pFilter->QueryFilterInfo( &fi);
//			if( fi.pGraph)fi.pGraph->Release();
//				
//			hr = pGraph->RemoveFilter( pFilter);
//			RELEASE(pFilter)
//			hr = pEnum->Reset();
//			hr = pEnum->Next(1, &pFilter, NULL);
//		}
//	}
//	catch(HRESULT hr1)
//	{
//		hr = hr1;
//	}
//	RELEASE(pMc);
//    RELEASE(pEnum);
//    RELEASE(pFilter);
//	RELEASE(pOutFilter);
//
//    return hr;
//}


