#ifndef DESEffect_h__
#define DESEffect_h__

#include "DESBaseObject.h"
#include "DESIAMTimelineSplittable.h"

class AFX_EXT_CLASS CDESEffect : public CDESBaseObject
{
public:
	CDESEffect(CDESTimeLine * inTimeLine);
	~CDESEffect(void);

	bool EffectGetPriority(long * outPriority);

	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);

private:
	IAMTimelineEffect *				m_InterfaceEffect;
	CDESIAMTimelineSplittable		m_Splittable;

};

#endif // DESEffect_h__


