#pragma once
#include <d3d9.h>
#include <vmr9.h>
#include "MultiScene.h"

class CMultiScene;

class CMultiAllocotar : public IVMRSurfaceAllocator9,
	                           IVMRImagePresenter9	                           
{

public:

	CMultiAllocotar(CMultiScene& scene);
	virtual ~CMultiAllocotar(void);

	HRESULT Attach(IBaseFilter* pVMRFilter,D3DFORMAT format,DWORD_PTR& pdwID);

	HRESULT SetRect(DWORD_PTR dwID ,NORMALIZEDRECT & newnrect);

	//void GetVideoSources(std::list<VideoSource *>&  videoList);

	void GetTexture(DWORD_PTR videoId,IDirect3DTexture9 **ppTexture);


	// IVMRSurfaceAllocator9
	virtual HRESULT STDMETHODCALLTYPE InitializeDevice( 
		/* [in] */ DWORD_PTR dwUserID,
		/* [in] */ VMR9AllocationInfo *lpAllocInfo,
		/* [out][in] */ DWORD *lpNumBuffers);

	virtual HRESULT STDMETHODCALLTYPE TerminateDevice( 
		/* [in] */ DWORD_PTR dwID);

	virtual HRESULT STDMETHODCALLTYPE GetSurface( 
		/* [in] */ DWORD_PTR dwUserID,
		/* [in] */ DWORD SurfaceIndex,
		/* [in] */ DWORD SurfaceFlags,
		/* [out] */ IDirect3DSurface9 **lplpSurface);

	virtual HRESULT STDMETHODCALLTYPE AdviseNotify( 
		/* [in] */ IVMRSurfaceAllocatorNotify9 *lpIVMRSurfAllocNotify);

	// IVMRImagePresenter9
	virtual HRESULT STDMETHODCALLTYPE StartPresenting( 
		/* [in] */ DWORD_PTR dwUserID);

	virtual HRESULT STDMETHODCALLTYPE StopPresenting( 
		/* [in] */ DWORD_PTR dwUserID);

	virtual HRESULT STDMETHODCALLTYPE PresentImage( 
		/* [in] */ DWORD_PTR dwUserID,
		/* [in] */ VMR9PresentationInfo *lpPresInfo);

	// IUnknown
	virtual HRESULT STDMETHODCALLTYPE QueryInterface( 
		REFIID riid,
		void** ppvObject);

	virtual ULONG STDMETHODCALLTYPE AddRef();
	virtual ULONG STDMETHODCALLTYPE Release();

	HRESULT  GetVideoSourceInfo(DWORD_PTR dwID,VideoSource **ppSource);
	
private:

	CCritSec                                        m_ObjectLock;
	long                                            m_refCount;
	CMultiScene&                                    m_scene;

public:
	std::list<VideoSource*>                         m_pVideoSources;
};

