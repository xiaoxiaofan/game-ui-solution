#pragma once
#include "CDESBaseInterface.h"

class CDESBaseObject;

class CDESIAMTimelineEffectable : public CDESBaseInterface
{
public:
	CDESIAMTimelineEffectable(void);
	~CDESIAMTimelineEffectable(void);

	virtual bool QueryInterfaceSelf(void);
	virtual bool ReleaseInterface(void);

	bool EffectGetCount(long * outCount);
	bool EffectInsBefore(CDESBaseObject & inEffectObject, long inPriority);
	bool EffectSwapPriorities(long inPriorityA, long inPriorityB);
	bool GetEffect(CDESBaseObject & outEffect, long inWhich);

protected:

private:
	void ReleaseSelf();

private:
	IAMTimelineEffectable * m_pEffectable;

};

