//
// CDESTransition.cpp
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
#include "CDESTransition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
CDESTransition::CDESTransition(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine)
{
	mInterfaceTrans = NULL;
}

CDESTransition::~CDESTransition()
{
	ReleaseSelf();
}

void CDESTransition::ReleaseSelf(void)
{
	if (mInterfaceTrans != NULL)
	{
		mInterfaceTrans->Release();
		mInterfaceTrans = NULL;
	}
}

bool CDESTransition::CreateInstance(void)
{
	if (mEmptyObject == NULL)
	{
		bool pass = mTimeLine->CreateEmptyNode(&mEmptyObject, TIMELINE_MAJOR_TYPE_TRANSITION);
		if (!pass)
		{
			mEmptyObject = NULL;
		}
		return pass;
	}
	return true;
}

bool CDESTransition::QueryExtraInterfaces(void)
{
	if (mEmptyObject)
	{
		ReleaseSelf();
		HRESULT hr = mEmptyObject->QueryInterface(IID_IAMTimelineTrans,
												(void **) &mInterfaceTrans);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass) // Query other interfaces
		{
			mSplittable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESTransition::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	mSplittable.SetOwner(NULL);
}

bool CDESTransition::SetCutPoint(REFERENCE_TIME inTLTime)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->SetCutPoint(inTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetCutPoint(REFERENCE_TIME * outTLTime)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->GetCutPoint(outTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::SetCutPoint2(REFTIME inTLTime)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->SetCutPoint2(inTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetCutPoint2(REFTIME * outTLTime)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->GetCutPoint2(outTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::SetCutsOnly(BOOL inIsCut)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->SetCutsOnly(inIsCut);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetCutsOnly(BOOL * outIsCut)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->GetCutsOnly(outIsCut);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::SetSwapInputs(BOOL inIsSwap)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->SetSwapInputs(inIsSwap);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetSwapInputs(BOOL * outIsSwap)
{
	if (mInterfaceTrans)
	{
		HRESULT hr = mInterfaceTrans->GetSwapInputs(outIsSwap);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineSplittable methods ---
bool CDESTransition::SplitAt(REFERENCE_TIME inTime)
{
	return mSplittable.SplitAt(inTime);
}

bool CDESTransition::SplitAt2(REFTIME inTime)
{
	return mSplittable.SplitAt2(inTime);
}