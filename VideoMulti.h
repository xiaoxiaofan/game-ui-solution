#pragma once
#include "Export.h"
#include <smartptr.h>
#include <d3d9.h>
#include <Vmr9.h>
#include <list>
class AVDEVICE_API CVideoMulti
{

public:
	CVideoMulti(HWND hwnd);
	~CVideoMulti(void);

	HRESULT AddMultiFileSource();

private:
	BSTR GetMoviePath();
	HRESULT SetAllocatorPresenter( IBaseFilter *filter);
	HRESULT CreateDevice();

private:
	SmartPtr<IGraphBuilder>              m_pGraph;
	SmartPtr<IMediaControl>              m_pMediaControl;
	SmartPtr<IMediaEvent>                m_pMediaEvent;

	SmartPtr<IBaseFilter>                m_pVRM;
	std::list<SmartPtr<IVMRSurfaceAllocator9>>      m_pMultiAllocators;
	SmartPtr<IVMRSurfaceAllocator9>      m_pMultiAllocator;
	SmartPtr<IDirect3DDevice9>           m_pDirect3DDevice;
	SmartPtr<IDirect3D9>                 m_pD3D;
	HWND                                 m_hwnd;
};

