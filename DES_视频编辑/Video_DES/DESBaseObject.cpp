#include "StdAfx.h"
#include <qedit.h>
#include "DESBaseObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESBaseObject::CDESBaseObject(CDESTimeLine *inTimeLine):
   m_pTimeLine(inTimeLine),
   m_pEmptyObject(NULL)
{
	ASSERT(m_pTimeLine);
}


CDESBaseObject::~CDESBaseObject(void)
{
	ReleaseSelf();
}

void CDESBaseObject::ReleaseSelf( void )
{
	if (m_pEmptyObject != NULL)
	{
		m_pEmptyObject->Release();
		m_pEmptyObject = NULL;
	}
}

bool CDESBaseObject::Attach( IAMTimelineObj * inObject )
{
	ReleaseExtraInterfaces();
	ReleaseSelf();
	if (inObject != NULL)
	{
		inObject->AddRef();
		m_pEmptyObject = inObject;
	}
	return QueryExtraInterfaces();
}

void CDESBaseObject::ReleaseExtraInterfaces( void )
{

}

bool CDESBaseObject::QueryExtraInterfaces( void )
{
	return true;
}

bool CDESBaseObject::Initialize( void )
{
	bool pass = CreateInstance();
	if (pass)
	{
		pass = QueryExtraInterfaces();
	}
	return pass;
}

bool CDESBaseObject::CreateInstance( void )
{
	return false;
}

IAMTimelineObj * CDESBaseObject::GetTimeLineObj( void )
{
	return m_pEmptyObject;
}

bool CDESBaseObject::GetTimeLineType( TIMELINE_MAJOR_TYPE * outType )
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetTimelineType(outType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::FixTimes( REFERENCE_TIME * ioStart,REFERENCE_TIME * ioStop )
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->FixTimes(ioStart,ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::FixTimes2( REFTIME * ioStart,REFTIME * ioStop )
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->FixTimes2(ioStart, ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetSubObjectGUID( GUID inGuid )
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetSubObjectGUID(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetSubObjectGUIDB(BSTR inGuid)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetSubObjectGUIDB(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetSubObjectGUID(GUID * outGuid)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetSubObjectGUID(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetSubObjectGUIDB(BSTR * outGuid)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetSubObjectGUIDB(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetPropertySetter(CDESPropertySetter & inSetter)
{
	if (m_pEmptyObject)
	{
		IPropertySetter * pSetter = inSetter.GetPropertySetter();
		ASSERT(pSetter);
		HRESULT hr = m_pEmptyObject->SetPropertySetter(pSetter);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetPropertySetter(CDESPropertySetter & outSetter)
{
	if (m_pEmptyObject)
	{
		IPropertySetter * pSetter = NULL;
		HRESULT hr = m_pEmptyObject->GetPropertySetter(&pSetter);
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
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetStartStop(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetStartStop2(REFTIME inStart, REFTIME inStop)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetStartStop2(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetStartStop(REFERENCE_TIME * outStart, REFERENCE_TIME * outStop)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetStartStop(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetStartStop2(REFTIME * outStart, REFTIME * outStop)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetStartStop2(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::Remove(void)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->Remove();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::RemoveAll(void)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->RemoveAll();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetMuted(BOOL inMuted)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetMuted(inMuted);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

BOOL CDESBaseObject::GetMuted(void)
{
	if (m_pEmptyObject)
	{
		BOOL isMuted = FALSE;
		m_pEmptyObject->GetMuted(&isMuted);
		return isMuted;
	}
	return FALSE;
}

bool CDESBaseObject::SetLocked(BOOL inLocked)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetLocked(inLocked);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

BOOL CDESBaseObject::GetLocked(void)
{
	if (m_pEmptyObject)
	{
		BOOL isLocked = FALSE;
		m_pEmptyObject->GetLocked(&isLocked);
		return isLocked;
	}
	return FALSE;
}

bool CDESBaseObject::SetUserData(BYTE * inData, long inSize)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetUserData(inData, inSize);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetUserID(long inObjectId)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetUserID(inObjectId);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::SetUserName(BSTR inObjectName)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->SetUserName(inObjectName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetUserData(BYTE * outData, long * outSize)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetUserData(outData, outSize);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetUserID(long * outObjectId)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetUserID(outObjectId);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESBaseObject::GetUserName(BSTR * outObjectName)
{
	if (m_pEmptyObject)
	{
		HRESULT hr = m_pEmptyObject->GetUserName(outObjectName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}