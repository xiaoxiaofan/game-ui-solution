#ifndef UnKnowLiveRTPSink_h__
#define UnKnowLiveRTPSink_h__
#include "UsageEnvironment.hh"
#include "Groupsock.hh"
#include "VideoRTPSink.hh"

class UnKnowLiveRTPSink : public VideoRTPSink
{
public:
	UnKnowLiveRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		unsigned rtpTimestampFrequency = 90000);
	~UnKnowLiveRTPSink(void);
};

#endif // UnKnowLiveRTPSink_h__


