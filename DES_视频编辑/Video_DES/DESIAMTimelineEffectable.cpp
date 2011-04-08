#include "StdAfx.h"
#include <qedit.h>
#include "DESBaseObject.h"
#include "DESIAMTimelineEffectable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESIAMTimelineEffectable::CDESIAMTimelineEffectable(void)
{
	m_pEffectable = NULL;
}


CDESIAMTimelineEffectable::~CDESIAMTimelineEffectable(void)
{
  ReleaseSelf();
}

void CDESIAMTimelineEffectable::ReleaseSelf(void)
{
	if (m_pEffectable != NULL)
	{
		m_pEffectable->Release();
		m_pEffectable = NULL;
	}
}

bool CDESIAMTimelineEffectable::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineEffectable,
			(void **) &m_pEffectable);
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
	if (m_pEffectable)
	{
		HRESULT hr = m_pEffectable->EffectGetCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineEffectable::EffectInsBefore(CDESBaseObject & inEffectObject, 
	long inPriority)
{
	if (m_pEffectable)
	{
		IAMTimelineObj * pEffectObj = inEffectObject.GetTimeLineObj();
		ASSERT(pEffectObj);
		HRESULT hr = m_pEffectable->EffectInsBefore(pEffectObj, inPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineEffectable::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	if (m_pEffectable)
	{
		HRESULT hr = m_pEffectable->EffectSwapPriorities(inPriorityA, inPriorityB);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineEffectable::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	if (m_pEffectable)
	{
		IAMTimelineObj * pEffectObj = NULL;
		HRESULT hr = m_pEffectable->GetEffect(&pEffectObj, inWhich);
		if (hr == S_OK)
		{
			outEffect.Attach(pEffectObj);
			pEffectObj->Release();
			return true;
		}
	}
	return false;
}
