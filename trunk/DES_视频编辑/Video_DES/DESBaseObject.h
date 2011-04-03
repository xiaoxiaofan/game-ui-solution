#pragma once
#include "DESTimeLine.h"
#include "DESPropertySetter.h"

class CDESBaseObject
{
public:
	CDESBaseObject(CDESTimeLine * inTimeLine);
	~CDESBaseObject(void);

	bool Attach(IAMTimelineObj * inObject);
	bool Initialize(void);

	IAMTimelineObj * GetTimeLineObj(void);
	bool GetTimeLineType(TIMELINE_MAJOR_TYPE * outType);

	bool FixTimes(REFERENCE_TIME * ioStart,REFERENCE_TIME * ioStop);
	bool FixTimes2(REFTIME * ioStart,REFTIME * ioStop);

	bool SetSubObjectGUID(GUID inGuid);
	bool SetSubObjectGUIDB(BSTR inGuid);
	bool GetSubObjectGUID(GUID * outGuid);
	bool GetSubObjectGUIDB(BSTR * outGuid);

	bool SetPropertySetter(CDESPropertySetter & inProperty);
	bool GetPropertySetter(CDESPropertySetter & outProperty);

	bool SetStartStop(REFERENCE_TIME inStart,REFERENCE_TIME inStop);
	bool SetStartStop2(REFTIME inStart,REFTIME inStop);
	bool GetStartStop(REFERENCE_TIME * outStart,REFERENCE_TIME * outStop);
	bool GetStartStop2(REFTIME * outStart,REFTIME * outStop);

	bool Remove(void);
	bool RemoveAll(void);

	bool SetMuted(BOOL inMuted);
	BOOL GetMuted(void);
	bool SetLocked(BOOL inLocked);
	BOOL GetLocked(void);

	bool SetUserData(BYTE * inData,long inSize);
	bool SetUserID(long inObjectId);
	bool SetUserName(BSTR inObjectName);
	bool GetUserData(BYTE * outData,long * outSize);
	bool GetUserID(long * outObjectId);
	bool GetUserName(BSTR * outObjectName);


protected:
	CDESTimeLine * m_pTimeLine;
	IAMTimelineObj * m_pEmptyObject;

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);

};

