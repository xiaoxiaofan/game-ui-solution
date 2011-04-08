#include "StdAfx.h"
#include <qedit.h>
#include "DESComposition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESComposition::CDESComposition(CDESTimeLine * inTimeLine) : 
CDESBaseObject(inTimeLine)
{
	m_pInterfaceComp = NULL;
}


CDESComposition::~CDESComposition(void)
{
	ReleaseSelf();
}

void CDESComposition::ReleaseSelf(void)
{
	if (m_pInterfaceComp != NULL)
	{
		m_pInterfaceComp->Release();
		m_pInterfaceComp = NULL;
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
			(void **) &m_pInterfaceComp);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass)  // Query other interfaces
		{
			// Not get pass flag because Group not support IAMTimelineVirtualTrack 
			m_Effectable.SetOwner(mEmptyObject);
			m_Transable.SetOwner(mEmptyObject);
			m_VirtualTrack.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESComposition::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	m_Effectable.SetOwner(NULL);
	m_Transable.SetOwner(NULL);
	m_VirtualTrack.SetOwner(NULL);
}

// --- IAMTimelineComp methods ---
bool CDESComposition::GetNextVTrack(CDESBaseObject * inVTrack, CDESBaseObject & outNextVTrack)
{
	if (m_pInterfaceComp)
	{
		IAMTimelineObj * pObjectOut = NULL;
		IAMTimelineObj * pObjectIn  = NULL;
		if (inVTrack != NULL)
		{
			pObjectIn = inVTrack->GetTimeLineObj();
		}
		if (S_OK == m_pInterfaceComp->GetNextVTrack(pObjectIn, &pObjectOut))
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
	if (m_pInterfaceComp)
	{
		IAMTimelineObj * pObjectOut = NULL;
		HRESULT hr = m_pInterfaceComp->GetRecursiveLayerOfType(&pObjectOut, inLayerIndex, inType);
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
	if (m_pInterfaceComp)
	{
		HRESULT hr = m_pInterfaceComp->VTrackGetCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESComposition::GetVTrack(CDESBaseObject & outVTrack, long inPriority)
{
	if (m_pInterfaceComp)
	{
		IAMTimelineObj * pObjectOut = NULL;
		HRESULT hr = m_pInterfaceComp->GetVTrack(&pObjectOut, inPriority);
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
	if (m_pInterfaceComp)
	{
		IAMTimelineObj * pObjectIn = inVTrack.GetTimeLineObj();
		ASSERT(pObjectIn);
		HRESULT hr = m_pInterfaceComp->VTrackInsBefore(pObjectIn, inPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESComposition::VTrackSwapPriorities(long inVTrackA, long inVTrackB)
{
	if (m_pInterfaceComp)
	{
		HRESULT hr = m_pInterfaceComp->VTrackSwapPriorities(inVTrackA, inVTrackB);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// Typically, an application will not call this method. 
// It is called by the render engine.
bool CDESComposition::GetCountOfType(long * outVal, long * outValWithComps, 
	TIMELINE_MAJOR_TYPE inType)
{
	if (m_pInterfaceComp)
	{
		HRESULT hr = m_pInterfaceComp->GetCountOfType(outVal, outValWithComps, inType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineEffectable methods ---
bool CDESComposition::EffectGetCount(long * outCount)
{
	return m_Effectable.EffectGetCount(outCount);
}

bool CDESComposition::EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority)
{
	return m_Effectable.EffectInsBefore(inEffectObject, inPriority);
}

bool CDESComposition::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	return m_Effectable.EffectSwapPriorities(inPriorityA, inPriorityB);
}

bool CDESComposition::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	return m_Effectable.GetEffect(outEffect, inWhich);
}


// --- IAMTimelineTransable methods ---
bool CDESComposition::TransGetCount(long * outCount)
{
	return mTransable.TransGetCount(outCount);
}

bool CDESComposition::TransAdd(CDESBaseObject & inTransition)
{
	return m_Transable.TransAdd(inTransition);
}

bool CDESComposition::GetNextTrans(CDESBaseObject & outTransition, 
	REFERENCE_TIME * ioStartStop)
{
	return m_Transable.GetNextTrans(outTransition, ioStartStop);
}

bool CDESComposition::GetNextTrans2(CDESBaseObject & outTransition, 
	REFTIME * ioStartStop)
{
	return m_Transable.GetNextTrans2(outTransition, ioStartStop);
}

bool CDESComposition::GetTransAtTime(CDESBaseObject & outTransition, 
	REFERENCE_TIME inTime, 
	long inSearchDirection)
{
	return m_Transable.GetTransAtTime(outTransition, inTime, inSearchDirection);
}

bool CDESComposition::GetTransAtTime2(CDESBaseObject & outTransition, 
	REFTIME inTime, 
	long inSearchDirection)
{
	return m_Transable.GetTransAtTime2(outTransition, inTime, inSearchDirection);
}


// --- IAMTimelineVirtualTrack methods ---
bool CDESComposition::TrackGetPriority(long * outPriority)
{
	return m_VirtualTrack.TrackGetPriority(outPriority);
}