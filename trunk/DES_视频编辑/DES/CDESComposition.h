//
// CDESComposition.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESComposition__
#define __H_CDESComposition__

#include "CDESBaseObject.h"
#include "CDESIAMTimelineEffectable.h"
#include "CDESIAMTimelineTransable.h"
#include "CDESIAMTimelineVirtualTrack.h"

class CDESComposition : public CDESBaseObject
{
protected:
	IAMTimelineComp *            mInterfaceComp; // Basic interface
	CDESIAMTimelineEffectable    mEffectable;    // Other interfaces
	CDESIAMTimelineTransable     mTransable;
	CDESIAMTimelineVirtualTrack  mVirtualTrack;

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

public:
	CDESComposition(CDESTimeLine * inTimeLine);
	~CDESComposition();

	// --- IAMTimelineComp methods ---
	bool GetNextVTrack(CDESBaseObject * inVTrack, CDESBaseObject & outNextVTrack);
	bool GetRecursiveLayerOfType(CDESBaseObject & outVTrack, 
		long inLayerIndex, TIMELINE_MAJOR_TYPE inType);

	bool VTrackGetCount(long * outCount);
	bool GetVTrack(CDESBaseObject & outVTrack, long inPriority);
	bool VTrackInsBefore(CDESBaseObject & inVTrack, long inPriority);
	bool VTrackSwapPriorities(long inVTrackA, long inVTrackB);
	bool GetCountOfType(long * outVal, long * outValWithComps, TIMELINE_MAJOR_TYPE inType);

	// --- IAMTimelineEffectable methods ---
	bool EffectGetCount(long * outCount);
	bool EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority);
	bool EffectSwapPriorities(long inPriorityA, long inPriorityB);
	bool GetEffect(CDESBaseObject & outEffect, long inWhich);

	// --- IAMTimelineTransable methods ---
	bool TransGetCount(long * outCount);
	bool TransAdd(CDESBaseObject & inTransition);
	bool GetNextTrans(CDESBaseObject & outTransition, REFERENCE_TIME * ioStartStop);
	bool GetNextTrans2(CDESBaseObject & outTransition, REFTIME * ioStartStop);
	bool GetTransAtTime(CDESBaseObject & outTransition, 
		REFERENCE_TIME inTime, long inSearchDirection);
	bool GetTransAtTime2(CDESBaseObject & outTransition, 
		REFTIME inTime, long inSearchDirection);

	// --- IAMTimelineVirtualTrack methods ---
	bool TrackGetPriority(long * outPriority);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);
};

#endif // __H_CDESComposition__