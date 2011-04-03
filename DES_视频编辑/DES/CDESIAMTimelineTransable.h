//
// CDESIAMTimelineTransable.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESIAMTimelineTransable__
#define __H_CDESIAMTimelineTransable__

#include "CDESBaseInterface.h"

class CDESBaseObject;
class CDESIAMTimelineTransable : public CDESBaseInterface
{
private:
	IAMTimelineTransable *   mTransable;

public:
	CDESIAMTimelineTransable();
	~CDESIAMTimelineTransable();

	virtual bool QueryInterfaceSelf(void);
	virtual void ReleaseInterface(void);

	bool TransGetCount(long * outCount);
	bool TransAdd(CDESBaseObject & inTransition);
	bool GetNextTrans(CDESBaseObject & outTransition, REFERENCE_TIME * ioStartStop);
	bool GetNextTrans2(CDESBaseObject & outTransition, REFTIME * ioStartStop);

	bool GetTransAtTime(CDESBaseObject & outTransition, 
		REFERENCE_TIME inTime, long inSearchDirection);
	bool GetTransAtTime2(CDESBaseObject & outTransition, 
		REFTIME inTime, long inSearchDirection);
	
private:
	void ReleaseSelf(void);
};

#endif // __H_CDESIAMTimelineTransable__