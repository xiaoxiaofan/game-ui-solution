//
// CDESTimeLine.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESTimeLine__
#define __H_CDESTimeLine__

#include <qedit.h>

class CDESBaseObject;
class CDESTimeLine
{
private:
	IAMTimeline *     mTimeLine;

public:
	CDESTimeLine();
	~CDESTimeLine();

	IAMTimeline * GetTimeLine(void); // NOT outstanding referencc!!
	bool Attach(IAMTimeline * inTimeLine);
	bool Initialize(void);  // Must be invoked!!

	// Group operations
	bool AddGroup(CDESBaseObject * inGroup);
	bool GetGroup(CDESBaseObject & outGroup, long inGroupIndex);
	bool ClearAllGroups(void);
	long GetGroupCount(void);

	// Effects
	BOOL EffectsEnabled(void);
	bool EnableEffects(BOOL inEnabled);
	bool SetDefaultEffect(GUID * inGuid);
	bool SetDefaultEffectB(BSTR inGuid);
	bool GetDefaultEffect(GUID * outGuid);
	bool GetDefaultEffectB(BSTR * outGuid);

	// Transitions
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
	bool ValidateSourceNames(long inNotifyEventHandle = 0);

	// Utilities for internal timeline object construction
public:
	bool CreateEmptyNode(IAMTimelineObj **outObject, TIMELINE_MAJOR_TYPE inType);
	bool GetCountOfType(long inGroupIndex, long * outVal, 
		long * outValWithComps, TIMELINE_MAJOR_TYPE inType);

private:
	void ReleaseSelf(void);
};

#endif // __H_CDESTimeLine__