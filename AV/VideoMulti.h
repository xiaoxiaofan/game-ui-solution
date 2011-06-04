#pragma once
#include "Export.h"
#include <smartptr.h>
#include <d3d9.h>
#include <Vmr9.h>
#include <list>
#include "MultiScene.h"
#include "MultiAllocotar.h"
class AVDEVICE_API CVideoMulti
{

public:
	CVideoMulti(HWND hwnd);
	~CVideoMulti(void);

	HRESULT AddMultiFileSource();

	void StartRenderThread();

	static DWORD WINAPI RenderThreadProc_( LPVOID lpParameter );

private:
	BSTR GetMoviePath();
	

private:
	SmartPtr<IGraphBuilder>              m_pGraph;
	SmartPtr<IMediaControl>              m_pMediaControl;
	SmartPtr<IMediaEvent>                m_pMediaEvent;
	SmartPtr<IBaseFilter>                m_pVRM;
	CMultiScene*                         m_pSence;
	SmartPtr<CMultiAllocotar>			 m_pMultiAllocotar;
	HWND                                 m_hwnd;
};

