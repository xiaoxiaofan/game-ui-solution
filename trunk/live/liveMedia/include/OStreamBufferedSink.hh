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


#ifndef _OSTREAMBUFFEREDSINK_H_
#define _OSTREAMBUFFEREDSINK_H_

#include <liveMedia.hh>
#include <MediaSink.hh>

// opencv
#include <cv.h>
#include <highgui.h>

#include "OStreamVideoDecoder.hh"

/**
 * @typedef on_packet_video_received_cb Callback function to which the IplImage(s)
 *          will be derivered to.
 * @param image IplImage. The video packet is converted to an IplImage.
 * @param stream_id Stream id.
 * @param client_data Callback data.
 * @return true on success, false on insuccess.
 */
typedef bool (on_packet_video_received_cb)( IplImage* image, int stream_id, const void* client_data );

/**
 * @typedef on_packet_audio_received_cb Callback function to which the audio packets will
 *          be delivered to.
 * @param audio_buf Buffer containing for example mp3 data.
 * @param audio_buf_size Buffer size.
 * @param stream_id Stream id.
 * @param client_data Callback data.
 * @return true on success, false on insuccess.
 */
typedef bool (on_packet_audio_received_cb)( unsigned char* audio_buf, int audio_buf_size, 
										   int stream_id, const void* client_data );

/**
 * Sinker class.
 * The MediaSink, from which this class derives, will receive RTP packets from the net. 
 * Then decapsulate them and pass to a "sinker" class. In this case it's this class.
 * OStreamBufferedSink will pass the received packets, via callbacks, to other processing
 * classes.
 */
class OStreamBufferedSink : public MediaSink
{
public:
	unsigned _frameSize;
	struct timeval _presentationTime;
	/**
	 * Creates and returns a new instance of OStreamBufferedSink.
	 * @param env UsageEnvironment see LiveMedia doc. here
	 *        http://www.live555.com/liveMedia/public/doxygen/html
	 * @param fv Callback func where to pass the video packets.
	 * @param vid_callback_data Callback video data.
	 * @param fa Callback func where to pass the audio packets.
	 * @param aud_callback_data Callback audio data.
	 * @param subsession_codec String that identifies the codec. Something like "H263-1998".
	 * @param stream_id The stream id to manage. It's useful for multi-stream of single-stream modes.
	 * @param receiving_iface A string to represent the receiving interface. FIXME. 
	 *        Won't work for now.
	 * @param buffer_size Should be at least as large as the largest expected. Defaults to 200000.
	 */
	static OStreamBufferedSink* createNew( UsageEnvironment& env,
						on_packet_video_received_cb* fv, const void *vid_callback_data,
						on_packet_audio_received_cb* fa, const void *aud_callback_data,
						const char* subsession_codec,				
						int stream_id,
						const char* receiving_iface,
						unsigned int buffer_size = 200000 );
	virtual void afterGettingFrame1();

protected:
	/** 
	 *Constructor
	 * @see createNew
	 */
	OStreamBufferedSink( UsageEnvironment& env,	
						on_packet_video_received_cb* fv, const void *vid_callback_data,
						on_packet_audio_received_cb* fa, const void *aud_callback_data,
						const char* subsession_codec,
						int stream_id,
						const char* receiving_iface,
						unsigned buffer_size );
	virtual ~OStreamBufferedSink();

	/** @see MP3FromPCM */	
	static void afterGettingFrame( void* clientData, unsigned frameSize,
						unsigned numTruncatedBytes,
						struct timeval presentationTime,
						unsigned durationInMicroseconds );
	
	/** @see MP3FromPCM */
	
	
	/** Callback function to which the frames will be delivered to. */
	on_packet_video_received_cb* f_on_packet_video_received_cb;
	
	/** Callback function to which the frames will be delivered to. */
	on_packet_audio_received_cb* f_on_packet_audio_received_cb;

private:
	/** Parse the codec string and set the _subsession_codec_id parameter */
	bool parse_codec_str ();

	/** Redefined virtual function */
public:
	virtual Boolean continuePlaying();

private:
	/** The received packet data will be put on this buffer. */
	unsigned char* _packet_buffer;	
	
	/** Buffer size. */
	unsigned int _packet_buffer_size;
	
	/** Char to specity the codec id. */
	char* _subsession_codec_str;
	
	/** Enum to wrap ffmpeg CodecID parameter. */
	ostream_decoding_type _subsession_codec_id;
	
	/** Stream id associated with this class. */
	int _stream_id;

	/** 
	 * VideoDecoder.
	 * @see OStreamVideoDecoder.
	 */
	OStreamVideoDecoder* _video_decoder;
	
	/** Callback data for video data. */
	const void *_callback_video_data_packet_receiver;
	
	/** Callback data for audio data. */
	const void *_callback_audio_data_packet_receiver;
};


#endif	//_OSTREAMBUFFEREDSINK_H_

