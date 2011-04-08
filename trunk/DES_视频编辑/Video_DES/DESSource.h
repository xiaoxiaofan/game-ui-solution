#ifndef DESSource_h__
#define DESSource_h__

#include "DESBaseObject.h"
#include "DESIAMTimelineSplittable.h"
#include "DESIAMTimelineEffectable.h"

class AFX_EXT_CLASS CDESSource : public CDESBaseObject
{
public:
	CDESSource(CDESTimeLine * inTimeLine);
	~CDESSource(void);

	IAMTimelineSrc * GetSourceObject(void);

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

	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

	bool EffectGetCount(long * outCount);
	bool EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority);
	bool EffectSwapPriorities(long inPriorityA, long inPriorityB);
	bool GetEffect(CDESBaseObject & outEffect, long inWhich);


protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);

private:
	IAMTimelineSrc *                   m_pInterfaceSource;
	CDESIAMTimelineSplittable          m_Splittable;
	CDESIAMTimelineEffectable          m_Effectable;

};

#endif // DESSource_h__


