//
// CDESIAMTimelineVirtualTrack.cpp
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
#include "CDESIAMTimelineVirtualTrack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
CDESIAMTimelineVirtualTrack::CDESIAMTimelineVirtualTrack()
{
	mVirtualTrack = NULL;
}

CDESIAMTimelineVirtualTrack::~CDESIAMTimelineVirtualTrack()
{
	ReleaseSelf();
}

void CDESIAMTimelineVirtualTrack::ReleaseSelf(void)
{
	if (mVirtualTrack != NULL)
	{
		mVirtualTrack->Release();
		mVirtualTrack = NULL;
	}
}

bool CDESIAMTimelineVirtualTrack::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineVirtualTrack,
												(void **) &mVirtualTrack);
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
	if (mVirtualTrack)
	{
		HRESULT hr = mVirtualTrack->TrackGetPriority(outPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}