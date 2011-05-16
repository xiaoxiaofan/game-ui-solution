/*
 *  Copyright (C) Massimo Cora' 2005 <maxcvs@email.it>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */


#ifndef _OSTREAMONDEMANDSMS_H_
#define _OSTREAMONDEMANDSMS_H_

#include <liveMedia.hh>
#include <BasicUsageEnvironment.hh>
#include <GroupsockHelper.hh>
#include <OnDemandServerMediaSubsession.hh>


#include "HardwareSingleVideoSource.hh"
#include "H263plusVideoSource.hh"


/**
 * On Demand Server Media Subsession.
 * It gives sink and source classes when requested by the streams.
 * Derives OnDemandServerMediaSubsession of LiveMedia.
 */
class OStreamOnDemandSMS : public OnDemandServerMediaSubsession
{
public:
	/**
 	 * Static method.
	 * @param env UsageEnvironment, see LiveMedia doc. here
	 *        http://www.live555.com/liveMedia/public/doxygen/html
	 * @param reuseFirstSource Should the class reuse the source when finished another one?
	 * @param input_video A BaseInputVideo class, can be a MultiVideoSource or a 
	 *        SingleVideoSource kind of class.
	 * @param encoding_type A wrapper enum to use OStream encoding parameters.
	 * @param audio_port Audio port mapped from the system. It is used only if 
	 *        input_video is NULL, and viceversa
	 * @param stream_id Stream id. Defaults to 0.
	 */
  	static OStreamOnDemandSMS *
	createNew( UsageEnvironment& env, bool reuseFirstSource, BaseInputVideo *input_video,
			   int encoding_type, int audio_port, int stream_id = 0 );

	virtual ~OStreamOnDemandSMS();
protected:


private:	// functions
	/**
	 * Contructor.
	 * @see createNew
	 */
	OStreamOnDemandSMS( UsageEnvironment& env, bool reuseFirstSource, BaseInputVideo *input_video,  
					    int audio_port, int encoding_type, int stream_id );

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

private:	// data
	/** BaseInputVideo instance */
	BaseInputVideo *_input_video;
	
	/** 
	 * Encoding type.
	 * @see ostream_encoding_type
	 */	
	int _encoding_type;
	
	/** Stream id. */
	int _stream_id;
	
	/** Audio port mapped by the system. */
	int _audio_port;
};


#endif	//_OSTREAMONDEMANDSMS_H_

