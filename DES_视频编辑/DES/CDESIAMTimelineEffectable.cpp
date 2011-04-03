//
// CDESIAMTimelineEffectable.cpp
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
#include "CDESBaseObject.h"
#include "CDESIAMTimelineEffectable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
CDESIAMTimelineEffectable::CDESIAMTimelineEffectable()
{
	mEffectable = NULL;
}

CDESIAMTimelineEffectable::~CDESIAMTimelineEffectable()
{
	ReleaseSelf();
}

void CDESIAMTimelineEffectable::ReleaseSelf(void)
{
	if (mEffectable != NULL)
	{
		mEffectable->Release();
		mEffectable = NULL;
	}
}

bool CDESIAMTimelineEffectable::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineEffectable,
												(void **) &mEffectable);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

void CDESIAMTimelineEffectable::ReleaseInterface(void)
{
	ReleaseSelf();
}

bool CDESIAMTimelineEffectable::EffectGetCount(long * outCount)
{
	if (mEffectable)
	{
		HRESULT hr = mEffectable->EffectGetCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineEffectable::EffectInsBefore(CDESBaseObject & inEffectObject, 
												long inPriority)
{
	if (mEffectable)
	{
		IAMTimelineObj * pEffectObj = inEffectObject.GetTimeLineObj();
		ASSERT(pEffectObj);
		HRESULT hr = mEffectable->EffectInsBefore(pEffectObj, inPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineEffectable::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	if (mEffectable)
	{
		HRESULT hr = mEffectable->EffectSwapPriorities(inPriorityA, inPriorityB);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineEffectable::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	if (mEffectable)
	{
		IAMTimelineObj * pEffectObj = NULL;
		HRESULT hr = mEffectable->GetEffect(&pEffectObj, inWhich);
		if (hr == S_OK)
		{
			outEffect.Attach(pEffectObj);
			pEffectObj->Release();
			return true;
		}
	}
	return false;
}