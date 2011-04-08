#ifndef DESComposition_h__
#define DESComposition_h__

#include "DESBaseObject.h"
#include "DESIAMTimelineEffectable.h"
#include "DESIAMTimelineTransable.h"
#include "DESIAMTimelineVirtualTrack.h"

class AFX_EXT_CLASS CDESComposition : public CDESBaseObject
{
public:
	CDESComposition(CDESTimeLine * inTimeLine);
	~CDESComposition(void);

	bool GetNextVTrack(CDESBaseObject * inVTrack, CDESBaseObject & outNextVTrack);
	bool GetRecursiveLayerOfType(CDESBaseObject & outVTrack, long inLayerIndex, TIMELINE_MAJOR_TYPE inType);
	bool VTrackGetCount(long * outCount);
	bool GetVTrack(CDESBaseObject & outVTrack, long inPriority);
	bool VTrackInsBefore(CDESBaseObject & inVTrack, long inPriority);
	bool VTrackSwapPriorities(long inVTrackA, long inVTrackB);
	bool GetCountOfType(long * outVal, long * outValWithComps, TIMELINE_MAJOR_TYPE inType);

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

protected:
	IAMTimelineComp *				m_pInterfaceComp;
	CDESIAMTimelineTransable		m_Transable;
	CDESIAMTimelineEffectable		m_Effectable;
	CDESIAMTimelineVirtualTrack		m_VirtualTrack;

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);

};

#endif // DESComposition_h__


