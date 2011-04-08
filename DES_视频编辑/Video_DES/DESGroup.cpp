#include "StdAfx.h"
#include <streams.h>
#include <qedit.h>
#include "DESSource.h"
#include "DESGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESGroup::CDESGroup(CDESTimeLine * inTimeLine) : 
CDESComposition(inTimeLine)
{
	m_pInterfaceGroup = NULL;
	m_IsVideoGroup = TRUE;
}


CDESGroup::~CDESGroup(void)
{
	ReleaseSelf();
}

void CDESGroup::ReleaseSelf(void)
{
	if (m_pInterfaceGroup != NULL)
	{
		m_pInterfaceGroup->Release();
		m_pInterfaceGroup = NULL;
	}
}

bool CDESGroup::CreateInstance(void)
{
	if (mEmptyObject == NULL)
	{
		bool pass = mTimeLine->CreateEmptyNode(&mEmptyObject, TIMELINE_MAJOR_TYPE_GROUP);
		if (!pass)
		{
			mEmptyObject = NULL;
		}
		return pass;
	}
	return true;
}

bool CDESGroup::QueryExtraInterfaces(void)
{
	bool pass = CDESComposition::QueryExtraInterfaces();
	if (pass)
	{
		ReleaseSelf();
		HRESULT hr = mEmptyObject->QueryInterface(IID_IAMTimelineGroup,
			(void **) &m_pInterfaceGroup);
		pass = SUCCEEDED(hr) ? true : false;
	}
	return pass;
}

void CDESGroup::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();	
	CDESComposition::ReleaseExtraInterfaces();
}

bool CDESGroup::GetTimeline(CDESTimeLine & outTimeLine)
{
	if (m_pInterfaceGroup)
	{
		IAMTimeline * pTimeLine = NULL;
		HRESULT hr = m_pInterfaceGroup->GetTimeline(&pTimeLine);
		if (SUCCEEDED(hr))
		{
			outTimeLine.Attach(pTimeLine);
			pTimeLine->Release();
			return true;
		}
	}
	return false;
}

bool CDESGroup::GetPriority(long * outPriority)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->GetPriority(outPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetMediaType(AM_MEDIA_TYPE * inMediaType)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->SetMediaType(inMediaType);
		if (SUCCEEDED(hr))
		{
			m_IsVideoGroup  = FALSE;
			if (inMediaType->majortype == MEDIATYPE_Video)
			{
				m_IsVideoGroup = TRUE;
			}
			return true;
		}
	}
	return false;
}

bool CDESGroup::GetMediaType(AM_MEDIA_TYPE * outMediaType)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->GetMediaType(outMediaType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetGroupType(BOOL inIsVideo)
{
	CMediaType   mt;
	mt.SetType(inIsVideo ? (&MEDIATYPE_Video) : (&MEDIATYPE_Audio));
	return SetMediaType(&mt);
}

bool CDESGroup::GetGroupType(BOOL * outIsVideo)
{
	*outIsVideo = m_IsVideoGroup;
	return true;
}

bool CDESGroup::SetOutputFPS(double inFPS)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->SetOutputFPS(inFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetOutputFPS(double * outFPS)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->GetOutputFPS(outFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetPreviewMode(BOOL inIsPreview)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->SetPreviewMode(inIsPreview);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetPreviewMode(BOOL * outIsPreview)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->GetPreviewMode(outIsPreview);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetOutputBuffering(int inBufferCount)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->SetOutputBuffering(inBufferCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetOutputBuffering(int * outBufferCount)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->GetOutputBuffering(outBufferCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetSmartRecompressFormat(long * inFormat)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->SetSmartRecompressFormat(inFormat);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetSmartRecompressFormat(long ** outFormat)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->GetSmartRecompressFormat(outFormat);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::IsSmartRecompressFormatSet(BOOL * outIsSmart)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->IsSmartRecompressFormatSet(outIsSmart);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetRecompFormatFromSource(CDESSource & inSource)
{
	if (m_pInterfaceGroup)
	{
		IAMTimelineSrc * pSource = inSource.GetSourceObject();
		ASSERT(pSource);
		HRESULT hr = m_pInterfaceGroup->SetRecompFormatFromSource(pSource);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetGroupName(BSTR inGroupName)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->SetGroupName(inGroupName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetGroupName(BSTR * outGroupName)
{
	if (m_pInterfaceGroup)
	{
		HRESULT hr = m_pInterfaceGroup->GetGroupName(outGroupName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}