#include "StdAfx.h"
#include "DESTimeLine.h"
#include "DESBaseObject.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESTimeLine::CDESTimeLine(void)
{
	m_pTimeLine = NULL;
	
}


CDESTimeLine::~CDESTimeLine(void)
{
	ReleaseSelf();
}

void CDESTimeLine::ReleaseSelf(void)
{
	if (m_pTimeLine != NULL)
	{
		m_pTimeLine->Release();
		m_pTimeLine = NULL;
	}
}

IAMTimeline * CDESTimeLine::GetTimeLine( void )
{
	return m_pTimeLine;
}

bool CDESTimeLine::Attach( IAMTimeline * inTimeLine )
{
	ReleaseSelf();
	if (inTimeLine != NULL)
	{
		inTimeLine->AddRef();
		m_pTimeLine = inTimeLine;
		return true;
	}
	return false;
}

bool CDESTimeLine::Initialize( void )
{
	if(m_pTimeLine == NULL)
	{
		HRESULT hr = CoCreateInstance(CLSID_AMTimeline,
			                         NULL,
									 CLSCTX_INPROC_SERVER,
									 IID_IAMTimeline,
									 (void**)&m_pTimeLine);
		if (FAILED(hr))
		{
			m_pTimeLine = NULL;
			return false;
			
		}
	}
	return true;
}

bool CDESTimeLine::AddGroup( CDESBaseObject * inGroup )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->AddGroup(inGroup->GetTimeLineObj());
		return SUCCEEDED(hr) ? true : false;
	} 
	return false;
}

bool CDESTimeLine::GetGroup( CDESBaseObject & outGroup, long inGroupIndex )
{
	if (m_pTimeLine)
	{
		IAMTimelineObj * pTimeLineObj = NULL;
		HRESULT hr = m_pTimeLine->GetGroup(&pTimeLineObj,inGroupIndex);
		if(SUCCEEDED(hr))
		{
			outGroup.Attach(pTimeLineObj);
			pTimeLineObj->Release();
			return true;
		}
	}
	return false;
}

bool CDESTimeLine::ClearAllGroup( void )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->ClearAllGroups();
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

long CDESTimeLine::GetGroupCount( void )
{
	if (m_pTimeLine)
	{
		long groupCount = 0;
		m_pTimeLine->GetGroupCount(&groupCount);
		return groupCount;
	}
	return 0;
}

BOOL CDESTimeLine::EffectsEnabled( void )
{
	if (m_pTimeLine)
	{
		BOOL bEnabled = FALSE;
		m_pTimeLine->EffectsEnabled(&bEnabled);
		return bEnabled;
	}
	return FALSE;
}

bool CDESTimeLine::EnableEffects( BOOL inEnabled )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->EnableEffects(inEnabled);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultEffect( GUID * inGuid )
{
	if (m_pTimeLine)
	{
	  HRESULT hr = m_pTimeLine->SetDefaultEffect(inGuid);
	  return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultEffectB( BSTR inGuid )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->SetDefaultEffectB(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultEffect( GUID * outGuid )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->GetDefaultEffect(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultEffectB( BSTR * outGuid )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->GetDefaultEffectB(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

BOOL CDESTimeLine::TransitionsEnabled( void )
{
	if (m_pTimeLine)
	{
		BOOL bEnable = FALSE;
		m_pTimeLine->TransitionsEnabled(&bEnable);
		return bEnable;
	}
	return FALSE;
}

bool CDESTimeLine::EnableTransitions( BOOL inEnabled )
{
	if(m_pTimeLine)
	{
        HRESULT hr = m_pTimeLine->EnableTransitions(inEnabled);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultTransition( GUID * inGuid )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->SetDefaultTransition(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultTransitionB( BSTR inGuid )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->SetDefaultTransitionB(inGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultTransition( GUID * outGuid )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->GetDefaultTransition(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultTransitionB( BSTR * outGuid )
{
	if(m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->GetDefaultTransitionB(outGuid);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::SetDefaultFPS( double inFPS )
{
	if(m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->SetDefaultFPS(inFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDefaultFPS( double * outFPS )
{
	if(m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->GetDefaultFPS(outFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDuration( REFERENCE_TIME * outDuration )
{
	if(m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine.GetDuration(outDuration);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetDuration2( double * outDuration )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->GetDuration2(outDuration);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::ValidateSourceNames( long inNotifyEventHandle /*= 0 */ )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->ValidateSourceNames(
			SFN_VALIDATEF_CHECK | SFN_VALIDATEF_POPUP | SFN_VALIDATEF_REPLACE,
			NULL,
			inNotifyEventHandle);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::CreateEmptyNode( IAMTimelineObj **outObject, TIMELINE_MAJOR_TYPE inType )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->CreateEmptyNode(outObject);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESTimeLine::GetCountOfType( long inGroupIndex, long * outVal, long * outValWithComps, TIMELINE_MAJOR_TYPE inType )
{
	if (m_pTimeLine)
	{
		HRESULT hr = m_pTimeLine->GetCountOfType(inGroupIndex,outVal,outValWithComps,inType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


