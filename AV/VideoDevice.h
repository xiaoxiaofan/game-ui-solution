#pragma once
#include "Export.h"
#include "streams.h"
#include "dshowutil.h"
#include "smartptr.h"
#include "qedit.h"
#include "cxcore.h"


typedef struct _VideoAttr{


}VideoAttr,*PVideoAttr;



// 提供回调ISampleGrabber，抓帧

class AVDEVICE_API VideoProcessAdapter : public ISampleGrabberCB
{
public:
	VideoProcessAdapter(){}
public:
	virtual ~VideoProcessAdapter(void){}

public:
	STDMETHOD(BufferCB)(double SampleTime, BYTE *pBuffer, long nBufferLen);

	STDMETHOD(SampleCB)(double, IMediaSample *){return S_OK;}

	STDMETHOD( QueryInterface )( REFIID iid, LPVOID *ppv )
	{
		if( iid == IID_ISampleGrabberCB || iid == IID_IUnknown )
		{ 
			*ppv = (void *) static_cast<ISampleGrabberCB*>( this );
			return NOERROR;
		} 
		return E_NOINTERFACE;
	}

	STDMETHOD_( ULONG, AddRef )(){return 2;}
	STDMETHOD_( ULONG, Release)(){return 1;}
};


class AVDEVICE_API CVideoDevice
{
public:
	CVideoDevice(ISampleGrabberCB* sampleCallBack);
	~CVideoDevice(void);

	 void OpenCamera(int devID);
	 void SetPosition(HWND hwnd,int x, int y, int cx, int cy);
	 void Start();
	 void Stop();
	 bool OpenFile();
	 IplImage* QueryFrame();
	 void SetBroadCast(bool isBroadCast);
	 void SetBuffer(bool isBuffer);
	 void StartRecord();
	 void OpenMutil();

private:
	 HRESULT BindFilter(int devID, IBaseFilter **pFilter);
	 BSTR GetMoviePath();

private:
	SmartPtr<IGraphBuilder>              m_pGraph;
	SmartPtr<IBaseFilter>                m_pSampleGrabberFilter;
	SmartPtr<ISampleGrabber>             m_pSampleGrabber;
	SmartPtr<IMediaControl>              m_pMediaControl;
	SmartPtr<IMediaEvent>                m_pMediaEvent;
	SmartPtr<IBaseFilter>                m_pDeviceFilter;
	SmartPtr<IBaseFilter>                m_pVideoRender;
	SmartPtr<IVideoWindow>               m_pVideoWindow;
	SmartPtr<IBaseFilter>                m_pVideoSource;
	SmartPtr<ICaptureGraphBuilder2>      m_pCaputer;
	SmartPtr<IAMStreamConfig>            m_pVideoConfig;
	SmartPtr<IBaseFilter>                m_pVRM;

	SmartPtr<IPin>                       m_pGrabberInput;
	SmartPtr<IPin>                       m_pGrabberOutput;
	SmartPtr<IPin>                       m_pCaputerOutput;
	SmartPtr<IPin>                       m_pVideoRenderInput;
	SmartPtr<IBaseFilter>                m_pNullFilter;
	SmartPtr<IPin>                       m_pNullInputPin;

	HWND                                 m_Hwnd;
	long                                 m_nBufferSize;
	IplImage*                            m_pFrame;
	int                                  m_nWidth;
	int                                  m_nHeight;
	SmartPtr<VideoProcessAdapter>        m_pSampleCallBack;
};

