//
// CDESComposition.cpp
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
#include "CDESComposition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
CDESComposition::CDESComposition(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine)
{
	mInterfaceComp = NULL;
}

CDESComposition::~CDESComposition()
{
	ReleaseSelf();
}

void CDESComposition::ReleaseSelf(void)
{
	if (mInterfaceComp != NULL)
	{
		mInterfaceComp->Release();
		mInterfaceComp = NULL;
	}
}

bool CDESComposition::CreateInstance(void)
{
	if (mEmptyObject == NULL)
	{
		bool pass = mTimeLine->CreateEmptyNode(&mEmptyObject, TIMELINE_MAJOR_TYPE_COMPOSITE);
		if (!pass)
		{
			mEmptyObject = NULL;
		}
		return pass;
	}
	return true;
}

bool CDESComposition::QueryExtraInterfaces(void)
{
	if (mEmptyObject)
	{
		ReleaseSelf();
		HRESULT hr = mEmptyObject->QueryInterface(IID_IAMTimelineComp,
												(void **) &mInterfaceComp);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass)  // Query other interfaces
		{
			// Not get pass flag because Group not support IAMTimelineVirtualTrack 
			mEffectable.SetOwner(mEmptyObject);
			mTransable.SetOwner(mEmptyObject);
			mVirtualTrack.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESComposition::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	mEffectable.SetOwner(NULL);
	mTransable.SetOwner(NULL);
	mVirtualTrack.SetOwner(NULL);
}

// --- IAMTimelineComp methods ---
bool CDESComposition::GetNextVTrack(CDESBaseObject * inVTrack, CDESBaseObject & outNextVTrack)
{
	if (mInterfaceComp)
	{
		IAMTimelineObj * pObjectOut = NULL;
		IAMTimelineObj * pObjectIn  = NULL;
		if (inVTrack != NULL)
		{
			pObjectIn = inVTrack->GetTimeLineObj();
		}
		if (S_OK == mInterfaceComp->GetNextVTrack(pObjectIn, &pObjectOut))
		{
			outNextVTrack.Attach(pObjectOut);
			pObjectOut->Release();
			return true;
		}
	}
	return false;
}

bool CDESComposition::GetRecursiveLayerOfType(CDESBaseObject & outVTrack, 
											  long inLayerIndex, 
											  TIMELINE_MAJOR_TYPE inType)
{
	if (mInterfaceComp)
	{
		IAMTimelineObj * pObjectOut = NULL;
		HRESULT hr = mInterfaceComp->GetRecursiveLayerOfType(&pObjectOut, inLayerIndex, inType);
		if (SUCCEEDED(hr))
		{
			outVTrack.Attach(pObjectOut);
			pObjectOut->Release();
			return true;
		}
	}
	return false;
}

bool CDESComposition::VTrackGetCount(long * outCount)
{
	if (mInterfaceComp)
	{
		HRESULT hr = mInterfaceComp->VTrackGetCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESComposition::GetVTrack(CDESBaseObject & outVTrack, long inPriority)
{
	if (mInterfaceComp)
	{
		IAMTimelineObj * pObjectOut = NULL;
		HRESULT hr = mInterfaceComp->GetVTrack(&pObjectOut, inPriority);
		if (SUCCEEDED(hr))
		{
			outVTrack.Attach(pObjectOut);
			pObjectOut->Release();
			return true;
		}
	}
	return false;
}

bool CDESComposition::VTrackInsBefore(CDESBaseObject & inVTrack, long inPriority)
{
	if (mInterfaceComp)
	{
		IAMTimelineObj * pObjectIn = inVTrack.GetTimeLineObj();
		ASSERT(pObjectIn);
		HRESULT hr = mInterfaceComp->VTrackInsBefore(pObjectIn, inPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESComposition::VTrackSwapPriorities(long inVTrackA, long inVTrackB)
{
	if (mInterfaceComp)
	{
		HRESULT hr = mInterfaceComp->VTrackSwapPriorities(inVTrackA, inVTrackB);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// Typically, an application will not call this method. 
// It is called by the render engine.
bool CDESComposition::GetCountOfType(long * outVal, long * outValWithComps, 
									 TIMELINE_MAJOR_TYPE inType)
{
	if (mInterfaceComp)
	{
		HRESULT hr = mInterfaceComp->GetCountOfType(outVal, outValWithComps, inType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineEffectable methods ---
bool CDESComposition::EffectGetCount(long * outCount)
{
	return mEffectable.EffectGetCount(outCount);
}

bool CDESComposition::EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority)
{
	return mEffectable.EffectInsBefore(inEffectObject, inPriority);
}

bool CDESComposition::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	return mEffectable.EffectSwapPriorities(inPriorityA, inPriorityB);
}

bool CDESComposition::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	return mEffectable.GetEffect(outEffect, inWhich);
}


// --- IAMTimelineTransable methods ---
bool CDESComposition::TransGetCount(long * outCount)
{
	return mTransable.TransGetCount(outCount);
}

bool CDESComposition::TransAdd(CDESBaseObject & inTransition)
{
	return mTransable.TransAdd(inTransition);
}

bool CDESComposition::GetNextTrans(CDESBaseObject & outTransition, 
								   REFERENCE_TIME * ioStartStop)
{
	return mTransable.GetNextTrans(outTransition, ioStartStop);
}

bool CDESComposition::GetNextTrans2(CDESBaseObject & outTransition, 
									REFTIME * ioStartStop)
{
	return mTransable.GetNextTrans2(outTransition, ioStartStop);
}

bool CDESComposition::GetTransAtTime(CDESBaseObject & outTransition, 
									 REFERENCE_TIME inTime, 
									 long inSearchDirection)
{
	return mTransable.GetTransAtTime(outTransition, inTime, inSearchDirection);
}

bool CDESComposition::GetTransAtTime2(CDESBaseObject & outTransition, 
									  REFTIME inTime, 
									  long inSearchDirection)
{
	return mTransable.GetTransAtTime2(outTransition, inTime, inSearchDirection);
}


// --- IAMTimelineVirtualTrack methods ---
bool CDESComposition::TrackGetPriority(long * outPriority)
{
	return mVirtualTrack.TrackGetPriority(outPriority);
}