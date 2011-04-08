#include "StdAfx.h"
#include <qedit.h>
#include "DESBaseObject.h"
#include "DESIAMTimelineTransable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESIAMTimelineTransable::CDESIAMTimelineTransable(void)
{
	m_pTransable = NULL;
}


CDESIAMTimelineTransable::~CDESIAMTimelineTransable(void)
{
	ReleaseSelf();
}

void CDESIAMTimelineTransable::ReleaseSelf(void)
{
	if (m_pTransable != NULL)
	{
		m_pTransable->Release();
		m_pTransable = NULL;
	}
}

bool CDESIAMTimelineTransable::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineTransable,
			(void **) &m_pTransable);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

void CDESIAMTimelineTransable::ReleaseInterface(void)
{
	ReleaseSelf();
}

bool CDESIAMTimelineTransable::TransGetCount(long * outCount)
{
	if (m_pTransable)
	{
		HRESULT hr = m_pTransable->TransGetCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineTransable::TransAdd(CDESBaseObject & inTransition)
{
	if (m_pTransable)
	{
		IAMTimelineObj * pTransObj = inTransition.GetTimeLineObj();
		ASSERT(pTransObj);
		HRESULT hr = m_pTransable->TransAdd(pTransObj);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineTransable::GetNextTrans(CDESBaseObject & outTransition, 
	REFERENCE_TIME * ioStartStop)
{
	if (m_pTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = m_pTransable->GetNextTrans(&pTransObj, ioStartStop);
		if (hr == S_OK)
		{
			outTransition.Attach(pTransObj);
			pTransObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESIAMTimelineTransable::GetNextTrans2(CDESBaseObject & outTransition, 
	REFTIME * ioStartStop)
{
	if (m_pTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = m_pTransable->GetNextTrans2(&pTransObj, ioStartStop);
		if (hr == S_OK)
		{
			outTransition.Attach(pTransObj);
			pTransObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESIAMTimelineTransable::GetTransAtTime(CDESBaseObject & outTransition, 
	REFERENCE_TIME inTime, 
	long inSearchDirection)
{
	if (m_pTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = m_pTransable->GetTransAtTime(&pTransObj, inTime, inSearchDirection);
		if (hr == S_OK)
		{
			outTransition.Attach(pTransObj);
			pTransObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESIAMTimelineTransable::GetTransAtTime2(CDESBaseObject & outTransition,
	REFTIME inTime, 
	long inSearchDirection)
{
	if (m_pTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = m_pTransable->GetTransAtTime2(&pTransObj, inTime, inSearchDirection);
		if (hr == S_OK)
		{
			outTransition.Attach(pTransObj);
			pTransObj->Release();
			return true;
		}
	}
	return false;
}