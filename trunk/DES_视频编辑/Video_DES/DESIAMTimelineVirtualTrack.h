#ifndef DESIAMTimelineVirtualTrack_h__
#define DESIAMTimelineVirtualTrack_h__

#include "DESBaseInterface.h"

class AFX_EXT_CLASS CDESIAMTimelineVirtualTrack : public CDESBaseInterface
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


#endif // DESIAMTimelineVirtualTrack_h__


