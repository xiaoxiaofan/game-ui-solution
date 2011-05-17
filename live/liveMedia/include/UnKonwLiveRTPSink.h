#pragma once
#include "VideoRTPSink.hh"
#include "UsageEnvironment.hh"
#include "Groupsock.hh"
class UnKonwLiveRTPSink : public VideoRTPSink
{
public:
	UnKonwLiveRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
		unsigned char rtpPayloadFormat,
		u_int32_t rtpTimestampFrequency);
	~UnKonwLiveRTPSink(void);
};

