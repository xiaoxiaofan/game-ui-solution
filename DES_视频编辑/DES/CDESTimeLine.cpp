//
// CDESTimeLine.cpp
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
#include "CDESTimeLine.h"
#include "CDESBaseObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
CDESTimeLine::CDESTimeLine()
{
	mTimeLine = NULL;
}

CDESTimeLine::~CDESTimeLine()
{
	ReleaseSelf();	
}

void CDESTimeLine::ReleaseSelf(void)
{
	if (mTimeLine != NULL)
	{
		mTimeLine->Release();
		mTimeLine = NULL;
	}
}

IAMTimeline * CDESTimeLine::GetTimeLine(void)
{
	return mTimeLine;
}

bool CDESTimeLine::Attach(IAMTimeline * inTimeLine)
{
	ReleaseSelf();
	if (inTimeLine != NULL)
	{
		// Outstanding reference
		inTimeLine->AddRef();
	}
	mTimeLine = inTimeLine;
	return true;
}

// Create timeline object instance
bool CDESTimeLine::Initialize(void)
{
	if (mTimeLine == NULL)
	{
		HRESULT hr = CoCreateInstance(CLSID_AMTimeline, 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									IID_IAMTimeline, 
									(void**) &mTimeLine);
		if (FAILED(hr))
		{
			mTimeLine = NULL;
			return false;
		}
	}
	return true;
}

bool CDESTimeLine::AddGroup(CDESBaseObject * inGroup)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->AddGroup(inGroup->GetTimeLineObj());
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetGroup(CDESBaseObject & outGroup, long inGroupIndex)
{
	if (mTimeLine)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = mTimeLine->GetGroup(&pTimeLineObj, inGroupIndex);
		if (SUCCEEDED(hr))
		{
			outGroup.Attach(pTimeLineObj);
			pTimeLineObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESTimeLine::ClearAllGroups(void)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->ClearAllGroups();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

long CDESTimeLine::GetGroupCount(void)
{
	if (mTimeLine)
	{
		long    groupCount = 0;
		mTimeLine->GetGroupCount(&groupCount);
		return groupCount;
	}
	return 0;
}

BOOL CDESTimeLine::EffectsEnabled(void)
{
	if (mTimeLine)
	{
		BOOL  bEnabled = FALSE;
		mTimeLine->EffectsEnabled(&bEnabled);
		return bEnabled;
	}
	return FALSE;
}

bool CDESTimeLine::EnableEffects(BOOL inEnabled)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->EnableEffects(inEnabled);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultEffect(GUID * inGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->SetDefaultEffect(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultEffectB(BSTR inGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->SetDefaultEffectB(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultEffect(GUID * outGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetDefaultEffect(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultEffectB(BSTR * outGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetDefaultEffectB(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

BOOL CDESTimeLine::TransitionsEnabled(void)
{
	if (mTimeLine)
	{
		BOOL  bEnabled = FALSE;
		mTimeLine->TransitionsEnabled(&bEnabled);
		return bEnabled;
	}
	return FALSE;
}

bool CDESTimeLine::EnableTransitions(BOOL inEnabled)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->EnableTransitions(inEnabled);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultTransition(GUID * inGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->SetDefaultTransition(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultTransitionB(BSTR inGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->SetDefaultTransitionB(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultTransition(GUID * outGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetDefaultTransition(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultTransitionB(BSTR * outGuid)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetDefaultTransitionB(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultFPS(double inFPS)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->SetDefaultFPS(inFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultFPS(double * outFPS)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetDefaultFPS(outFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDuration(REFERENCE_TIME * outDuration)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetDuration(outDuration);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDuration2(double * outDuration)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetDuration2(outDuration);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


bool CDESTimeLine::ValidateSourceNames(long inNotifyEventHandle)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->ValidateSourceNames(
			SFN_VALIDATEF_CHECK | SFN_VALIDATEF_POPUP | SFN_VALIDATEF_REPLACE,
			NULL,  // Use the default media locator
			inNotifyEventHandle);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// Create detailed timeline object tool method
bool CDESTimeLine::CreateEmptyNode(IAMTimelineObj **outObject, TIMELINE_MAJOR_TYPE inType)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->CreateEmptyNode(outObject, inType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetCountOfType(long inGroupIndex, long * outVal, 
								  long * outValWithComps, 
								  TIMELINE_MAJOR_TYPE inType)
{
	if (mTimeLine)
	{
		HRESULT hr = mTimeLine->GetCountOfType(inGroupIndex, outVal, outValWithComps, inType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}
