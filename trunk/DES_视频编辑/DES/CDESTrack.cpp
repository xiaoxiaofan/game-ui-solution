//
// CDESTrack.cpp
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
#include "CDESTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
CDESTrack::CDESTrack(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine)
{
	mInterfaceTrack = NULL;
}

CDESTrack::~CDESTrack()
{
	ReleaseSelf();
}

void CDESTrack::ReleaseSelf(void)
{
	if (mInterfaceTrack != NULL)
	{
		mInterfaceTrack->Release();
		mInterfaceTrack = NULL;
	}
}

bool CDESTrack::CreateInstance(void)
{
	if (mEmptyObject == NULL)
	{
		bool pass = mTimeLine->CreateEmptyNode(&mEmptyObject, TIMELINE_MAJOR_TYPE_TRACK);
		if (!pass)
		{
			mEmptyObject = NULL;
		}
		return pass;
	}
	return true;
}

bool CDESTrack::QueryExtraInterfaces(void)
{
	if (mEmptyObject)
	{
		ReleaseSelf();
		HRESULT hr = mEmptyObject->QueryInterface(IID_IAMTimelineTrack,
												(void **) &mInterfaceTrack);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass)  // Query other interfaces
		{
			mEffectable.SetOwner(mEmptyObject);
			mTransable.SetOwner(mEmptyObject);
			mVirtualTrack.SetOwner(mEmptyObject);
			mSplittable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESTrack::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	mEffectable.SetOwner(NULL);
	mTransable.SetOwner(NULL);
	mVirtualTrack.SetOwner(NULL);
	mSplittable.SetOwner(NULL);
}

bool CDESTrack::AreYouBlank(long * outIsBlank)
{
	if (mInterfaceTrack)
	{
		HRESULT hr = mInterfaceTrack->AreYouBlank(outIsBlank);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::GetSourcesCount(long * outCount)
{
	if (mInterfaceTrack)
	{
		HRESULT hr = mInterfaceTrack->GetSourcesCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::SrcAdd(CDESBaseObject & inSource)
{
	if (mInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = inSource.GetTimeLineObj();
		ASSERT(pTimeLineObj);
		HRESULT hr = mInterfaceTrack->SrcAdd(pTimeLineObj);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::GetNextSrc(CDESBaseObject & outSource, REFERENCE_TIME * ioStartStop)
{
	if (mInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = mInterfaceTrack->GetNextSrc(&pTimeLineObj, ioStartStop);
		if (hr == S_OK)
		{
			outSource.Attach(pTimeLineObj);
			pTimeLineObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESTrack::GetNextSrc2(CDESBaseObject & outSource, REFTIME * ioStartStop)
{
	if (mInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = mInterfaceTrack->GetNextSrc2(&pTimeLineObj, ioStartStop);
		if (hr == S_OK)
		{
			outSource.Attach(pTimeLineObj);
			pTimeLineObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESTrack::GetNextSrcEx(CDESBaseObject * inLast, CDESBaseObject & outNext)
{
	if (mInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObjOut = NULL;
		IAMTimelineObj * pTimeLineObjIn  = NULL;
		if (inLast != NULL)
		{
			pTimeLineObjIn = inLast->GetTimeLineObj();
		}
		HRESULT hr = mInterfaceTrack->GetNextSrcEx(pTimeLineObjIn, &pTimeLineObjOut);
		if (hr == S_OK)
		{
			outNext.Attach(pTimeLineObjOut);
			pTimeLineObjOut->Release();
			return true;
		}
	}
	return false;
}

bool CDESTrack::GetSrcAtTime(CDESBaseObject & outSource, 
										REFERENCE_TIME inTime, 
										long inSearchDirection)
{
	if (mInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = mInterfaceTrack->GetSrcAtTime(&pTimeLineObj, inTime, inSearchDirection);
		if (hr == S_OK)
		{
			outSource.Attach(pTimeLineObj);
			pTimeLineObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESTrack::GetSrcAtTime2(CDESBaseObject & outSource, REFTIME inTime, long inSearchDirection)
{
	if (mInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = mInterfaceTrack->GetSrcAtTime2(&pTimeLineObj, inTime, inSearchDirection);
		if (hr == S_OK)
		{
			outSource.Attach(pTimeLineObj);
			pTimeLineObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESTrack::InsertSpace(REFERENCE_TIME inStart, REFERENCE_TIME inEnd)
{
	if (mInterfaceTrack)
	{
		HRESULT hr = mInterfaceTrack->InsertSpace(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::InsertSpace2(REFTIME inStart, REFTIME inEnd)
{
	if (mInterfaceTrack)
	{
		HRESULT hr = mInterfaceTrack->InsertSpace2(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::ZeroBetween(REFERENCE_TIME inStart, REFERENCE_TIME inEnd)
{
	if (mInterfaceTrack)
	{
		HRESULT hr = mInterfaceTrack->ZeroBetween(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::ZeroBetween2(REFTIME inStart, REFTIME inEnd)
{
	if (mInterfaceTrack)
	{
		HRESULT hr = mInterfaceTrack->ZeroBetween2(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineEffectable methods ---
bool CDESTrack::EffectGetCount(long * outCount)
{
	return mEffectable.EffectGetCount(outCount);
}

bool CDESTrack::EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority)
{
	return mEffectable.EffectInsBefore(inEffectObject, inPriority);
}

bool CDESTrack::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	return mEffectable.EffectSwapPriorities(inPriorityA, inPriorityB);
}

bool CDESTrack::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	return mEffectable.GetEffect(outEffect, inWhich);
}


// --- IAMTimelineTransable methods ---
bool CDESTrack::TransGetCount(long * outCount)
{
	return mTransable.TransGetCount(outCount);
}

bool CDESTrack::TransAdd(CDESBaseObject & inTransition)
{
	return mTransable.TransAdd(inTransition);
}

bool CDESTrack::GetNextTrans(CDESBaseObject & outTransition, 
							 REFERENCE_TIME * ioStartStop)
{
	return mTransable.GetNextTrans(outTransition, ioStartStop);
}

bool CDESTrack::GetNextTrans2(CDESBaseObject & outTransition, 
							  REFTIME * ioStartStop)
{
	return mTransable.GetNextTrans2(outTransition, ioStartStop);
}

bool CDESTrack::GetTransAtTime(CDESBaseObject & outTransition, 
							   REFERENCE_TIME inTime, 
							   long inSearchDirection)
{
	return mTransable.GetTransAtTime(outTransition, inTime, inSearchDirection);
}

bool CDESTrack::GetTransAtTime2(CDESBaseObject & outTransition, 
								REFTIME inTime, 
								long inSearchDirection)
{
	return mTransable.GetTransAtTime2(outTransition, inTime, inSearchDirection);
}


// --- IAMTimelineVirtualTrack methods ---
bool CDESTrack::TrackGetPriority(long * outPriority)
{
	return mVirtualTrack.TrackGetPriority(outPriority);
}


// --- IAMTimelineSplittable methods ---
bool CDESTrack::SplitAt(REFERENCE_TIME inTime)
{
	return mSplittable.SplitAt(inTime);
}

bool CDESTrack::SplitAt2(REFTIME inTime)
{
	return mSplittable.SplitAt2(inTime);
}