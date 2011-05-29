
#include "MultiVMR9.h"
// Filter name strings
#define g_wszPush    L"PushSource  Filter"
typedef struct _MultiVMR9AllocatorProperties {
    long cBuffers;
    long width;
	long height;
	D3DFORMAT format;
    long cbPrefix;
} MultiVMR9_ALLOCATOR_PROPERTIES;
/**********************************************
 *
 *  CMultiVMR9_MemAllocator
 *  重写内存分配器，使其分配IDirect3DSurface9
 *
 **********************************************/
	
class CMultiVMR9_MemAllocator: 
		public CBaseAllocator
{
	public:
	CMultiVMR9_MemAllocator(TCHAR *, LPUNKNOWN, HRESULT *);
	#ifdef UNICODE
	CMultiVMR9_MemAllocator(CHAR *, LPUNKNOWN, HRESULT *);
	#endif

	~CMultiVMR9_MemAllocator();
	//
	HRESULT Set3DDevice(IDirect3DDevice9* pSampleDevice);
	CUnknown *CreateInstance(LPUNKNOWN pUnk, HRESULT *phr);
	STDMETHODIMP SetProperties( ALLOCATOR_PROPERTIES* pRequest, ALLOCATOR_PROPERTIES* pActual);
	STDMETHODIMP GetProperties( ALLOCATOR_PROPERTIES * pActual);
	STDMETHODIMP SetProperties( MultiVMR9_ALLOCATOR_PROPERTIES* pRequest, MultiVMR9_ALLOCATOR_PROPERTIES* pActual);
	void Free(void);
	private:
	void ReallyFree(void);
	HRESULT Alloc(void);
	IDirect3DSurface9 ** _ppSurface;
	IDirect3DDevice9*   _pSampleDevice;
	LONG _lWidth;
	LONG _lHeight;
	D3DFORMAT _eFormat;
};
/**********************************************
 *
 *  CMultiVMR9_MemAllocator
 * 重写IMediaSample，使其能接受IDirect3DSurface9
 *
 **********************************************/	
	class CMultiVMR9_MediaSample:
		public CMediaSample
	{
	public:
		CMultiVMR9_MediaSample(
				TCHAR *pName,
				CBaseAllocator *pAllocator,
				HRESULT *phr,
				IDirect3DSurface9 *pSurface=NULL,
				LONG length = 0);
		#ifdef UNICODE
			CMultiVMR9_MediaSample(
				CHAR *pName,
				CBaseAllocator *pAllocator,
				HRESULT *phr,
				IDirect3DSurface9 *pSurface=NULL,
				LONG length = 0);
		#endif
		~CMultiVMR9_MediaSample(){
			if(_pSurface)_pSurface->Release();
		}
		HRESULT GetSurface(IDirect3DSurface9** ppSurface){
				if(_pSurface) 
				{
					*ppSurface = _pSurface;
					_pSurface->AddRef();
					return S_OK;
				}
				else return S_FALSE;
			}
		STDMETHOD( GetPointer)
		(
			BYTE ** ppBuffer
		);
	private:
		IDirect3DSurface9 * _pSurface;
	};
class CPushPin : public CSourceStream
{
protected:

	IDirect3DDevice9* _pSampleDevice;

    CMediaType m_MediaType;
	GUID m_SubTypeGUID;
	int m_iImageWidth;
	int m_iImageHeight;
	UINT m_nCurrentBitDepth;
  
private:

	HRESULT DoBufferProcessingLoop(void);
	
public:
	CCritSec m_cSharedState;            // Protects our internal state
    CPushPin(IDirect3DDevice9* pSampleDevice ,HRESULT *phr, CSource *pFilter);
    ~CPushPin();
	HRESULT GetDeliveryBuffer(IMediaSample ** ppSample,
                                  REFERENCE_TIME * pStartTime,
                                  REFERENCE_TIME * pEndTime,
								  DWORD dwFlags){
		return CSourceStream::GetDeliveryBuffer(ppSample,pStartTime,pEndTime,dwFlags);
	}
	HRESULT DecideAllocator(IMemInputPin * pPin, IMemAllocator ** pAlloc);

    HRESULT DecideBufferSize(IMemAllocator *pAlloc, ALLOCATOR_PROPERTIES *pRequest);
    HRESULT FillBuffer(IMediaSample *pSample);
   
    HRESULT SetMediaType(const CMediaType *pMediaType);

    HRESULT CheckMediaType(const CMediaType *pMediaType);
    HRESULT GetMediaType(int iPosition, CMediaType *pmt);
	HRESULT InitAllocator(IMemAllocator **ppAlloc);
	HRESULT DecideBufferSize(
        IMemAllocator * pAlloc,
        MultiVMR9_ALLOCATOR_PROPERTIES * ppropInputRequest
    );
	
    STDMETHODIMP Notify(IBaseFilter *pSelf, Quality q)
    {
        return E_FAIL;
    }

};



class CPushSource : public CSource
{

public:
    // Constructor is private because you have to use CreateInstance
    CPushSource(IDirect3DDevice9* pSampleDevice,IUnknown *pUnk, HRESULT *phr);
    ~CPushSource();
private:
    CPushPin *m_pPin;

//public:
    static CUnknown * WINAPI CreateInstance(IUnknown *pUnk, HRESULT *phr);  

};


