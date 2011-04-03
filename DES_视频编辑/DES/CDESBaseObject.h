//
// CDESBaseObject.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESBaseObject__
#define __H_CDESBaseObject__

#include "CDESTimeLine.h"
#include "CDESPropertySetter.h"

class CDESBaseObject
{
protected:
	CDESTimeLine *     mTimeLine;      // Owner timeline
	IAMTimelineObj *   mEmptyObject;   // Common object interface

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

public:
	CDESBaseObject(CDESTimeLine * inTimeLine);
	~CDESBaseObject();

	bool Attach(IAMTimelineObj * inObject);
	bool Initialize(void);	

	IAMTimelineObj * GetTimeLineObj(void); // NOT outstanding referencc!!
	bool GetTimelineType(TIMELINE_MAJOR_TYPE * outType);

	bool FixTimes(REFERENCE_TIME * ioStart, REFERENCE_TIME * ioStop);
	bool FixTimes2(REFTIME * ioStart, REFTIME * ioStop);

	bool SetSubObjectGUID(GUID inGuid);
	bool SetSubObjectGUIDB(BSTR inGuid);
	bool GetSubObjectGUID(GUID * outGuid);
	bool GetSubObjectGUIDB(BSTR * outGuid);

	bool SetPropertySetter(CDESPropertySetter & inSetter);
	bool GetPropertySetter(CDESPropertySetter & outSetter);

	bool SetStartStop(REFERENCE_TIME inStart, REFERENCE_TIME inStop);
	bool SetStartStop2(REFTIME inStart, REFTIME inStop);
	bool GetStartStop(REFERENCE_TIME * outStart, REFERENCE_TIME * outStop);
	bool GetStartStop2(REFTIME * outStart, REFTIME * outStop);

	bool Remove(void);    // Remove for reinsertion elsewhere immediately
	bool RemoveAll(void); // Permanently remove from the timeline

	bool SetMuted(BOOL inMuted);   // Muted object will not be rendered
	BOOL GetMuted(void);
	bool SetLocked(BOOL inLocked); // Locked object not allow editing 
	BOOL GetLocked(void);

	// Application-defined properties
	bool SetUserData(BYTE * inData, long inSize);
	bool SetUserID(long inObjectId);
	bool SetUserName(BSTR inObjectName);
	bool GetUserData(BYTE * outData, long * outSize); 
	bool GetUserID(long * outObjectId);
	bool GetUserName(BSTR * outObjectName);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);
};

#endif // __H_CDESBaseObject__