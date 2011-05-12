// AVDevice.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "AVDevice.h"
#include <assert.h>
#include <strsafe.h>

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 AVDevice.h

CAVDeviceEnum* CAVDeviceEnum::m_pMe = NULL;

CAVDeviceEnum::CAVDeviceEnum(void)
{

}

CAVDeviceEnum::~CAVDeviceEnum(void)
{

}

bool CAVDeviceEnum::Initalize(void)
{

	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		
	HRESULT hr = S_OK;
		// Create the Filter Graph Manager.
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC,IID_IGraphBuilder, (void **)&m_pGraph); 
	
	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = CoCreateInstance(CLSID_SystemDeviceEnum,NULL,CLSCTX_INPROC_SERVER,IID_ICreateDevEnum,(void **)&m_pCreateDevEnum);

	if (FAILED(hr))
	{
		return FALSE;
	}

	hr = m_pCreateDevEnum->CreateClassEnumerator(CLSID_AudioInputDeviceCategory,
		&m_pAudioEm, 0);

	if (FAILED(hr))
	{
		return FALSE;
	}

	m_pAudioEm->Reset();

	hr = m_pCreateDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,
		&m_pVideoEm, 0);


	if (FAILED(hr))
	{
		return FALSE;
	}

	m_pVideoEm->Reset();
	

	return true;
}


void CAVDeviceEnum::Release( void )
{

}

void CAVDeviceEnum::GetAVCount(int& count)
{
	int audioCount,videoCount;
	GetAudioCount(audioCount);
	GetVideoCount(videoCount);
	count = audioCount + videoCount;
	return;
}

void CAVDeviceEnum::GetAudioCount(int& nAudioCount)
{
	int nCount = 0;
	ULONG cFetched;
	IMoniker *pM;
	assert(m_pAudioEm);
	while(m_pAudioEm->Next(1, &pM, &cFetched) == S_OK)
	{
		nCount++;
	}
	return;
}

void CAVDeviceEnum::GetVideoCount(int& nVideoCount)
{
	int nCount = 0;
	ULONG cFetched;
	IMoniker *pM;
	assert(m_pVideoEm);
	while(m_pVideoEm->Next(1, &pM, &cFetched) == S_OK)
	{
		nCount++;
	}
	return;
}

void CAVDeviceEnum::GetAudioName( int nDevID,char * sName,int nBufferSize )
{
	int nCount = 0;
	ULONG cFetched;
	IMoniker* pM;
	assert(m_pAudioEm);
	while(m_pAudioEm->Next(1, &pM, &cFetched) == S_OK)
	{
		if (nCount == nDevID)
		{
			IPropertyBag* pBag;
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

void CAVDeviceEnum::GetVideoName( int nDevID,char * sName,int nBufferSize )
{
	int nCount = 0;
	ULONG cFetched;
	IMoniker* pM;
	assert(m_pVideoEm);
	while(m_pVideoEm->Next(1, &pM, &cFetched) == S_OK)
	{
		if (nCount == nDevID)
		{
			IPropertyBag* pBag;
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

CAVDeviceEnum* CAVDeviceEnum::GetInstance( void )
{
	if (m_pMe == NULL)
	{
		m_pMe = new CAVDeviceEnum();
	}
	return m_pMe;
}

























void ErrMsg(LPTSTR szFormat,...)
{
	static TCHAR szBuffer[2048]={0};
	const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
	const int LASTCHAR = NUMCHARS - 1;

	// Format the input string
	va_list pArgs;
	va_start(pArgs, szFormat);

	// Use a bounded buffer size to prevent buffer overruns.  Limit count to
	// character size minus one to allow for a NULL terminating character.
	HRESULT hr = StringCchVPrintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
	va_end(pArgs);

	// Ensure that the formatted string is NULL-terminated
	szBuffer[LASTCHAR] = TEXT('\0');

	MessageBox(NULL, szBuffer, NULL,
		MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
}


