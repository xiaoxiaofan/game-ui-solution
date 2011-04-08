#ifndef DESTimeLine_h__
#define DESTimeLine_h__

#include <qedit.h>

class CDESBaseObject;

class AFX_EXT_CLASS CDESTimeLine
{
private:
	IAMTimeline * m_pTimeLine;

public:
	CDESTimeLine(void);
	~CDESTimeLine(void);

	IAMTimeline * GetTimeLine(void);
	bool Attach(IAMTimeline * inTimeLine);
	bool Initialize(void);

	//
	bool AddGroup(CDESBaseObject * inGroup);
	bool GetGroup(CDESBaseObject & outGroup, long inGroupIndex);
	bool ClearAllGroup(void);
	long GetGroupCount(void);

	//
	BOOL EffectsEnabled(void);
	bool EnableEffects(BOOL inEnabled);
	bool SetDefaultEffect(GUID * inGuid);
	bool SetDefaultEffectB(BSTR inGuid);
	bool GetDefaultEffect(GUID * outGuid);
	bool GetDefaultEffectB(BSTR * outGuid);

	//
	BOOL TransitionsEnabled(void);
	bool EnableTransitions(BOOL inEnabled);
	bool SetDefaultTransition(GUID * inGuid);
	bool SetDefaultTransitionB(BSTR inGuid);
	bool GetDefaultTransition(GUID * outGuid);
	bool GetDefaultTransitionB(BSTR * outGuid);

	bool SetDefaultFPS(double inFPS);
	bool GetDefaultFPS(double * outFPS);
	bool GetDuration(REFERENCE_TIME * outDuration);
	bool GetDuration2(double * outDuration);
	bool ValidateSourceNames(long inNotifyEventHandle = 0 );

	bool CreateEmptyNode(IAMTimelineObj **outObject, TIMELINE_MAJOR_TYPE inType);
	bool GetCountOfType(long inGroupIndex, long * outVal, long * outValWithComps, TIMELINE_MAJOR_TYPE inType);

private:
	void ReleaseSelf(void);
};

#endif // DESTimeLine_h__

