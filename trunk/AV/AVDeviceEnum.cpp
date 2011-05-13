// AVDevice.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "AVDevice.h"


// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 AVDevice.h

CAVDeviceEnum::CAVDeviceEnum(void)
{
	Initalize();
}

CAVDeviceEnum::~CAVDeviceEnum(void)
{
	Release();
}

bool CAVDeviceEnum::Initalize(void)
{

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	return true;
}


void CAVDeviceEnum::Release( void )
{
	CoUninitialize();
}

void CAVDeviceEnum::GetAVCount(int& count)
{
	int audioCount = 0,videoCount = 0;
	GetAudioCount(audioCount);
	GetVideoCount(videoCount);
	count = audioCount + videoCount;
	return;
}

void CAVDeviceEnum::GetAudioCount(int& nAudioCount)
{
	HRESULT hr = S_OK;

	CComPtr<ICreateDevEnum> pCreateDevEnum;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory,
		&pEm, 0);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}

	
	ULONG cFetched;
	IMoniker *pM;

	while(hr = pEm->Next(1, &pM, &cFetched), hr == S_OK)
	{
		nAudioCount++;
	}
	return;
}

void CAVDeviceEnum::GetVideoCount(int& nVideoCount)
{
	HRESULT hr = S_OK;

	CComPtr<ICreateDevEnum> pCreateDevEnum;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
		&pEm, 0);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}
	
	ULONG cFetched;
	IMoniker *pM;

	while(hr = pEm->Next(1, &pM, &cFetched) ,hr == S_OK)
	{
		nVideoCount++;
	}
	return;
}

void CAVDeviceEnum::GetAudioName( int nDevID,char * sName,int nBufferSize )
{
    HRESULT hr = S_OK;

	CComPtr<ICreateDevEnum> pCreateDevEnum;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory,
		&pEm, 0);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}
	
	int nCount = 0;
	ULONG cFetched;
	IMoniker* pM;

	while(hr = pEm->Next(1, &pM, &cFetched),hr == S_OK)
	{
		if (nCount == nDevID)
		{
			CComPtr<IPropertyBag> pBag;
			hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
			if(SUCCEEDED(hr))
			{
				VARIANT var;
				var.vt = VT_BSTR;
				hr = pBag->Read(L"FriendlyName", &var, NULL);
				if(SUCCEEDED(hr))
				{
					//获取设备名称			
					WideCharToMultiByte(CP_ACP,0,var.bstrVal,-1,sName, nBufferSize ,"",NULL);

					SysFreeString(var.bstrVal);				
				}
			}
			break;
		}
		nCount++;
	}
	return;
}

void CAVDeviceEnum::GetVideoName( int nDevID,char * sName,int nBufferSize )
{
	HRESULT hr = S_OK;
	CComPtr<ICreateDevEnum> pCreateDevEnum;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pCreateDevEnum);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}

	CComPtr<IEnumMoniker> pEm;
	hr = pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
		&pEm, 0);

	if (FAILED(hr))
	{
		ErrMsg(TEXT("设备读取失败！"));
	}
	
	
	int nCount = 0;
	ULONG cFetched;
	IMoniker* pM;
	
	while(hr = pEm->Next(1, &pM, &cFetched), hr == S_OK)
	{
		if (nCount == nDevID)
		{
			CComPtr<IPropertyBag> pBag;
			HRESULT hr = S_OK;
			hr = pM->BindToStorage(0, 0, IID_IPropertyBag, (void **)&pBag);
			if(SUCCEEDED(hr))
			{
				VARIANT var;
				var.vt = VT_BSTR;
				hr = pBag->Read(L"FriendlyName", &var, NULL);
				if(SUCCEEDED(hr))
				{
					//获取设备名称			
					WideCharToMultiByte(CP_ACP,0,var.bstrVal,-1,sName, nBufferSize ,"",NULL);

					SysFreeString(var.bstrVal);				
				}
			}
			break;
		}
		nCount++;
	}
	return;
}














