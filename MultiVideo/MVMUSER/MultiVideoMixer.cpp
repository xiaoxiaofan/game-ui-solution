//------------------------------------------------------------------------------
// File: MultiVideoMixer.cpp
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#include "stdafx.h"
#include "VMR9Subgraph.h"
#include "MultiVideoMixer.h"
#include "d3dx9core.h"

#include "MultiVMR9_i.c"

//extern HINSTANCE g_hInstance;
const TCHAR g_achVideoWindowClass[] = TEXT("MultiVMR9 Video Window class");

/******************************Public*Routine******************************\
* CMultiVideoMixer
*
* constructor
\**************************************************************************/
CMultiVideoMixer::CMultiVideoMixer()
    : m_hwndVideo( NULL )
    , m_pWizard( NULL )
    , m_pRenderEngine( NULL )
    , m_pMixerControl( NULL )
    , m_pUILayer( NULL )
	,m_pCapGraph(NULL)	
	,m_pCapMc(NULL)		
{
	
}
/******************************Public*Routine******************************\
* ~CMultiVideoMixer
*
* destructor
\**************************************************************************/
CMultiVideoMixer::~CMultiVideoMixer()
{
    Terminate();

 
}
HRESULT CMultiVideoMixer::Initialize(HWND hwnd,UINT Width, UINT Height,D3DFORMAT FinalFormat,BOOL bBufferInSystemMem)
{
	
    HRESULT hr;
    // Verify that the VMR exists on this system
    IBaseFilter* pBF = NULL;
	m_hwndVideo = hwnd;

	
    try
    {
        if( m_pWizard )
            throw VFW_E_WRONG_STATE;

        // create wizard
        hr = CoCreateInstance( CLSID_MultiVMR9Wizard,
                                NULL,
                                CLSCTX_INPROC_SERVER,
                                IID_IMultiVMR9Wizard,
                                (void**)&m_pWizard);
        CHECK_HR( hr, DbgMsg("CMultiPlayerSession::Initialize: Failed to create instance of MultiVMR9Wizard, hr = 0x%08x", hr));

        // create video window
       /* CHECK_HR(
            hr = CreateVideoWindow_(800, 600, WS_CAPTION|WS_OVERLAPPED|WS_THICKFRAME|WS_POPUP),
            DbgMsg("CMultiPlayerSession::Initialize: failed to create video window"));*/

        // initialize wizard with default
        CHECK_HR(
            hr = m_pWizard->Initialize(NULL, hwnd, NULL,FinalFormat,bBufferInSystemMem),
            DbgMsg("CMultiPlayerSession::Initialize: failed to initialize the wizard, hr = 0x%08x", hr));

        // get interfaces
        CHECK_HR(
            m_pWizard->GetRenderEngine( &m_pRenderEngine),
            DbgMsg("CMultiPlayerSession::Initialize: failed to get Render Engine, hr = 0x%08x", hr));

        CHECK_HR(
            m_pRenderEngine->GetMixerControl( &m_pMixerControl),
            DbgMsg("CMultiPlayerSession::Initialize: failed to get Mixer Control, hr = 0x%08x", hr));

        CHECK_HR(
            m_pRenderEngine->GetUILayer( &m_pUILayer),
            DbgMsg("CMultiPlayerSession::Initialize: failed to get UILayer, hr = 0x%08x", hr));
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
	RELEASE(pBF);
    return hr;
}
HRESULT CMultiVideoMixer::InitializeEx(HWND hwnd,HWND hwndCpy,UINT Width, UINT Height,D3DFORMAT FinalFormat,BOOL bBufferInSystemMem)
{
	
    HRESULT hr;
    // Verify that the VMR exists on this system
    IBaseFilter* pBF = NULL;
	m_hwndVideo = hwnd;

	
    try
    {
        if( m_pWizard )
            throw VFW_E_WRONG_STATE;

        // create wizard
        hr = CoCreateInstance( CLSID_MultiVMR9Wizard,
                                NULL,
                                CLSCTX_INPROC_SERVER,
                                IID_IMultiVMR9Wizard,
                                (void**)&m_pWizard);
        CHECK_HR( hr, DbgMsg("CMultiPlayerSession::Initialize: Failed to create instance of MultiVMR9Wizard, hr = 0x%08x", hr));

        // create video window
       /* CHECK_HR(
            hr = CreateVideoWindow_(800, 600, WS_CAPTION|WS_OVERLAPPED|WS_THICKFRAME|WS_POPUP),
            DbgMsg("CMultiPlayerSession::Initialize: failed to create video window"));*/

        // initialize wizard with default
        CHECK_HR(
            hr = m_pWizard->InitializeEx(NULL, hwnd,hwndCpy, NULL,FinalFormat,bBufferInSystemMem),
            DbgMsg("CMultiPlayerSession::Initialize: failed to initialize the wizard, hr = 0x%08x", hr));

        // get interfaces
        CHECK_HR(
            m_pWizard->GetRenderEngine( &m_pRenderEngine),
            DbgMsg("CMultiPlayerSession::Initialize: failed to get Render Engine, hr = 0x%08x", hr));

        CHECK_HR(
            m_pRenderEngine->GetMixerControl( &m_pMixerControl),
            DbgMsg("CMultiPlayerSession::Initialize: failed to get Mixer Control, hr = 0x%08x", hr));

        CHECK_HR(
            m_pRenderEngine->GetUILayer( &m_pUILayer),
            DbgMsg("CMultiPlayerSession::Initialize: failed to get UILayer, hr = 0x%08x", hr));
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }
	RELEASE(pBF);
    return hr;
}

void CMultiVideoMixer::Release()
{
	Terminate();
	delete this;
}
HRESULT CMultiVideoMixer::Get3DDevice(IDirect3DDevice9 ** pDevice)
{
	if(!pDevice) return E_POINTER;
	if(!m_pRenderEngine) return E_INVALIDARG;
	return m_pRenderEngine->Get3DDevice(pDevice);
	
}
/******************************Public*Routine******************************\
* AddSource
*
* adds new source to the list, attaches it to the wizard
\**************************************************************************/
HRESULT CMultiVideoMixer::AddImageDIBSource(UINT id,D3DFORMAT imgtp,LPRECT rcSrc,DWORD ColorKey,DWORD_PTR& dwID ,LPRECT rcDest)
{
	CVMR9Subgraph *pSubgraph = NULL;

    HRESULT hr = S_OK;
  
    if( !m_pWizard )
    {
        return VFW_E_WRONG_STATE;
    }

    try
    {

        pSubgraph = new CVMR9Subgraph;
        if( !pSubgraph )
        {
            throw E_OUTOFMEMORY;
        }
	

		hr = pSubgraph->BuildAndRender(id,imgtp,rcSrc ,ColorKey,m_pWizard );
        if( FAILED(hr))
        {
            throw hr;
        }
		
        dwID = pSubgraph->GetID();
        m_sources.push_back( pSubgraph );
		if(rcDest)
		{
		hr =SourceSetPos(dwID,rcDest,0);
		if( FAILED(hr))
        {
            throw hr;
        }
		}

    }
    catch( HRESULT hr1 )
    {
        if( pSubgraph )
        {
            delete pSubgraph;
        }
        hr = hr1;
    }
    return hr;
}
HRESULT CMultiVideoMixer::AddImageDIBSource(LPCVOID pSrcMemory,D3DFORMAT imgtp,long bmWidthBytes,LPRECT rcSrc,DWORD ColorKey, DWORD_PTR& dwID, LPRECT rcDest)
{
	CVMR9Subgraph *pSubgraph = NULL;

    HRESULT hr = S_OK;
  
    if( !m_pWizard )
    {
        return VFW_E_WRONG_STATE;
    }

    try
    {

        pSubgraph = new CVMR9Subgraph;
        if( !pSubgraph )
        {
            throw E_OUTOFMEMORY;
        }
	

		hr = pSubgraph->BuildAndRender(pSrcMemory,imgtp,bmWidthBytes,rcSrc ,ColorKey,m_pWizard );
        if( FAILED(hr))
        {
            throw hr;
        }
		
        dwID = pSubgraph->GetID();
        m_sources.push_back( pSubgraph );
		if(rcDest)
		{
		hr =SourceSetPos(dwID,rcDest,0);
		if( FAILED(hr))
        {
            throw hr;
        }
		}

    }
    catch( HRESULT hr1 )
    {
        if( pSubgraph )
        {
            delete pSubgraph;
        }
        hr = hr1;
    }
    return hr;

	
}
HRESULT CMultiVideoMixer::AddMediaFileSource(LPCWSTR Path, DWORD_PTR& dwID ,LPRECT rcDest,SourceConnectProc ConnectProc)
{
    CVMR9Subgraph *pSubgraph = NULL;

    HRESULT hr = S_OK;
    if( !Path )
    {
        return E_POINTER;
    }
    if( !m_pWizard )
    {
        return VFW_E_WRONG_STATE;
    }

    try
    {

        pSubgraph = new CVMR9Subgraph;
        if( !pSubgraph )
        {
            throw E_OUTOFMEMORY;
        }

		hr = pSubgraph->BuildAndRender( Path, m_pWizard , ConnectProc);
        if( FAILED(hr))
        {
            throw hr;
        }

     
        dwID = pSubgraph->GetID();

        m_sources.push_back( pSubgraph );
		
		if(rcDest)
		{
			hr = SourceSetPos( dwID, rcDest,0 );
			if( FAILED(hr))
			{
				throw hr;
			}
		}
		
    }
    catch( HRESULT hr1 )
    {
        if( pSubgraph )
        {
            delete pSubgraph;
        }
        hr = hr1;
    }
    return hr;
}
HRESULT CMultiVideoMixer::AddCaptureDeviceSource(LPCWSTR Devicename,int index, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace,LPRECT rcDest,SourceConnectProc ConnectProc)
{
    CVMR9Subgraph *pSubgraph = NULL;

    HRESULT hr = S_OK;
	IBaseFilter* pCap = 0;
    if( !m_pWizard )
    {
        return VFW_E_WRONG_STATE;
    }
	
    try
    {
		

        pSubgraph = new CVMR9Subgraph;
        if( !pSubgraph )
        {
            throw E_OUTOFMEMORY;
        }
		CMediaHelper help;
		
		hr = help.GetVidCapDevice(Devicename,index,&pCap);
		if( FAILED(hr) || !pCap)
        {
            throw hr;
        }
		hr = pSubgraph->BuildAndRender(pCap,  VidType , Width, Height, nFPS,m_pWizard ,bUsingColorSpace ,ConnectProc);

        if( FAILED(hr))
        {
            throw hr;
        }

        //remember the ID, add to the list
        dwID = pSubgraph->GetID();

        m_sources.push_back( pSubgraph );
		if(rcDest)
		{
			hr = SourceSetPos( dwID, rcDest,0 );
			if( FAILED(hr))
			{
				throw hr;
			}
		}
    }
    catch( HRESULT hr1 )
    {
        if( pSubgraph )
        {
            delete pSubgraph;
        }
        hr = hr1;
    }
	RELEASE(pCap);
    return hr;
}
HRESULT CMultiVideoMixer::AddCaptureDeviceSource(LPCWSTR Devicename, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace,LPRECT rcDest,SourceConnectProc ConnectProc)
{
    CVMR9Subgraph *pSubgraph = NULL;

    HRESULT hr = S_OK;
	IBaseFilter* pCap = 0;
    if( !m_pWizard )
    {
        return VFW_E_WRONG_STATE;
    }

    try
    {
		

        pSubgraph = new CVMR9Subgraph;
        if( !pSubgraph )
        {
            throw E_OUTOFMEMORY;
        }
		CMediaHelper help;
		
		hr = help.GetVidCapDevice(Devicename,&pCap);
		if( FAILED(hr) || !pCap)
        {
            throw hr;
        }
		hr = pSubgraph->BuildAndRender(pCap,  VidType , Width, Height, nFPS,m_pWizard ,bUsingColorSpace ,ConnectProc);

        if( FAILED(hr))
        {
            throw hr;
        }

        //remember the ID, add to the list
        dwID = pSubgraph->GetID();

        m_sources.push_back( pSubgraph );
		if(rcDest)
		{
			hr = SourceSetPos( dwID, rcDest,0 );
			if( FAILED(hr))
			{
				throw hr;
			}
		}
    }
    catch( HRESULT hr1 )
    {
        if( pSubgraph )
        {
            delete pSubgraph;
        }
        hr = hr1;
    }
	RELEASE(pCap);
    return hr;
}
HRESULT CMultiVideoMixer::AddCaptureDeviceSource(UINT DeviceId, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace,LPRECT rcDest,SourceConnectProc ConnectProc)
{
    CVMR9Subgraph *pSubgraph = NULL;

    HRESULT hr = S_OK;
	IBaseFilter* pCap = 0;
    if( !m_pWizard )
    {
        return VFW_E_WRONG_STATE;
    }

    try
    {
        pSubgraph = new CVMR9Subgraph;
        if( !pSubgraph )
        {
            throw E_OUTOFMEMORY;
        }
		CMediaHelper help;
		
		hr = help.GetVidCapDevice(DeviceId,&pCap);
		if( FAILED(hr) || !pCap)
        {
            throw hr;
        }
		hr = pSubgraph->BuildAndRender(pCap,  VidType , Width, Height, nFPS,m_pWizard ,bUsingColorSpace ,ConnectProc);

        if( FAILED(hr))
        {
            throw hr;
        }

        //remember the ID, add to the list
        dwID = pSubgraph->GetID();

        m_sources.push_back( pSubgraph );
		if(rcDest)
		{
			hr = SourceSetPos( dwID, rcDest,0 );
			if( FAILED(hr))
			{
				throw hr;
			}
		}
    }
    catch( HRESULT hr1 )
    {
        if( pSubgraph )
        {
            delete pSubgraph;
        }
        hr = hr1;
    }
	RELEASE(pCap);
    return hr;
}

/******************************Public*Routine******************************\
* DeleteSource
*
* deletes a source from the list, detaches it from the wizard
\**************************************************************************/
HRESULT CMultiVideoMixer::DeleteSource( DWORD_PTR dwID )
{
    HRESULT hr = S_OK;

    CVMR9Subgraph *pSubgraph = NULL;

    try
    {
        if( !m_pWizard )
        {
            throw VFW_E_WRONG_STATE;
        }

        pSubgraph = GetSubgraph( dwID );
        if( !pSubgraph )
        {
            throw VFW_E_NOT_FOUND;
        }
		hr = pSubgraph->StopCapture();
        if( FAILED(hr))
        {
            throw hr;
        }
        hr = pSubgraph->Stop();
        if( FAILED(hr))
        {
            throw hr;
        }
		
        hr = m_pWizard->Detach( pSubgraph->GetID());
        if( FAILED(hr))
        {
            throw hr;
        }
        m_sources.remove( pSubgraph );

        delete pSubgraph;
        pSubgraph = NULL;
        hr = S_OK;
    }
    catch( HRESULT hr1 )
    {
        hr = hr1;
    }

    return hr;
}

HRESULT CMultiVideoMixer::InitCapture(LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName )
{
	HRESULT hr = S_OK;
	if(!m_pWizard) return E_INVALIDARG;
    IGraphBuilder*  pGb = 0;
	ICaptureGraphBuilder2 * pBuild = NULL;
	IBaseFilter* pStreamFt = NULL;
	IBaseFilter* pAudFt = NULL;
	IBaseFilter* pAudCom = NULL;//音频压缩
	IBaseFilter* pVidCom = NULL;//视频压缩
	IBaseFilter* pAviMux = NULL;
	IFileSinkFilter	*pSink  = NULL;//file
	IConfigAviMux *pConfigMux = NULL;
	IConfigInterleaving *pInterleave = NULL;
	CMediaHelper Helper;
	if(m_pCapGraph) 
	hr = TerminateCapture();
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
		//	audio device	--->	|-------|
		//
		///////////////////////////////////////////////////////////
		hr = m_pWizard->InitializeGlobalOutStream();
		if( FAILED(hr)) throw hr;
		hr = m_pWizard->GetGlobalOutStreamFilter(&pStreamFt);
		if( FAILED(hr)) throw hr;
		if(pStreamFt == 0) throw E_INVALIDARG;
		hr = m_pCapGraph->AddFilter( pStreamFt, L"OutFilter");
		if( FAILED(hr))throw hr;

		//create AVI MUX Filter

		hr = pBuild->SetOutputFileName(&MEDIASUBTYPE_Avi,lpPath, &pAviMux, &pSink); 
		if( FAILED(hr) || !pAviMux) throw hr;
		if(pszVidComName){//视频压缩
			hr = Helper.GetVidCompression(pszVidComName,&pVidCom);
			if( FAILED(hr) || !pVidCom) throw hr;
			hr = m_pCapGraph->AddFilter(pVidCom,L"VidCom");
			if( FAILED(hr) ) throw hr;
		}
		if(lpszAudDevice){//音频采集
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
		hr = pBuild->RenderStream(0, 0,pStreamFt,pVidCom,pAviMux);

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
	RELEASE(pInterleave);
	RELEASE(pAudFt);
	RELEASE(pAudCom );
	RELEASE(pVidCom );
	RELEASE(pAviMux );
	RELEASE(pSink);
	RELEASE(pConfigMux);

    return hr;

	
}
HRESULT CMultiVideoMixer::TerminateCapture()
{	
	CMediaHelper help;
	help.DestroyGraph(m_pCapGraph);
	RELEASE(m_pCapGraph);	
	RELEASE(m_pCapMc);	
	if(m_pWizard)m_pWizard->TerminateGlobalOutStream();
	return S_OK;
}
//录像
HRESULT  CMultiVideoMixer::StartCapture()
{
	HRESULT hr = S_OK;

    if( !m_pCapMc ) {
        return E_UNEXPECTED;
    }
    hr = m_pCapMc->Run();
    return hr;
}
//停止录像
HRESULT  CMultiVideoMixer::StopCapture()
{
	HRESULT hr = S_OK;

    if( !m_pCapMc ) {
        return S_OK;
    }
	hr = m_pCapMc->Stop();
    return hr;
}
HRESULT CMultiVideoMixer::ClearSource()
{
	HRESULT hr = S_OK;
	list<CVMR9Subgraph*>::iterator it;
	CVMR9Subgraph* pSubgraph = NULL;
	while( false == m_sources.empty())
    {
        it = m_sources.begin();
        pSubgraph = (CVMR9Subgraph*)(*it);
        ASSERT( pSubgraph );

        hr = DeleteSource( pSubgraph->GetID());
        if( FAILED(hr))
            return  hr;
    }

     return  hr;
}
/******************************Public*Routine******************************\
* Terminate
*
* terminates wizard
\**************************************************************************/
HRESULT CMultiVideoMixer::Terminate()
{
	//return S_OK;
    HRESULT hr = S_OK;
    list<CVMR9Subgraph*>::iterator it;

    CVMR9Subgraph* pSubgraph = NULL;

    try
    {
        // 1. Detach all the existing subgraphs
        while( false == m_sources.empty())
        {
            it = m_sources.begin();
            pSubgraph = (CVMR9Subgraph*)(*it);
            ASSERT( pSubgraph );

            hr = DeleteSource( pSubgraph->GetID());
            if( FAILED(hr))
                throw hr;
        }

        // 2. Terminate Wizard, if there is any
       if( m_pWizard )
        {
            hr = m_pWizard->Terminate();
            if( FAILED(hr))
                throw hr;

        }

        // 3. Destroy video window
        if( IsWindow( m_hwndVideo ))
        {
            ::DestroyWindow( m_hwndVideo );
            m_hwndVideo = NULL;
        }

       // UnregisterClass( g_achVideoWindowClass, g_hInstance);
    }
    catch( HRESULT hr1)
    {
        hr = hr1;
    }
	RELEASE( m_pWizard );
    RELEASE( m_pRenderEngine );
    RELEASE( m_pMixerControl );
    RELEASE( m_pUILayer );
	RELEASE( m_pCapGraph );
	RELEASE( m_pCapMc );
    return hr;

}
/******************************Public*Routine******************************\
* GetData
*
* 全局抓图
\**************************************************************************/
HRESULT CMultiVideoMixer::GetData(CSurfaceBuff** ppBuff)
{
	//从显存复制纹理,在转化为DIB
	HRESULT hr = E_FAIL;
	IDirect3DSurface9*	pTempSurface		= NULL;
	IDirect3DDevice9*	pSampleDevice       = NULL;
	D3DSURFACE_DESC				dest ;
	ZeroMemory(&dest,sizeof(D3DSURFACE_DESC));
	if(!m_pRenderEngine)return E_FAIL;
	try
    {
		hr = m_pRenderEngine->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&pTempSurface,TRUE);
		if( FAILED(hr)||! pTempSurface)			throw hr;

		if(ppBuff)
		{
			*ppBuff  = new CSurfaceBuff(pTempSurface);
			if(FAILED(hr))								throw hr;
		}
	}
	catch( HRESULT hr1 )
    {
        hr = hr1;
    }
	RELEASE(pTempSurface);
	RELEASE(pSampleDevice);
	return hr;
	
}
/******************************Public*Routine******************************\
* SetTransformProc
*
* 全局逐帧回调
\**************************************************************************/
HRESULT CMultiVideoMixer::SetTransformProc(TransformProc pProc,TransformProc* pOldProc)
{
	return m_pWizard->SetGlobalTransformProc(pProc,pOldProc);
}
HRESULT CMultiVideoMixer::GetTransformProc(TransformProc * pProc)
{
	return m_pWizard->GetGlobalTransformProc(pProc);
}
/******************************Public*Routine******************************\
* GetSubgraph
*
* find subgraph in the list by dwID
\**************************************************************************/
CVMR9Subgraph* CMultiVideoMixer::GetSubgraph(  DWORD_PTR dwID  )
{
    CVMR9Subgraph* pSubgraph = NULL;
    list<CVMR9Subgraph*>::iterator start, end, it;

    start = m_sources.begin();
    end = m_sources.end();

    for(it = start; it!= end; it++)
    {
        if( (*it) && (*it)->GetID() == dwID )
        {
            pSubgraph = (CVMR9Subgraph*)(*it);
            break;
        }
    }
    return pSubgraph;
}

/******************************Public*Routine******************************\
* GetWizard
*
\**************************************************************************/
IMultiVMR9Wizard* CMultiVideoMixer::GetWizard( )
{
    IMultiVMR9Wizard* pRes = NULL;
    if( m_pWizard )
    {
        pRes = m_pWizard;
        pRes->AddRef();
    }
    return pRes;
}

/******************************Public*Routine******************************\
* GetRenderEngine
*
\**************************************************************************/
IMultiVMR9RenderEngine* CMultiVideoMixer::GetRenderEngine( )
{
    IMultiVMR9RenderEngine* pRes = NULL;
    if( m_pRenderEngine )
    {
        pRes = m_pRenderEngine;
        pRes->AddRef();
    }
    return pRes;
}

/******************************Public*Routine******************************\
* GetMixerControl
*
\**************************************************************************/
IMultiVMR9MixerControl* CMultiVideoMixer::GetMixerControl( )
{
    IMultiVMR9MixerControl* pRes = NULL;
    if( m_pMixerControl )
    {
        pRes = m_pMixerControl;
        pRes->AddRef();
    }
    return pRes;
}

/******************************Public*Routine******************************\
* GetUILayer
*
\**************************************************************************/
IMultiVMR9UILayer* CMultiVideoMixer::GetUILayer( )
{
    IMultiVMR9UILayer* pRes = NULL;
    if( m_pUILayer )
    {
        pRes = m_pUILayer;
        pRes->AddRef();
    }
    return pRes;
}
//得到源数目
HRESULT CMultiVideoMixer:: GetSourceNum(int * num)
{
	if(!num)return E_POINTER;
	*num = (int)m_sources.size();
	return S_OK;
}
	//得到显示窗口
HRESULT CMultiVideoMixer:: GetWindow(HWND *hWnd)
{
	if(!hWnd)return E_POINTER;
	*hWnd = m_hwndVideo;
	return S_OK;
}
//设置刷新帧率(显示窗口的帧率,并非源的帧率)
HRESULT CMultiVideoMixer::SetFrameRate( int nFPS)
{
	int nRes = 0;

    if( !m_pRenderEngine )
        return E_FAIL;
	HRESULT hr  = m_pRenderEngine->SetFrameRate( nFPS );
    return hr;
}
//得到平均刷新率
HRESULT CMultiVideoMixer::GetFrameRateAvg(int * nFPS)
{
	if(!nFPS)return E_POINTER;
	if(!m_pRenderEngine ){ *nFPS = 30 ;return S_OK;}
    HRESULT hr = m_pRenderEngine->GetFrameRateAvg( nFPS );
    return hr;
}
//得到刷新帧率(显示窗口的帧率,并非源的帧率)
/******************************Public*Routine******************************\
* GetFrameRate
*
\**************************************************************************/
HRESULT CMultiVideoMixer::GetFrameRate(int * nFPS)
{
    if(!nFPS) return E_POINTER;
	if(!m_pRenderEngine ){ *nFPS = 30 ;return S_OK;}
    HRESULT hr = m_pRenderEngine->GetFrameRate( nFPS );
    return hr;
}

/******************************Public*Routine******************************\
* SetColor
*
\**************************************************************************/
HRESULT CMultiVideoMixer::SetBkColor( COLORREF color )
{
    HRESULT hr = S_OK;
    if( !m_pMixerControl )
        return E_FAIL;
    hr = m_pMixerControl->SetBackgroundColor( color );
    return hr;
}
HRESULT CMultiVideoMixer::GetBkColor( COLORREF * color )
{
  
	if(!color)return E_POINTER;
	HRESULT hr = S_OK;
    if( !m_pMixerControl )
        return E_FAIL;
    hr = m_pMixerControl->GetBackgroundColor( color );
    return hr;
}
HRESULT CMultiVideoMixer::SourceSetTransformProc(DWORD_PTR dwID,TransformProc pProc,TransformProc* pOldProc)
{
	return m_pWizard->SetSrcTransformProc(dwID,pProc,pOldProc);
}
HRESULT CMultiVideoMixer::SourceGetTransformProc(DWORD_PTR dwID,TransformProc * pProc)
{
	return m_pWizard->GetSrcTransformProc(dwID,pProc);
}
HRESULT CMultiVideoMixer::SourceGetData(DWORD_PTR dwID,CSurfaceBuff** ppBuff)
{
	//从显存复制纹理,在转化为DIB
	HRESULT hr = E_FAIL;
	IDirect3DSurface9*	pTexturePrivSurf	= NULL ;
	IDirect3DTexture9*  pTexture			= NULL;
	IDirect3DSurface9*	pTempSurface		= NULL;
	IDirect3DDevice9*	pSampleDevice       = NULL;
	D3DSURFACE_DESC				dest;
	try
    {
		hr = m_pWizard->GetTexture(dwID,&pTexture);
		if( FAILED(hr)||!pTexture )					throw  hr;
		hr = pTexture->GetSurfaceLevel(0,&pTexturePrivSurf);
		if( FAILED(hr)||! pTexturePrivSurf)			throw hr;
		hr = pTexturePrivSurf->GetDevice(&pSampleDevice);
		if( FAILED(hr)||! pSampleDevice)			throw hr;
		hr = pTexturePrivSurf->GetDesc(&dest);
		if(FAILED(hr))								throw hr;
		hr = pSampleDevice->CreateOffscreenPlainSurface(
				dest.Width,
				dest.Height,
				dest.Format,
				D3DPOOL_SYSTEMMEM,
				&pTempSurface,0);
		if(FAILED(hr)||!pTempSurface)				throw hr;
		hr = pSampleDevice->GetRenderTargetData(pTexturePrivSurf,pTempSurface);
		if(FAILED(hr))								throw hr;
		if(ppBuff)
		{
			*ppBuff  = new CSurfaceBuff(pTempSurface);
			if(FAILED(hr))								throw hr;
		}
	}
	catch( HRESULT hr1 )
    {
        hr = hr1;
    }
	RELEASE(pTexturePrivSurf);
	RELEASE(pTexture);
	RELEASE(pTempSurface);
	RELEASE(pSampleDevice);
	return hr;
}
//增加采集设备
HRESULT CMultiVideoMixer::SourceInitCapture(DWORD_PTR dwID,LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName )
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr && m_pWizard) hr = pSr->AddCaptureFilter(lpPath,pszVidComName, lpszAudDevice,pszAudComName,m_pWizard);
	return hr;
}
//删除采集设备
HRESULT CMultiVideoMixer::SourceTerminateCapture(DWORD_PTR dwID)
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr ) hr = pSr->DelCaptureFilter();
	return hr;
}
//录像
HRESULT CMultiVideoMixer::SourceStartCapture(DWORD_PTR dwID )
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr ) hr = pSr->StartCapture();
	return hr;
}
//停止录像
HRESULT CMultiVideoMixer::SourceStopCapture(DWORD_PTR dwID )
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr ) hr = pSr->StopCapture();
	return hr;
}
HRESULT CMultiVideoMixer::SourceRun(  DWORD_PTR dwID )
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr ) hr = pSr->Run();
	return hr;

}
HRESULT  CMultiVideoMixer:: SourceStopWhenReady(DWORD_PTR dwID)
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr ) hr = pSr->StopWhenReady();
	return hr;
}
HRESULT CMultiVideoMixer::SourceStop( DWORD_PTR dwID)
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr ) hr = pSr->Stop();
	return hr;
}
HRESULT CMultiVideoMixer::SourceStopAt( DWORD_PTR dwID,LONGLONG llDur)
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	LONGLONG rtNow = 0;
	if( pSr ) 
		hr = pSr->StopAt(llDur);
	return hr;
	
}
HRESULT CMultiVideoMixer::SourcePause( DWORD_PTR dwID)
{
	HRESULT hr = E_FAIL;
	CVMR9Subgraph *pSr  =  GetSubgraph( dwID);
	if( pSr ) hr = pSr->Pause();
	return hr;
}
HRESULT CMultiVideoMixer::SourceSetTimeFormat(DWORD_PTR dwID,const GUID *pFormat)
{
	HRESULT hr = E_FAIL;
    CVMR9Subgraph *pSrc = NULL;
    pSrc = GetSubgraph( dwID);
    if( !pSrc )
        return hr;
	hr = pSrc->SetTimeFormat(pFormat);
	return hr;
}
HRESULT CMultiVideoMixer::SourceGetTimeFormat(DWORD_PTR dwID, GUID *pFormat)
{
	HRESULT hr = E_FAIL;
    CVMR9Subgraph *pSrc = NULL;
    pSrc = GetSubgraph( dwID);
    if( !pSrc )
        return hr;
	hr = pSrc->GetTimeFormat(pFormat);
	return hr;
}
HRESULT CMultiVideoMixer::SourceGetTimes( DWORD_PTR dwID,LONGLONG & llCur,LONGLONG& llDur)
{
	HRESULT hr = E_FAIL;
    CVMR9Subgraph *pSrc = NULL;
    pSrc = GetSubgraph( dwID);
    if( !pSrc )
        return hr;
    hr = pSrc->GetTimes( llCur ,llDur);
	
   return hr;
}
HRESULT CMultiVideoMixer::SourceGetVideoLen( DWORD_PTR dwID,LONGLONG &llLen)
{
	HRESULT hr = E_FAIL;
    CVMR9Subgraph *pSrc = NULL;
    pSrc = GetSubgraph( dwID);
    if( !pSrc )
        return hr;
	hr = pSrc->GetVideoLen( llLen);
	
       return hr;

}
HRESULT CMultiVideoMixer::SourceSeekto(DWORD_PTR dwID,LONGLONG llCur)
{
	HRESULT hr = E_FAIL;
    CVMR9Subgraph *pSrc = NULL;
    pSrc = GetSubgraph( dwID);
    if( !pSrc )
        return hr;
    hr = pSrc->SetTime( llCur );

   return hr;
}
HRESULT CMultiVideoMixer::SourceShow( DWORD_PTR dwID ,BOOL bVisible)
{
	HRESULT hr = S_OK;
	IMultiVMR9MixerControl* pMixer = 0;
	pMixer = GetMixerControl();
    if( !pMixer )
        return E_FAIL;
	hr = pMixer->Show(dwID,bVisible);
	RELEASE(pMixer);
	return hr;
}
HRESULT CMultiVideoMixer::SourceGetIdealOutputRect( DWORD_PTR dwID ,LPRECT lprc)//得到理想输出大小
{
	HRESULT hr = E_FAIL;
    NORMALIZEDRECT nr;
    int nItem = -1;
    RECT rc;
 
    if( !IsWindow( m_hwndVideo ))
        return E_FAIL;
    ::GetClientRect( m_hwndVideo, &rc);
    hr = m_pMixerControl->GetIdealOutputRect( dwID, rc.right, rc.bottom, &nr);
	lprc->bottom = LONG(float(rc.bottom - rc.top )*nr.bottom);
	lprc->top	 = LONG(float(rc.bottom - rc.top )*nr.top);
	lprc->left = LONG(float(rc.right - rc.left )*nr.left);
	lprc->right = LONG(float(rc.right - rc.left )*nr.right);
	return hr;

}
HRESULT CMultiVideoMixer::SourceGetVideoSize( DWORD_PTR dwID ,long *width,long *height)//得到视频输出实际大小
{
	return  m_pWizard->GetVideoSize(dwID,width,height);
}
HRESULT CMultiVideoMixer::SourceGetPos( DWORD_PTR dwID ,LPRECT lprc,int* z)
{ 
	HRESULT hr = S_OK;
	CVMR9Subgraph *pSrc = NULL;
	IMultiVMR9MixerControl* pMixer = 0;
	NORMALIZEDRECT nr;ZeroMemory(&nr,sizeof(NORMALIZEDRECT));
    NORMALIZEDRECT nrI;ZeroMemory(&nrI,sizeof(NORMALIZEDRECT));
    RECT rc;
  
    pSrc = GetSubgraph( dwID );
    if( !pSrc )
        return E_FAIL;

    pMixer = GetMixerControl();
    if( !pMixer )
        return E_FAIL;

 
    if( !IsWindow( m_hwndVideo ))
	{
		RELEASE(pMixer)
        return E_FAIL;
	}
	if(lprc)
	{
		::GetClientRect( m_hwndVideo, &rc);
		hr =pMixer->GetOutputRect( dwID, &nr);
		lprc->left = LONG(((float)rc.right - (float)rc.left)*nr.left);
		lprc->right = LONG(((float)rc.right - (float)rc.left)*nr.right);
		lprc->top = LONG(((float)rc.bottom - (float)rc.top)*nr.top);
		lprc->bottom = LONG(((float)rc.bottom - (float)rc.top)*nr.bottom);
	}
	if(z)
	{
		DWORD pZ=0;
		hr = pMixer->GetZOrder( dwID, &pZ);
		*z = pZ;
	}
	RELEASE(pMixer)
	return hr;
}
HRESULT CMultiVideoMixer::SourceSetPos( DWORD_PTR dwID ,int x,int y,int cx,int cy,int z)
{
	HRESULT hr = S_OK;
   
    CVMR9Subgraph *pSrc = NULL;
  
    IMultiVMR9MixerControl* pMixer = 0;;
    NORMALIZEDRECT nr;ZeroMemory(&nr,sizeof(NORMALIZEDRECT));
    NORMALIZEDRECT nrI;ZeroMemory(&nrI,sizeof(NORMALIZEDRECT));
    RECT rc;
  
    pSrc = GetSubgraph( dwID );
    if( !pSrc )
        return E_FAIL;

    pMixer = GetMixerControl();
    if( !pMixer )
        return E_FAIL;

 
    if( !IsWindow( m_hwndVideo ))
	{
		RELEASE(pMixer)
        return E_FAIL;
	}

    ::GetClientRect( m_hwndVideo, &rc);

	nr.left   = (float)x /((float)rc.right - (float)rc.left);
    nr.right  = (float)(x+cx) /((float)rc.right - (float)rc.left);
	nr.top    = (float)y /((float)rc.bottom - (float)rc.top);
    nr.bottom = (float)(y+cy) /((float)rc.bottom - (float)rc.top);
	hr = pMixer->SetOutputRect( dwID, &nr);
	if(FAILED(hr)) {RELEASE(pMixer);return hr;}
	pMixer->SetZOrder( dwID, z);
	RELEASE(pMixer);
	return hr;

}
HRESULT CMultiVideoMixer::SourceSetPos( DWORD_PTR dwID ,LPRECT lprc,int z)
{ 
	HRESULT hr = SourceSetPos(dwID,lprc->left,lprc->top,lprc->right - lprc->left , lprc->bottom - lprc->top,z);
	
	return hr;
}
HRESULT CMultiVideoMixer::SourceSetAlphaValue( DWORD_PTR dwID ,BYTE AlphaValue)
{ 
	HRESULT hr = S_OK;
	IMultiVMR9MixerControl* pMixer = 0;
	 pMixer = GetMixerControl();
    if( !pMixer )
        return E_FAIL;
	float alpha = (float)AlphaValue/255;
	hr = pMixer->SetAlpha(dwID,alpha);
	RELEASE(pMixer);
	return hr;
}
HRESULT CMultiVideoMixer::SourceGetAlphaValue( DWORD_PTR dwID ,BYTE *AlphaValue)
{ 
	HRESULT hr = S_OK;
	IMultiVMR9MixerControl* pMixer = 0;
	 pMixer = GetMixerControl();
    if( !pMixer )
        return E_FAIL;
	float alpha = 0;
	hr = pMixer->GetAlpha(dwID,&alpha);
	*AlphaValue = BYTE(alpha * 255.0);
	RELEASE(pMixer);
	return hr;
}
/******************************Public*Routine******************************\
* LoopSources
*
* go through the list and reset time to start if movie is close to the end
\**************************************************************************/
HRESULT CMultiVideoMixer::LoopSources()
{
    CVMR9Subgraph *pSource = NULL;
    LONGLONG llCur;
    LONGLONG llDur;

    list<CVMR9Subgraph*>::iterator start, end, it;
    start = m_sources.begin();
    end = m_sources.end();

    for( it = start; it != end; it++)
    {
        pSource = (CVMR9Subgraph*)(*it);
        if( !pSource )
            continue;
		if(pSource->m_GraphType == Image_DIB) continue;
        pSource->GetTimes( llCur, llDur);
        // 100ms
        if( llDur - llCur < 1000000L )
        {
            pSource->SetTime( 0L );
			return  S_OK;
        }
    }
	return S_FALSE;
}
HRESULT CMultiVideoMixer::UpdateImmediatly()
{
	 if( ! m_pRenderEngine )
        return E_FAIL;
	 return m_pRenderEngine->RenderNow(FALSE);
}

