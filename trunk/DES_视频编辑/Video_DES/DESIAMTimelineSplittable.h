#ifndef DESIAMTimelineSplittable_h__
#define DESIAMTimelineSplittable_h__

#include "DESBaseInterface.h"

class AFX_EXT_CLASS CDESIAMTimelineSplittable : public CDESBaseInterface
{
public:
	CDESIAMTimelineSplittable(void);
	~CDESIAMTimelineSplittable(void);

	virtual bool QueryInterfaceSelf(void);
	virtual bool ReleaseInterface(void);

	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

protected:

private:
	void ReleaseSelf(void);

private:
	IAMTimelineSplittable * m_pSplittable;

};

#endif // DESIAMTimelineSplittable_h__


