#include "StdAfx.h"
#include <qedit.h>
#include "DESTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESTrack::CDESTrack(CDESTimeLine * inTimeLine) : 
CDESBaseObject(inTimeLine)
{
	m_pInterfaceTrack = NULL;
}


CDESTrack::~CDESTrack(void)
{
	ReleaseSelf();
}

void CDESTrack::ReleaseSelf(void)
{
	if (m_pInterfaceTrack != NULL)
	{
		m_pInterfaceTrack->Release();
		m_pInterfaceTrack = NULL;
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
			(void **) &m_pInterfaceTrack);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass)  // Query other interfaces
		{
			m_Effectable.SetOwner(mEmptyObject);
			m_Transable.SetOwner(mEmptyObject);
			m_VirtualTrack.SetOwner(mEmptyObject);
			m_Splittable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESTrack::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	m_Effectable.SetOwner(NULL);
	m_Transable.SetOwner(NULL);
	m_VirtualTrack.SetOwner(NULL);
	m_Splittable.SetOwner(NULL);
}

bool CDESTrack::AreYouBlank(long * outIsBlank)
{
	if (m_pInterfaceTrack)
	{
		HRESULT hr = m_pInterfaceTrack->AreYouBlank(outIsBlank);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::GetSourcesCount(long * outCount)
{
	if (m_pInterfaceTrack)
	{
		HRESULT hr = m_pInterfaceTrack->GetSourcesCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::SrcAdd(CDESBaseObject & inSource)
{
	if (m_pInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = inSource.GetTimeLineObj();
		ASSERT(pTimeLineObj);
		HRESULT hr = m_pInterfaceTrack->SrcAdd(pTimeLineObj);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::GetNextSrc(CDESBaseObject & outSource, REFERENCE_TIME * ioStartStop)
{
	if (m_pInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = m_pInterfaceTrack->GetNextSrc(&pTimeLineObj, ioStartStop);
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
	if (m_pInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = m_pInterfaceTrack->GetNextSrc2(&pTimeLineObj, ioStartStop);
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
	if (m_pInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObjOut = NULL;
		IAMTimelineObj * pTimeLineObjIn  = NULL;
		if (inLast != NULL)
		{
			pTimeLineObjIn = inLast->GetTimeLineObj();
		}
		HRESULT hr = m_pInterfaceTrack->GetNextSrcEx(pTimeLineObjIn, &pTimeLineObjOut);
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
	if (m_pInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = m_pInterfaceTrack->GetSrcAtTime(&pTimeLineObj, inTime, inSearchDirection);
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
	if (m_pInterfaceTrack)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = m_pInterfaceTrack->GetSrcAtTime2(&pTimeLineObj, inTime, inSearchDirection);
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
	if (m_pInterfaceTrack)
	{
		HRESULT hr = m_pInterfaceTrack->InsertSpace(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::InsertSpace2(REFTIME inStart, REFTIME inEnd)
{
	if (m_pInterfaceTrack)
	{
		HRESULT hr = m_pInterfaceTrack->InsertSpace2(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::ZeroBetween(REFERENCE_TIME inStart, REFERENCE_TIME inEnd)
{
	if (m_pInterfaceTrack)
	{
		HRESULT hr = m_pInterfaceTrack->ZeroBetween(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTrack::ZeroBetween2(REFTIME inStart, REFTIME inEnd)
{
	if (m_pInterfaceTrack)
	{
		HRESULT hr = m_pInterfaceTrack->ZeroBetween2(inStart, inEnd);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineEffectable methods ---
bool CDESTrack::EffectGetCount(long * outCount)
{
	return m_Effectable.EffectGetCount(outCount);
}

bool CDESTrack::EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority)
{
	return m_Effectable.EffectInsBefore(inEffectObject, inPriority);
}

bool CDESTrack::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	return m_Effectable.EffectSwapPriorities(inPriorityA, inPriorityB);
}

bool CDESTrack::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	return m_Effectable.GetEffect(outEffect, inWhich);
}


// --- IAMTimelineTransable methods ---
bool CDESTrack::TransGetCount(long * outCount)
{
	return m_Transable.TransGetCount(outCount);
}

bool CDESTrack::TransAdd(CDESBaseObject & inTransition)
{
	return m_Transable.TransAdd(inTransition);
}

bool CDESTrack::GetNextTrans(CDESBaseObject & outTransition, 
	REFERENCE_TIME * ioStartStop)
{
	return m_Transable.GetNextTrans(outTransition, ioStartStop);
}

bool CDESTrack::GetNextTrans2(CDESBaseObject & outTransition, 
	REFTIME * ioStartStop)
{
	return m_Transable.GetNextTrans2(outTransition, ioStartStop);
}

bool CDESTrack::GetTransAtTime(CDESBaseObject & outTransition, 
	REFERENCE_TIME inTime, 
	long inSearchDirection)
{
	return m_Transable.GetTransAtTime(outTransition, inTime, inSearchDirection);
}

bool CDESTrack::GetTransAtTime2(CDESBaseObject & outTransition, 
	REFTIME inTime, 
	long inSearchDirection)
{
	return m_Transable.GetTransAtTime2(outTransition, inTime, inSearchDirection);
}


// --- IAMTimelineVirtualTrack methods ---
bool CDESTrack::TrackGetPriority(long * outPriority)
{
	return m_VirtualTrack.TrackGetPriority(outPriority);
}


// --- IAMTimelineSplittable methods ---
bool CDESTrack::SplitAt(REFERENCE_TIME inTime)
{
	return m_Splittable.SplitAt(inTime);
}

bool CDESTrack::SplitAt2(REFTIME inTime)
{
	return m_Splittable.SplitAt2(inTime);
}