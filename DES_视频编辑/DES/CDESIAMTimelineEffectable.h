//
// CDESIAMTimelineEffectable.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESIAMTimelineEffectable__
#define __H_CDESIAMTimelineEffectable__

#include "CDESBaseInterface.h"

class CDESBaseObject;
class CDESIAMTimelineEffectable : public CDESBaseInterface
{
private:
	IAMTimelineEffectable *   mEffectable;

public:
	CDESIAMTimelineEffectable();
	~CDESIAMTimelineEffectable();

	virtual bool QueryInterfaceSelf(void);
	virtual void ReleaseInterface(void);

	bool EffectGetCount(long * outCount);
	bool EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority);
	bool EffectSwapPriorities(long inPriorityA, long inPriorityB);
	bool GetEffect(CDESBaseObject & outEffect, long inWhich);

private:
	void ReleaseSelf(void);
};

#endif // __H_CDESIAMTimelineEffectable__