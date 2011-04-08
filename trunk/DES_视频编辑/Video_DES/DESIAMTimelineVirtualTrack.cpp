#include "StdAfx.h"
#include <qedit.h>
#include "DESIAMTimelineVirtualTrack.h"


CDESIAMTimelineVirtualTrack::CDESIAMTimelineVirtualTrack(void)
{
	m_pVirtualTrack = NULL;
}


CDESIAMTimelineVirtualTrack::~CDESIAMTimelineVirtualTrack(void)
{
	ReleaseSelf();
}

void CDESIAMTimelineVirtualTrack::ReleaseSelf(void)
{
	if (m_pVirtualTrack != NULL)
	{
		m_pVirtualTrack->Release();
		m_pVirtualTrack = NULL;
	}
}

bool CDESIAMTimelineVirtualTrack::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineVirtualTrack,
			(void **) &m_pVirtualTrack);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

void CDESIAMTimelineVirtualTrack::ReleaseInterface(void)
{
	ReleaseSelf();
}

bool CDESIAMTimelineVirtualTrack::TrackGetPriority(long * outPriority)
{
	if (m_pVirtualTrack)
	{
		HRESULT hr = m_pVirtualTrack->TrackGetPriority(outPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}