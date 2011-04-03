//
// CDESBaseInterface.cpp
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
#include "CDESBaseInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
CDESBaseInterface::CDESBaseInterface()
{
	mOwnerObject = NULL;
}

CDESBaseInterface::~CDESBaseInterface()
{
	ReleaseSelf();
}

void CDESBaseInterface::ReleaseSelf(void)
{
	if (mOwnerObject != NULL)
	{
		mOwnerObject->Release();
		mOwnerObject = NULL;
	}
}

bool CDESBaseInterface::SetOwner(IAMTimelineObj * inOwner)
{
	ReleaseInterface();
	ReleaseSelf();

	if (inOwner != NULL)
	{
		inOwner->AddRef();
		mOwnerObject = inOwner;
		return QueryInterfaceSelf();
	}
	return true;
}

IAMTimelineObj * CDESBaseInterface::GetOwner(void)
{
	return mOwnerObject;
}

/*
bool CDESBaseInterface::QueryInterfaceSelf(void)
{
	return false;
}*/