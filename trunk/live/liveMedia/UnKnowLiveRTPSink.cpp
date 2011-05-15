#include "UnKnowLiveRTPSink.h"


UnKnowLiveRTPSink::UnKnowLiveRTPSink(UsageEnvironment& env, Groupsock* RTPgs,
	unsigned char rtpPayloadFormat,
	unsigned rtpTimestampFrequency)
	: VideoRTPSink(env,RTPgs,rtpPayloadFormat,rtpTimestampFrequency,"")
{
}


UnKnowLiveRTPSink::~UnKnowLiveRTPSink(void)
{

}
