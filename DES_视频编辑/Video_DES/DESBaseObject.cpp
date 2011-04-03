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
