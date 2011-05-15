#include "LiveStreamOnDemandSMS.h"
#include "UnKnowLiveRTPSink.h"
#include "UnKnowLiveSource.h"

LiveStreamOnDemandSMS::LiveStreamOnDemandSMS( UsageEnvironment& env, bool reuseFirstSource ,int stream_id )
	: OnDemandServerMediaSubsession(env,reuseFirstSource)
	, _stream_id(stream_id)
{

}

LiveStreamOnDemandSMS::~LiveStreamOnDemandSMS( void )
{

}

FramedSource* LiveStreamOnDemandSMS::createNewStreamSource( unsigned clientSessionId, unsigned& estBitrate )
{
	return new UnKnowLiveSource(envir(),_stream_id);
}

RTPSink* LiveStreamOnDemandSMS::createNewRTPSink( Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource )
{
	return new UnKnowLiveRTPSink(envir(),rtpGroupsock,98);
}
