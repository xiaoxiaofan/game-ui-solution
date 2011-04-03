//
// CDESBaseObject.cpp
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

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
CDESBaseObject::CDESBaseObject(CDESTimeLine * inTimeLine) :
mTimeLine(inTimeLine),
mEmptyObject(NULL)
{
	ASSERT(mTimeLine);
}

CDESBaseObject::~CDESBaseObject()
{
	ReleaseSelf();
}

void CDESBaseObject::ReleaseSelf(void)
{
	if (mEmptyObject != NULL)
	{
		mEmptyObject->Release();
		mEmptyObject = NULL;
	}
}

bool CDESBaseObject::Attach(IAMTimelineObj * inObject)
{
	ReleaseExtraInterfaces();
	ReleaseSelf();
	if (inObject != NULL)
	{
		// Outstanding Reference
		inObject->AddRef();
	}
	mEmptyObject = inObject;
	return QueryExtraInterfaces();
}

bool CDESBaseObject::Initialize(void)
{
	// Create instance and query extra interfaces
	bool pass = CreateInstance();
	if (pass)
	{
		pass = QueryExtraInterfaces();
	}
	return pass;
}

bool CDESBaseObject::CreateInstance(void)
{
	return false;
}

bool CDESBaseObject::QueryExtraInterfaces(void)
{
	return true;
}

void CDESBaseObject::ReleaseExtraInterfaces(void)
{
}

IAMTimelineObj * CDESBaseObject::GetTimeLineObj(void)
{
	return mEmptyObject;
}

bool CDESBaseObject::GetTimelineType(TIMELINE_MAJOR_TYPE * outType)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetTimelineType(outType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::FixTimes(REFERENCE_TIME * ioStart, REFERENCE_TIME * ioStop)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->FixTimes(ioStart, ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::FixTimes2(REFTIME * ioStart, REFTIME * ioStop)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->FixTimes2(ioStart, ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetSubObjectGUID(GUID inGuid)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetSubObjectGUID(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetSubObjectGUIDB(BSTR inGuid)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetSubObjectGUIDB(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetSubObjectGUID(GUID * outGuid)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetSubObjectGUID(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetSubObjectGUIDB(BSTR * outGuid)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetSubObjectGUIDB(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetPropertySetter(CDESPropertySetter & inSetter)
{
	if (mEmptyObject)
	{
		IPropertySetter * pSetter = inSetter.GetPropertySetter();
		ASSERT(pSetter);
		HRESULT hr = mEmptyObject->SetPropertySetter(pSetter);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetPropertySetter(CDESPropertySetter & outSetter)
{
	if (mEmptyObject)
	{
		IPropertySetter * pSetter = NULL;
		HRESULT hr = mEmptyObject->GetPropertySetter(&pSetter);
		if (SUCCEEDED(hr) && pSetter != NULL)
		{
			outSetter.Attach(pSetter);
			pSetter->Release();
			return true;
		}
	}
	return false;
}

bool CDESBaseObject::SetStartStop(REFERENCE_TIME inStart, REFERENCE_TIME inStop)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetStartStop(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetStartStop2(REFTIME inStart, REFTIME inStop)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetStartStop2(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetStartStop(REFERENCE_TIME * outStart, REFERENCE_TIME * outStop)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetStartStop(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetStartStop2(REFTIME * outStart, REFTIME * outStop)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetStartStop2(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::Remove(void)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->Remove();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::RemoveAll(void)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->RemoveAll();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetMuted(BOOL inMuted)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetMuted(inMuted);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

BOOL CDESBaseObject::GetMuted(void)
{
	if (mEmptyObject)
	{
		BOOL isMuted = FALSE;
		mEmptyObject->GetMuted(&isMuted);
		return isMuted;
	}
	return FALSE;
}

bool CDESBaseObject::SetLocked(BOOL inLocked)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetLocked(inLocked);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

BOOL CDESBaseObject::GetLocked(void)
{
	if (mEmptyObject)
	{
		BOOL isLocked = FALSE;
		mEmptyObject->GetLocked(&isLocked);
		return isLocked;
	}
	return FALSE;
}

bool CDESBaseObject::SetUserData(BYTE * inData, long inSize)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetUserData(inData, inSize);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetUserID(long inObjectId)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetUserID(inObjectId);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetUserName(BSTR inObjectName)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->SetUserName(inObjectName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

// Pass outData NULL to get buffer size needed
bool CDESBaseObject::GetUserData(BYTE * outData, long * outSize)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetUserData(outData, outSize);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetUserID(long * outObjectId)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetUserID(outObjectId);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetUserName(BSTR * outObjectName)
{
	if (mEmptyObject)
	{
		HRESULT hr = mEmptyObject->GetUserName(outObjectName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}