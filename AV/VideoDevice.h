#pragma once
#include "streams.h"


typedef struct _VideoAttr{


}VideoAttr,*PVideoAttr;

class VideoDevice
{
public:
	VideoDevice(void);
	~VideoDevice(void);

	 bool OpenVideo(int devID,VideoAttr& videoAttr);
	 bool BindFilter(int devID, IBaseFilter **pFilter);

private:
	CComPtr<IGraphBuilder>              m_pGraph;
	CComPtr<IBaseFilter>                m_pSampleGrabberFilter;
	CComPtr<ISampleGrabber>             m_pSampleGrabber;
	CComPtr<IMediaControl>              m_pMediaControl;
	CComPtr<IMediaEvent>                m_pMediaEvent;
	CComPtr<IBaseFilter>                m_pDeviceFilter;

	CComPtr<IPin>                       m_pGrabberInput;
	CComPtr<IPin>                       m_pGrabberOutput;
	CComPtr<IPin>                       m_pCameraOutput;
	CComPtr<IBaseFilter>                m_pNullFilter;
	CComPtr<IPin>                       m_pNullInputPin;

};

