//
// CDESIAMTimelineVirtualTrack.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESIAMTimelineVirtualTrack__
#define __H_CDESIAMTimelineVirtualTrack__

#include "CDESBaseInterface.h"

class CDESIAMTimelineVirtualTrack : public CDESBaseInterface
{
private:
	IAMTimelineVirtualTrack *   mVirtualTrack;

public:
	CDESIAMTimelineVirtualTrack();
	~CDESIAMTimelineVirtualTrack();

	virtual bool QueryInterfaceSelf(void);
	virtual void ReleaseInterface(void);

	bool TrackGetPriority(long * outPriority);

private:
	void ReleaseSelf(void);
};

#endif // __H_CDESIAMTimelineVirtualTrack__