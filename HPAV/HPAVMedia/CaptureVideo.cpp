// CaptureVideo.cpp: implementation of the CCaptureVideo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CaptureVideo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
BOOL bOneShot=FALSE;//ȫ�ֱ���
class CSampleGrabberCB : public ISampleGrabberCB 
{
public:
	long lWidth;
	long lHeight;
	TCHAR m_szFileName[MAX_PATH];// λͼ�ļ�����
	CSampleGrabberCB()
	{
		//strcpy(m_szFileName, "c:\\donaldo.bmp");
	}
	STDMETHODIMP_(ULONG) AddRef()
	{
		return 2;
	}
	STDMETHODIMP_(ULONG) Release() 
	{
		return 1; 
	}
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		if( riid == IID_ISampleGrabberCB || riid == IID_IUnknown )
		{ 
			*ppv = (void *) static_cast<ISampleGrabberCB*> ( this );
			return NOERROR;
		} 
		return E_NOINTERFACE;
	}
	STDMETHODIMP SampleCB( double SampleTime, IMediaSample * pSample )
	{
		return 0;
	}
	STDMETHODIMP BufferCB( double dblSampleTime, BYTE * pBuffer, long lBufferSize )
	{
		if( !bOneShot )return 0;
		if (!pBuffer)return E_POINTER;
		SaveBitmap(pBuffer, lBufferSize);
		bOneShot = FALSE;
		return 0;
	}
	//����λͼ�ļ�
	BOOL SaveBitmap(BYTE * pBuffer, long lBufferSize )
	{
		HANDLE hf = CreateFile(
			m_szFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL,
			CREATE_ALWAYS, NULL, NULL );
		if( hf == INVALID_HANDLE_VALUE )return 0;
		// д�ļ�ͷ 
		BITMAPFILEHEADER bfh;
		memset( &bfh, 0, sizeof( bfh ));
		bfh.bfType = 'MB';
		bfh.bfSize = sizeof( bfh ) + lBufferSize + sizeof( BITMAPINFOHEADER );
		bfh.bfOffBits = sizeof( BITMAPINFOHEADER ) + sizeof( BITMAPFILEHEADER );
		DWORD dwWritten = 0;
		WriteFile( hf, &bfh, sizeof( bfh ), &dwWritten, NULL );
		// дλͼ��ʽ
		BITMAPINFOHEADER bih;
		memset( &bih, 0, sizeof( bih ) );
		bih.biSize = sizeof( bih );
		bih.biWidth = lWidth;
		bih.biHeight = lHeight;
		bih.biPlanes = 1;
		bih.biBitCount = 24;
		WriteFile( hf, &bih, sizeof( bih ), &dwWritten, NULL );
		// дλͼ����
		WriteFile( hf, pBuffer, lBufferSize, &dwWritten, NULL );
		CloseHandle( hf );
		return 0;
	}
};

CSampleGrabberCB mCB;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCaptureVideo::CCaptureVideo()
{
	//COM Library Intialization
	if(FAILED(CoInitialize(NULL))) /*, COINIT_APARTMENTTHREADED)))*/
	{
		MessageBox(_T("CoInitialize Failed!\r\n")); 
		return;
	}

	m_hWnd = NULL;
	m_pVW = NULL;
	m_pMC = NULL;
	m_pGB = NULL;
	m_pCapture = NULL; 
}
CCaptureVideo::~CCaptureVideo()
{
	// Stop media playback
	if(m_pMC)
		m_pMC->Stop();
	if(m_pVW)
	{
		m_pVW->put_Visible(OAFALSE);
		m_pVW->put_Owner(NULL);
	}
	SAFE_RELEASE(m_pCapture);
	SAFE_RELEASE(m_pMC);
	SAFE_RELEASE(m_pGB);
	SAFE_RELEASE(m_pBF);
	SAFE_RELEASE(m_pVW);
	SAFE_RELEASE(m_pGrabber);
	CoUninitialize();
}

HRESULT CCaptureVideo::ReInit(int iDeviceID, HWND hWnd)
{
	if(m_pMC)
		m_pMC->Stop();
	if(m_pVW)
	{
		m_pVW->put_Visible(OAFALSE);
		m_pVW->put_Owner(NULL);
	}

	SAFE_RELEASE(m_pCapture);
	SAFE_RELEASE(m_pMC);
	SAFE_RELEASE(m_pGB);
	SAFE_RELEASE(m_pBF);
	SAFE_RELEASE(m_pVW);
	SAFE_RELEASE(m_pGrabber);
	m_hWnd = NULL;
	m_pVW = NULL;
	m_pMC = NULL;
	m_pGB = NULL;
	m_pCapture = NULL; 
	return Init(iDeviceID,hWnd);
}

/*���ò�����Ƶ���ļ�����ʼ��׽��Ƶ����д�ļ�*/
HRESULT CCaptureVideo::CaptureImagesToAVI(CString inFileName)
{
	HRESULT hr=0;
	m_pMC->Stop();
	//��ֹͣ��Ƶ//�����ļ�����ע��ڶ�������������
	hr = m_pCapture->SetOutputFileName( &MEDIASUBTYPE_Avi,inFileName.AllocSysString(), &pMux, NULL );
	//��Ⱦý�壬���������˲���
	hr = m_pCapture->RenderStream( &PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video, m_pBF, NULL, pMux );
	pMux->Release();
	m_pMC->Run();//�ظ���Ƶ
	return hr;
}

int CCaptureVideo::EnumDevices(HWND hList)
{
	if (!hList)
		return -1;
	int id = 0;
	//ö����Ƶ��׽�豸
	ICreateDevEnum *pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if (hr != NOERROR)return -1;
	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
	if (hr != NOERROR)return -1;
	pEm->Reset();
	ULONG cFetched;
	IMoniker *pM;
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK)
	{
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				TCHAR str[2048]; 
				id++;
			//	WideCharToMultiByte(CP_ACP,0,var.bstrVal, -1, str, 2048, NULL, NULL);
				::SendMessage(hList, CB_ADDSTRING, 0,(LPARAM)str);
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
	}
	return id;
}

HRESULT CCaptureVideo::Init(int iDeviceID, HWND hWnd)
{
	HRESULT hr;
	hr = InitCaptureGraphBuilder();
	if (FAILED(hr))
	{
	    MessageBox(_T("Failed to get video interfaces!"));
		return hr;
	}
	// Bind Device Filter. We know the device because the id was passed in
	if(!BindFilter(iDeviceID, &m_pBF))return S_FALSE;
	hr = m_pGB->AddFilter(m_pBF, L"Capture Filter");
	// hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video, 
	// m_pBF, NULL, NULL);
	// create a sample grabber

//	hr = m_pGrabber.CoCreateInstance( CLSID_SampleGrabber );
	hr = CoCreateInstance( CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER, IID_ISampleGrabber, (void**)&m_pGrabber );
	if( !m_pGrabber )
	{
		MessageBox(_T("Fail to create SampleGrabber, maybe qedit.dll is not registered?"));
		return hr;
	}

	CComQIPtr< IBaseFilter, &IID_IBaseFilter > pGrabBase( m_pGrabber );

	//������Ƶ��ʽ
	AM_MEDIA_TYPE mt; 
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
	mt.subtype = MEDIASUBTYPE_RGB24;
	hr = m_pGrabber->SetMediaType(&mt);
	if( FAILED( hr ) )
	{
		MessageBox(_T("Fail to set media type!"));
		return hr;
	}
	hr = m_pGB->AddFilter( pGrabBase, L"Grabber" );
	if( FAILED( hr ) )
	{
		MessageBox(_T("Fail to put sample grabber in graph"));
		return hr;
	}
	// try to render preview/capture pin
	hr = m_pCapture->RenderStream(&PIN_CATEGORY_PREVIEW, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL);
	if( FAILED( hr ) )
		hr = m_pCapture->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,m_pBF,pGrabBase,NULL);
	if( FAILED( hr ) )
	{
		MessageBox(_T("Can��t build the graph"));
		return hr;
	}
	hr = m_pGrabber->GetConnectedMediaType( &mt );
	if ( FAILED( hr) )
	{
		MessageBox(_T("Failt to read the connected media type"));
		return hr;
	}
	VIDEOINFOHEADER * vih = (VIDEOINFOHEADER*) mt.pbFormat;
	mCB.lWidth = vih->bmiHeader.biWidth;
	mCB.lHeight = vih->bmiHeader.biHeight;
	FreeMediaType(mt);
	hr = m_pGrabber->SetBufferSamples( FALSE );
	hr = m_pGrabber->SetOneShot( FALSE );
	hr = m_pGrabber->SetCallback( &mCB, 1 );
	//������Ƶ��׽����
	m_hWnd = hWnd ; 
	SetupVideoWindow();
	hr = m_pMC->Run();//��ʼ��Ƶ��׽
	if(FAILED(hr))
	{
		MessageBox(_T("Couldn't run the graph!"));
		return hr;
	}
	return S_OK;
}

bool CCaptureVideo::BindFilter(int deviceId, IBaseFilter **pFilter)
{
	if (deviceId < 0)
		return false;
	// enumerate all video capture devices
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);
	if (hr != NOERROR)
	{
		return false;
	}
	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&pEm, 0);
	if (hr != NOERROR) 
	{
		return false;
	}
	pEm->Reset();
	ULONG cFetched;
	IMoniker *pM;
	int index = 0;
	while(hr = pEm->Next(1, &pM, &cFetched), hr==S_OK, index <= deviceId)
	{
		IPropertyBag *pBag;
		hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
		if(SUCCEEDED(hr)) 
		{
			VARIANT var;
			var.vt = VT_BSTR;
			hr = pBag->Read(L"FriendlyName", &var, NULL);
			if (hr == NOERROR) 
			{
				if (index ==deviceId)
				{
					pM->BindToObject(0, 0, IID_IBaseFilter, (void**)pFilter);
				}
				SysFreeString(var.bstrVal);
			}
			pBag->Release();
		}
		pM->Release();
		index++;
	}
	return true;
}

HRESULT CCaptureVideo::InitCaptureGraphBuilder()
{
	HRESULT hr;
	// ����IGraphBuilder�ӿ�
	hr=CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGB);
	// ����ICaptureGraphBuilder2�ӿ�
	hr = CoCreateInstance (CLSID_CaptureGraphBuilder2,NULL, CLSCTX_INPROC,
		IID_ICaptureGraphBuilder2, (void **) &m_pCapture);
	if (FAILED(hr))
		return hr;
	m_pCapture->SetFiltergraph(m_pGB);
	hr = m_pGB->QueryInterface(IID_IMediaControl, (void **)&m_pMC);
	if (FAILED(hr))return hr;
	hr = m_pGB->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVW);
	if (FAILED(hr))return hr;
	return hr;
}

HRESULT CCaptureVideo::SetupVideoWindow()
{
	HRESULT hr;
	hr = m_pVW->put_Owner((OAHWND)m_hWnd);
	if (FAILED(hr))return hr;
	hr = m_pVW->put_WindowStyle(WS_CHILD | WS_CLIPCHILDREN);
	if (FAILED(hr))return hr;
	ResizeVideoWindow();
	hr = m_pVW->put_Visible(OATRUE);
	return hr;
}

void CCaptureVideo::ResizeVideoWindow()
{
	if (m_pVW)
	{
		//��ͼ�������������
		CRect rc;
		::GetClientRect(m_hWnd,&rc);
		m_pVW->SetWindowPosition(0, 0, rc.right, rc.bottom);
	} 
}

void CCaptureVideo::GrabOneFrame(BOOL bGrab)
{
	bOneShot=bGrab;
}

void CCaptureVideo::FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if (mt.cbFormat != 0) 
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		// Strictly unnecessary but tidier
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL) 
	{
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}