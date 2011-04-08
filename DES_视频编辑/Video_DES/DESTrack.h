#ifndef DESTrack_h__
#define DESTrack_h__

#include "DESBaseObject.h"
#include "DESIAMTimelineEffectable.h"
#include "DESIAMTimelineSplittable.h"
#include "DESIAMTimelineTransable.h"
#include "DESIAMTimelineVirtualTrack.h"

class AFX_EXT_CLASS CDESTrack : public CDESBaseObject
{
public:
	CDESTrack(CDESTimeLine * inTimeLine);
	~CDESTrack(void);

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

	bool EffectGetCount(long * outCount);
	bool EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority);
	bool EffectSwapPriorities(long inPriorityA, long inPriorityB);
	bool GetEffect(CDESBaseObject & outEffect, long inWhich);

	bool TransGetCount(long * outCount);
	bool TransAdd(CDESBaseObject & inTransition);
	bool GetNextTrans(CDESBaseObject & outTransition, REFERENCE_TIME * ioStartStop);
	bool GetNextTrans2(CDESBaseObject & outTransition, REFTIME * ioStartStop);
	bool GetTransAtTime(CDESBaseObject & outTransition, REFERENCE_TIME inTime, long inSearchDirection);
	bool GetTransAtTime2(CDESBaseObject & outTransition, REFTIME inTime, long inSearchDirection);


	bool TrackGetPriority(long * outPriority); 

	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);

private:
	IAMTimelineTrack *				m_pInterfaceTrack;
	CDESIAMTimelineEffectable		m_Effectable;
	CDESIAMTimelineSplittable		m_Splittable;
	CDESIAMTimelineTransable		m_Transable;
	CDESIAMTimelineVirtualTrack		m_VirtualTrack;

};

#endif // DESTrack_h__
