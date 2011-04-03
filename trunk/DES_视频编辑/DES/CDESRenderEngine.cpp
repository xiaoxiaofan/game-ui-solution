//
// CDESRenderEngine.cpp
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#include "stdafx.h"
#include <qedit.h>
#include "CDESTimeLine.h"
#include "CDESRenderEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
CDESRenderEngine::CDESRenderEngine()
{
	mRenderEngine = NULL;
	mMediaControl = NULL;
	mMediaEvent   = NULL;
	mRenderRangeStart  = 0;
	mRenderRangeStop   = 0;
}

CDESRenderEngine::~CDESRenderEngine()
{
	if (mRenderEngine != NULL)
	{
		mRenderEngine->Release();
		mRenderEngine = NULL;
	}
	if (mMediaControl != NULL)
	{
		mMediaControl->Release();
		mMediaControl = NULL;
	}
	if (mMediaEvent != NULL)
	{
		mMediaEvent->Release();
		mMediaEvent = NULL;
	}
}

bool CDESRenderEngine::Initialize(void)
{
	if (mRenderEngine == NULL)
	{
		HRESULT hr = CoCreateInstance(CLSID_RenderEngine, 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									IID_IRenderEngine, 
									(void**) &mRenderEngine);
		if (FAILED(hr))
		{
			mRenderEngine = NULL;
			return false;
		}
	}
	return true;
}

bool CDESRenderEngine::SetTimelineObject(CDESTimeLine & inTimeLine)
{
	if (mRenderEngine)
	{
		IAMTimeline * pTimeLine = inTimeLine.GetTimeLine();
		ASSERT(pTimeLine);
		HRESULT hr = mRenderEngine->SetTimelineObject(pTimeLine);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::GetTimelineObject(CDESTimeLine & outTimeLine)
{
	if (mRenderEngine)
	{
		IAMTimeline * pTimeLine = NULL;
		HRESULT hr = mRenderEngine->GetTimelineObject(&pTimeLine);
		if (SUCCEEDED(hr))
		{
			outTimeLine.Attach(pTimeLine);
			pTimeLine->Release();
			return true;
		}
	}
	return false;
}

bool CDESRenderEngine::ConnectFrontEnd(BOOL * outNeedReset)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->ConnectFrontEnd();
		if (outNeedReset != NULL)
		{
			*outNeedReset = FALSE;
			if (hr == S_WARN_OUTPUTRESET)
			{
				*outNeedReset = TRUE;
			}
		}
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::RenderOutputPins(void)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->RenderOutputPins();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::GetGroupOutputPin(long inGroupIndex, IPin ** outRenderPin)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->GetGroupOutputPin(inGroupIndex, outRenderPin);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::ScrapIt(void)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->ScrapIt();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::SetFilterGraph(IGraphBuilder * inFilterGraph)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->SetFilterGraph(inFilterGraph);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::GetFilterGraph(IGraphBuilder ** outFilterGraph)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->GetFilterGraph(outFilterGraph);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

/*
Constant Value Description:
CONNECTF_DYNAMIC_NONE       0x00  
CONNECTF_DYNAMIC_SOURCES    0x01  
CONNECTF_DYNAMIC_EFFECTS    0x02 
*/
bool CDESRenderEngine::SetDynamicReconnectLevel(DWORD inLevel)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->SetDynamicReconnectLevel(inLevel);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::SetRenderRange(REFERENCE_TIME inStart, REFERENCE_TIME inStop)
{
	if (mRenderEngine)
	{
		mRenderRangeStart = inStart / UNITS;
		mRenderRangeStop  = inStop  / UNITS;
		HRESULT hr = mRenderEngine->SetRenderRange(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::SetRenderRange2(double inStart, double inStop)
{
	if (mRenderEngine)
	{
		mRenderRangeStart = inStart;
		mRenderRangeStop  = inStop;
		HRESULT hr = mRenderEngine->SetRenderRange2(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::GetRenderRange2(double * outStart, double * outStop)
{
	if (mRenderEngine && mRenderRangeStart != mRenderRangeStop)
	{
		*outStart  = mRenderRangeStart;
		*outStop   = mRenderRangeStop;
		return true;
	}
	return false;
}

bool CDESRenderEngine::SetSourceNameValidation(const char * inFilterString)
{
	if (mRenderEngine)
	{
		WCHAR    szFilter[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inFilterString, -1, szFilter, MAX_PATH);
		HRESULT hr = mRenderEngine->SetSourceNameValidation(szFilter, NULL,
			SFN_VALIDATEF_CHECK | SFN_VALIDATEF_POPUP | SFN_VALIDATEF_REPLACE);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESRenderEngine::GetVendorString(BSTR * outVendorID)
{
	if (mRenderEngine)
	{
		HRESULT hr = mRenderEngine->GetVendorString(outVendorID);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


//--- Filter graph manager interfaces ---
bool CDESRenderEngine::GraphRun(void)
{
	if (mRenderEngine)
	{
		if (mMediaControl == NULL)
		{
			IGraphBuilder * pBuilder = NULL;
			if (GetFilterGraph(&pBuilder) && pBuilder != NULL)
			{
				pBuilder->QueryInterface(IID_IMediaControl, (void **) &mMediaControl);
				pBuilder->Release();
			}
		}

		if (mMediaControl)
		{
			HRESULT hr = mMediaControl->Run();
			return SUCCEEDED(hr) ? true : false;
		}
	}
	return false;
}

bool CDESRenderEngine::GraphPause(void)
{
	if (mRenderEngine)
	{
		if (mMediaControl == NULL)
		{
			IGraphBuilder * pBuilder = NULL;
			if (GetFilterGraph(&pBuilder) && pBuilder != NULL)
			{
				pBuilder->QueryInterface(IID_IMediaControl, (void **) &mMediaControl);
				pBuilder->Release();
			}
		}

		if (mMediaControl)
		{
			HRESULT hr = mMediaControl->Pause();
			return SUCCEEDED(hr) ? true : false;
		}
	}
	return false;
}

bool CDESRenderEngine::GraphStop(void)
{
	if (mRenderEngine)
	{
		if (mMediaControl == NULL)
		{
			IGraphBuilder * pBuilder = NULL;
			if (GetFilterGraph(&pBuilder) && pBuilder != NULL)
			{
				pBuilder->QueryInterface(IID_IMediaControl, (void **) &mMediaControl);
				pBuilder->Release();
			}
		}

		if (mMediaControl)
		{
			HRESULT hr = mMediaControl->Stop();
			return SUCCEEDED(hr) ? true : false;
		}
	}
	return false;
}

bool CDESRenderEngine::WaitForCompletion(void)
{
	if (mRenderEngine)
	{
		if (mMediaEvent == NULL)
		{
			IGraphBuilder * pBuilder = NULL;
			if (GetFilterGraph(&pBuilder) && pBuilder != NULL)
			{
				pBuilder->QueryInterface(IID_IMediaEvent, (void **) &mMediaEvent);
				pBuilder->Release();
			}
		}

		if (mMediaEvent)
		{
			long EventCode = 0;
			HRESULT hr = mMediaEvent->WaitForCompletion(-1, &EventCode);
			return SUCCEEDED(hr) ? true : false;
		}
	}
	return false;
}