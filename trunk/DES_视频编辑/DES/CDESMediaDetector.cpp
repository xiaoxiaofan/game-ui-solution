//
// CDESMediaDetector.cpp
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
#include "CDESMediaDetector.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
CDESMediaDetector::CDESMediaDetector()
{
	mDetector = NULL;
}

CDESMediaDetector::~CDESMediaDetector()
{
	if (mDetector != NULL)
	{
		mDetector->Release();
		mDetector = NULL;
	}
}

bool CDESMediaDetector::Initialize()
{
	if (mDetector == NULL)
	{
		HRESULT hr = CoCreateInstance(CLSID_MediaDet, 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									IID_IMediaDet, 
									(void**) &mDetector);
		if (FAILED(hr))
		{
			mDetector = NULL;
			return false;
		}
	}
	return true;
}

bool CDESMediaDetector::put_Filename(const char * inFileName)
{
	if (mDetector)
	{
		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inFileName, -1, szFilePath, MAX_PATH);
		HRESULT hr = mDetector->put_Filename(szFilePath);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_Filename(char * outFileName)
{
	if (mDetector && outFileName)
	{
		BSTR     pFileName;
		HRESULT  hr = mDetector->get_Filename(&pFileName);
		if (SUCCEEDED(hr))
		{
			char   szFilePath[MAX_PATH];
			WideCharToMultiByte(CP_ACP, 0, pFileName, -1, szFilePath, MAX_PATH, 0, 0);
			SysFreeString(pFileName);
			strcpy(outFileName, szFilePath);
			return true;
		}
	}
	return false;
}

bool CDESMediaDetector::put_Filter(IUnknown * inSourceFilter)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->put_Filter(inSourceFilter);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_Filter(IUnknown ** outSourceFilter)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_Filter(outSourceFilter);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::put_CurrentStream(long inStreamIndex)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->put_CurrentStream(inStreamIndex);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_CurrentStream(long * outStreamIndex)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_CurrentStream(outStreamIndex);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_OutputStreams(long * outStreamCount)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_OutputStreams(outStreamCount);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_StreamLength(double * outLength)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_StreamLength(outLength);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_StreamType(GUID * outType)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_StreamType(outType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_StreamTypeB(BSTR * outType)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_StreamTypeB(outType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_StreamMediaType(AM_MEDIA_TYPE * outMediaType)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_StreamMediaType(outMediaType);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::get_FrameRate(double * outFrameRate)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->get_FrameRate(outFrameRate);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::EnterBitmapGrabMode(double inStreamTime)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->EnterBitmapGrabMode(inStreamTime);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::GetSampleGrabber(ISampleGrabber ** outGrabber)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->GetSampleGrabber(outGrabber);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::GetBitmapBits(double inStreamTime, long * outBufferSize, 
									  char * ioBuffer, long inWidth, long inHeight)
{
	if (mDetector)
	{
		HRESULT hr = mDetector->GetBitmapBits(inStreamTime, outBufferSize, 
			ioBuffer, inWidth, inHeight);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESMediaDetector::WriteBitmapBits(double inStreamTime, long inWidth, 
										long inHeight, const char * inFilename)
{
	if (mDetector)
	{
		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inFilename, -1, szFilePath, MAX_PATH);
		HRESULT hr = mDetector->WriteBitmapBits(inStreamTime, inWidth,
			inHeight, szFilePath);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}
