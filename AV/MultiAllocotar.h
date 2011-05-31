#pragma once
#include <d3d9.h>
#include <vmr9.h>
#include <vector>
#include "MultiScene.h"
using namespace std;

class CMultiAllocotar : public IVMRSurfaceAllocator9,
	                           IVMRImagePresenter9	                           
{

public:

	CMultiAllocotar(HWND wnd, IDirect3D9* d3d, IDirect3DDevice9* d3dd);
	virtual ~CMultiAllocotar(void);


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


protected:
	HRESULT CreateDevice();

	// a helper function to erase every surface in the vector
	void DeleteSurfaces();

	bool NeedToHandleDisplayChange();

	// This function is here so we can catch the loss of surfaces.
	// All the functions are using the FAIL_RET macro so that they exit
	// with the last error code.  When this returns with the surface lost
	// error code we can restore the surfaces.
	HRESULT PresentHelper(VMR9PresentationInfo *lpPresInfo);

private:
	// needed to make this a thread safe object
	CCritSec    m_ObjectLock;
	HWND        m_window;
	long        m_refCount;

	SmartPtr<IDirect3D9>                     m_D3D;
	SmartPtr<IDirect3DDevice9>               m_D3DDev;
	SmartPtr<IVMRSurfaceAllocatorNotify9>    m_lpIVMRSurfAllocNotify;
	vector<SmartPtr<IDirect3DSurface9> >     m_surfaces;
	SmartPtr<IDirect3DSurface9>              m_renderTarget;
	SmartPtr<IDirect3DTexture9>              m_privateTexture;
	CMultiScene                              m_scene;
};

