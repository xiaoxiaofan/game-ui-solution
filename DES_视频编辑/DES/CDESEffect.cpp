//
// CDESEffect.cpp
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
#include "CDESEffect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
CDESEffect::CDESEffect(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine)
{
	mInterfaceEffect = NULL;
}

CDESEffect::~CDESEffect()
{
	ReleaseSelf();
}

void CDESEffect::ReleaseSelf(void)
{
	if (mInterfaceEffect != NULL)
	{
		mInterfaceEffect->Release();
		mInterfaceEffect = NULL;
	}
}

bool CDESEffect::CreateInstance(void)
{
	if (mEmptyObject == NULL)
	{
		bool pass = mTimeLine->CreateEmptyNode(&mEmptyObject, TIMELINE_MAJOR_TYPE_EFFECT);
		if (!pass)
		{
			mEmptyObject = NULL;
		}
		return pass;
	}
	return true;
}

bool CDESEffect::QueryExtraInterfaces(void)
{
	if (mEmptyObject)
	{
		ReleaseSelf();
		HRESULT hr = mEmptyObject->QueryInterface(IID_IAMTimelineEffect,
												(void **) &mInterfaceEffect);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass) // Query other interfaces
		{
			mSplittable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESEffect::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	mSplittable.SetOwner(NULL);
}

bool CDESEffect::EffectGetPriority(long * outPriority)
{
	if (mInterfaceEffect)
	{
		HRESULT hr = mInterfaceEffect->EffectGetPriority(outPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// --- IAMTimelineSplittable methods ---
bool CDESEffect::SplitAt(REFERENCE_TIME inTime)
{
	return mSplittable.SplitAt(inTime);
}

bool CDESEffect::SplitAt2(REFTIME inTime)
{
	return mSplittable.SplitAt2(inTime);
}