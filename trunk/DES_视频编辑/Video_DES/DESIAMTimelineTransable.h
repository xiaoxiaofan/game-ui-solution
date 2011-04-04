#pragma once

#include "CDESBaseInterface.h"

class CDESBaseObject;

class CDESIAMTimelineTransable : public CDESBaseInterface
{
public:
	CDESIAMTimelineTransable(void);
	~CDESIAMTimelineTransable(void);

	virtual bool QueryInterfaceSelf(void);
	virtual void ReleaseInterface(void);

	bool TransGetCount(long * outCount);
	bool TransAdd(CDESBaseObject & inTransition);
	bool GetNextTrans(CDESBaseObject & outTransition, REFERENCE_TIME * ioStartStop);
	bool GetNextTrans2(CDESBaseObject & outTransition, REFTIME * ioStartStop);

	bool GetTransAtTime(CDESBaseObject & outTransition, REFERENCE_TIME inTime, long inSearchDirection);
	bool GetTransAtTime2(CDESBaseObject & outTransition, REFTIME inTime, long inSearchDirection);


protected:

private:
	void ReleaseSelf(void);

private:
	IAMTimelineTransable * m_pTransable;

};

