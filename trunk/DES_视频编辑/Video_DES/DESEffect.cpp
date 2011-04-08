#include "StdAfx.h"
#include <qedit.h>
#include "DESEffect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESEffect::CDESEffect(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine)
{
	m_InterfaceEffect = NULL;
}


CDESEffect::~CDESEffect(void)
{
	ReleaseSelf();
}

void CDESEffect::ReleaseSelf(void)
{
	if (m_InterfaceEffect != NULL)
	{
		m_InterfaceEffect->Release();
		m_InterfaceEffect = NULL;
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
			(void **) &m_InterfaceEffect);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass) // Query other interfaces
		{
			m_Splittable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESEffect::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	m_Splittable.SetOwner(NULL);
}

bool CDESEffect::EffectGetPriority(long * outPriority)
{
	if (m_InterfaceEffect)
	{
		HRESULT hr = m_InterfaceEffect->EffectGetPriority(outPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// --- IAMTimelineSplittable methods ---
bool CDESEffect::SplitAt(REFERENCE_TIME inTime)
{
	return m_Splittable.SplitAt(inTime);
}

bool CDESEffect::SplitAt2(REFTIME inTime)
{
	return m_Splittable.SplitAt2(inTime);
}
