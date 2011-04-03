//
// CDESGroup.cpp
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
#include <streams.h>
#include <qedit.h>
#include "CDESSource.h"
#include "CDESGroup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
CDESGroup::CDESGroup(CDESTimeLine * inTimeLine) :
CDESComposition(inTimeLine)
{
	mInterfaceGroup = NULL;
	mIsVideoGroup   = TRUE;
}

CDESGroup::~CDESGroup()
{
	ReleaseSelf();
}

void CDESGroup::ReleaseSelf(void)
{
	if (mInterfaceGroup != NULL)
	{
		mInterfaceGroup->Release();
		mInterfaceGroup = NULL;
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
												(void **) &mInterfaceGroup);
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
	if (mInterfaceGroup)
	{
		IAMTimeline * pTimeLine = NULL;
		HRESULT hr = mInterfaceGroup->GetTimeline(&pTimeLine);
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
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->GetPriority(outPriority);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetMediaType(AM_MEDIA_TYPE * inMediaType)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->SetMediaType(inMediaType);
		if (SUCCEEDED(hr))
		{
			mIsVideoGroup  = FALSE;
			if (inMediaType->majortype == MEDIATYPE_Video)
			{
				mIsVideoGroup = TRUE;
			}
			return true;
		}
	}
	return false;
}

bool CDESGroup::GetMediaType(AM_MEDIA_TYPE * outMediaType)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->GetMediaType(outMediaType);
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
	*outIsVideo = mIsVideoGroup;
	return true;
}

bool CDESGroup::SetOutputFPS(double inFPS)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->SetOutputFPS(inFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetOutputFPS(double * outFPS)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->GetOutputFPS(outFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetPreviewMode(BOOL inIsPreview)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->SetPreviewMode(inIsPreview);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetPreviewMode(BOOL * outIsPreview)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->GetPreviewMode(outIsPreview);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetOutputBuffering(int inBufferCount)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->SetOutputBuffering(inBufferCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetOutputBuffering(int * outBufferCount)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->GetOutputBuffering(outBufferCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetSmartRecompressFormat(long * inFormat)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->SetSmartRecompressFormat(inFormat);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetSmartRecompressFormat(long ** outFormat)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->GetSmartRecompressFormat(outFormat);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::IsSmartRecompressFormatSet(BOOL * outIsSmart)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->IsSmartRecompressFormatSet(outIsSmart);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetRecompFormatFromSource(CDESSource & inSource)
{
	if (mInterfaceGroup)
	{
		IAMTimelineSrc * pSource = inSource.GetSourceObject();
		ASSERT(pSource);
		HRESULT hr = mInterfaceGroup->SetRecompFormatFromSource(pSource);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::SetGroupName(BSTR inGroupName)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->SetGroupName(inGroupName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESGroup::GetGroupName(BSTR * outGroupName)
{
	if (mInterfaceGroup)
	{
		HRESULT hr = mInterfaceGroup->GetGroupName(outGroupName);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}