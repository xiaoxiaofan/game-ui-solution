#ifndef DESTransition_h__
#define DESTransition_h__

#include "DESBaseObject.h"
#include "DESIAMTimelineSplittable.h"

class AFX_EXT_CLASS CDESTransition : public CDESBaseObject
{
public:
	CDESTransition(CDESTimeLine * inTimeLine);
	~CDESTransition(void);

	bool SetCutPoint(REFERENCE_TIME inTLTime);
	bool GetCutPoint(REFERENCE_TIME * outTLTime);
	bool SetCutPoint2(REFTIME inTLTime);
	bool GetCutPoint2(REFTIME * outTLTime);
	bool SetCutsOnly(BOOL inIsCut);
	bool GetCutsOnly(BOOL * outIsCut);
	bool SetSwapInputs(BOOL inIsSwap);
	bool GetSwapInputs(BOOL * outIsSwap);

	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);

private:
	IAMTimelineTrans *				m_pInterfaceTrans;
	CDESIAMTimelineSplittable		m_Splittable;

};

#endif // DESTransition_h__
