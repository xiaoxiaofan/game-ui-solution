//
// CDESEffect.h
// 
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESEffect__
#define __H_CDESEffect__

#include "CDESBaseObject.h"
#include "CDESIAMTimelineSplittable.h"

class CDESEffect : public CDESBaseObject
{
private:
	IAMTimelineEffect *          mInterfaceEffect;
	CDESIAMTimelineSplittable    mSplittable;  // Other interfaces

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

public:
	CDESEffect(CDESTimeLine * inTimeLine);
	~CDESEffect();

	bool EffectGetPriority(long * outPriority);

	// --- IAMTimelineSplittable methods ---
	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);
};

#endif // __H_CDESEffect__