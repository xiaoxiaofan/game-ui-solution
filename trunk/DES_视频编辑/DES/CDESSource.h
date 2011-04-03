//
// CDESSource.h
// 
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESSource__
#define __H_CDESSource__

#include "CDESBaseObject.h"
#include "CDESIAMTimelineSplittable.h"
#include "CDESIAMTimelineEffectable.h"

class CDESSource : public CDESBaseObject
{
private:
	IAMTimelineSrc *             mInterfaceSource;
	CDESIAMTimelineSplittable    mSplittable;  // Other interfaces
	CDESIAMTimelineEffectable    mEffectable;

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

public:
	CDESSource(CDESTimeLine * inTimeLine);
	~CDESSource();

	IAMTimelineSrc * GetSourceObject(void); // NOT outstanding referencc!!

	bool SetMediaName(const char * inFilePath);
	bool GetMediaName(char * outFilePath);
	bool SetMediaTimes(REFERENCE_TIME inStart, REFERENCE_TIME inStop);
	bool GetMediaTimes(REFERENCE_TIME * outStart, REFERENCE_TIME * outStop);
	bool SetMediaTimes2(REFTIME inStart, REFTIME inStop);
	bool GetMediaTimes2(REFTIME * outStart, REFTIME * outStop);
	bool FixMediaTimes(REFERENCE_TIME * ioStart, REFERENCE_TIME * ioStop);
	bool FixMediaTimes2(REFTIME * ioStart, REFTIME * ioStop);
	bool SetMediaLength(REFERENCE_TIME inLength);
	bool GetMediaLength(REFERENCE_TIME * outLength);
	bool SetMediaLength2(REFTIME inLength);
	bool GetMediaLength2(REFTIME * outLength);
	bool ModifyStopTime(REFERENCE_TIME inStop);
	bool ModifyStopTime2(REFTIME inStop);
	bool SetDefaultFPS(double inFPS);
	bool GetDefaultFPS(double * outFPS);
	bool SetStreamNumber(long inIndex);
	bool GetStreamNumber(long * outIndex);
	bool SetStretchMode(int inStretchMode);
	bool GetStretchMode(int * outStretchMode);
	bool IsNormalRate(BOOL * outIsNormal);
	bool SpliceWithNext(CDESBaseObject & inNextSource);

	// --- IAMTimelineSplittable methods ---
	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

	// --- IAMTimelineEffectable methods ---
	bool EffectGetCount(long * outCount);
	bool EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority);
	bool EffectSwapPriorities(long inPriorityA, long inPriorityB);
	bool GetEffect(CDESBaseObject & outEffect, long inWhich);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);
};

#endif // __H_CDESSource__