#include "StdAfx.h"
#include <qedit.h>
#include "DESTransition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESTransition::CDESTransition(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine)
{
	m_pInterfaceTrans = NULL;
}


CDESTransition::~CDESTransition(void)
{
	ReleaseSelf();
}

void CDESTransition::ReleaseSelf(void)
{
	if (m_pInterfaceTrans != NULL)
	{
		m_pInterfaceTrans->Release();
		m_pInterfaceTrans = NULL;
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
			(void **) &m_pInterfaceTrans);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass)   
		{
			m_Splittable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESTransition::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	m_Splittable.SetOwner(NULL);
}

bool CDESTransition::SetCutPoint(REFERENCE_TIME inTLTime)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->SetCutPoint(inTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetCutPoint(REFERENCE_TIME * outTLTime)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->GetCutPoint(outTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::SetCutPoint2(REFTIME inTLTime)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->SetCutPoint2(inTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetCutPoint2(REFTIME * outTLTime)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->GetCutPoint2(outTLTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::SetCutsOnly(BOOL inIsCut)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->SetCutsOnly(inIsCut);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetCutsOnly(BOOL * outIsCut)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->GetCutsOnly(outIsCut);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::SetSwapInputs(BOOL inIsSwap)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->SetSwapInputs(inIsSwap);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTransition::GetSwapInputs(BOOL * outIsSwap)
{
	if (m_pInterfaceTrans)
	{
		HRESULT hr = m_pInterfaceTrans->GetSwapInputs(outIsSwap);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineSplittable methods ---
bool CDESTransition::SplitAt(REFERENCE_TIME inTime)
{
	return m_Splittable.SplitAt(inTime);
}

bool CDESTransition::SplitAt2(REFTIME inTime)
{
	return m_Splittable.SplitAt2(inTime);
}