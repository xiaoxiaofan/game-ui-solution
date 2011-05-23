#pragma once
#include "Export.h"
#include "streams.h"
#include "dshowutil.h"
#include "smartptr.h"
#include "qedit.h"


typedef struct _VideoAttr{


}VideoAttr,*PVideoAttr;

class AVDEVICE_API CVideoDevice
{
public:
	CVideoDevice(void);
	~CVideoDevice(void);

	 void OpenCamera(int devID);
	 bool SetPosition(HWND hwnd,int x, int y, int cx, int cy);
	 void Start();
	 bool OpenFile();

private:
	 HRESULT BindFilter(int devID, IBaseFilter **pFilter);

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

	SmartPtr<IPin>                       m_pGrabberInput;
	SmartPtr<IPin>                       m_pGrabberOutput;
	SmartPtr<IPin>                       m_pCameraOutput;
	SmartPtr<IPin>                       m_pVideoRenderInput;
	SmartPtr<IBaseFilter>                m_pNullFilter;
	SmartPtr<IPin>                       m_pNullInputPin;

};

