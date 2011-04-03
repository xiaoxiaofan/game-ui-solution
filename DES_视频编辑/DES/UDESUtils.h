//
// UDESUtils.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_UDESUtils__
#define __H_UDESUtils__

#include <afxtempl.h>
#include "CDESGuid.h"

typedef CList<CDESGuid, CDESGuid&>  CTypeGuidList;

class UDESUtils
{
private:
	// Internet Explorer 5.5 or later
	// C:\WINNT\system32\dxtmsft.dll
	static WCHAR  sMsEffectProgIDs[][100];
	static WCHAR  sMsTransitionProgIDs[][100];

public:
	static CTypeGuidList  sEffectList;
	static CTypeGuidList  sTransitionList;

public:
	static bool QueryLocalAvailableEffects(void);
	static bool QueryLocalAvailableTransitions(void);

	static bool IsMsEffect(GUID * inEffectGuid);
	static bool IsMsTransition(GUID * inTransGuid);

private:
	static bool QueryLocalGuids(CLSID inCategory, CTypeGuidList & inList);
};

#endif // __H_UDESUtils__