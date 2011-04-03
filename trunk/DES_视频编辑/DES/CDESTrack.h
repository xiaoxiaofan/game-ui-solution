//
// CDESTrack.h
// 
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESTrack__
#define __H_CDESTrack__

#include "CDESBaseObject.h"
#include "CDESIAMTimelineEffectable.h"
#include "CDESIAMTimelineTransable.h"
#include "CDESIAMTimelineVirtualTrack.h"
#include "CDESIAMTimelineSplittable.h"

class CDESTrack : public CDESBaseObject
{
private:
	IAMTimelineTrack *           mInterfaceTrack;
	CDESIAMTimelineEffectable    mEffectable;    // Other interfaces
	CDESIAMTimelineTransable     mTransable;
	CDESIAMTimelineVirtualTrack  mVirtualTrack;
	CDESIAMTimelineSplittable    mSplittable;

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

public:
	CDESTrack(CDESTimeLine * inTimeLine);
	~CDESTrack();

	bool AreYouBlank(long * outIsBlank);
	bool GetSourcesCount(long * outCount);
	bool SrcAdd(CDESBaseObject & inSource);
	bool GetNextSrc(CDESBaseObject & outSource, REFERENCE_TIME * ioStartStop);
	bool GetNextSrc2(CDESBaseObject & outSource, REFTIME * ioStartStop);
	bool GetNextSrcEx(CDESBaseObject * inLast, CDESBaseObject & outNext);
	bool GetSrcAtTime(CDESBaseObject & outSource, REFERENCE_TIME inTime, long inSearchDirection);
	bool GetSrcAtTime2(CDESBaseObject & outSource, REFTIME inTime, long inSearchDirection);
	bool InsertSpace(REFERENCE_TIME inStart, REFERENCE_TIME inEnd);
	bool InsertSpace2(REFTIME inStart, REFTIME inEnd);
	bool ZeroBetween(REFERENCE_TIME inStart, REFERENCE_TIME inEnd);
	bool ZeroBetween2(REFTIME inStart, REFTIME inEnd);

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

	// --- IAMTimelineSplittable methods ---
	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);
};

#endif // __H_CDESTrack__