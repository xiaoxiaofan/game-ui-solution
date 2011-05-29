// MVMUSER.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "VMR9Subgraph.h"
#include "MultiVideoMixer.h"
#include "D3DFont.h"
BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}
MVMUSER_API HRESULT CreateMVMixer(CMVMixer** pMixer,HWND hwnd,UINT Width, UINT Height,D3DFORMAT format,BOOL bBufferInSystemMem)
{
	if(!pMixer )return E_POINTER;
	*pMixer = new CMultiVideoMixer();
	if(!(*pMixer))return E_OUTOFMEMORY;
	HRESULT hr  =(( CMultiVideoMixer*)(*pMixer))->Initialize(hwnd,Width,Height,format,bBufferInSystemMem);
	if(FAILED(hr)){
		(( CMultiVideoMixer*)(*pMixer))->Terminate();
		delete (*pMixer);
		(*pMixer) = 0;
	}
	return hr;
}
MVMUSER_API HRESULT CreateMVMixerEx(CMVMixer** pMixer,HWND hwnd,HWND hwndCpy,UINT Width, UINT Height,D3DFORMAT format,BOOL bBufferInSystemMem)
{
	if(!pMixer )return E_POINTER;
	*pMixer = new CMultiVideoMixer();
	if(!(*pMixer))return E_OUTOFMEMORY;
	HRESULT hr  =(( CMultiVideoMixer*)(*pMixer))->InitializeEx(hwnd,hwndCpy,Width,Height,format,bBufferInSystemMem);
	if(FAILED(hr)){
		(( CMultiVideoMixer*)(*pMixer))->Terminate();
		delete (*pMixer);
		(*pMixer) = 0;
	}
	return hr;
}
MVMUSER_API HRESULT CreatD3DText(
			CD3DText** pD3DText			// [out] 新建的CD3DText
			, const TCHAR* strFontName	// [in ] 字体名
			, DWORD dwHeight			// [in ] 字体高度
			, DWORD dwFlags				// [in ] 字体重量和倾斜参数,通过|连接
										//		 ,如D3DFONT_BOLD|D3DFONT_ITALIC
			)
{
	if(!pD3DText)return E_POINTER;
	*pD3DText = new CD3DFont(strFontName,dwHeight,dwFlags);
	if(!(*pD3DText)) return E_OUTOFMEMORY;
	return NOERROR;

}
///////////////////////////////////////////class CMediaHelper////////////////////////////////////////////////////////////

CMediaHelper::CMediaHelper(void)
{
}
CMediaHelper::~CMediaHelper(void)
{
}
void CMediaHelper::ClearVector( LPNAMELIST pList)
{
	if(pList)pList->clear();
}
HRESULT CMediaHelper::EnumFormat(IBaseFilter * ppFilter,int iIndex,AM_MEDIA_TYPE **pmt,BYTE *pSCC,int*formatnum)//AUDIO_STREAM_CONFIG_CAPS 
{
	HRESULT hr = S_OK;
	if(formatnum)*formatnum = 0;
	if(!ppFilter)		return E_POINTER;
	IFilterGraph		*	pGraph = NULL;
	IGraphBuilder		*	pGb= NULL;
	ICaptureGraphBuilder2 * pBuild = NULL;
	IAMStreamConfig *pStrCfig = 0;
	
    // create graph
	try
	{
		hr = CoCreateInstance( CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
			IID_IFilterGraph, (void**)&(pGraph) );
		if( FAILED(hr))throw hr;if(!pGraph)throw  E_OUTOFMEMORY;
		//--
		hr = pGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb) );
		if( FAILED(hr))throw hr;if(!pGb)throw  E_OUTOFMEMORY;
		//--
		hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&pBuild);		
		if( FAILED(hr))throw hr;if(!pBuild)throw  E_OUTOFMEMORY;
		//--
		hr =pBuild->SetFiltergraph(pGb);
		if( FAILED(hr))throw hr;

		hr = pGraph->AddFilter(ppFilter,L"Capture");
		if( FAILED(hr))throw hr;
	
		hr = pBuild->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Interleaved,ppFilter,IID_IAMStreamConfig,(void **)&pStrCfig);
		if( FAILED( hr) ){
			hr = pBuild->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,ppFilter,IID_IAMStreamConfig,(void **)&pStrCfig);
			if (FAILED(hr ))throw hr;	
		}
		int num = 0;
		int size = 0;
		hr = pStrCfig->GetNumberOfCapabilities(&num,&size);
		if (FAILED(hr ) || num<=0)throw hr;	
		if(formatnum)*formatnum = num;
		hr = pStrCfig->GetStreamCaps(iIndex,pmt,pSCC);
		if (FAILED(hr ) )throw hr;	
	}
	catch(HRESULT hr1 )
	{
		hr = hr1;
	}
	RELEASE(pGraph);
	RELEASE(pGb);
	RELEASE(pBuild);
	RELEASE(pStrCfig);
	return hr;
}
/******************************Public*Routine******************************\
* EnumFilter
*
* 枚举设备
\**************************************************************************/
HRESULT CMediaHelper::EnumCapFormat(
		 int  iDeviceCode			    // [in ] 设备标号,>=0的整数
		,int iIndex						// [in ] 支持的媒体类型序号,如0表示至此的第一种媒体类型
		,AM_MEDIA_TYPE **pmt			// [out] 媒体类型AM_MEDIA_TYPE结构,不需要事先分配内存,
										//		 但使用完后必须调用CMediaHelper::DeleteMediaType()释放内存
		,BYTE *pSCC						// [out] 结构VIDEO_STREAM_CONFIG_CAPS,必须事先分配内存,
		,int*formatnum					// [in ] 支持的媒体类型数量
		)
{
	HRESULT hr =S_OK;
	IBaseFilter * pFt = 0;
	hr = this->GetVidCapDevice(iDeviceCode,&pFt);
	if(FAILED(hr)) return hr;
	if(!pFt)       return E_OUTOFMEMORY;
	hr = EnumFormat(pFt,iIndex,pmt,pSCC,formatnum);
	RELEASE(pFt);
	return hr;

}
/******************************Public*Routine******************************\
* EnumFilter
*
* 枚举设备
\**************************************************************************/
HRESULT CMediaHelper::EnumFilter(REFCLSID TypeId,LPNAMELIST pList,int * iCount )
{
	if(!pList)return E_INVALIDARG;
	pList->clear();
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	IMoniker * pMoniker = NULL;
	IPropertyBag *pPropBag = NULL;
	int count = 0;
	HRESULT hr = S_OK;
	try
	{
		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
						CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
						reinterpret_cast<void**>(&pDevEnum));
		if (FAILED(hr) || !pDevEnum) throw hr;

		hr = pDevEnum->CreateClassEnumerator(
					TypeId,//CLSID_AudioInputDeviceCategory,
					&pEnum, 0);
		if (FAILED(hr) || !pEnum) throw hr;
		while (pEnum->Next(1, &pMoniker, NULL) == S_OK){
			count++;
			if(pList){
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,  (void **)&pPropBag);
				if (FAILED(hr) || !pPropBag) throw hr;
				VARIANT var;
				VariantInit(&var);
				hr = pPropBag->Read(L"FriendlyName", &var, 0);
				if (FAILED(hr)) throw hr;
				wstring  wstr= (LPCWSTR)var.pbstrVal;
				pList->push_back(wstr);
				VariantClear(&var);
				RELEASE(pPropBag);
				
			}
			RELEASE(pMoniker);
		}
	}
	catch(HRESULT hr1)
	{
		hr = hr1;
	}
	if(iCount) * iCount = count;
	RELEASE(pDevEnum);
	RELEASE(pEnum);
	RELEASE(pMoniker);
	RELEASE(pPropBag);
	return hr;
}
/******************************Public*Routine******************************\
* EnumVidCapDevice
*
* 枚举视频采集设备，成功返回S_OK；
\**************************************************************************/

HRESULT CMediaHelper:: EnumVidCapDevice( LPNAMELIST pDeviceList ,int * iCount)
{
	return EnumFilter(CLSID_VideoInputDeviceCategory,pDeviceList,iCount);
}
/******************************Public*Routine******************************\
* EnumAudCapDevice
*
* 枚举音频采集设备，成功返回S_OK；
\**************************************************************************/
	
HRESULT CMediaHelper:: EnumAudCapDevice( LPNAMELIST pDeviceList ,int * iCount)
{
	return EnumFilter(CLSID_AudioInputDeviceCategory,pDeviceList,iCount);
}
/******************************Public*Routine******************************\
* EnumAudCompression
*
* 枚举音频压缩器，成功返回S_OK；
\**************************************************************************/
HRESULT CMediaHelper:: EnumAudCompression(LPNAMELIST pList ,int * iCount)
{
	return EnumFilter(CLSID_AudioCompressorCategory,pList,iCount);
}
/******************************Public*Routine******************************\
* EnumVidCompression
*
* 枚举视频压缩器
\**************************************************************************/
HRESULT CMediaHelper:: EnumVidCompression(LPNAMELIST pList,int * iCount )
{
	return EnumFilter(CLSID_VideoCompressorCategory,pList,iCount);
}
/******************************Public*Routine******************************\
* GetFilter
*
* 按名字取得设备
\**************************************************************************/
HRESULT CMediaHelper::GetFilter( REFCLSID TypeId,LPCWSTR pwsName ,IBaseFilter ** ppFilter )
{
	
	if(!ppFilter)return E_POINTER;
	if(!pwsName)return E_POINTER;
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	IMoniker * pMoniker = NULL;
	IPropertyBag *pPropBag = NULL;
	* ppFilter = NULL;
	
	HRESULT hr = S_OK;
	bool found = 0;
	
	try
	{
		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
						CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
						reinterpret_cast<void**>(&pDevEnum));
		if (FAILED(hr) || !pDevEnum) throw hr;

		hr = pDevEnum->CreateClassEnumerator(
					TypeId,
					&pEnum, 0);
		if (FAILED(hr) || !pEnum) throw hr;
		while (pEnum->Next(1, &pMoniker, NULL) == S_OK){
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,  (void **)&pPropBag);
			if (FAILED(hr) || !pPropBag) throw hr;
			VARIANT var;
			VariantInit(&var);
			hr = pPropBag->Read(L"FriendlyName", &var, 0);
			if (FAILED(hr)) throw hr;
			if(0 == wcscmp( pwsName, (LPCWSTR)var.pbstrVal))
			{
				found = 1;
				hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)ppFilter);
				break;
			}
				
			RELEASE(pMoniker);
		}
	}
	catch(HRESULT hr1)
	{
		hr = hr1;
	}
	RELEASE(pDevEnum);
	RELEASE(pEnum);
	RELEASE(pMoniker);
	RELEASE(pPropBag);
	if(!found) return E_FAIL;
	return hr;
}
/******************************Public*Routine******************************\
* GetFilter
*
* 按名字取得设备,标示同名的设备
\**************************************************************************/
HRESULT CMediaHelper::GetFilter( REFCLSID TypeId,LPCWSTR pwsName ,int index ,IBaseFilter ** ppFilter )
{
	
	if(!ppFilter)return E_POINTER;
	if(!pwsName)return E_POINTER;
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	IMoniker * pMoniker = NULL;
	IPropertyBag *pPropBag = NULL;
	* ppFilter = NULL;
	
	HRESULT hr = S_OK;
	bool found = 0;
	int id =0;
	try
	{
		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
						CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
						reinterpret_cast<void**>(&pDevEnum));
		if (FAILED(hr) || !pDevEnum) throw hr;

		hr = pDevEnum->CreateClassEnumerator(
					TypeId,
					&pEnum, 0);
		if (FAILED(hr) || !pEnum) throw hr;
		while (pEnum->Next(1, &pMoniker, NULL) == S_OK){
			hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,  (void **)&pPropBag);
			if (FAILED(hr) || !pPropBag) throw hr;
			VARIANT var;
			VariantInit(&var);
			hr = pPropBag->Read(L"FriendlyName", &var, 0);
			if (FAILED(hr)) throw hr;
			if(0 == wcscmp( pwsName, (LPCWSTR)var.pbstrVal) )
			{
				if( index == id){
					found = 1;
					hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)ppFilter);
					break;
				}
				else
					id++;
			}
				
			RELEASE(pMoniker);
		}
	}
	catch(HRESULT hr1)
	{
		hr = hr1;
	}
	RELEASE(pDevEnum);
	RELEASE(pEnum);
	RELEASE(pMoniker);
	RELEASE(pPropBag);
	if(!found) return E_FAIL;
	return hr;
}


/******************************Public*Routine******************************\
* GetFilter
*
* 按序号取得设备
\**************************************************************************/
HRESULT CMediaHelper::GetFilter( REFCLSID TypeId,int  iCode ,IBaseFilter ** ppFilter )
{
	if(!ppFilter)return E_POINTER;
	if(iCode<0)return E_INVALIDARG;
	ICreateDevEnum *pDevEnum = NULL;
	IEnumMoniker *pEnum = NULL;
	IMoniker * pMoniker = 0;
	* ppFilter = NULL;
	UINT index  = 0;
	HRESULT hr = S_OK;
	bool found = 0;
	try
	{
		hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL,
						CLSCTX_INPROC_SERVER, IID_ICreateDevEnum, 
						reinterpret_cast<void**>(&pDevEnum));
		if (FAILED(hr) || !pDevEnum) throw hr;

		hr = pDevEnum->CreateClassEnumerator(
					TypeId,//CLSID_AudioInputDeviceCategory,
					&pEnum, 0);
		if (FAILED(hr) || !pEnum) throw hr;
		while (pEnum->Next(1, &pMoniker, NULL) == S_OK){
				if(index==iCode){
					found = 1;
					hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)ppFilter);
					break;
				}
			index++;
			RELEASE(pMoniker);
		}
	}
	catch(HRESULT hr1)
	{
		hr = hr1;
	}
	RELEASE(pDevEnum);
	RELEASE(pEnum);
	RELEASE(pMoniker);
	if(!found) return E_FAIL;
	return hr;
}


/******************************Public*Routine******************************\
* GetAudCapDevice
*
* 得到视频采集设备
\**************************************************************************/
HRESULT CMediaHelper::GetVidCapDevice ( int  iDeviceCode ,IBaseFilter ** ppCapFilter)
{
	return GetFilter(CLSID_VideoInputDeviceCategory,iDeviceCode,ppCapFilter);
}
HRESULT CMediaHelper::GetVidCapDevice ( LPCWSTR pwsName ,IBaseFilter ** ppCapFilter)
{
	return GetFilter(CLSID_VideoInputDeviceCategory,pwsName,ppCapFilter);
}
HRESULT CMediaHelper::GetVidCapDevice ( LPCWSTR pwsName ,int index,IBaseFilter ** ppCapFilter)
{
	return GetFilter(CLSID_VideoInputDeviceCategory,pwsName,index,ppCapFilter);
}
/******************************Public*Routine******************************\
* GetAudCapDevice
*
* 得到音频采集设备
\**************************************************************************/
HRESULT CMediaHelper::GetAudCapDevice ( int  iDeviceCode ,IBaseFilter ** ppCapFilter)
{
	return GetFilter(CLSID_AudioInputDeviceCategory,iDeviceCode,ppCapFilter);
}
HRESULT CMediaHelper::GetAudCapDevice ( LPCWSTR pwsName ,IBaseFilter ** ppCapFilter)
{
	return GetFilter(CLSID_AudioInputDeviceCategory,pwsName,ppCapFilter);
}
HRESULT CMediaHelper::GetAudCapDevice ( LPCWSTR pwsName ,int index,IBaseFilter ** ppCapFilter)
{
	return GetFilter(CLSID_AudioInputDeviceCategory,pwsName,index,ppCapFilter);
}
/******************************Public*Routine******************************\
* GetVidCompression
*
* 得到视频压缩器
\**************************************************************************/
HRESULT CMediaHelper::GetVidCompression( int  iCode ,IBaseFilter ** ppFilter )
{
	return GetFilter(CLSID_VideoCompressorCategory,iCode,ppFilter);
}
HRESULT CMediaHelper::GetVidCompression( LPCWSTR pwsName ,IBaseFilter ** ppFilter )
{
	return GetFilter(CLSID_VideoCompressorCategory,pwsName,ppFilter);
}
HRESULT CMediaHelper::GetVidCompression( LPCWSTR pwsName ,int index,IBaseFilter ** ppFilter )
{
	return GetFilter(CLSID_VideoCompressorCategory,pwsName,index,ppFilter);
}
/******************************Public*Routine******************************\
* GetAudCompression
*
* 得到音频压缩器
\**************************************************************************/
HRESULT CMediaHelper::GetAudCompression( LPCWSTR pwsName ,IBaseFilter ** ppFilter )
{
	return GetFilter(CLSID_AudioCompressorCategory,pwsName,ppFilter);
}
HRESULT CMediaHelper::GetAudCompression( LPCWSTR pwsName ,int index,IBaseFilter ** ppFilter )
{
	return GetFilter(CLSID_AudioCompressorCategory,pwsName,index,ppFilter);
}
HRESULT CMediaHelper::GetAudCompression( int  iCode ,IBaseFilter ** ppFilter )
{
	return GetFilter(CLSID_AudioCompressorCategory,iCode,ppFilter);
}

//删除AM_MEDIA_TYPE类型
void CMediaHelper::DeleteMediaType(AM_MEDIA_TYPE *pmt)
{
    if (pmt != NULL)
    {
       if (pmt->cbFormat != 0)
		{
			CoTaskMemFree((PVOID)pmt->pbFormat);
			pmt->cbFormat = 0;
			pmt->pbFormat = NULL;
		}
		if (pmt->pUnk != NULL)
		{
			// Unecessary because pUnk should not be used, but safest.
			pmt->pUnk->Release();
			pmt->pUnk = NULL;
		}

        CoTaskMemFree(pmt);
    }
}
//销毁 FilterGraph
HRESULT CMediaHelper::DestroyGraph(IFilterGraph * pGraph)
{
    HRESULT hr = S_OK;
    OAFilterState state;

    if( !pGraph )return S_OK;

    FILTER_INFO fi;
    IMediaControl* pMc= NULL;
    IEnumFilters* pEnum= NULL;
    IBaseFilter*  pFilter= NULL;
	IBaseFilter*  pOutFilter = NULL;	
    // 1. stop the graph
	try
	{
		hr = pGraph->QueryInterface( IID_IMediaControl, (void**)&(pMc) );
		if( FAILED(hr)) throw hr;
		pMc->Stop();
		do
		{
			hr = pMc->GetState(100, &state);
		} while( S_OK == hr && State_Stopped != state );

		hr = pGraph->EnumFilters( &(pEnum) );
		if( FAILED(hr))throw hr;
	
		// tear off
		hr = pEnum->Next(1, &(pFilter), NULL);
		while( S_OK == hr && pFilter )
		{
			hr = DisconnectPins( pFilter );
			RELEASE(pFilter);
			hr = pEnum->Next(1, &(pFilter), NULL);
		}
		// remove filters
		hr = pEnum->Reset();
		hr = pEnum->Next(1, &(pFilter), NULL);
		while( S_OK == hr && pFilter )
		{
			hr = pFilter->QueryFilterInfo( &fi);
			if( fi.pGraph)fi.pGraph->Release();
				
			hr = pGraph->RemoveFilter( pFilter);
			RELEASE(pFilter)
			hr = pEnum->Reset();
			hr = pEnum->Next(1, &pFilter, NULL);
		}
	}
	catch(HRESULT hr1)
	{
		hr = hr1;
	}
	RELEASE(pMc);
    RELEASE(pEnum);
    RELEASE(pFilter);
	RELEASE(pOutFilter);

    return hr;
}

/******************************Public*Routine******************************\
* DisconnectPins
*
* Disconnects pins of a filter
*
\**************************************************************************/
HRESULT CMediaHelper::DisconnectPins( IBaseFilter* pFilter)
{
    HRESULT hr = S_OK;

    IEnumPins* pEnum = 0;
    IPin* pPin= 0;

    if( !pFilter )
    {
        return E_POINTER;
    }
	
    hr = pFilter->EnumPins( &pEnum );
    if( FAILED(hr))
    {
        return hr;
    }
    hr = pEnum->Next( 1, &pPin, NULL);

    while( S_OK == hr && pPin )
    {
		IPin* pConnectedPin = 0;
		hr = pPin->ConnectedTo( &pConnectedPin );
		if( pConnectedPin )
			hr = pPin->Disconnect();
		RELEASE(pConnectedPin);
        RELEASE(pPin);
        hr = pEnum->Next( 1, &pPin, NULL);
    }

    RELEASE(pPin);
	RELEASE(pEnum);

    return S_OK;
}
/******************************Public*Routine******************************\
* CSurfaceBuff
*
* 
\**************************************************************************/
CSurfaceBuff::CSurfaceBuff(IDirect3DSurface9* pSurface,BOOL bCopyFromVGA)
			:_pSurface (0)
			,_pBits (0)
			,_iRes (0)
			,_iPitch (0)
			,_pRenderTarget(0)
{
	if(!pSurface)return ;
	ZeroMemory(&_pDesc,sizeof(D3DSURFACE_DESC));
	HRESULT hr = S_OK;
	RELEASE(_pSurface);
	if(bCopyFromVGA){//复制
		_pRenderTarget = pSurface;
		_pRenderTarget->AddRef();
		D3DSURFACE_DESC		dest;
		IDirect3DDevice9*   pSampleDevice       = NULL;
		IDirect3DSurface9 *	pTempSurface		= NULL;
		hr = _pRenderTarget->GetDevice(&pSampleDevice);
		if(SUCCEEDED(hr) && pSampleDevice){
			hr = _pRenderTarget->GetDesc(&dest);
			if(SUCCEEDED(hr)){
				hr = pSampleDevice->CreateOffscreenPlainSurface(
					dest.Width,
					dest.Height,
					dest.Format,
					D3DPOOL_SYSTEMMEM,
					&pTempSurface,0);
				if(SUCCEEDED(hr) && pTempSurface){
					hr = pSampleDevice->GetRenderTargetData(_pRenderTarget,pTempSurface);//从显存复制数据，
					if(SUCCEEDED(hr)) {
						_pSurface = pTempSurface;
						_pSurface->AddRef();
					}

				}
			}
		}
		RELEASE(pSampleDevice);
		RELEASE(pTempSurface);
	}
	else{ 
		_pSurface = pSurface;
		_pSurface->AddRef();
	}
	if(!_pSurface) return ;
	
	D3DLOCKED_RECT lkrc = { 0 , 0 };
	hr = _pSurface->GetDesc(&_pDesc);
	if(FAILED(hr)){
		if(_pSurface){ _pSurface->Release();_pSurface = 0;}
		return ;
	}
	hr = _pSurface->LockRect(&lkrc,0,0);
	if(FAILED(hr)){
		if(_pSurface){ _pSurface->Release();_pSurface = 0;}
		return ;
	}
	_pBits = lkrc.pBits;
	_iPitch = lkrc.Pitch;

}
CSurfaceBuff::~CSurfaceBuff(void)
{
	if(_pSurface){
		_pSurface->UnlockRect();
		_pSurface->Release();
		_pSurface = 0;
	}
	RELEASE(_pRenderTarget);
}
void CSurfaceBuff::Release()
{
	if(_pSurface){
		_pSurface->UnlockRect();
		_pSurface->Release();
		_pSurface = 0;
	}
	RELEASE(_pRenderTarget);
}
HRESULT CSurfaceBuff::UpdateSurface()
{
	if(!_pRenderTarget) return S_OK;
	if(!_pSurface)return E_INVALIDARG;
	IDirect3DDevice9*   pSampleDevice       = NULL;
	HRESULT hr = S_OK;
	try 
	{
		hr = _pRenderTarget->GetDevice(&pSampleDevice);
		if(FAILED(hr)) throw hr;
		if(!pSampleDevice) throw E_OUTOFMEMORY;
		hr = pSampleDevice->UpdateSurface(_pSurface,0,_pRenderTarget,0);
		if(FAILED(hr)) throw hr;
	}
	catch(HRESULT hr1)
	{
		hr = hr1;
	}
	RELEASE(pSampleDevice);
	return hr;

}
LPVOID CSurfaceBuff::Bits()
{
	return _pBits;
}
SIZE_T CSurfaceBuff::Size()
{
	return SIZE_T(_iPitch) * SIZE_T(_pDesc.Height);
}
UINT   CSurfaceBuff::Height()
{
	return _pDesc.Height;
}
UINT   CSurfaceBuff::Width()
{
	return  _pDesc.Width;
}
UINT   CSurfaceBuff::Pitch()
{
	return  _iPitch;
}
D3DFORMAT   CSurfaceBuff::Format()
{
	return _pDesc.Format;
}