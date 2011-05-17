#pragma once
#include "AVCapture.h"
#include "AVRecord.h"


class CCamerCapture  
	:public CAVCapture
{
public:
	CCamerCapture(IMXEC_CapChanCallback& capChanHandle);
	~CCamerCapture(void);

	int OpenVideo(PLBVideoSet videoSet);

	virtual bool StartRecord(void);
	virtual void StopRecord(void);
	virtual bool IsRecording(void);

private:
	PLBVideoSet                      m_pVideoSet;
};

