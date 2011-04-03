//
// CDESTransition.h
// 
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESTransition__
#define __H_CDESTransition__

#include "CDESBaseObject.h"
#include "CDESIAMTimelineSplittable.h"

class CDESTransition : public CDESBaseObject
{
private:
	IAMTimelineTrans *           mInterfaceTrans;
	CDESIAMTimelineSplittable    mSplittable;  // Other interfaces

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

public:
	CDESTransition(CDESTimeLine * inTimeLine);
	~CDESTransition();

	bool SetCutPoint(REFERENCE_TIME inTLTime);
	bool GetCutPoint(REFERENCE_TIME * outTLTime);
	bool SetCutPoint2(REFTIME inTLTime);
	bool GetCutPoint2(REFTIME * outTLTime);
	bool SetCutsOnly(BOOL inIsCut);
	bool GetCutsOnly(BOOL * outIsCut);
	bool SetSwapInputs(BOOL inIsSwap);
	bool GetSwapInputs(BOOL * outIsSwap);

	// --- IAMTimelineSplittable methods ---
	bool SplitAt(REFERENCE_TIME inTime);
	bool SplitAt2(REFTIME inTime);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);
};

#endif // __H_CDESTransition__