//
// CDESIAMTimelineSplittable.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESIAMTimelineSplittable__
#define __H_CDESIAMTimelineSplittable__

#include "CDESBaseInterface.h"

class CDESIAMTimelineSplittable : public CDESBaseInterface
{
private:
	IAMTimelineSplittable *   mSplittable;

public:
	CDESIAMTimelineSplittable();
	~CDESIAMTimelineSplittable();

	virtual bool QueryInterfaceSelf(void);
	virtual void ReleaseInterface(void);

	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

private:
	void ReleaseSelf(void);
};

#endif // __H_CDESIAMTimelineSplittable__