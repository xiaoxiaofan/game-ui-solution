//
// CDESIAMTimelineSplittable.cpp
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
#include "CDESIAMTimelineSplittable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
CDESIAMTimelineSplittable::CDESIAMTimelineSplittable()
{
	mSplittable = NULL;
}

CDESIAMTimelineSplittable::~CDESIAMTimelineSplittable()
{
	ReleaseSelf();
}

void CDESIAMTimelineSplittable::ReleaseSelf(void)
{
	if (mSplittable != NULL)
	{
		mSplittable->Release();
		mSplittable = NULL;
	}
}

bool CDESIAMTimelineSplittable::QueryInterfaceSelf(void)
{
	if (mOwnerObject)
	{
		ReleaseSelf();
		HRESULT hr = mOwnerObject->QueryInterface(IID_IAMTimelineSplittable,
												(void **) &mSplittable);
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
	if (mSplittable)
	{
		HRESULT hr = mSplittable->SplitAt(inTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESIAMTimelineSplittable::SplitAt2(REFTIME inTime)
{
	if (mSplittable)
	{
		HRESULT hr = mSplittable->SplitAt2(inTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}
