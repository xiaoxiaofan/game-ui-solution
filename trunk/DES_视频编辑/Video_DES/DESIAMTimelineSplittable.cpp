#include "StdAfx.h"
#include <qedit.h>
#include "DESIAMTimelineSplittable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESIAMTimelineSplittable::CDESIAMTimelineSplittable(void)
{
	m_pSplittable = NULL;
}


CDESIAMTimelineSplittable::~CDESIAMTimelineSplittable(void)
{
	ReleaseSelf();
}

void CDESIAMTimelineSplittable::ReleaseSelf(void)
{
	if (m_pSplittable != NULL)
	{
		m_pSplittable->Release();
		m_pSplittable = NULL;
	}
}

bool CDESIAMTimelineSplittable::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineSplittable,
			(void **) &m_pSplittable);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

void CDESIAMTimelineSplittable::ReleaseInterface(void)
{
	ReleaseSelf();
}

bool CDESIAMTimelineSplittable::SplitAt(REFERENCE_TIME inTime)
{
	if (m_pSplittable)
	{
		HRESULT hr = m_pSplittable->SplitAt(inTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineSplittable::SplitAt2(REFTIME inTime)
{
	if (m_pSplittable)
	{
		HRESULT hr = m_pSplittable->SplitAt2(inTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}
