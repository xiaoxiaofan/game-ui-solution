//
// CDESSource.cpp
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
#include "CDESSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////////
CDESSource::CDESSource(CDESTimeLine * inTimeLine) :
CDESBaseObject(inTimeLine)
{
	mInterfaceSource = NULL;
}

CDESSource::~CDESSource()
{
	ReleaseSelf();
}

void CDESSource::ReleaseSelf(void)
{
	if (mInterfaceSource != NULL)
	{
		mInterfaceSource->Release();
		mInterfaceSource = NULL;
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
	return mInterfaceSource;
}

bool CDESSource::QueryExtraInterfaces(void)
{
	if (mEmptyObject)
	{
		ReleaseSelf();
		HRESULT hr = mEmptyObject->QueryInterface(IID_IAMTimelineSrc,
												(void **) &mInterfaceSource);
		bool pass = SUCCEEDED(hr) ? true : false;
		if (pass)  // Query other interfaces
		{
			mSplittable.SetOwner(mEmptyObject);
			mEffectable.SetOwner(mEmptyObject);
		}
		return pass;
	}
	return false;
}

void CDESSource::ReleaseExtraInterfaces(void)
{
	ReleaseSelf();
	mSplittable.SetOwner(NULL);
	mEffectable.SetOwner(NULL);
}

bool CDESSource::SetMediaName(const char * inFilePath)
{
	if (mInterfaceSource)
	{
		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inFilePath, -1, szFilePath, MAX_PATH);
		HRESULT hr = mInterfaceSource->SetMediaName(szFilePath);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;	
}

bool CDESSource::GetMediaName(char * outFilePath)
{
	if (mInterfaceSource)
	{
		BSTR  pFilePath = NULL;  
		HRESULT hr = mInterfaceSource->GetMediaName(&pFilePath);
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
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->SetMediaTimes(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaTimes(REFERENCE_TIME * outStart, REFERENCE_TIME * outStop)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->GetMediaTimes(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetMediaTimes2(REFTIME inStart, REFTIME inStop)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->SetMediaTimes2(inStart, inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaTimes2(REFTIME * outStart, REFTIME * outStop)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->GetMediaTimes2(outStart, outStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::FixMediaTimes(REFERENCE_TIME * ioStart, REFERENCE_TIME * ioStop)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->FixMediaTimes(ioStart, ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::FixMediaTimes2(REFTIME * ioStart, REFTIME * ioStop)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->FixMediaTimes2(ioStart, ioStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetMediaLength(REFERENCE_TIME inLength)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->SetMediaLength(inLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaLength(REFERENCE_TIME * outLength)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->GetMediaLength(outLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetMediaLength2(REFTIME inLength)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->SetMediaLength2(inLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetMediaLength2(REFTIME * outLength)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->GetMediaLength2(outLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::ModifyStopTime(REFERENCE_TIME inStop)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->ModifyStopTime(inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::ModifyStopTime2(REFTIME inStop)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->ModifyStopTime2(inStop);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetDefaultFPS(double inFPS)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->SetDefaultFPS(inFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetDefaultFPS(double * outFPS)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->GetDefaultFPS(outFPS);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SetStreamNumber(long inIndex)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->SetStreamNumber(inIndex);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetStreamNumber(long * outIndex)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->GetStreamNumber(outIndex);
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
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->SetStretchMode(inStretchMode);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::GetStretchMode(int * outStretchMode)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->GetStretchMode(outStretchMode);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::IsNormalRate(BOOL * outIsNormal)
{
	if (mInterfaceSource)
	{
		HRESULT hr = mInterfaceSource->IsNormalRate(outIsNormal);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESSource::SpliceWithNext(CDESBaseObject & inNextSource)
{
	if (mInterfaceSource)
	{
		IAMTimelineObj * pTimeLineObj = inNextSource.GetTimeLineObj();
		ASSERT(pTimeLineObj);
		HRESULT hr = mInterfaceSource->SpliceWithNext(pTimeLineObj);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}


// --- IAMTimelineSplittable methods ---
bool CDESSource::SplitAt(REFERENCE_TIME inTime)
{
	return mSplittable.SplitAt(inTime);
}

bool CDESSource::SplitAt2(REFTIME inTime)
{
	return mSplittable.SplitAt2(inTime);
}


// --- IAMTimelineEffectable methods ---
bool CDESSource::EffectGetCount(long * outCount)
{
	return mEffectable.EffectGetCount(outCount);
}

bool CDESSource::EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority)
{
	return mEffectable.EffectInsBefore(inEffectObject, inPriority);
}

bool CDESSource::EffectSwapPriorities(long inPriorityA, long inPriorityB)
{
	return mEffectable.EffectSwapPriorities(inPriorityA, inPriorityB);
}

bool CDESSource::GetEffect(CDESBaseObject & outEffect, long inWhich)
{
	return mEffectable.GetEffect(outEffect, inWhich);
}