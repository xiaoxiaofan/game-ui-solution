//
// CDESGuid.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESGuid__
#define __H_CDESGuid__

class CDESGuid
{
public:
	CString     mFriendlyName;
	GUID        mGuid;

public:
	CDESGuid();
	~CDESGuid();
};

#endif // __H_CDESGuid__