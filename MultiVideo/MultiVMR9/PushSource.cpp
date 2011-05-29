//------------------------------------------------------------------------------
// File: PushSource.cpp
//
// Desc: DirectShow sample code - In-memory push mode source filter
//       Provides an image of the user's  as a continuously updating stream.
//
//------------------------------------------------------------------------------

#include <streams.h>

#include "PushSource.h"
#include <initguid.h>
#ifndef __PUSHGUIDS_DEFINED
#define __PUSHGUIDS_DEFINED
// {B60272CF-C09B-4dd9-AB42-13F907764FE6}
DEFINE_GUID(CLSID_PushSource, 
0xb60272cf, 0xc09b, 0x4dd9, 0xab, 0x42, 0x13, 0xf9, 0x7, 0x76, 0x4f, 0xe6);
#endif
#ifndef	CONNECT_TRACE_LEVEL
#define CONNECT_TRACE_LEVEL 3
#endif
//#include "PushGuids.h"

/////////////////////// Private class CMultiVMR9_MemAllocator ////////////////////////////////

CMultiVMR9_MemAllocator::CMultiVMR9_MemAllocator(
														TCHAR *pName,
														LPUNKNOWN pUnk,
														HRESULT *phr)
						: CBaseAllocator(pName, pUnk, phr, TRUE, TRUE)
						,_ppSurface(0)
						,_pSampleDevice(0)
						,_lWidth(0)
						,_lHeight(0)
						,_eFormat(D3DFMT_UNKNOWN)
{
	
}
#ifdef UNICODE
CMultiVMR9_MemAllocator::CMultiVMR9_MemAllocator(
																	CHAR *pName,
																	LPUNKNOWN pUnk,
																	HRESULT *phr)
						: CBaseAllocator(pName, pUnk, phr, TRUE, TRUE)
						,_ppSurface(0)
						,_pSampleDevice(0)
						,_lWidth(0)
						,_lHeight(0)
						,_eFormat(D3DFMT_UNKNOWN)
{
}
#endif
CMultiVMR9_MemAllocator::~CMultiVMR9_MemAllocator(void)
{
	if(_pSampleDevice)_pSampleDevice->Release();
	Decommit();
	ReallyFree();

}
CUnknown *CMultiVMR9_MemAllocator::CreateInstance(LPUNKNOWN pUnk, HRESULT *phr)
{
	CUnknown *pUnkRet = new CMultiVMR9_MemAllocator(NAME("CMultiVMR9_MemAllocator"), pUnk, phr);
    return pUnkRet;
}
HRESULT CMultiVMR9_MemAllocator::Alloc(void)
{
	 CAutoLock lck(this);
	
    /* Check he has called SetProperties */
    HRESULT hr = NOERROR;
	 if (m_lCount <= 0 ) {
        return VFW_E_SIZENOTSET;
    }

    /* should never get here while buffers outstanding */
    ASSERT(m_lFree.GetCount() == m_lAllocated);

    /* If the requirements haven't changed then don't reallocate */
    if (m_bChanged == FALSE) {
        return NOERROR;
    }
	if(_pSampleDevice == NULL) return S_FALSE;
    ASSERT(hr == S_OK); // we use this fact in the loop below
	
    /* Free the old resources */
	
    if(_ppSurface)
		ReallyFree();


   
    //ASSERT(lAlignedSize % m_lAlignment == 0);
	_ppSurface = new IDirect3DSurface9*[m_lCount];
    if (_ppSurface == NULL) {
        return E_OUTOFMEMORY;
    }
    ZeroMemory( _ppSurface, m_lCount * sizeof(IDirect3DSurface9*));

    ASSERT(m_lAllocated == 0);
	CMediaSample *pSample;
    // Create the new samples - we have allocated m_lSize bytes for each sample
    // plus m_lPrefix bytes per sample as a prefix. We set the pointer to
    // the memory after the prefix - so that GetPointer() will return a pointer
    // to m_lSize bytes.
    for (; m_lAllocated < m_lCount; m_lAllocated++) {
	
		hr = _pSampleDevice->CreateOffscreenPlainSurface(
				_lWidth,
				_lHeight,
				_eFormat,
				D3DPOOL_SYSTEMMEM,
				&_ppSurface[m_lAllocated],0);//
		if (FAILED(hr))return hr;
		if(_ppSurface[m_lAllocated] == 0 )return E_OUTOFMEMORY;
		D3DLOCKED_RECT lkrc = { 0 , 0 };
		if(m_lSize == 0){//得到内存分配大小
			hr = _ppSurface[m_lAllocated]->LockRect(&lkrc,0,0);
			if (FAILED(hr))return hr;
			m_lSize = lkrc.Pitch * _lHeight;
			m_lAlignment = lkrc.Pitch;
		}

        pSample = new CMultiVMR9_MediaSample(
                            NAME("Default memory media sample"),
							this,
                            &hr,
                            _ppSurface[m_lAllocated],      // GetPointer() value
                            m_lSize);               // not including prefix

            ASSERT(SUCCEEDED(hr));
        if (pSample == NULL) {
            return E_OUTOFMEMORY;
        }

        // This CANNOT fail
        m_lFree.Add(pSample);
    }
	
    m_bChanged = FALSE;
    return NOERROR;
}
void CMultiVMR9_MemAllocator::Free(void)
{
    return;
}
void CMultiVMR9_MemAllocator::ReallyFree(void)
{
	 ASSERT(m_lAllocated == m_lFree.GetCount());

    /* Free up all the CMediaSamples */
	
    CMediaSample *pSample;
    for (;;) {
        pSample = m_lFree.RemoveHead();
        if (pSample != NULL) {
            delete pSample;
        } else {
            break;
        }
    }
	for(int i = 0;i<m_lAllocated;i++)
	{
		if(_ppSurface[i])
		{
			_ppSurface[i]->UnlockRect();
			_ppSurface[i]->Release();
			_ppSurface[i] = 0;
		}
	}
	delete []_ppSurface;
	_ppSurface = 0;
    m_lAllocated = 0;
}
HRESULT
CMultiVMR9_MemAllocator::Set3DDevice(IDirect3DDevice9* pSampleDevice){
			if(pSampleDevice){
				_pSampleDevice = pSampleDevice;
				_pSampleDevice->AddRef();
				return S_OK;
			}
			else return E_FAIL;
		}
STDMETHODIMP
CMultiVMR9_MemAllocator::SetProperties(
                ALLOCATOR_PROPERTIES* pRequest,
                ALLOCATOR_PROPERTIES* pActual)
{
	return NOERROR;
}
STDMETHODIMP 
CMultiVMR9_MemAllocator::SetProperties(
				MultiVMR9_ALLOCATOR_PROPERTIES* pRequest,
				MultiVMR9_ALLOCATOR_PROPERTIES* pActual)
{
	CheckPointer(pActual,E_POINTER);
    ValidateReadWritePtr(pActual,sizeof(MultiVMR9_ALLOCATOR_PROPERTIES));
    CAutoLock cObjectLock(this);

    ZeroMemory(pActual, sizeof(ALLOCATOR_PROPERTIES));

    ASSERT(pRequest->height > 0);
	ASSERT(pRequest->width  > 0);

    /* Can't do this if already committed, there is an argument that says we
       should not reject the SetProperties call if there are buffers still
       active. However this is called by the source filter, which is the same
       person who is holding the samples. Therefore it is not unreasonable
       for them to free all their samples before changing the requirements */

    if (m_bCommitted == TRUE) {
        return VFW_E_ALREADY_COMMITTED;
    }

    /* Must be no outstanding buffers */

    if (m_lFree.GetCount() < m_lAllocated) {
        return VFW_E_BUFFERS_OUTSTANDING;
    }

    /* There isn't any real need to check the parameters as they
       will just be rejected when the user finally calls Commit */

    // round length up to alignment - remember that prefix is included in
    // the alignment
 
    pActual->cBuffers	= m_lCount = pRequest->cBuffers;
    pActual->cbPrefix	= m_lPrefix = pRequest->cbPrefix;
	pActual->height		= _lHeight	= pRequest->height;
	pActual->width		= _lWidth	= pRequest->width;
	pActual->format		= _eFormat	= pRequest->format;

    m_bChanged = TRUE;
    return NOERROR;
}
STDMETHODIMP
CMultiVMR9_MemAllocator::GetProperties(
    ALLOCATOR_PROPERTIES * pActual)
{
	
    CheckPointer(pActual,E_POINTER);
    ValidateReadWritePtr(pActual,sizeof(ALLOCATOR_PROPERTIES));

    CAutoLock cObjectLock(this);
	Alloc();
    pActual->cbBuffer = m_lSize;
    pActual->cBuffers = m_lCount;
    pActual->cbAlign = m_lAlignment;
    pActual->cbPrefix = m_lPrefix;
    return NOERROR;
}
/////////////////////// Private class CMultiVMR9_MediaSample ///////////////////////////////////////
CMultiVMR9_MediaSample::CMultiVMR9_MediaSample(TCHAR *pName,
               CBaseAllocator *pAllocator,
               HRESULT *phr,
               IDirect3DSurface9 *pSurface,
               LONG length) 
			   :CMediaSample(pName,pAllocator,phr,0,length)
			   ,_pSurface(pSurface)
{
	if(_pSurface)_pSurface->AddRef();
    /* We must have an owner and it must also be derived from class
       CBaseAllocator BUT we do not hold a reference count on it */

    ASSERT(pAllocator);
}

#ifdef UNICODE
CMultiVMR9_MediaSample::CMultiVMR9_MediaSample(CHAR *pName,
               CBaseAllocator *pAllocator,
               HRESULT *phr,
               IDirect3DSurface9 *pSurface,
               LONG length) 
			   :CMediaSample(pName,pAllocator,phr,0,length) 
			   ,_pSurface(pSurface)
{
	if(_pSurface)_pSurface->AddRef();
    /* We must have an owner and it must also be derived from class
       CBaseAllocator BUT we do not hold a reference count on it */
    ASSERT(pAllocator);
}
#endif
STDMETHODIMP CMultiVMR9_MediaSample::GetPointer(BYTE ** ppBuffer)
{
	 ValidateReadWritePtr(ppBuffer,sizeof(BYTE *));

    // creator must have set pointer either during
    // constructor or by SetPointer
    ASSERT(_pSurface);
	_pSurface->UnlockRect();
	D3DLOCKED_RECT lkrc = { 0 , 0 };
	HRESULT hr = _pSurface->LockRect(&lkrc,0,0);
	*ppBuffer = (BYTE*)lkrc.pBits;
    return hr;
}
/**********************************************
 *
 *  CPushPin Class
 *  
 *
 **********************************************/

CPushPin::CPushPin(IDirect3DDevice9* pSampleDevice,HRESULT *phr, CSource *pFilter)
        : CSourceStream(NAME("Push Source "), phr, pFilter, L"Out")
		,_pSampleDevice(pSampleDevice)
		, m_SubTypeGUID(GUID_NULL)
		, m_iImageWidth(0)
		, m_iImageHeight(0)
		, m_nCurrentBitDepth(0)
{
	_pSampleDevice->AddRef();
}

CPushPin::~CPushPin()
{   
	_pSampleDevice->Release();
	_pSampleDevice = 0;
   // DbgLog((LOG_TRACE, 3, TEXT("Frames written %d"), m_iFrameNumber));
}
HRESULT CPushPin::InitAllocator(IMemAllocator **ppAlloc)
{
	HRESULT hr = NOERROR;
	*ppAlloc = new CMultiVMR9_MemAllocator(NAME("CMultiVMR9_MemAllocator"), 0, &hr);
	(*ppAlloc)->AddRef();
	((CMultiVMR9_MemAllocator*)*ppAlloc)->Set3DDevice(_pSampleDevice);
	return hr;
}
HRESULT CPushPin::DecideBufferSize(IMemAllocator *pAlloc,
                                      MultiVMR9_ALLOCATOR_PROPERTIES *pProperties)
{  
	CheckPointer(pAlloc,E_POINTER);
    CheckPointer(pProperties,E_POINTER);

    CAutoLock cAutoLock(m_pFilter->pStateLock());
    HRESULT hr = NOERROR;
    VIDEOINFO *pvi = (VIDEOINFO *) m_MediaType.Format();
    pProperties->cBuffers = 1;
	pProperties->height =abs( pvi->bmiHeader.biHeight);
	pProperties->width	=pvi->bmiHeader.biWidth;
	const GUID *subtp = m_MediaType.Subtype();
	if( *subtp == MEDIASUBTYPE_RGB565 )
		pProperties->format = D3DFMT_R5G6B5;
	else if( *subtp == MEDIASUBTYPE_RGB555)
		pProperties->format = D3DFMT_X1R5G5B5;
	else if( *subtp ==  MEDIASUBTYPE_RGB24)
		pProperties->format = D3DFMT_R8G8B8;
	else if( *subtp ==  MEDIASUBTYPE_RGB32)
		pProperties->format = D3DFMT_X8R8G8B8;
	else if( *subtp ==  MEDIASUBTYPE_ARGB1555)
		pProperties->format = D3DFMT_A1R5G5B5;
	else if( *subtp ==  MEDIASUBTYPE_ARGB4444)
		pProperties->format = D3DFMT_A4R4G4B4;
	else if( *subtp ==  MEDIASUBTYPE_ARGB32)
		pProperties->format = D3DFMT_A8R8G8B8;
	else if( *subtp ==  MEDIASUBTYPE_YUY2)
		pProperties->format = D3DFMT_YUY2;
	else if( *subtp ==  MEDIASUBTYPE_UYVY)
		pProperties->format = D3DFMT_UYVY;
	else if( *subtp ==  MEDIASUBTYPE_AI44)
		pProperties->format = D3DFMT_A4L4;
	else return E_FAIL;

	ASSERT(pProperties->height);
	ASSERT(pProperties->width);

    // Ask the allocator to reserve us some sample memory. NOTE: the function
    // can succeed (return NOERROR) but still not have allocated the
    // memory that we requested, so we must check we got whatever we wanted.
    MultiVMR9_ALLOCATOR_PROPERTIES Actual;
    hr = ((CMultiVMR9_MemAllocator*)pAlloc)->SetProperties(pProperties,&Actual);
    if(FAILED(hr))
    {
        return hr;
    }

    // Make sure that we have only 1 buffer (we erase the ball in the
    // old buffer to save having to zero a 200k+ buffer every time
    // we draw a frame)
    ASSERT(Actual.cBuffers == 1);
    return NOERROR;
}
HRESULT CPushPin::DecideAllocator(IMemInputPin * pPin, IMemAllocator ** ppAlloc)
{
	if (*ppAlloc) {
        (*ppAlloc)->Release();
        *ppAlloc = NULL;
    }
	MultiVMR9_ALLOCATOR_PROPERTIES prop;
	ZeroMemory(&prop,sizeof(prop));
    /* Try the output pin's allocator by the same method */
	HRESULT hr;
    hr = InitAllocator(ppAlloc);
    if (SUCCEEDED(hr)) {

        // note - the properties passed here are in the same
        // structure as above and may have been modified by
        // the previous call to DecideBufferSize
        hr = DecideBufferSize(*ppAlloc, &prop);
        if (SUCCEEDED(hr)) {
            hr = pPin->NotifyAllocator(*ppAlloc, FALSE);
            if (SUCCEEDED(hr)) {
                return NOERROR;
            }
        }
    }

    /* Likewise we may not have an interface to release */

    if (*ppAlloc) {
        (*ppAlloc)->Release();
        *ppAlloc = NULL;
    }
    return hr;
}
HRESULT CPushPin::DoBufferProcessingLoop(void) {

	Command com;

    OnThreadStartPlay();

    do {
	while (!CheckRequest(&com)) {

	   Sleep(1);

            // all paths release the sample
	}

        // For all commands sent to us there must be a Reply call!

	if (com == CMD_RUN || com == CMD_PAUSE) {
	    Reply(NOERROR);
	} else if (com != CMD_STOP) {
	    Reply((DWORD) E_UNEXPECTED);
	    DbgLog((LOG_ERROR, 1, TEXT("Unexpected command!!!")));
	}
    } while (com != CMD_STOP);

    return S_FALSE;
}


HRESULT CPushPin::GetMediaType(int iPosition, CMediaType *pmt)
{
    CheckPointer(pmt,E_POINTER);
    CAutoLock cAutoLock(m_pFilter->pStateLock());

    if(iPosition < 0)
        return E_INVALIDARG;

    // Have we run off the end of types?
    if(iPosition > 0)
        return VFW_S_NO_MORE_ITEMS;

    VIDEOINFO *pvi = (VIDEOINFO *) pmt->AllocFormatBuffer(sizeof(VIDEOINFO));
    if(NULL == pvi)
        return(E_OUTOFMEMORY);

    // Initialize the VideoInfo structure before configuring its members
    ZeroMemory(pvi, sizeof(VIDEOINFO));
	pvi->bmiHeader.biBitCount	 = m_nCurrentBitDepth;
	pvi->bmiHeader.biCompression = BI_RGB;
	pvi->bmiHeader.biSize       = sizeof(BITMAPINFOHEADER);
    pvi->bmiHeader.biWidth      = m_iImageWidth;
    pvi->bmiHeader.biHeight     = m_iImageHeight;
    pvi->bmiHeader.biPlanes     = 1;
    pvi->bmiHeader.biSizeImage  = GetBitmapSize(&pvi->bmiHeader);
    pvi->bmiHeader.biClrImportant = 0;
    SetRectEmpty(&(pvi->rcSource)); // we want the whole image area rendered.
    SetRectEmpty(&(pvi->rcTarget)); // no particular destination rectangle


    pmt->SetType(&MEDIATYPE_Video);
    pmt->SetFormatType(&FORMAT_VideoInfo);
    pmt->SetTemporalCompression(FALSE);

    // Work out the GUID for the subtype from the header info.
   
    pmt->SetSubtype(&m_SubTypeGUID);
    pmt->SetSampleSize(pvi->bmiHeader.biSizeImage);

    return NOERROR;

} // AttemptConnection

HRESULT CPushPin::CheckMediaType(const CMediaType *pMediaType)
{
    CheckPointer(pMediaType,E_POINTER);

    if((*(pMediaType->Type()) != MEDIATYPE_Video) ||   // we only output video
        !(pMediaType->IsFixedSize()))                  // in fixed size samples
    {                                                  
        return E_INVALIDARG;
    }

    // Check for the subtypes we support
    const GUID *SubType = pMediaType->Subtype();
    if (SubType == NULL)
        return E_INVALIDARG;

	if( *m_MediaType.Subtype() != *SubType  )
    {
        return E_INVALIDARG;
    }

    // Get the format area of the media type
    VIDEOINFO *pvi = (VIDEOINFO *) pMediaType->Format();
	VIDEOINFO *pvi_this = (VIDEOINFO *) m_MediaType.Format();

    if(pvi == NULL)
        return E_INVALIDARG;

    // Check if the image width & height have changed
    if(    pvi->bmiHeader.biWidth   != pvi_this->bmiHeader.biWidth || 
       abs(pvi->bmiHeader.biHeight) != abs(pvi_this->bmiHeader.biHeight))
    {
        // If the image width/height is changed, fail CheckMediaType() to force
        // the renderer to resize the image.
        return E_INVALIDARG;
    }
    //  Accept formats with negative height, which would cause the 
    // image to be displayed upside down.
 
    return S_OK;  // This format is acceptable.

} // CheckMediaType


//
// DecideBufferSize
//
// This will always be called after the format has been sucessfully
// negotiated. So we have a look at m_mt to see what size image we agreed.
// Then we can ask for buffers of the correct size to contain them.
//
HRESULT CPushPin::DecideBufferSize(IMemAllocator *pAlloc,
                                      ALLOCATOR_PROPERTIES *pProperties)
{

    return NOERROR;

} // DecideBufferSize


//
// SetMediaType
//
// Called when a media type is agreed between filters
//
HRESULT CPushPin::SetMediaType(const CMediaType *pMediaType)
{
     CAutoLock cAutoLock(m_pFilter->pStateLock());

    // Pass the call up to my base class
    HRESULT hr = CSourceStream::SetMediaType(pMediaType);

    if(SUCCEEDED(hr))
    {
        VIDEOINFO * pvi = (VIDEOINFO *) m_mt.Format();
        if (pvi == NULL)
            return E_UNEXPECTED;

		 m_MediaType = m_mt;
		 m_SubTypeGUID = *m_mt.Subtype();
         m_nCurrentBitDepth = pvi->bmiHeader.biBitCount;
		 m_SubTypeGUID;
		 m_iImageWidth = pvi->bmiHeader.biWidth;
		 m_iImageHeight = abs(pvi->bmiHeader.biHeight);
    } 

    return hr;

} // SetMediaType


// This is where we insert the DIB bits into the video stream.
// FillBuffer is called once for every sample in the stream.
HRESULT CPushPin::FillBuffer(IMediaSample *pSample)
{


    return S_OK;
}



/**********************************************
 *
 *  CPushSource Class
 *
 **********************************************/

CPushSource::CPushSource(IDirect3DDevice9* pSampleDevice,IUnknown *pUnk, HRESULT *phr)
           : CSource(NAME("PushSource"), pUnk, CLSID_PushSource)
{
    // The pin magically adds itself to our pin array.
    m_pPin = new CPushPin(pSampleDevice,phr, this);

	if (phr)
	{
		if (m_pPin == NULL)
			*phr = E_OUTOFMEMORY;
		else
			*phr = S_OK;
	}  
}


CPushSource::~CPushSource()
{

    delete m_pPin;
}



