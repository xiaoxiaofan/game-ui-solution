#include "StdAfx.h"
#include "VideoDevice.h"


CVideoDevice::CVideoDevice(void)
{
	
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

	hr = CoCreateInstance(CLSID_VideoRenderer,NULL,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(PVOID *)&m_pVideoRender);

	
	hr = ConnectFilters(m_pGraph,m_pDeviceFilter,m_pVideoRender);


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

bool CVideoDevice::SetPosition( HWND hwnd,int x, int y, int cx, int cy )
{
/*
	m_pGraph->QueryInterface(IID_IVideoWindow,(void **)&m_pVideoWindow);

	ASSERT( m_pVideoWindow != NULL );

	m_pVideoWindow->put_Owner((OAHWND)hwnd);
	m_pVideoWindow->put_WindowStyle(WS_CHILD);
	m_pVideoWindow->SetWindowPosition(x,y,cx,cy);
	m_pVideoWindow->put_Visible(OATRUE);
	m_pVideoWindow->put_AutoShow(true);*/

	m_pGraph->QueryInterface(IID_IVideoWindow,(void **)&m_pVideoWindow);

	m_pVideoWindow->put_AutoShow(true);
	return true;
}

void CVideoDevice::Start()
{
	m_pGraph->QueryInterface(IID_IMediaControl, (void **) &m_pMediaControl);
	ASSERT( m_pMediaControl != NULL );

	m_pCaputer->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pDeviceFilter,NULL,NULL);

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
