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

#ifndef _OSTREAMRECEIVER_H_
#define _OSTREAMRECEIVER_H_

#include <liveMedia.hh>
#include <BasicUsageEnvironment.hh>

#include "OStreamBufferedSink.hh"

/**
 * @typedef ostream_receiver_error_codes Enumerates the errors that can be
 *          received by the RTSPClient.
 */
typedef enum  {

	ERROR_NORMAL_STATUS = 0,
	ERROR_FAILED_SDP_DESCRIPTION,
	ERROR_FAILED_FILE_SINK_CREATION,
	ERROR_FAILED_TO_CREATE_RECEIVER,
	ERROR_FAILED_CREATE_RTSP_CLIENT,
	ERROR_FAILED_CREATE_MEDIASESSION,
	ERROR_FAILED_SETUP_STREAMS,
	ERROR_UNKOWN_ERROR
} ostream_receiver_error_codes;


/**
 * Receiver class.
 * Will have an internal RTSPClient that will manage the RTSP connections.
 * @see OStreamUCast.
 */
class OStreamReceiver
{
public:
     OStreamBufferedSink* buffered_sink;
	/**
	 * Constructor.
	 * @param dest_rtsp_url Something like "rtsp://12.23.34.45:8554/testStream"
	 * @param f_on_packet_video_received_cb Callback function. Will be used by the Sink Class [video].
	 * @param video_callback_data Callback data for video parsing function.
	 * @param f_on_packet_audio_received_cb Callback function. Will be used by the Sink Class [audio].
	 * @param audio_callback_data Callback data for audio parsing function.
	 * @param receiving_iface FIXME. won't work for now. Defaults to "0.0.0.0"
	 * @param sink_buffer_size Size of the internal buffer will have. 
	 * @see OStreamBufferedSink
	 */
	OStreamReceiver( const char* dest_rtsp_url,
				  	 on_packet_video_received_cb* f_on_packet_video_received_cb,
					 const void *video_callback_data,
					 on_packet_audio_received_cb* f_on_packet_audio_received_cb,
				  	 const void *audio_callback_data,
					 const char* receiving_iface = "0.0.0.0",
				  	 unsigned int sink_buffer_size = 200000 );
	
	virtual ~OStreamReceiver();

	/** 
	 * Check the receiving status.
	 * @return An error level identified by an int
	 * @see ostream_receiver_error_codes
	 */
	int isReadyToStream();
	
	/** 
	 * Start to receive.
	 * @return Errror status.
	 * @see ostream_receiver_error_codes	 
	 */ 
	int startReceiving();
	
	/** Commands the stop of the receiving session. */
	void stopReceiving();
	
	/**
	 * Static members: mainly to manage callbacks functions. 
	 * @note A system with functors and/or with static callbacks-wrappers
	 *       wouldn't be the best choice here coz LiveMedia uses (void *)
	 *       method to pass callback data.
	 * @see http://www.live555.com/liveMedia/public/doxygen/html
	 */
	static void subsessionAfterPlaying( void* mediaSubSess );
	static void subsessionByeHandler( void* mediaSubSess );
	static void startPlayingStreams( void* OStreamReceiverClassPointer );
	static void checkForPacketArrival(void* OStreamReceiverClassPointer );

private:	// functions

	/**
	 * Create a new RTSPClient internally stored.
	 * @return true on success. False on insuccess.
	 * @see http://www.live555.com/liveMedia/public/doxygen/html	 
	 */
	bool createRTSPClient();
	
	/**
	 * Create a new MediaSession internally stored.
	 * @return true on success. False on insuccess.
	 * @see http://www.live555.com/liveMedia/public/doxygen/html	 
	 */
	bool createMediaSession();
	
	/**
	 * Retrieves the SDP description from the specified url.
	 * @param url Something like "rtsp://12.23.34.45:8554/testStream"
	 * @return Errror status.
	 * @see ostream_receiver_error_codes	 
	 */
	int getSDPDescriptionFromURL( char const* url );
	
	/** Setup the internal streams. */
	void setupStreams();
	
	/** Start the playing session. */
	bool clientStartPlayingSession();
	bool clientSetupSubsession( void* mediaSubSess );
	void closeMediaSinks();
	
	/** 
	 * Shutdown the client and the connections, e.g. sockets etc. 
	 * This is called when a "stop receive" command is issued.
	 */
	void shutdown();

	/** callback functions to which the frames will be delivered */
	on_packet_video_received_cb* f_on_packet_video_received_cb;
	
	/** callback functions to which the frames will be delivered */
	on_packet_audio_received_cb* f_on_packet_audio_received_cb;

private:	// data

	/** Last error status. */
	int _error_status;
	
	/** SDP end time. */
	double _end_time;
	
	/** The SDP Description, something like "Session streamed by Omnimeeting" */
	char* _sdp_description;
	
	/** Protocol name. Usually set at "RTSP" */
	const char* _client_protocol_name;
	
	/** This var is used to exit the event-driven loop made by LiveMedia on receiving */
	char _watch_variable;
	
	/** 
	 * The Sink Buffer Size. 
	 * This should be set quite high or there will be problems receiving for instance
	 * large JPEG frames.
	 */
	unsigned int _sink_buffer_size;
	
	/** Callback video data */
	const void *_callback_video_data_client;
	
	/** Callback audio data */
	const void *_callback_audio_data_client;
	
	/** Receiving interface. */
	char *_receiving_iface;

	/** @see http://www.live555.com/liveMedia/public/doxygen/html */
	UsageEnvironment* _env;
	TaskScheduler* _scheduler;
	RTSPClient* _rtsp_client;
	TaskToken _arrival_check_timer_task;
	
	/**
	 * A data structure that represents a session that consists of
	 * potentially multiple (audio and/or video) sub-sessions
	 * (This data structure is used for media *receivers* - i.e., clients.
	 * For media streamers, use "ServerMediaSession" instead.)
	 * @see http://live555.com/liveMedia/doxygen/html/MediaSession_8hh-source.html
	 */
	MediaSession* _media_session;
};


#endif	//_OSTREAMRECEIVER_H_

