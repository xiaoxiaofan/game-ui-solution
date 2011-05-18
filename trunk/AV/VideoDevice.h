#pragma once


typedef struct _VideoAttr{


}VideoAttr,*PVideoAttr;

class VideoDevice
{
public:
	VideoDevice(void);
	~VideoDevice(void);

	 bool OpenVideo(int devID,VideoAttr& videoAttr);

private:
	CComPtr<IGraphBuilder>              m_pGraph;
	CComPtr<IBaseFilter>                m_pSampleGrabberFilter;
	CComPtr<ISampleGrabber>             m_pSampleGrabber;
	CComPtr<IMediaControl>              m_pMediaControl;
	CComPtr<IMediaEvent>                m_pMediaEvent;

};

