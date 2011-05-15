/*
*  Copyright (C) Massimo Cora' 2006 <maxcvs@email.it>
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


#include "OStreamOnDemandSMS.hh"
#include "RTCP.hh"
#include "BasicUDPSink.hh"
#include <GroupsockHelper.hh>


OStreamOnDemandSMS::OStreamOnDemandSMS( UsageEnvironment& env, bool reuseFirstSource, 
									   BaseInputVideo *input_video,
									   int encoding_type,
									   int audio_port,
									   int stream_id ) 
									   : OnDemandServerMediaSubsession( env, reuseFirstSource ),
									   _encoding_type( encoding_type ),
									   _input_video( input_video ),
									   _stream_id( stream_id ),
									   _audio_port( audio_port )
{


}

OStreamOnDemandSMS *
OStreamOnDemandSMS::createNew( UsageEnvironment& env, bool reuseFirstSource, BaseInputVideo *input_video,
							  int audio_port, int encoding_type, int stream_id /* = 0 */ ) 
{
	return new OStreamOnDemandSMS( env, reuseFirstSource, input_video, audio_port, encoding_type, stream_id );
}

OStreamOnDemandSMS::~OStreamOnDemandSMS()
{
	//	DEBUG_PRINT ("deletion!!!!!! OStreamOnDemandSMS::~OStreamOnDemandSMS()");
	// WARNING !
	// _rtp_sink_inst and _video_source_inst will be responsible of their destroying
}

FramedSource* OStreamOnDemandSMS::createNewStreamSource( unsigned clientSessionId,
														unsigned& estBitrate ) 
{
	
	FramedSource *framed_source;
	estBitrate = 64; // kbps, estimate
	switch ( _encoding_type ) {
		case OSTREAM_ENCODING_H263P:
			framed_source = H263plusVideoSource::createNew( envir(), _input_video, _stream_id,15 );
			break;
		case OSTREAM_ENCODING_MJPEG:
			{
				char const* sessionAddressStr = "0.0.0.0";
				const unsigned short rtpPortNum = _audio_port+3;
				struct in_addr sessionAddress;
				sessionAddress.s_addr = our_inet_addr(sessionAddressStr);
			    Port rtpPort(rtpPortNum);

				rtpGroupsock = new Groupsock(envir(), sessionAddress, rtpPort, 1);
				framed_source = H263plusVideoRTPSource::createNew( envir(), rtpGroupsock, 98,this->_audio_port);
			}
			break;
		default:
			framed_source = NULL;
			break;
	}

	return framed_source;
}


//--------------------------------------------------------------------------
//

RTPSink* OStreamOnDemandSMS::createNewRTPSink(Groupsock* rtpGroupsock,
											  unsigned char rtpPayloadTypeIfDynamic,
											  FramedSource* inputSource) 
{
	 	

	
	RTPSink* rtp_sink;
	// ugly but we need rtpGroupsock, which we cannot have outsite OStreamOnDemandSMS
	switch ( _encoding_type ) {
		case OSTREAM_ENCODING_H263P:
			rtp_sink = H263plusVideoRTPSink::createNew( envir(), rtpGroupsock, 98 );
			break;
		case OSTREAM_ENCODING_MJPEG:
			rtp_sink = H263plusVideoRTPSink::createNew( envir(), rtpGroupsock, 98 );
			break;
		default:
			rtp_sink = NULL;
			break;
	}


	return rtp_sink;
}







