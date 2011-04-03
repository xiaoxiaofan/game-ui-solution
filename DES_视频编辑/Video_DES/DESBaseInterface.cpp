#include "StdAfx.h"
#include <qedit.h>
#include "DESBaseInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESBaseInterface::CDESBaseInterface(void)
{
	m_OwnerObject = NULL;
}


CDESBaseInterface::~CDESBaseInterface(void)
{
	ReleaseSelf();
}

void CDESBaseInterface::ReleaseSelf(void)
{
	if (m_OwnerObject != NULL)
	{
		m_OwnerObject->Release();
		m_OwnerObject = NULL;
	}
}


bool CDESBaseInterface::SetOwner(IAMTimelineObj * inOwner)
{
	ReleaseInterface();
	ReleaseSelf();

	if (inOwner != NULL)
	{
		inOwner->AddRef();
		m_OwnerObject = inOwner;
		return QueryInterfaceSelf();
	}
	return true;
}

IAMTimelineObj * CDESBaseInterface::GetOwner(void)
{
	return m_OwnerObject;
}