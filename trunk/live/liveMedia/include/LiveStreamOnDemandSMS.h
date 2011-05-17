#pragma once
#include "OnDemandServerMediaSubsession.hh"
#include "UsageEnvironment.hh"
#include "Groupsock.hh"
#include "FramedSource.hh"
#include "RTPSink.hh"

class LiveStreamOnDemandSMS : public OnDemandServerMediaSubsession
{
public:
	LiveStreamOnDemandSMS(UsageEnvironment& env, bool reuseFirstSource ,int stream_id);
	~LiveStreamOnDemandSMS(void);

private:
	Groupsock *rtpGroupsock;



	/**
	 * Creates a new stream source.
	 * @param clientSessionId
	 * @param estBitrate It's the stream's estimated bitrate, in kbps.
	 * @return A FramedSource instance. See liveMedia doc for this. 
	 * @see http://www.live555.com/liveMedia/public/doxygen/html
	 */
	virtual FramedSource* createNewStreamSource( unsigned clientSessionId,
							unsigned& estBitrate );

	/**
	 * Creates a new RTP sink.
	 * @param rtpGroupsock 
	 * @param rtpPayloadTypeIfDynamic
	 * @param inputSource
	 * @return A new RTPSink instance.
	 * @see http://www.live555.com/liveMedia/public/doxygen/html
	 */
	virtual RTPSink* createNewRTPSink( Groupsock* rtpGroupsock,
				    unsigned char rtpPayloadTypeIfDynamic,
				    FramedSource* inputSource );
};

