//
// CDESXml.cpp
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
#include "CDESTimeLine.h"
#include "CDESXml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
CDESXml::CDESXml()
{
	mXmlInterface = NULL;
}

CDESXml::~CDESXml()
{
	if (mXmlInterface != NULL)
	{
		mXmlInterface->Release();
		mXmlInterface = NULL;
	}
}

bool CDESXml::Initialize(void)
{
	if (mXmlInterface == NULL)
	{
		HRESULT hr = CoCreateInstance(CLSID_Xml2Dex, 
									NULL, 
									CLSCTX_INPROC_SERVER, 
									IID_IXml2Dex, 
									(void**) &mXmlInterface);
		if (FAILED(hr))
		{
			mXmlInterface = NULL;
			return false;
		}
	}
	return true;
}

bool CDESXml::ReadXMLFile(CDESTimeLine & ioTimeline, const char * inXmlFile)
{
	if (mXmlInterface)
	{
		IAMTimeline * pTimeLine = ioTimeline.GetTimeLine();
		ASSERT(pTimeLine);

		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inXmlFile, -1, szFilePath, MAX_PATH);
		ioTimeline.ClearAllGroups();
		HRESULT hr = mXmlInterface->ReadXMLFile(pTimeLine, szFilePath);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESXml::WriteXMLFile(CDESTimeLine & inTimeline, const char * inXmlFile)
{
	if (mXmlInterface)
	{
		IAMTimeline * pTimeLine = inTimeline.GetTimeLine();
		ASSERT(pTimeLine);

		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inXmlFile, -1, szFilePath, MAX_PATH);
		HRESULT hr = mXmlInterface->WriteXMLFile(pTimeLine, szFilePath);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESXml::WriteXML(CDESTimeLine & inTimeline, BSTR * outXMLString)
{
	if (mXmlInterface)
	{
		IAMTimeline * pTimeLine = inTimeline.GetTimeLine();
		ASSERT(pTimeLine);
		HRESULT hr = mXmlInterface->WriteXML(pTimeLine, outXMLString);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}

bool CDESXml::WriteGrfFile(IUnknown * inGraph, const char * inFileName)
{
	if (mXmlInterface)
	{
		ASSERT(inGraph);
		WCHAR    szFilePath[MAX_PATH];
		MultiByteToWideChar(CP_ACP, 0, inFileName, -1, szFilePath, MAX_PATH);
		HRESULT hr = mXmlInterface->WriteGrfFile(inGraph, szFilePath);
		return SUCCEEDED(hr) ? true : false;
	}
	return false;
}
