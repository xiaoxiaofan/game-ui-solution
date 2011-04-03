//
// CDESBaseInterface.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESBaseInterface__
#define __H_CDESBaseInterface__

class CDESBaseInterface
{
protected:
	IAMTimelineObj *   mOwnerObject;

public:
	CDESBaseInterface();
	~CDESBaseInterface();

	bool SetOwner(IAMTimelineObj * inOwner);  // Keep a reference count
	IAMTimelineObj * GetOwner(void);          // NOT outstanding referencc!!

	virtual bool QueryInterfaceSelf(void) = 0;
	virtual void ReleaseInterface(void) = 0;

private:
	void ReleaseSelf(void);
};

#endif // __H_CDESBaseInterface__