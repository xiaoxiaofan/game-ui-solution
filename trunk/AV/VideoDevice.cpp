#include "StdAfx.h"
#include "VideoDevice.h"


VideoDevice::VideoDevice(void)
{

}


VideoDevice::~VideoDevice(void)
{

}

bool VideoDevice::OpenVideo( int devID,VideoAttr& videoAttr )
{
	HRESULT hr = S_OK;

	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
		IID_IGraphBuilder, (void **)&m_pGraph);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("CLSID_FilterGraph 创建失败！"));
	}

	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, 
		IID_IBaseFilter, (LPVOID *)&m_pSampleGrabberFilter);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("CLSID_SampleGrabber 创建失败！"));
	}

	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("IID_IMediaControl 创建失败！"));
	}

	hr = m_pGraph->QueryInterface(IID_IMediaEvent, (void **) &m_pMediaEvent);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("IID_IMediaEvent 创建失败！"));
	}

    /*
		hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
			IID_IBaseFilter, (LPVOID*) &m_pNullFilter);
	
	
		hr = m_pGraph->AddFilter(m_pNullFilter, L"NullRenderer");*/
	

	hr = m_pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber, (void**)&m_pSampleGrabber);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("IID_ISampleGrabber 创建失败！"));
	}

	AM_MEDIA_TYPE   mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	mt.formattype = FORMAT_VideoInfo; 
	hr = m_pSampleGrabber->SetMediaType(&mt);
	MYFREEMEDIATYPE(mt);

	m_pGraph->AddFilter(m_pSampleGrabberFilter, L"Grabber");
}
