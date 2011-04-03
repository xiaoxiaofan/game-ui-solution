//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#include "stdafx.h"
#include "StWaitCursor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

StWaitCursor::StWaitCursor(void)
{
	mCursor = ::SetCursor(LoadCursor(NULL, IDC_WAIT));
}

StWaitCursor::~StWaitCursor(void)
{
	::SetCursor(mCursor);
}