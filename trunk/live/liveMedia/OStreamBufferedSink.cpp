/*
 *  Copyright (C) Massimo Cora' 2006 <maxcvs@gmail.com>
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


#include "OStreamBufferedSink.hh"

#include <GroupsockHelper.hh>

OStreamBufferedSink::OStreamBufferedSink( UsageEnvironment& env, 
										  on_packet_video_received_cb* fv, 
										  const void *vid_callback_data,
										  on_packet_audio_received_cb* fa, 
										  const void *aud_callback_data,
										  const char* subsession_codec,
										  int stream_id,
										  const char* receiving_iface,
										  unsigned int buffer_size )
								: MediaSink( env ),
								f_on_packet_video_received_cb( fv ),
								_callback_video_data_packet_receiver( vid_callback_data ),
								f_on_packet_audio_received_cb( fa ),
								_callback_audio_data_packet_receiver( aud_callback_data ),
								_stream_id( stream_id ),
								_packet_buffer_size( buffer_size )
{

	// set up the global variable
	ReceivingInterfaceAddr = our_inet_addr( receiving_iface );

	_packet_buffer = new unsigned char[_packet_buffer_size];	
	memset( _packet_buffer, 0, _packet_buffer_size );

	_subsession_codec_str = strdup( subsession_codec );
		_video_decoder = NULL;
	// we will fill with this function the 
	if ( parse_codec_str () == false ) {
//		DEBUG_PRINT("WARNING: Codec not recognized.\n");
		return;
	}

	switch ( _subsession_codec_id ) {
		case OSTREAM_DECODING_H263P:
		case OSTREAM_DECODING_MJPEG:

			// FIXME: the PIX_FMT_RGB24 is an hack here. It's done to have an RGB
			// iplimage decoded, instead of a BGR. This will avoid a conversion
			// BGR -> RGB once we want to display the result image with wxImage.

			// NOTE: *IMPORTANT* the video format width and height will be automatically
			// detected by the decoder, so there's no need to specify them here.
			// Libavcodec will take them for us.
			_video_decoder = new OStreamVideoDecoder( 1000000, _subsession_codec_id,
														25, PIX_FMT_RGB24 );
			break;

		case OSTREAM_DECODING_MP3:
			// TODO: we will not use a decoder for mp3 packets, coz we'll give them entirely
			// to the callback function, which will provide playback support and buffer management.
			break;
	}	
}


OStreamBufferedSink* OStreamBufferedSink::createNew( UsageEnvironment& env, 
			on_packet_video_received_cb* fv, const void *vid_callback_data,
			on_packet_audio_received_cb* fa, const void *aud_callback_data,
			const char* subsession_codec, int stream_id, const char* receiving_iface, 
			unsigned int buffer_size )
{
	return new OStreamBufferedSink( env, fv, vid_callback_data, fa, aud_callback_data, subsession_codec, 
								    stream_id, receiving_iface, buffer_size );
}


OStreamBufferedSink::~OStreamBufferedSink()
{
	if ( _packet_buffer != NULL ) {
		delete[] _packet_buffer;
		_packet_buffer = NULL;
	}

	if ( _subsession_codec_str )
		free( _subsession_codec_str );

	if ( _video_decoder )
		delete _video_decoder;
}


Boolean OStreamBufferedSink::continuePlaying() 
{
	if (fSource == NULL) 
		return False;

	fSource->getNextFrame( _packet_buffer, _packet_buffer_size, 
							afterGettingFrame, this,
							onSourceClosure, this);	

	return True;
}



//-------------------------------------------------------------------------
// perform actions after getting a frame

void OStreamBufferedSink::afterGettingFrame( void* clientData, unsigned frameSize,
										unsigned /*numTruncatedBytes*/,
				 						struct timeval presentationTime,
				 						unsigned /*durationInMicroseconds*/) 
{
	OStreamBufferedSink* sink = (OStreamBufferedSink*)clientData;
	
	sink->_frameSize = frameSize;
	sink->_presentationTime = presentationTime;

	//sink->afterGettingFrame1();
} 

//-------------------------------------------------------------------------
//

void OStreamBufferedSink::afterGettingFrame1() 
{

	/*	IplImage *decoded_image = NULL;
		if ( f_on_packet_video_received_cb( decoded_image, _stream_id, 
					_callback_video_data_packet_receiver ) == false ) {
					return;
		}
	*/
	// Then try getting the next frame
	//continuePlaying();
}


//-----------------------------------------------------------------------------
// to know which codecs are supported by liveMedia, jusr give 
// grep -R fCodecName * 
// inside liveMedia directory. 

bool OStreamBufferedSink::parse_codec_str()
{
	
	if ( _subsession_codec_str == NULL )
		return false;
	
	if ( strcmp( _subsession_codec_str, "H263-1998" ) == 0 ) {
		_subsession_codec_id = OSTREAM_DECODING_H263P;
	}
	else if ( strcmp( _subsession_codec_str, "H263-2000" ) == 0 ) {
		_subsession_codec_id = OSTREAM_DECODING_H263P;
	}
	else if ( strcmp( _subsession_codec_str, "JPEG" ) == 0 ) {
		_subsession_codec_id = OSTREAM_DECODING_MJPEG;
	}
	else if ( strcmp( _subsession_codec_str, "MPA-ROBUST" ) == 0 ) {
		_subsession_codec_id = OSTREAM_DECODING_MP3;
	}
	else if ( strcmp( _subsession_codec_str, "MPA" ) == 0 ) {
		_subsession_codec_id = OSTREAM_DECODING_MP3;
	}
	
	return true;

}




