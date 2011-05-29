//------------------------------------------------------------------------------
// File: Wizard.h
//
// Desc: DirectShow sample code - Declaration of the CMultiVMR9Wizard
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#pragma once
#include "resource.h"       // main symbols
#include "MultiVMR9.h"

#pragma warning(push, 2)
#include <list>
using namespace std;
#pragma warning(pop)

//const LONGLONG MILLISECONDS = (1000);            // 10 ^ 3
//const LONGLONG NANOSECONDS = (1000000000);       // 10 ^ 9
//const LONGLONG UNITS = (NANOSECONDS / 100);      // 10 ^ 7

/**************************************************************************\
* class CMultiVMR9Wizard
* 
* Objects exposing this interface are responsible for management of several VMRs 
* in a single rendering environment. Interface implementation of this object contains 
* reference to the render engine (IMultiVMR9RenderEngine). Upon initialization, 
* this object creates a separate thread for rendering composed video asynchronously 
* from attached subgraphs
\**************************************************************************/
class CMultiVMR9Wizard : 
    public CUnknown,
    public IMultiVMR9Wizard,
    public IVMRSurfaceAllocator9,
    public IVMRImagePresenter9
{
public:

    CMultiVMR9Wizard(LPUNKNOWN pUnk, HRESULT *phr);
    virtual ~CMultiVMR9Wizard();
	
    // IUnknown implementation
    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void**);
    static CUnknown *CreateInstance(LPUNKNOWN, HRESULT *);

    // IMultiVMR9Wizard implementation
    STDMETHOD(Initialize)(
        DWORD dwFlags,
        HWND hWnd,
        IMultiVMR9RenderEngine *pRenderEngine
		,D3DFORMAT format
		,BOOL BufferInSystemMEM
        );
	STDMETHOD(InitializeEx)(
        DWORD dwFlags,
        HWND hWnd,
		HWND hWndCpy,
        IMultiVMR9RenderEngine *pRenderEngine
		,D3DFORMAT format
		,BOOL BufferInSystemMEM
        );

        // terminate wizard
    STDMETHOD(Terminate)(
        );


    STDMETHOD(Attach)(
        IBaseFilter* pVMRFilter, 
		D3DFORMAT format,
		DWORD_PTR* pdwID
        );

    STDMETHOD(Detach)(
        DWORD_PTR dwID
        );

    STDMETHOD(VerifyID)(
        DWORD_PTR dwID
        );

    STDMETHOD(GetGraph)(
        DWORD_PTR dwID, 
        IFilterGraph** ppGraph
        );

    STDMETHOD(GetRenderEngine)(
        IMultiVMR9RenderEngine** pRenderEngine
        );

    STDMETHOD(GetMixerControl)(
        IMultiVMR9MixerControl** ppMixerControl
        );

    STDMETHOD(GetTexture)(
        DWORD_PTR dwID,
        LPDIRECT3DTEXTURE9* ppTexture 
        );

    STDMETHOD(GetVideoSize)(
        DWORD_PTR dwID,
        LONG* plWidth,
        LONG* plHeight
        );

    // IVMRSurfaceAllocator9 implementation
    STDMETHOD(AdviseNotify)(
        IVMRSurfaceAllocatorNotify9*  lpIVMRSurfAllocNotify
        );

    STDMETHOD(GetSurface)(
        DWORD_PTR  dwUserID,
        DWORD  SurfaceIndex,
        DWORD  SurfaceFlags,
        IDirect3DSurface9**  lplpSurface
        );

    STDMETHOD(InitializeDevice)(
        DWORD_PTR  dwUserID,
        VMR9AllocationInfo*  lpAllocInfo,
        DWORD*  lpNumBuffers
        );

    STDMETHOD(TerminateDevice)(
        DWORD_PTR  dwID
        );

    // IVMRImagePresenter9 implementation
    STDMETHOD(StartPresenting)(
        DWORD_PTR  dwUserID
        );

    STDMETHOD(StopPresenting)(
        DWORD_PTR  dwUserID
        );

    STDMETHOD(PresentImage)(
        DWORD_PTR  dwUserID,
        VMR9PresentationInfo*  lpPresInfo
        );
	//独立帧内处理
	STDMETHOD( SetSrcTransformProc)(
		DWORD_PTR dwID,
		TransformProc pProc,
		TransformProc*	pOldProc
		);
	STDMETHOD( GetSrcTransformProc)(
		DWORD_PTR dwID,
		TransformProc* pProc
		);
	//全局帧内处理
	STDMETHOD( SetGlobalTransformProc)(
		TransformProc pProc,
		TransformProc*	pOldProc
		);
	STDMETHOD( GetGlobalTransformProc)(
		TransformProc* pProc
		);
	//初始化输出流
	STDMETHOD( InitializeOutStream)(
		DWORD_PTR  dwUserID
		);
	//结束输出流
	STDMETHOD( TerminateOutStream)(
		DWORD_PTR  dwUserID
		);
	//得到输出filter
	STDMETHOD( GetOutStreamFilter)(
		DWORD_PTR  dwUserID,
		IBaseFilter** ppFilter
		);
	//得到输出pin
	STDMETHOD( GetOutStreamPin)(
		DWORD_PTR  dwUserID,
		IPin ** ppPin
		);
	//初始化输出流(全局图像)
	STDMETHOD( InitializeGlobalOutStream)(
		
		);
	//结束输出流(全局图像)
	STDMETHOD( TerminateGlobalOutStream)(
	
		);
	//得到输出filter(全局图像)
	STDMETHOD( GetGlobalOutStreamFilter)(
	
		IBaseFilter** ppFilter
		);
	//得到输出pin(全局图像)
	STDMETHOD( GetGlobalOutStreamPin)(
	
		IPin ** ppPin
		);
	STDMETHOD(Transform)(
		IDirect3DSurface9*  
		pTexturePrivSurf
		,REFERENCE_TIME  rtStart
		, REFERENCE_TIME  rtEnd
		);
	STDMETHOD( StreamOut)(
		IDirect3DSurface9 * pSurface,
		REFERENCE_TIME  rtStart, 
		REFERENCE_TIME  rtEnd
	);
	STDMETHOD( ScrVisible)(
		DWORD_PTR  dwUserID,
		BOOL bVisible
		);
    // Private classes
private:

	
    class MultiVMR9_VideoSource
    {
    public:
        MultiVMR9_VideoSource();
        ~MultiVMR9_VideoSource();
		HRESULT  StreamOut(IDirect3DSurface9 * pSurface,REFERENCE_TIME  rtStart, REFERENCE_TIME  rtEnd);
        // methods 
        void DeleteSurfaces();
        HRESULT DisconnectPins();
        HRESULT AllocateSurfaceBuffer( DWORD dwN );
        HRESULT SetVideoSize(   LONG lImageW, 
                                LONG lImageH );
		HRESULT Transform(IDirect3DSurface9*  pTexturePrivSurf,REFERENCE_TIME  rtStart, REFERENCE_TIME  rtEnd);//D3DXLoadSurfaceFromSurface
		TransformProc SetTransformProc(TransformProc pProc);
		TransformProc GetTransformProc(){return pTransformProc;}
		HRESULT CreateOutStream();//构造输出流filter
		HRESULT DeleteOutStream();//结束输出流filter
        // data
        // we use this tag to verify that (MultiVMR9_VideoSource*)(void*)pVideoSource
        // is really MultiVMR9_VideoSource
        DWORD_PTR dwTag;
        DWORD_PTR dwID; 
        DWORD dwNumBuf;
        DWORD dwNumBufActuallyAllocated;
		IBaseFilter * pSrcFt;
		IPin		* pOutP;
		//IMediaSeeking*  pMs;	// media seeking

        LONG lImageWidth;
        LONG lImageHeight;
		BOOL bInit;
		BOOL bVisible;
		
		
        LPDIRECT3DTEXTURE9 pTexturePriv;
		//IDirect3DSurface9 *pTempSurface;
        IDirect3DSurface9 **ppSurface;
        IFilterGraph *pGraph;
        IVMRSurfaceAllocatorNotify9 *pDefaultNotify;
        IBaseFilter *pVMR;
		TransformProc  pTransformProc;	//纹理处理函数指针,用于逐帧回调
		REFERENCE_TIME m_rtFrameLength ;
		REFERENCE_TIME m_rtStartTime ;
		//REFERENCE_TIME m_rtLastStart;
		CCritSec                m_ObjectLock; 

    };

    typedef enum RenderThreadStatus
    {
        eNotStarted = 0x0,
        eRunning,
        eWaitingToStop,
        eFinished,
    } RenderThreadStatus;

    // Private methods
private:
	//LONGLONG m_llFrameNumber;
    HRESULT StartRenderingThread_();
    HRESULT StopRenderingThread_();
	HRESULT StartStreamOutThread_();
	HRESULT StopStreamOutThread_();
    void Clean_();
 
    HRESULT GetSourceInfo_(DWORD_PTR dwID, MultiVMR9_VideoSource** ppsource );
	
    static DWORD WINAPI RenderThreadProc_( LPVOID lpParameter );
	static DWORD WINAPI StreamOutThreadProc_( LPVOID lpParameter );

    // Private data
private:

	D3DFORMAT m_RenderFormat;        //最终显示颜色空间
	D3DFORMAT m_ScrFormat;	         //源颜色空间
	IBaseFilter * pSrcFt;
	IPin		* pOutP;
	TransformProc					m_pTransformProc;	//纹理处理函数指针,用于逐帧回调
    HWND                            m_hWnd;             // video window
    CCritSec                        m_ObjectLock;       // this object has to be thread-safe
    BOOL                            m_bInitialized;     // true if Initialize() was called and succeeded
    RenderThreadStatus              m_RenderThreadStatus; // 0: not started, 1: running, 2: requested to stop, 3: stopped
	RenderThreadStatus				m_StreamOutThreadStatus;
    DWORD                           m_dwConfigFlags;    // configuration flags
	list<CMediaSample*>				m_listMediaSamples;
    IMultiVMR9RenderEngine*         m_pRenderEngine;    // render engine
    IVMRSurfaceAllocatorNotify9*    m_pNotify;          // see DirecX docs, "Applications use this interface to 
                                // set a custom allocator-presenter and the allocator-presenter uses this interface 
                                // to inform the VMR of changes to the system environment that affect the Direct3D surfaces.
	BOOL m_bBufferInSystemMEM;
    list<MultiVMR9_VideoSource*>    m_listVideoSources;
	REFERENCE_TIME m_rtFrameLength ;
	REFERENCE_TIME m_rtStartTime ;
	DWORD m_dwFroptFrames;
	//REFERENCE_TIME m_rtLastStart;
public:
};

// class factory
extern long g_CountWizard;

class CCFMultiVMR9Wizard : public IClassFactory
{
public:
    // Constructor
    CCFMultiVMR9Wizard() : m_RefCount(1) {} 

    // IUnknown methods
    STDMETHOD(QueryInterface)(REFIID riid, void ** ppv)
    {
        if (IID_IUnknown == riid)
            *ppv = static_cast<IUnknown *>(this);
        else if (IID_IClassFactory == riid)
            *ppv = static_cast<IClassFactory *>(this);
        else
        {
            *ppv = NULL;
            return E_NOINTERFACE;
        }
        static_cast<IUnknown *>(*ppv)->AddRef();
        return S_OK;
    }

    STDMETHOD_(ULONG, AddRef())
    {
        return InterlockedIncrement(&m_RefCount);
    }

    STDMETHOD_(ULONG, Release())
    {
        LONG ref = InterlockedDecrement(&m_RefCount);
        if (0 == ref)
        {
            delete this;
        }
        return ref;
    }

    // IClassFactory methods
    STDMETHOD(CreateInstance)(IUnknown * punkOuter, REFIID riid, void ** ppvObject)
    {
        HRESULT hr = S_OK;
        if (NULL == ppvObject)
            return E_POINTER;

        *ppvObject = NULL; // initialize the pointer
        // we don't support aggregation
        if (NULL != punkOuter)
            return CLASS_E_NOAGGREGATION;

        // create a new Wizard object
        CMultiVMR9Wizard * pWizard = new CMultiVMR9Wizard(punkOuter, &hr);
        if (NULL == pWizard)
            return E_OUTOFMEMORY;

        // now QI for the requested interface.  If this fails, delete the object
        hr = pWizard->QueryInterface(riid, ppvObject);
        if (FAILED(hr))
            delete pWizard;

        return hr;
    }

    STDMETHOD(LockServer)(BOOL fLock)
    {
        if (fLock)
            InterlockedIncrement(&g_CountWizard);
        else
            InterlockedDecrement(&g_CountWizard);
        return S_OK;
    }

private:
    LONG m_RefCount;
};

