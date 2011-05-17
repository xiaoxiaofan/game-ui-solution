#include "LiveStreamOnDemandSMS.h"
#include "UnKnowLiveSource.h"
#include "UnKonwLiveRTPSink.h"

LiveStreamOnDemandSMS::LiveStreamOnDemandSMS( UsageEnvironment& env, bool reuseFirstSource ,int stream_id )
	: OnDemandServerMediaSubsession(env,reuseFirstSource)
{

}

LiveStreamOnDemandSMS::~LiveStreamOnDemandSMS( void )
{

}

FramedSource* LiveStreamOnDemandSMS::createNewStreamSource( unsigned clientSessionId, unsigned& estBitrate )
{
	return new UnKnowLiveSource(envir());
}

RTPSink* LiveStreamOnDemandSMS::createNewRTPSink( Groupsock* rtpGroupsock, unsigned char rtpPayloadTypeIfDynamic, FramedSource* inputSource )
{
	return new UnKonwLiveRTPSink(envir(),rtpGroupsock,98,9000);
}
