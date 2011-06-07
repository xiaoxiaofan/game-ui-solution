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

	HRESULT AddMultiFileSource(DWORD_PTR& useId,LPRECT pRect = NULL);

	void SetPosition(DWORD_PTR dwID,int x,int y,int cx,int cy);

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
	std::list<DWORD_PTR>                 m_pVSIDs;
	HWND                                 m_hwnd;
};

