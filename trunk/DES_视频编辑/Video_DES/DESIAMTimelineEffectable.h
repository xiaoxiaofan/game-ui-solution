#ifndef DESIAMTimelineEffectable_h__
#define DESIAMTimelineEffectable_h__

#include "DESBaseInterface.h"

class CDESBaseObject;

class AFX_EXT_CLASS CDESIAMTimelineEffectable : public CDESBaseInterface
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

#endif // DESIAMTimelineEffectable_h__


