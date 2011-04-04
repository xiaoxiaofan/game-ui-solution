#pragma once

#include "CDESBaseInterface.h"

class CDESIAMTimelineVirtualTrack : public CDESBaseInterface
{
public:
	CDESIAMTimelineVirtualTrack(void);
	~CDESIAMTimelineVirtualTrack(void);

	virtual bool QueryInterfaceSelf(void);
	virtual void ReleaseInterface(void);

	bool TrackGetPriority(long * outPriority);

protected:

private:
	void ReleaseSelf(void);

private:
	IAMTimelineVirtualTrack * m_pVirtualTrack;

};

