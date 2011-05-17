#include "UnKonwLiveRTPSink.h"


UnKonwLiveRTPSink::UnKonwLiveRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
	unsigned char rtpPayloadFormat,
	u_int32_t rtpTimestampFrequency)
	: VideoRTPSink(env,RTPgs,rtpPayloadFormat,rtpTimestampFrequency,"H263P")
{
}


UnKonwLiveRTPSink::~UnKonwLiveRTPSink(void)
{
}
