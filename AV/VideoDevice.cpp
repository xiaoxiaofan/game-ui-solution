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

	hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
		IID_IBaseFilter, (LPVOID*) &m_pNullFilter);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("CLSID_NullRenderer 创建失败！"));
	}

	hr = m_pGraph->AddFilter(m_pNullFilter, L"NullRenderer");
	
	if (FAILED(hr))
	{
		ErrMsg(TEXT("NullRenderer 增加失败！"));
	}

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
	FreeMediaType(mt);

	hr = m_pGraph->AddFilter(m_pSampleGrabberFilter, L"Grabber");

	if (FAILED(hr))
	{
		ErrMsg(TEXT("Grabber 增加失败！"));
	}

	if (!BindFilter(devID,&m_pDeviceFilter))
	{
		ErrMsg(TEXT("BindVideoFilter 失败！"));
	}

	hr = m_pGraph->AddFilter(m_pDeviceFilter,L"VideoDeviceFilter");

	if (FAILED(hr))
	{
		ErrMsg(TEXT("VideoDeviceFilter 增加失败！"));
	}

	CComPtr<IEnumPins> pPins;
	m_pDeviceFilter->EnumPins(&pPins);
	pPins->Reset();
	pPins->Next(1,&m_pCameraOutput,NULL);

	pPins = NULL; 
	m_pSampleGrabberFilter->EnumPins(&pEnum);
	pPins->Reset();
	pPins->Next(1, &m_pGrabberInput, NULL); 

	pPins = NULL;
	m_pSampleGrabberFilter->EnumPins(&pEnum);
	pPins->Reset();
	pPins->Skip(1);
	pPins->Next(1, &m_pGrabberOutput, NULL); 

	pPins = NULL;
	m_pNullFilter->EnumPins(&pPins);
	pPins->Reset();
	pPins->Next(1, &m_pNullInputPin, NULL);


	CComPtr<IAMStreamConfig>  iconfig; 

	hr = m_pCameraOutput->QueryInterface(IID_IAMStreamConfig,(void**)&iconfig);

	AM_MEDIA_TYPE* pmt;    
	if(iconfig->GetFormat(&pmt) !=S_OK) 
	{
		return false;   
	}

	VIDEOINFOHEADER*   phead;
	if ( pmt->formattype == FORMAT_VideoInfo)   
	{   
		phead=( VIDEOINFOHEADER*)pmt->pbFormat;   
		phead->bmiHeader.biWidth = 600;   
		phead->bmiHeader.biHeight = 400;   
		if(( hr = iconfig->SetFormat(pmt)) != S_OK )   
		{
			return false;
		}
	} 
	FreeMediaType(*pmt);

	hr = m_pGraph->Connect(m_pCameraOutput, m_pGrabberInput);
	hr = m_pGraph->Connect(m_pGrabberOutput, m_pNullInputPin);

	if (FAILED(hr))
	{
		switch(hr)
		{
		case VFW_S_NOPREVIEWPIN :
			break;
		case E_FAIL :
			break;
		case E_INVALIDARG :
			break;
		case E_POINTER :
			break;
		}
	}

	m_pSampleGrabber->SetBufferSamples(TRUE);
	m_pSampleGrabber->SetOneShot(TRUE);

	return true;
}

bool VideoDevice::BindFilter( int devID, IBaseFilter **pFilter )
{
	if ( devID < 0 )
	{
		return false;
	}

	CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum,NULL,CLSCTX_INPROC_SERVER,IID_ICreateDevEnum,(void **)&pCreateDevEnum);
	if (FAILED(hr))
	{
		ErrMsg(TEXT("IID_ICreateDevEnum 创建失败！"));
	}

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,(void **)&pEm);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("IID_IEnumMoniker 创建失败！"));
	}

	pEm->Reset();

	ULONG cFetched;
	CComPtr<IMoniker> pM;
	int index = 0;
	while ( hr == pEm->Next(1,(void **)&pM,&cFetched) , SUCCEEDED(hr))
	{
		if ( index == devID )
		{
			IPropertyBag *pBag;
			hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
			if (SUCCEEDED(hr))
			{
				VARIANT var;
				var.vt = VT_BSTR;
				hr = pBag->Read(L"FriendlyName", &var, NULL);
				if (SUCCEEDED(hr)) 
				{
					pM->BindToObject(0, 0, IID_IBaseFilter, (void**)pFilter);

					SysFreeString(var.bstrVal);
				}
			}
			return true;
		}
		index++;
	}
	return false;
}
