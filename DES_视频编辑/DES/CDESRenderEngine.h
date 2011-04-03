//
// CDESRenderEngine.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESRenderEngine__
#define __H_CDESRenderEngine__

#include <streams.h>

class CDESTimeLine;
class CDESRenderEngine
{
private:
	IRenderEngine *      mRenderEngine;
	IMediaControl *      mMediaControl;  // Filter graph manager
	IMediaEvent *        mMediaEvent;

	double               mRenderRangeStart;
	double               mRenderRangeStop;

public:
	CDESRenderEngine();
	~CDESRenderEngine();

	bool Initialize(void);  // Must be invoked!!

	bool SetTimelineObject(CDESTimeLine & inTimeLine);
	bool GetTimelineObject(CDESTimeLine & outTimeLine);

	bool ConnectFrontEnd(BOOL * outNeedReset = NULL);
	bool RenderOutputPins(void);
	bool GetGroupOutputPin(long inGroupIndex, IPin ** outRenderPin);

	bool ScrapIt(void);
	bool SetFilterGraph(IGraphBuilder * inFilterGraph);
	bool GetFilterGraph(IGraphBuilder ** outFilterGraph);
	bool SetDynamicReconnectLevel(DWORD inLevel);
	bool SetRenderRange(REFERENCE_TIME inStart, REFERENCE_TIME inStop);
	bool SetRenderRange2(double inStart, double inStop);
	bool GetRenderRange2(double * outStart, double * outStop);

	bool SetSourceNameValidation(const char * inFilterString);
	bool GetVendorString(BSTR * outVendorID);

	//--- Filter graph manager interfaces ---
	bool GraphRun(void);
	bool GraphPause(void);
	bool GraphStop(void);
	bool WaitForCompletion(void);
};

#endif // __H_CDESRenderEngine__