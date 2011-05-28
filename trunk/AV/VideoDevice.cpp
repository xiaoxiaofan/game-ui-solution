#include "StdAfx.h"
#include "VideoDevice.h"
#include "highgui.h"
#include "..\live\liveDll\live.h"


//×¥Ö¡Êý¾Ý
STDMETHODIMP VideoProcessAdapter::BufferCB(double SampleTime, BYTE *pBuffer, long nBufferLen)
{
	SetLiveData(pBuffer,nBufferLen);
	return S_OK;
}


CVideoDevice::CVideoDevice(ISampleGrabberCB* sampleCallBack)
	: m_pFrame(NULL)
{
	m_pSampleCallBack = (VideoProcessAdapter *)sampleCallBack;
}


CVideoDevice::~CVideoDevice(void)
{

}

void CVideoDevice::OpenCamera( int devID)
{
	HRESULT hr = S_OK;

	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
		IID_IGraphBuilder, (void **)&m_pGraph);
	
	hr = CoCreateInstance(CLSID_CaptureGraphBuilder2,NULL,CLSCTX_INPROC,IID_ICaptureGraphBuilder2,(PVOID *)&m_pCaputer);
	
	hr = m_pCaputer->SetFiltergraph(m_pGraph);

    hr = BindFilter(devID,&m_pDeviceFilter);
	
	hr = m_pGraph->AddFilter(m_pDeviceFilter,L"VideoDeviceFilter");

	//hr = CoCreateInstance(CLSID_VideoRenderer,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(PVOID *)&m_pVideoRender);

	hr = m_pCaputer->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,m_pDeviceFilter,NULL,NULL);

	
	hr = m_pCaputer->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video, m_pDeviceFilter,IID_IAMStreamConfig, (void **)&m_pVideoConfig);
	

		AM_MEDIA_TYPE *pmt;
		hr = m_pVideoConfig->GetFormat(&pmt);
		VIDEOINFOHEADER *pheader;
		if (pmt->formattype == FORMAT_VideoInfo)
		{
			pheader = (VIDEOINFOHEADER *)pmt->pbFormat;
	
			m_nWidth = pheader->bmiHeader.biWidth;
			m_nHeight = pheader->bmiHeader.biHeight;
		//	m_pVideoConfig->SetFormat(pmt);
		}
	
		m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);
		m_pGraph->QueryInterface(IID_IMediaEvent,(void **)&m_pMediaEvent);

		SaveGraphFile(m_pGraph,L"C:\\open.grf");
}

HRESULT CVideoDevice::BindFilter( int devID, IBaseFilter **pFilter )
{
	if ( devID < 0 )
	{
		return S_FALSE;
	}
	HRESULT hr = S_OK;
	SmartPtr<ICreateDevEnum> pCreateDevEnum;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum,NULL,CLSCTX_INPROC_SERVER,IID_ICreateDevEnum,(void **)&pCreateDevEnum);

	SmartPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm,0);

	pEm->Reset();

	ULONG cFetched;
	SmartPtr<IMoniker> pM;
	int index = 0;
	while ( hr == pEm->Next(1,&pM,&cFetched) , SUCCEEDED(hr))
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
	       return S_OK;
		}
		index++;
	}

	return S_FALSE;
}

void CVideoDevice::SetPosition( HWND hwnd,int x, int y, int cx, int cy )
{

	m_pGraph->QueryInterface(IID_IVideoWindow,(void **)&m_pVideoWindow);

	ASSERT( m_pVideoWindow != NULL );

	m_pVideoWindow->put_Owner((OAHWND)hwnd);
	m_pVideoWindow->put_WindowStyle(WS_CHILD);
	m_pVideoWindow->SetWindowPosition(x,y,cx,cy);

	m_pVideoWindow->put_Visible(OATRUE);

	return ;
}

void CVideoDevice::Start()
{
	ASSERT( m_pMediaEvent != NULL );
	ASSERT( m_pMediaControl != NULL );
	m_pMediaControl->Run();
}

bool CVideoDevice::OpenFile()
{
	HRESULT hr = S_OK;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,
		IID_IGraphBuilder, (void **)&m_pGraph);

	hr = CoCreateInstance(CLSID_VideoRenderer,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(PVOID *)&m_pVideoRender);

	hr = m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);

//	m_pGraph->AddSourceFilter(_T("C:\\12.avi"),_T("soucrce"),&m_pVideoSource);

	ConnectFilters(m_pGraph,m_pVideoSource,m_pVideoRender);

	m_pGraph->QueryInterface(IID_IVideoWindow,(void **)&m_pVideoWindow);

	m_pVideoWindow->put_AutoShow(true);

//	m_pGraph->RenderFile(_T("C:\\12.avi"),NULL);
	m_pMediaControl->Run();
	return true;
}

IplImage* CVideoDevice::QueryFrame()
{
	long evCode;
	long size = 0;

	/*
	m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);
		m_pGraph->QueryInterface(IID_IMediaEvent,(void **)&m_pMediaEvent);
		m_pMediaControl->Run();
		m_pMediaEvent->WaitForCompletion(INFINITE, &evCode);*/
	

	m_pSampleGrabber->GetCurrentBuffer(&size, NULL);

	//if the buffer size changed
	if (size != m_nBufferSize)
	{
		if (m_pFrame)
			cvReleaseImage(&m_pFrame);

		m_nBufferSize = size;
		m_pFrame = cvCreateImage(cvSize(m_nWidth, m_nHeight), IPL_DEPTH_8U, 3);
	}

	m_pSampleGrabber->GetCurrentBuffer(&m_nBufferSize, (long*)m_pFrame->imageData);
	cvFlip(m_pFrame);
	
	cvSaveImage("C:\\wuban.jpg",m_pFrame->imageData);
	return m_pFrame;
}

void CVideoDevice::SetBroadCast( bool isBroadCast )
{
	if(isBroadCast)
	{
        HRESULT hr = S_OK;

		hr = CoCreateInstance(CLSID_SampleGrabber,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(PVOID *)&m_pSampleGrabberFilter);
		hr = m_pGraph->AddFilter(m_pSampleGrabberFilter,L"Grabber");

		hr = CoCreateInstance(CLSID_NullRenderer,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(PVOID *)&m_pNullFilter);
		hr = m_pGraph->AddFilter(m_pNullFilter, L"NullRenderer");

		hr = m_pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber,(void **)&m_pSampleGrabber);

		hr = m_pCaputer->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pDeviceFilter,m_pSampleGrabberFilter,m_pNullFilter);

		m_pSampleGrabber->SetBufferSamples(false);
		m_pSampleGrabber->SetCallback(m_pSampleCallBack,1);

		SaveGraphFile(m_pGraph,L"C:\\BroadCast.grf");
	}
}

void CVideoDevice::StartRecord()
{
	
	Stop();
	IBaseFilter *pMux;
	IFileSinkFilter *pSink;
	m_pCaputer->SetOutputFileName(&MEDIASUBTYPE_Avi, L"C:\\YourFileName.avi", 
		&pMux, &pSink);
	m_pCaputer->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, 
		m_pDeviceFilter, NULL, pMux);

	Start();
	SaveGraphFile(m_pGraph,L"C:\\Record.grf");
}

void CVideoDevice::Stop()
{
	ASSERT(m_pMediaControl);
	m_pMediaControl->Stop();
}

void CVideoDevice::SetBuffer( bool isBuffer )
{
	if (isBuffer)
	{
		HRESULT hr = S_OK;

		hr = CoCreateInstance(CLSID_SampleGrabber,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(PVOID *)&m_pSampleGrabberFilter);
		hr = m_pGraph->AddFilter(m_pSampleGrabberFilter,L"Grabber");

		hr = CoCreateInstance(CLSID_NullRenderer,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(PVOID *)&m_pNullFilter);
		hr = m_pGraph->AddFilter(m_pNullFilter, L"NullRenderer");

		hr = m_pSampleGrabberFilter->QueryInterface(IID_ISampleGrabber,(void **)&m_pSampleGrabber);

		hr = m_pCaputer->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pDeviceFilter,m_pSampleGrabberFilter,m_pNullFilter);

		m_pSampleGrabber->SetBufferSamples(true);

		SaveGraphFile(m_pGraph,L"C:\\SetBuffer.grf");
	}
}
