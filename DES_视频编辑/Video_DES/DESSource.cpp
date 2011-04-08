#include "StdAfx.h"
#include <qedit.h>
#include "DESSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDESSource::CDESSource(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine);
{
	m_pInterfaceSource = NULL;
}


CDESSource::~CDESSource(void)
{
	ReleaseSelf();
}

void CDESSource::ReleaseSelf(void)
{
	if (m_pInterfaceSource != NULL)
	{
		m_pInterfaceSource->Release();
		m_pInterfaceSource = NULL;
	}
}

bool CDESSource::CreateInstance(void)
{
	if (mEmptyObject == NULL)
	{
		bool pass = mTimeLine->CreateEmptyNode(&mEmptyObject, TIMELINE_MAJOR_TYPE_SOURCE);
		if (!pass)
		{
			mEmptyObject = NULL;
		}
		return pass;
	}
	return true;
}

IAMTimelineSrc * CDESSource::GetSourceObject(void)
{
	return m_pInterfaceSource;
}

bool CDESSource::QueryExtraInterfaces(void)
{
	if (mEmptyObject)
	{
		ReleaseSelf();
		HRESULT hr = mEmptyObject->QueryInterface(IID_IAMTimelineSrc,
												(void **) &m_pInterfaceSource);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass)  
		{
			m_Splittable.SetOwner(mEmptyObject);
			m_Effectable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESSource::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	m_Splittable.SetOwner(NULL);
	m_Effectable.SetOwner(NULL);
}

bool CDESSource::SetMediaName(const char * inFilePath)
{
	if (m_pInterfaceSource)
	{
		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inFilePath, -1, szFilePath, MAX_PATH);
		HRESULT hr = m_pInterfaceSource->SetMediaName(szFilePath);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;	
}

bool CDESSource::GetMediaName(char * outFilePath)
{
	if (m_pInterfaceSource)
	{
		BSTR  pFilePath = NULL;  
		HRESULT hr = m_pInterfaceSource->GetMediaName(&pFilePath);
		if (SUCCEEDED(hr))
		{
			char   szFilePath[MAX_PATH];
			WideCharToMultiByte(CP_ACP, 0, pFilePath, -1, szFilePath, MAX_PATH, NULL, NULL);
			SysFreeString(pFilePath);
			strcpy(outFilePath, szFilePath);
			return true;
		}
	}
	return false;
}

bool CDESSource::SetMediaTimes(REFERENCE_TIME inStart, REFERENCE_TIME inStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->SetMediaTimes(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaTimes(REFERENCE_TIME * outStart, REFERENCE_TIME * outStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->GetMediaTimes(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetMediaTimes2(REFTIME inStart, REFTIME inStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->SetMediaTimes2(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaTimes2(REFTIME * outStart, REFTIME * outStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->GetMediaTimes2(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::FixMediaTimes(REFERENCE_TIME * ioStart, REFERENCE_TIME * ioStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->FixMediaTimes(ioStart, ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::FixMediaTimes2(REFTIME * ioStart, REFTIME * ioStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->FixMediaTimes2(ioStart, ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetMediaLength(REFERENCE_TIME inLength)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->SetMediaLength(inLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaLength(REFERENCE_TIME * outLength)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->GetMediaLength(outLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetMediaLength2(REFTIME inLength)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->SetMediaLength2(inLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaLength2(REFTIME * outLength)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->GetMediaLength2(outLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::ModifyStopTime(REFERENCE_TIME inStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->ModifyStopTime(inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::ModifyStopTime2(REFTIME inStop)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->ModifyStopTime2(inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetDefaultFPS(double inFPS)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->SetDefaultFPS(inFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetDefaultFPS(double * outFPS)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->GetDefaultFPS(outFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetStreamNumber(long inIndex)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->SetStreamNumber(inIndex);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetStreamNumber(long * outIndex)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->GetStreamNumber(outIndex);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

/*
Possible StretchMode values include the following: 
	RESIZEF_STRETCH 
	RESIZEF_CROP 
	RESIZEF_PRESERVEASPECTRATIO 
	RESIZEF_PRESERVEASPECTRATIO_NOLETTERBOX 
*/
bool CDESSource::SetStretchMode(int inStretchMode)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->SetStretchMode(inStretchMode);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetStretchMode(int * outStretchMode)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->GetStretchMode(outStretchMode);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::IsNormalRate(BOOL * outIsNormal)
{
	if (m_pInterfaceSource)
	{
		HRESULT hr = m_pInterfaceSource->IsNormalRate(outIsNormal);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SpliceWithNext(CDESBaseObject & inNextSource)
{
	if (m_pInterfaceSource)
	{
		IAMTimelineObj * pTimeLineObj = inNextSource.GetTimeLineObj();
		ASSERT(pTimeLineObj);
		HRESULT hr = m_pInterfaceSource->SpliceWithNext(pTimeLineObj);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineSplittable methods ---
bool CDESSource::SplitAt(REFERENCE_TIME inTime)
{
	return m_Splittable.SplitAt(inTime);
}

bool CDESSource::SplitAt2(REFTIME inTime)
{
	return m_Splittable.SplitAt2(inTime);
}


// --- IAMTimelineEffectable methods ---
bool CDESSource::EffectGetCount(long * outCount)
{
	return m_Effectable.EffectGetCount(outCount);
}

bool CDESSource::EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority)
{
	return m_Effectable.EffectInsBefore(inEffectObject, inPriority);
}

bool CDESSource::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	return m_Effectable.EffectSwapPriorities(inPriorityA, inPriorityB);
}

bool CDESSource::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	return m_Effectable.GetEffect(outEffect, inWhich);
}