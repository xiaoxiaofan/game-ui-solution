//
// CDESIAMTimelineTransable.cpp
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
#include "CDESBaseObject.h"
#include "CDESIAMTimelineTransable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
CDESIAMTimelineTransable::CDESIAMTimelineTransable()
{
	mTransable = NULL;
}

CDESIAMTimelineTransable::~CDESIAMTimelineTransable()
{
	ReleaseSelf();
}

void CDESIAMTimelineTransable::ReleaseSelf(void)
{
	if (mTransable != NULL)
	{
		mTransable->Release();
		mTransable = NULL;
	}
}

bool CDESIAMTimelineTransable::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineTransable,
												(void **) &mTransable);
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
	if (mTransable)
	{
		HRESULT hr = mTransable->TransGetCount(outCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineTransable::TransAdd(CDESBaseObject & inTransition)
{
	if (mTransable)
	{
		IAMTimelineObj * pTransObj = inTransition.GetTimeLineObj();
		ASSERT(pTransObj);
		HRESULT hr = mTransable->TransAdd(pTransObj);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineTransable::GetNextTrans(CDESBaseObject & outTransition, 
											REFERENCE_TIME * ioStartStop)
{
	if (mTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = mTransable->GetNextTrans(&pTransObj, ioStartStop);
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
	if (mTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = mTransable->GetNextTrans2(&pTransObj, ioStartStop);
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
	if (mTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = mTransable->GetTransAtTime(&pTransObj, inTime, inSearchDirection);
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
	if (mTransable)
	{
		IAMTimelineObj * pTransObj = NULL;
		HRESULT hr = mTransable->GetTransAtTime2(&pTransObj, inTime, inSearchDirection);
		if (hr == S_OK)
		{
			outTransition.Attach(pTransObj);
			pTransObj->Release();
			return true;
		}
	}
	return false;
}