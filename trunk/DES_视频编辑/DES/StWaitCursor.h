//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_StWaitCursor__
#define __H_StWaitCursor__

class StWaitCursor
{
protected:
	HCURSOR		mCursor;

public:
	StWaitCursor(void);
	virtual ~StWaitCursor(void);
};

#endif // __H_StWaitCursor__