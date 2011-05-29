

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat May 28 17:06:51 2011
 */
/* Compiler settings for MultiVMR9.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MultiVMR9_h__
#define __MultiVMR9_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMultiVMR9Wizard_FWD_DEFINED__
#define __IMultiVMR9Wizard_FWD_DEFINED__
typedef interface IMultiVMR9Wizard IMultiVMR9Wizard;
#endif 	/* __IMultiVMR9Wizard_FWD_DEFINED__ */


#ifndef __IMultiVMR9RenderEngine_FWD_DEFINED__
#define __IMultiVMR9RenderEngine_FWD_DEFINED__
typedef interface IMultiVMR9RenderEngine IMultiVMR9RenderEngine;
#endif 	/* __IMultiVMR9RenderEngine_FWD_DEFINED__ */


#ifndef __IMultiVMR9UILayer_FWD_DEFINED__
#define __IMultiVMR9UILayer_FWD_DEFINED__
typedef interface IMultiVMR9UILayer IMultiVMR9UILayer;
#endif 	/* __IMultiVMR9UILayer_FWD_DEFINED__ */


#ifndef __IMultiVMR9MixerControl_FWD_DEFINED__
#define __IMultiVMR9MixerControl_FWD_DEFINED__
typedef interface IMultiVMR9MixerControl IMultiVMR9MixerControl;
#endif 	/* __IMultiVMR9MixerControl_FWD_DEFINED__ */


#ifndef __INullInPlace_FWD_DEFINED__
#define __INullInPlace_FWD_DEFINED__
typedef interface INullInPlace INullInPlace;
#endif 	/* __INullInPlace_FWD_DEFINED__ */


#ifndef __MultiVMR9Wizard_FWD_DEFINED__
#define __MultiVMR9Wizard_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiVMR9Wizard MultiVMR9Wizard;
#else
typedef struct MultiVMR9Wizard MultiVMR9Wizard;
#endif /* __cplusplus */

#endif 	/* __MultiVMR9Wizard_FWD_DEFINED__ */


#ifndef __MultiVMR9RenderEngine_FWD_DEFINED__
#define __MultiVMR9RenderEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiVMR9RenderEngine MultiVMR9RenderEngine;
#else
typedef struct MultiVMR9RenderEngine MultiVMR9RenderEngine;
#endif /* __cplusplus */

#endif 	/* __MultiVMR9RenderEngine_FWD_DEFINED__ */


#ifndef __MultiVMR9UILayer_FWD_DEFINED__
#define __MultiVMR9UILayer_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiVMR9UILayer MultiVMR9UILayer;
#else
typedef struct MultiVMR9UILayer MultiVMR9UILayer;
#endif /* __cplusplus */

#endif 	/* __MultiVMR9UILayer_FWD_DEFINED__ */


#ifndef __MultiVMR9MixerControl_FWD_DEFINED__
#define __MultiVMR9MixerControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class MultiVMR9MixerControl MultiVMR9MixerControl;
#else
typedef struct MultiVMR9MixerControl MultiVMR9MixerControl;
#endif /* __cplusplus */

#endif 	/* __MultiVMR9MixerControl_FWD_DEFINED__ */


#ifndef __NullInPlace_FWD_DEFINED__
#define __NullInPlace_FWD_DEFINED__

#ifdef __cplusplus
typedef class NullInPlace NullInPlace;
#else
typedef struct NullInPlace NullInPlace;
#endif /* __cplusplus */

#endif 	/* __NullInPlace_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_MultiVMR9_0000_0000 */
/* [local] */ 

#if 0
typedef LPVOID *IBaseFilter;

typedef LPVOID *IPin;

typedef LPVOID *IFilterGraph;

typedef LPVOID *LPDIRECT3DTEXTURE9;

typedef LPVOID *IDirect3DDevice9;

typedef LPVOID *IVMRSurfaceAllocator9;

typedef LPVOID *IDirect3DSurface9;

typedef LPVOID *D3DBACKBUFFER_TYPE;

typedef LPVOID *IVMRImagePresenter9;

typedef LPVOID *IVMRSurfaceAllocatorNotify;

typedef LPVOID *IMediaSample;

typedef LPVOID *VMR9AllocationInfo;

typedef LPVOID *TransformProc;

typedef LPVOID *D3DFORMAT;

typedef LPVOID *REFERENCE_TIME;

typedef LPVOID *CCritSec;

typedef DWORD DWORD_PTR;

#endif
#include <d3d9.h>
#include <dshow.h>
#include <vmr9.h>
#ifndef VIDEO_SOURCE_TAG
#define VIDEO_SOURCE_TAG 0x12345
#endif
#ifndef DWORD_PTR
#define DWORD_PTR DWORD
#endif
typedef HRESULT (*TransformProc)(DWORD_PTR pdwID,IDirect3DSurface9* pD3DSurface,REFERENCE_TIME  rtStart, REFERENCE_TIME  rtEnd);







extern RPC_IF_HANDLE __MIDL_itf_MultiVMR9_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MultiVMR9_0000_0000_v0_0_s_ifspec;

#ifndef __IMultiVMR9Wizard_INTERFACE_DEFINED__
#define __IMultiVMR9Wizard_INTERFACE_DEFINED__

/* interface IMultiVMR9Wizard */
/* [unique][helpstring][uuid][object][local] */ 


EXTERN_C const IID IID_IMultiVMR9Wizard;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3A54122C-1180-4468-B997-3A427841D6DE")
    IMultiVMR9Wizard : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ HWND hWnd,
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine,
            /* [in] */ D3DFORMAT format,
            /* [in] */ BOOL BufferInSystemMEM) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeEx( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ HWND hWnd,
            /* [in] */ HWND hWndCpy,
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine,
            /* [in] */ D3DFORMAT format,
            /* [in] */ BOOL BufferInSystemMEM) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Terminate( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Attach( 
            /* [in] */ IBaseFilter *pVMR,
            /* [in] */ D3DFORMAT format,
            /* [out] */ DWORD_PTR *pdwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Detach( 
            /* [in] */ DWORD_PTR dwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE VerifyID( 
            /* [in] */ DWORD_PTR dwID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGraph( 
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ IFilterGraph **ppGraph) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRenderEngine( 
            /* [out] */ IMultiVMR9RenderEngine **ppRenderEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMixerControl( 
            /* [out] */ IMultiVMR9MixerControl **ppMixerControl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetTexture( 
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ LPDIRECT3DTEXTURE9 *ppTexture) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoSize( 
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ LONG *plWidth,
            /* [out] */ LONG *plHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeDevice( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [out] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out] */ DWORD *lpNumBuffers) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetSrcTransformProc( 
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ TransformProc pProc,
            /* [out] */ TransformProc *pOldProc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSrcTransformProc( 
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ TransformProc *pProc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetGlobalTransformProc( 
            /* [in] */ TransformProc pProc,
            /* [out] */ TransformProc *pOldProc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGlobalTransformProc( 
            /* [out] */ TransformProc *pProc) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeOutStream( 
            /* [in] */ DWORD_PTR dwUserID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TerminateOutStream( 
            /* [in] */ DWORD_PTR dwUserID) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutStreamFilter( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [out] */ IBaseFilter **ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeGlobalOutStream( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE TerminateGlobalOutStream( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetGlobalOutStreamFilter( 
            /* [out] */ IBaseFilter **ppFilter) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Transform( 
            /* [in] */ IDirect3DSurface9 *pTexturePrivSurf,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE StreamOut( 
            /* [in] */ IDirect3DSurface9 *pSurface,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ScrVisible( 
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ BOOL bVisible) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiVMR9WizardVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiVMR9Wizard * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiVMR9Wizard * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiVMR9Wizard * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ HWND hWnd,
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine,
            /* [in] */ D3DFORMAT format,
            /* [in] */ BOOL BufferInSystemMEM);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeEx )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ HWND hWnd,
            /* [in] */ HWND hWndCpy,
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine,
            /* [in] */ D3DFORMAT format,
            /* [in] */ BOOL BufferInSystemMEM);
        
        HRESULT ( STDMETHODCALLTYPE *Terminate )( 
            IMultiVMR9Wizard * This);
        
        HRESULT ( STDMETHODCALLTYPE *Attach )( 
            IMultiVMR9Wizard * This,
            /* [in] */ IBaseFilter *pVMR,
            /* [in] */ D3DFORMAT format,
            /* [out] */ DWORD_PTR *pdwID);
        
        HRESULT ( STDMETHODCALLTYPE *Detach )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwID);
        
        HRESULT ( STDMETHODCALLTYPE *VerifyID )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwID);
        
        HRESULT ( STDMETHODCALLTYPE *GetGraph )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ IFilterGraph **ppGraph);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderEngine )( 
            IMultiVMR9Wizard * This,
            /* [out] */ IMultiVMR9RenderEngine **ppRenderEngine);
        
        HRESULT ( STDMETHODCALLTYPE *GetMixerControl )( 
            IMultiVMR9Wizard * This,
            /* [out] */ IMultiVMR9MixerControl **ppMixerControl);
        
        HRESULT ( STDMETHODCALLTYPE *GetTexture )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ LPDIRECT3DTEXTURE9 *ppTexture);
        
        HRESULT ( STDMETHODCALLTYPE *GetVideoSize )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ LONG *plWidth,
            /* [out] */ LONG *plHeight);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeDevice )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [out] */ VMR9AllocationInfo *lpAllocInfo,
            /* [out] */ DWORD *lpNumBuffers);
        
        HRESULT ( STDMETHODCALLTYPE *SetSrcTransformProc )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ TransformProc pProc,
            /* [out] */ TransformProc *pOldProc);
        
        HRESULT ( STDMETHODCALLTYPE *GetSrcTransformProc )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ TransformProc *pProc);
        
        HRESULT ( STDMETHODCALLTYPE *SetGlobalTransformProc )( 
            IMultiVMR9Wizard * This,
            /* [in] */ TransformProc pProc,
            /* [out] */ TransformProc *pOldProc);
        
        HRESULT ( STDMETHODCALLTYPE *GetGlobalTransformProc )( 
            IMultiVMR9Wizard * This,
            /* [out] */ TransformProc *pProc);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeOutStream )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwUserID);
        
        HRESULT ( STDMETHODCALLTYPE *TerminateOutStream )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwUserID);
        
        HRESULT ( STDMETHODCALLTYPE *GetOutStreamFilter )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeGlobalOutStream )( 
            IMultiVMR9Wizard * This);
        
        HRESULT ( STDMETHODCALLTYPE *TerminateGlobalOutStream )( 
            IMultiVMR9Wizard * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetGlobalOutStreamFilter )( 
            IMultiVMR9Wizard * This,
            /* [out] */ IBaseFilter **ppFilter);
        
        HRESULT ( STDMETHODCALLTYPE *Transform )( 
            IMultiVMR9Wizard * This,
            /* [in] */ IDirect3DSurface9 *pTexturePrivSurf,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd);
        
        HRESULT ( STDMETHODCALLTYPE *StreamOut )( 
            IMultiVMR9Wizard * This,
            /* [in] */ IDirect3DSurface9 *pSurface,
            /* [in] */ REFERENCE_TIME rtStart,
            /* [in] */ REFERENCE_TIME rtEnd);
        
        HRESULT ( STDMETHODCALLTYPE *ScrVisible )( 
            IMultiVMR9Wizard * This,
            /* [in] */ DWORD_PTR dwUserID,
            /* [in] */ BOOL bVisible);
        
        END_INTERFACE
    } IMultiVMR9WizardVtbl;

    interface IMultiVMR9Wizard
    {
        CONST_VTBL struct IMultiVMR9WizardVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiVMR9Wizard_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiVMR9Wizard_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiVMR9Wizard_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiVMR9Wizard_Initialize(This,dwFlags,hWnd,pRenderEngine,format,BufferInSystemMEM)	\
    ( (This)->lpVtbl -> Initialize(This,dwFlags,hWnd,pRenderEngine,format,BufferInSystemMEM) ) 

#define IMultiVMR9Wizard_InitializeEx(This,dwFlags,hWnd,hWndCpy,pRenderEngine,format,BufferInSystemMEM)	\
    ( (This)->lpVtbl -> InitializeEx(This,dwFlags,hWnd,hWndCpy,pRenderEngine,format,BufferInSystemMEM) ) 

#define IMultiVMR9Wizard_Terminate(This)	\
    ( (This)->lpVtbl -> Terminate(This) ) 

#define IMultiVMR9Wizard_Attach(This,pVMR,format,pdwID)	\
    ( (This)->lpVtbl -> Attach(This,pVMR,format,pdwID) ) 

#define IMultiVMR9Wizard_Detach(This,dwID)	\
    ( (This)->lpVtbl -> Detach(This,dwID) ) 

#define IMultiVMR9Wizard_VerifyID(This,dwID)	\
    ( (This)->lpVtbl -> VerifyID(This,dwID) ) 

#define IMultiVMR9Wizard_GetGraph(This,dwID,ppGraph)	\
    ( (This)->lpVtbl -> GetGraph(This,dwID,ppGraph) ) 

#define IMultiVMR9Wizard_GetRenderEngine(This,ppRenderEngine)	\
    ( (This)->lpVtbl -> GetRenderEngine(This,ppRenderEngine) ) 

#define IMultiVMR9Wizard_GetMixerControl(This,ppMixerControl)	\
    ( (This)->lpVtbl -> GetMixerControl(This,ppMixerControl) ) 

#define IMultiVMR9Wizard_GetTexture(This,dwID,ppTexture)	\
    ( (This)->lpVtbl -> GetTexture(This,dwID,ppTexture) ) 

#define IMultiVMR9Wizard_GetVideoSize(This,dwID,plWidth,plHeight)	\
    ( (This)->lpVtbl -> GetVideoSize(This,dwID,plWidth,plHeight) ) 

#define IMultiVMR9Wizard_InitializeDevice(This,dwUserID,lpAllocInfo,lpNumBuffers)	\
    ( (This)->lpVtbl -> InitializeDevice(This,dwUserID,lpAllocInfo,lpNumBuffers) ) 

#define IMultiVMR9Wizard_SetSrcTransformProc(This,dwID,pProc,pOldProc)	\
    ( (This)->lpVtbl -> SetSrcTransformProc(This,dwID,pProc,pOldProc) ) 

#define IMultiVMR9Wizard_GetSrcTransformProc(This,dwID,pProc)	\
    ( (This)->lpVtbl -> GetSrcTransformProc(This,dwID,pProc) ) 

#define IMultiVMR9Wizard_SetGlobalTransformProc(This,pProc,pOldProc)	\
    ( (This)->lpVtbl -> SetGlobalTransformProc(This,pProc,pOldProc) ) 

#define IMultiVMR9Wizard_GetGlobalTransformProc(This,pProc)	\
    ( (This)->lpVtbl -> GetGlobalTransformProc(This,pProc) ) 

#define IMultiVMR9Wizard_InitializeOutStream(This,dwUserID)	\
    ( (This)->lpVtbl -> InitializeOutStream(This,dwUserID) ) 

#define IMultiVMR9Wizard_TerminateOutStream(This,dwUserID)	\
    ( (This)->lpVtbl -> TerminateOutStream(This,dwUserID) ) 

#define IMultiVMR9Wizard_GetOutStreamFilter(This,dwUserID,ppFilter)	\
    ( (This)->lpVtbl -> GetOutStreamFilter(This,dwUserID,ppFilter) ) 

#define IMultiVMR9Wizard_InitializeGlobalOutStream(This)	\
    ( (This)->lpVtbl -> InitializeGlobalOutStream(This) ) 

#define IMultiVMR9Wizard_TerminateGlobalOutStream(This)	\
    ( (This)->lpVtbl -> TerminateGlobalOutStream(This) ) 

#define IMultiVMR9Wizard_GetGlobalOutStreamFilter(This,ppFilter)	\
    ( (This)->lpVtbl -> GetGlobalOutStreamFilter(This,ppFilter) ) 

#define IMultiVMR9Wizard_Transform(This,pTexturePrivSurf,rtStart,rtEnd)	\
    ( (This)->lpVtbl -> Transform(This,pTexturePrivSurf,rtStart,rtEnd) ) 

#define IMultiVMR9Wizard_StreamOut(This,pSurface,rtStart,rtEnd)	\
    ( (This)->lpVtbl -> StreamOut(This,pSurface,rtStart,rtEnd) ) 

#define IMultiVMR9Wizard_ScrVisible(This,dwUserID,bVisible)	\
    ( (This)->lpVtbl -> ScrVisible(This,dwUserID,bVisible) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiVMR9Wizard_INTERFACE_DEFINED__ */


#ifndef __IMultiVMR9RenderEngine_INTERFACE_DEFINED__
#define __IMultiVMR9RenderEngine_INTERFACE_DEFINED__

/* interface IMultiVMR9RenderEngine */
/* [unique][helpstring][uuid][object][local] */ 


EXTERN_C const IID IID_IMultiVMR9RenderEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("476B9DBC-D303-4E71-A568-2738F81E58AE")
    IMultiVMR9RenderEngine : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ HWND hWnd,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IMultiVMR9MixerControl *pMixerControl,
            /* [in] */ IMultiVMR9UILayer *pUILayer,
            /* [out] */ D3DFORMAT format) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE InitializeEx( 
            /* [in] */ HWND hWnd,
            /* [in] */ HWND hWndCpy,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IMultiVMR9MixerControl *pMixerControl,
            /* [in] */ IMultiVMR9UILayer *pUILayer,
            /* [out] */ D3DFORMAT format) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Terminate( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetUILayer( 
            /* [out] */ IMultiVMR9UILayer **ppUILayer) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetFrameRate( 
            /* [in] */ int nFramesPerSecBy100) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameRate( 
            /* [out] */ int *pnFramesPerSecBy100) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetFrameRateAvg( 
            /* [out] */ int *pnFramesPerSecBy100) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMixingPrefs( 
            /* [out] */ DWORD *pdwPrefs) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetWizardOwner( 
            /* [in] */ IMultiVMR9Wizard *pWizard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetWizardOwner( 
            /* [out] */ IMultiVMR9Wizard **ppWizard) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMixerControl( 
            /* [out] */ IMultiVMR9MixerControl **ppMixerControl) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Get3DDevice( 
            /* [out] */ IDirect3DDevice9 **ppDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetVideoWindow( 
            /* [out] */ HWND *phwnd) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBackBuffer( 
            /* [in] */ UINT iSwapChain,
            /* [in] */ UINT BackBuffer,
            /* [in] */ D3DBACKBUFFER_TYPE Type,
            /* [out] */ IDirect3DSurface9 **pBackBuff,
            /* [in] */ BOOL bCopy) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RenderNow( 
            /* [in] */ BOOL bStreamOut) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetSetedFrameRate( 
            /* [out] */ int *nFramesPerSecBy100) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiVMR9RenderEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiVMR9RenderEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiVMR9RenderEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiVMR9RenderEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMultiVMR9RenderEngine * This,
            /* [in] */ HWND hWnd,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IMultiVMR9MixerControl *pMixerControl,
            /* [in] */ IMultiVMR9UILayer *pUILayer,
            /* [out] */ D3DFORMAT format);
        
        HRESULT ( STDMETHODCALLTYPE *InitializeEx )( 
            IMultiVMR9RenderEngine * This,
            /* [in] */ HWND hWnd,
            /* [in] */ HWND hWndCpy,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IMultiVMR9MixerControl *pMixerControl,
            /* [in] */ IMultiVMR9UILayer *pUILayer,
            /* [out] */ D3DFORMAT format);
        
        HRESULT ( STDMETHODCALLTYPE *Terminate )( 
            IMultiVMR9RenderEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IMultiVMR9RenderEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetUILayer )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ IMultiVMR9UILayer **ppUILayer);
        
        HRESULT ( STDMETHODCALLTYPE *SetFrameRate )( 
            IMultiVMR9RenderEngine * This,
            /* [in] */ int nFramesPerSecBy100);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameRate )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ int *pnFramesPerSecBy100);
        
        HRESULT ( STDMETHODCALLTYPE *GetFrameRateAvg )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ int *pnFramesPerSecBy100);
        
        HRESULT ( STDMETHODCALLTYPE *GetMixingPrefs )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ DWORD *pdwPrefs);
        
        HRESULT ( STDMETHODCALLTYPE *SetWizardOwner )( 
            IMultiVMR9RenderEngine * This,
            /* [in] */ IMultiVMR9Wizard *pWizard);
        
        HRESULT ( STDMETHODCALLTYPE *GetWizardOwner )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ IMultiVMR9Wizard **ppWizard);
        
        HRESULT ( STDMETHODCALLTYPE *GetMixerControl )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ IMultiVMR9MixerControl **ppMixerControl);
        
        HRESULT ( STDMETHODCALLTYPE *Get3DDevice )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ IDirect3DDevice9 **ppDevice);
        
        HRESULT ( STDMETHODCALLTYPE *GetVideoWindow )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ HWND *phwnd);
        
        HRESULT ( STDMETHODCALLTYPE *GetBackBuffer )( 
            IMultiVMR9RenderEngine * This,
            /* [in] */ UINT iSwapChain,
            /* [in] */ UINT BackBuffer,
            /* [in] */ D3DBACKBUFFER_TYPE Type,
            /* [out] */ IDirect3DSurface9 **pBackBuff,
            /* [in] */ BOOL bCopy);
        
        HRESULT ( STDMETHODCALLTYPE *RenderNow )( 
            IMultiVMR9RenderEngine * This,
            /* [in] */ BOOL bStreamOut);
        
        HRESULT ( STDMETHODCALLTYPE *GetSetedFrameRate )( 
            IMultiVMR9RenderEngine * This,
            /* [out] */ int *nFramesPerSecBy100);
        
        END_INTERFACE
    } IMultiVMR9RenderEngineVtbl;

    interface IMultiVMR9RenderEngine
    {
        CONST_VTBL struct IMultiVMR9RenderEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiVMR9RenderEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiVMR9RenderEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiVMR9RenderEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiVMR9RenderEngine_Initialize(This,hWnd,dwFlags,pMixerControl,pUILayer,format)	\
    ( (This)->lpVtbl -> Initialize(This,hWnd,dwFlags,pMixerControl,pUILayer,format) ) 

#define IMultiVMR9RenderEngine_InitializeEx(This,hWnd,hWndCpy,dwFlags,pMixerControl,pUILayer,format)	\
    ( (This)->lpVtbl -> InitializeEx(This,hWnd,hWndCpy,dwFlags,pMixerControl,pUILayer,format) ) 

#define IMultiVMR9RenderEngine_Terminate(This)	\
    ( (This)->lpVtbl -> Terminate(This) ) 

#define IMultiVMR9RenderEngine_Render(This)	\
    ( (This)->lpVtbl -> Render(This) ) 

#define IMultiVMR9RenderEngine_GetUILayer(This,ppUILayer)	\
    ( (This)->lpVtbl -> GetUILayer(This,ppUILayer) ) 

#define IMultiVMR9RenderEngine_SetFrameRate(This,nFramesPerSecBy100)	\
    ( (This)->lpVtbl -> SetFrameRate(This,nFramesPerSecBy100) ) 

#define IMultiVMR9RenderEngine_GetFrameRate(This,pnFramesPerSecBy100)	\
    ( (This)->lpVtbl -> GetFrameRate(This,pnFramesPerSecBy100) ) 

#define IMultiVMR9RenderEngine_GetFrameRateAvg(This,pnFramesPerSecBy100)	\
    ( (This)->lpVtbl -> GetFrameRateAvg(This,pnFramesPerSecBy100) ) 

#define IMultiVMR9RenderEngine_GetMixingPrefs(This,pdwPrefs)	\
    ( (This)->lpVtbl -> GetMixingPrefs(This,pdwPrefs) ) 

#define IMultiVMR9RenderEngine_SetWizardOwner(This,pWizard)	\
    ( (This)->lpVtbl -> SetWizardOwner(This,pWizard) ) 

#define IMultiVMR9RenderEngine_GetWizardOwner(This,ppWizard)	\
    ( (This)->lpVtbl -> GetWizardOwner(This,ppWizard) ) 

#define IMultiVMR9RenderEngine_GetMixerControl(This,ppMixerControl)	\
    ( (This)->lpVtbl -> GetMixerControl(This,ppMixerControl) ) 

#define IMultiVMR9RenderEngine_Get3DDevice(This,ppDevice)	\
    ( (This)->lpVtbl -> Get3DDevice(This,ppDevice) ) 

#define IMultiVMR9RenderEngine_GetVideoWindow(This,phwnd)	\
    ( (This)->lpVtbl -> GetVideoWindow(This,phwnd) ) 

#define IMultiVMR9RenderEngine_GetBackBuffer(This,iSwapChain,BackBuffer,Type,pBackBuff,bCopy)	\
    ( (This)->lpVtbl -> GetBackBuffer(This,iSwapChain,BackBuffer,Type,pBackBuff,bCopy) ) 

#define IMultiVMR9RenderEngine_RenderNow(This,bStreamOut)	\
    ( (This)->lpVtbl -> RenderNow(This,bStreamOut) ) 

#define IMultiVMR9RenderEngine_GetSetedFrameRate(This,nFramesPerSecBy100)	\
    ( (This)->lpVtbl -> GetSetedFrameRate(This,nFramesPerSecBy100) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiVMR9RenderEngine_INTERFACE_DEFINED__ */


#ifndef __IMultiVMR9UILayer_INTERFACE_DEFINED__
#define __IMultiVMR9UILayer_INTERFACE_DEFINED__

/* interface IMultiVMR9UILayer */
/* [unique][helpstring][uuid][object][local] */ 


EXTERN_C const IID IID_IMultiVMR9UILayer;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("102A1639-48DA-4C93-8B2E-EFF597B01E01")
    IMultiVMR9UILayer : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IDirect3DDevice9 *pDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ProcessMessage( 
            /* [in] */ UINT msg,
            /* [in] */ UINT wParam,
            /* [in] */ LONG lParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ IDirect3DDevice9 *pDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetRenderEngineOwner( 
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRenderEngineOwner( 
            /* [out] */ IMultiVMR9RenderEngine **ppRenderEngine) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiVMR9UILayerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiVMR9UILayer * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiVMR9UILayer * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiVMR9UILayer * This);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMultiVMR9UILayer * This,
            /* [in] */ IDirect3DDevice9 *pDevice);
        
        HRESULT ( STDMETHODCALLTYPE *ProcessMessage )( 
            IMultiVMR9UILayer * This,
            /* [in] */ UINT msg,
            /* [in] */ UINT wParam,
            /* [in] */ LONG lParam);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IMultiVMR9UILayer * This,
            /* [in] */ IDirect3DDevice9 *pDevice);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderEngineOwner )( 
            IMultiVMR9UILayer * This,
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderEngineOwner )( 
            IMultiVMR9UILayer * This,
            /* [out] */ IMultiVMR9RenderEngine **ppRenderEngine);
        
        END_INTERFACE
    } IMultiVMR9UILayerVtbl;

    interface IMultiVMR9UILayer
    {
        CONST_VTBL struct IMultiVMR9UILayerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiVMR9UILayer_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiVMR9UILayer_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiVMR9UILayer_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiVMR9UILayer_Initialize(This,pDevice)	\
    ( (This)->lpVtbl -> Initialize(This,pDevice) ) 

#define IMultiVMR9UILayer_ProcessMessage(This,msg,wParam,lParam)	\
    ( (This)->lpVtbl -> ProcessMessage(This,msg,wParam,lParam) ) 

#define IMultiVMR9UILayer_Render(This,pDevice)	\
    ( (This)->lpVtbl -> Render(This,pDevice) ) 

#define IMultiVMR9UILayer_SetRenderEngineOwner(This,pRenderEngine)	\
    ( (This)->lpVtbl -> SetRenderEngineOwner(This,pRenderEngine) ) 

#define IMultiVMR9UILayer_GetRenderEngineOwner(This,ppRenderEngine)	\
    ( (This)->lpVtbl -> GetRenderEngineOwner(This,ppRenderEngine) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiVMR9UILayer_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_MultiVMR9_0000_0003 */
/* [local] */ 

#if 0
typedef struct _NORMALIZEDRECT
    {
    float left;
    float top;
    float right;
    float bottom;
    } 	NORMALIZEDRECT;

typedef struct _NORMALIZEDRECT *PNORMALIZEDRECT;

#endif


extern RPC_IF_HANDLE __MIDL_itf_MultiVMR9_0000_0003_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_MultiVMR9_0000_0003_v0_0_s_ifspec;

#ifndef __IMultiVMR9MixerControl_INTERFACE_DEFINED__
#define __IMultiVMR9MixerControl_INTERFACE_DEFINED__

/* interface IMultiVMR9MixerControl */
/* [unique][helpstring][uuid][object][local] */ 


EXTERN_C const IID IID_IMultiVMR9MixerControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("35CE8FF4-3673-42F8-A2FF-544F3AFA2DE2")
    IMultiVMR9MixerControl : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetRenderEngineOwner( 
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetRenderEngineOwner( 
            /* [out] */ IMultiVMR9RenderEngine **ppRenderEngine) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IDirect3DDevice9 *pDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Compose( 
            /* [in] */ void *lpParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Render( 
            /* [in] */ IDirect3DDevice9 *pDevice,
            /* [in] */ void *lpParam) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputRect( 
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ NORMALIZEDRECT *lpNormRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetOutputRect( 
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ NORMALIZEDRECT *lpNormRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetIdealOutputRect( 
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ DWORD dwWidth,
            /* [in] */ DWORD dwHeight,
            /* [out] */ NORMALIZEDRECT *lpNormRect) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetZOrder( 
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ DWORD *pdwZOrder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetZOrder( 
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ DWORD dwZOrder) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetAlpha( 
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ float *pAlpha) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetAlpha( 
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ float Alpha) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetBackgroundColor( 
            /* [out] */ COLORREF *pColor) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE SetBackgroundColor( 
            /* [in] */ COLORREF Color) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Show( 
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ BOOL visible) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddVideoSource( 
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ LONG lImageWidth,
            /* [in] */ LONG lImageHeight,
            /* [in] */ LONG lTextureWidth,
            /* [in] */ LONG lTextureHeight) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE DeleteVideoSource( 
            /* [in] */ DWORD_PTR dwID) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMultiVMR9MixerControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMultiVMR9MixerControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMultiVMR9MixerControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetRenderEngineOwner )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ IMultiVMR9RenderEngine *pRenderEngine);
        
        HRESULT ( STDMETHODCALLTYPE *GetRenderEngineOwner )( 
            IMultiVMR9MixerControl * This,
            /* [out] */ IMultiVMR9RenderEngine **ppRenderEngine);
        
        HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ IDirect3DDevice9 *pDevice);
        
        HRESULT ( STDMETHODCALLTYPE *Compose )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ void *lpParam);
        
        HRESULT ( STDMETHODCALLTYPE *Render )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ IDirect3DDevice9 *pDevice,
            /* [in] */ void *lpParam);
        
        HRESULT ( STDMETHODCALLTYPE *GetOutputRect )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ NORMALIZEDRECT *lpNormRect);
        
        HRESULT ( STDMETHODCALLTYPE *SetOutputRect )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ NORMALIZEDRECT *lpNormRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetIdealOutputRect )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ DWORD dwWidth,
            /* [in] */ DWORD dwHeight,
            /* [out] */ NORMALIZEDRECT *lpNormRect);
        
        HRESULT ( STDMETHODCALLTYPE *GetZOrder )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ DWORD *pdwZOrder);
        
        HRESULT ( STDMETHODCALLTYPE *SetZOrder )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ DWORD dwZOrder);
        
        HRESULT ( STDMETHODCALLTYPE *GetAlpha )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [out] */ float *pAlpha);
        
        HRESULT ( STDMETHODCALLTYPE *SetAlpha )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ float Alpha);
        
        HRESULT ( STDMETHODCALLTYPE *GetBackgroundColor )( 
            IMultiVMR9MixerControl * This,
            /* [out] */ COLORREF *pColor);
        
        HRESULT ( STDMETHODCALLTYPE *SetBackgroundColor )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ COLORREF Color);
        
        HRESULT ( STDMETHODCALLTYPE *Show )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ BOOL visible);
        
        HRESULT ( STDMETHODCALLTYPE *AddVideoSource )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID,
            /* [in] */ LONG lImageWidth,
            /* [in] */ LONG lImageHeight,
            /* [in] */ LONG lTextureWidth,
            /* [in] */ LONG lTextureHeight);
        
        HRESULT ( STDMETHODCALLTYPE *DeleteVideoSource )( 
            IMultiVMR9MixerControl * This,
            /* [in] */ DWORD_PTR dwID);
        
        END_INTERFACE
    } IMultiVMR9MixerControlVtbl;

    interface IMultiVMR9MixerControl
    {
        CONST_VTBL struct IMultiVMR9MixerControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMultiVMR9MixerControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IMultiVMR9MixerControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IMultiVMR9MixerControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IMultiVMR9MixerControl_SetRenderEngineOwner(This,pRenderEngine)	\
    ( (This)->lpVtbl -> SetRenderEngineOwner(This,pRenderEngine) ) 

#define IMultiVMR9MixerControl_GetRenderEngineOwner(This,ppRenderEngine)	\
    ( (This)->lpVtbl -> GetRenderEngineOwner(This,ppRenderEngine) ) 

#define IMultiVMR9MixerControl_Initialize(This,pDevice)	\
    ( (This)->lpVtbl -> Initialize(This,pDevice) ) 

#define IMultiVMR9MixerControl_Compose(This,lpParam)	\
    ( (This)->lpVtbl -> Compose(This,lpParam) ) 

#define IMultiVMR9MixerControl_Render(This,pDevice,lpParam)	\
    ( (This)->lpVtbl -> Render(This,pDevice,lpParam) ) 

#define IMultiVMR9MixerControl_GetOutputRect(This,dwID,lpNormRect)	\
    ( (This)->lpVtbl -> GetOutputRect(This,dwID,lpNormRect) ) 

#define IMultiVMR9MixerControl_SetOutputRect(This,dwID,lpNormRect)	\
    ( (This)->lpVtbl -> SetOutputRect(This,dwID,lpNormRect) ) 

#define IMultiVMR9MixerControl_GetIdealOutputRect(This,dwID,dwWidth,dwHeight,lpNormRect)	\
    ( (This)->lpVtbl -> GetIdealOutputRect(This,dwID,dwWidth,dwHeight,lpNormRect) ) 

#define IMultiVMR9MixerControl_GetZOrder(This,dwID,pdwZOrder)	\
    ( (This)->lpVtbl -> GetZOrder(This,dwID,pdwZOrder) ) 

#define IMultiVMR9MixerControl_SetZOrder(This,dwID,dwZOrder)	\
    ( (This)->lpVtbl -> SetZOrder(This,dwID,dwZOrder) ) 

#define IMultiVMR9MixerControl_GetAlpha(This,dwID,pAlpha)	\
    ( (This)->lpVtbl -> GetAlpha(This,dwID,pAlpha) ) 

#define IMultiVMR9MixerControl_SetAlpha(This,dwID,Alpha)	\
    ( (This)->lpVtbl -> SetAlpha(This,dwID,Alpha) ) 

#define IMultiVMR9MixerControl_GetBackgroundColor(This,pColor)	\
    ( (This)->lpVtbl -> GetBackgroundColor(This,pColor) ) 

#define IMultiVMR9MixerControl_SetBackgroundColor(This,Color)	\
    ( (This)->lpVtbl -> SetBackgroundColor(This,Color) ) 

#define IMultiVMR9MixerControl_Show(This,dwID,visible)	\
    ( (This)->lpVtbl -> Show(This,dwID,visible) ) 

#define IMultiVMR9MixerControl_AddVideoSource(This,dwID,lImageWidth,lImageHeight,lTextureWidth,lTextureHeight)	\
    ( (This)->lpVtbl -> AddVideoSource(This,dwID,lImageWidth,lImageHeight,lTextureWidth,lTextureHeight) ) 

#define IMultiVMR9MixerControl_DeleteVideoSource(This,dwID)	\
    ( (This)->lpVtbl -> DeleteVideoSource(This,dwID) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IMultiVMR9MixerControl_INTERFACE_DEFINED__ */


#ifndef __INullInPlace_INTERFACE_DEFINED__
#define __INullInPlace_INTERFACE_DEFINED__

/* interface INullInPlace */
/* [unique][helpstring][uuid][object][local] */ 


EXTERN_C const IID IID_INullInPlace;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("3A878B6A-1590-4cb9-809A-8C7542EDFB56")
    INullInPlace : public IUnknown
    {
    public:
    };
    
#else 	/* C style interface */

    typedef struct INullInPlaceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            INullInPlace * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            INullInPlace * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            INullInPlace * This);
        
        END_INTERFACE
    } INullInPlaceVtbl;

    interface INullInPlace
    {
        CONST_VTBL struct INullInPlaceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define INullInPlace_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define INullInPlace_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define INullInPlace_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __INullInPlace_INTERFACE_DEFINED__ */



#ifndef __MultiVMR9Lib_LIBRARY_DEFINED__
#define __MultiVMR9Lib_LIBRARY_DEFINED__

/* library MultiVMR9Lib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MultiVMR9Lib;

EXTERN_C const CLSID CLSID_MultiVMR9Wizard;

#ifdef __cplusplus

class DECLSPEC_UUID("CE8ED243-0078-41A2-B56C-EC9CF0E887C2")
MultiVMR9Wizard;
#endif

EXTERN_C const CLSID CLSID_MultiVMR9RenderEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("8BBB5505-250D-486D-BB49-F74141880490")
MultiVMR9RenderEngine;
#endif

EXTERN_C const CLSID CLSID_MultiVMR9UILayer;

#ifdef __cplusplus

class DECLSPEC_UUID("70A2E5FE-981E-4518-83C7-9324DC957DA4")
MultiVMR9UILayer;
#endif

EXTERN_C const CLSID CLSID_MultiVMR9MixerControl;

#ifdef __cplusplus

class DECLSPEC_UUID("BB22E7B6-54E1-4C4D-ABF7-99193550A3F4")
MultiVMR9MixerControl;
#endif

EXTERN_C const CLSID CLSID_NullInPlace;

#ifdef __cplusplus

class DECLSPEC_UUID("E89555FF-9F9B-417e-ACEC-E8A2DBF70BA6")
NullInPlace;
#endif
#endif /* __MultiVMR9Lib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


