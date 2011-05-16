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


#include "OStreamReceiver.hh"


//--------------------------------------------------------------------------
// constructor

OStreamReceiver::OStreamReceiver( const char* dest_rtsp_url, 
								 on_packet_video_received_cb* fv, 
								 const void *video_callback_data, 
								 on_packet_audio_received_cb* fa, 
								 const void *audio_callback_data, 
								 const char* receiving_iface /* = 0.0.0.0 */,
								 unsigned int sink_buffer_size /* = 200000 */ ) :
f_on_packet_video_received_cb( fv ),
_callback_video_data_client( video_callback_data ),
f_on_packet_audio_received_cb( fa ),
_callback_audio_data_client( audio_callback_data ),
_sink_buffer_size( sink_buffer_size )
{

	_scheduler = BasicTaskScheduler::createNew();
	_env = BasicUsageEnvironment::createNew( *_scheduler );

	_receiving_iface = strdup( receiving_iface );

	// set up the endtime [0 means to play following the SDP time]
	_end_time = 0;
	_error_status = ERROR_NORMAL_STATUS;
	_client_protocol_name = "RTSP";
	_watch_variable = 0;

	_media_session = NULL;
	_arrival_check_timer_task = NULL;

	if ( createRTSPClient() == false ) {
		shutdown();
		_error_status = ERROR_FAILED_CREATE_RTSP_CLIENT;
		return;
	}

	if ( getSDPDescriptionFromURL( dest_rtsp_url ) < 0 ) {
		shutdown();
		_error_status = ERROR_FAILED_SDP_DESCRIPTION;
		return;
	}

	if ( createMediaSession() == false ) {
		shutdown();
		_error_status = ERROR_FAILED_CREATE_MEDIASESSION;
		return;
	}
}


//--------------------------------------------------------------------------
//

OStreamReceiver::~OStreamReceiver() {

	if ( _sdp_description != NULL )
		delete[] _sdp_description;

	if ( _receiving_iface != NULL )
		free( _receiving_iface );


	_env->reclaim();
	delete _scheduler;
}


//--------------------------------------------------------------------------
// simply return an error level identified by an int
// return 0 on "ok, ready to stream"

int OStreamReceiver::isReadyToStream() 
{
	return _error_status;
}



//--------------------------------------------------------------------------
// start playing the global media session

bool OStreamReceiver::clientStartPlayingSession( ) 
{
	return _rtsp_client->playMediaSession( *_media_session ) == 1 ? true : false;
}





//--------------------------------------------------------------------------
// setup a single media subsession

bool OStreamReceiver::clientSetupSubsession( void* mediaSubSess ) 
{
	MediaSubsession* media_subsession = (MediaSubsession*)mediaSubSess;
	return _rtsp_client->setupMediaSubsession(*media_subsession, 
		false, false) == 1 ? true : false;
}



//--------------------------------------------------------------------------
//

void OStreamReceiver::closeMediaSinks() {

	if ( _media_session == NULL ) 
		return;

	MediaSubsessionIterator iter( *_media_session );
	MediaSubsession* _media_subsession;

	// let's close its subsession
	while ( ( _media_subsession = iter.next() ) != NULL ) {
		Medium::close( _media_subsession->sink );
		_media_subsession->sink = NULL;
	}
}


//--------------------------------------------------------------------------
// shutdown the tasks delayed and closes the media sinks

void OStreamReceiver::shutdown( ) 
{
	_env->taskScheduler().unscheduleDelayedTask( _arrival_check_timer_task );
	_watch_variable = 1;
}


//--------------------------------------------------------------------------
//
/*
void OStreamReceiver::retrieve_wh_from_session_name( char* name, int* width, int* height )
{
// ok it's just a matter of string parsing
_media_session->sessionName();
}
*/

//--------------------------------------------------------------------------
// start receiving RTP packets from the rtsp://host.com/stream provided URL
// return: error_status

int OStreamReceiver::startReceiving() {

	// first of all check that no errors occurred in stream and class
	// initialization
	if ( _error_status != ERROR_NORMAL_STATUS )
		return _error_status;

	// Then, setup the "RTPSource"s for the session:
	MediaSubsessionIterator iter(*_media_session);
	MediaSubsession *media_subsession;
	bool made_progress = false;

	while ( (media_subsession = iter.next()) != NULL) {
		if ( !media_subsession->initiate() ) {
			*_env << "Unable to create receiver for \"" << media_subsession->mediumName()
				<< "/" << media_subsession->codecName()
				<< "\" subsession: " << _env->getResultMsg() << "\n";
			_error_status = ERROR_FAILED_TO_CREATE_RECEIVER;
		} else {
			*_env << "Created receiver for \"" << media_subsession->mediumName()
				<< "/" << media_subsession->codecName()
				<< "\" subsession (client ports " << media_subsession->clientPortNum()
				<< "-" << media_subsession->clientPortNum() + 1 << ")\n";
			made_progress = true;

			if ( media_subsession->rtpSource() != NULL ) {
				// let some time for reordering the packets
				unsigned const thresh = 500000; // 0.5 seconds
				media_subsession->rtpSource()->setPacketReorderingThresholdTime( thresh );
			}
		}	 
	}

	// are we able to continue?
	if ( !made_progress )  {
		shutdown();
		return _error_status;
	}

	// Perform additional 'setup' on each subsession, before playing them:
	setupStreams();

	// Create and start "OStreamBufferedSink"s for each subsession:
	made_progress = False;


	iter.reset();
	int stream_count = 0;
	while ((media_subsession = iter.next()) != NULL) {

		// was it initialized?
		if ( media_subsession->readSource() == NULL )
			continue; 

		

		// Normal case:
		buffered_sink = OStreamBufferedSink::createNew(*_env, 
			f_on_packet_video_received_cb, _callback_video_data_client,
			f_on_packet_audio_received_cb, _callback_audio_data_client,
			media_subsession->codecName(), stream_count,
			_receiving_iface,
			_sink_buffer_size );

		media_subsession->sink = buffered_sink;

		if ( media_subsession->sink == NULL ) {
			_error_status = ERROR_FAILED_FILE_SINK_CREATION;
		} else {

			// we have a new stream, increment them.
			stream_count++;

			// let's start it!
			media_subsession->sink->startPlaying( *(media_subsession->readSource()),
				subsessionAfterPlaying,
				media_subsession );

			// Also set a handler to be called if a RTCP "BYE" arrives
			// for this subsession:
			if (media_subsession->rtcpInstance() != NULL) {
				media_subsession->rtcpInstance()->setByeHandler( subsessionByeHandler,
					media_subsession);
			}

			made_progress = true;
		}
	}

	if ( !made_progress ) {
		shutdown();
		return _error_status;
	}

	// Finally, start playing each subsession, to start the data flow:
	startPlayingStreams( this );

	// returns only after a setting to watchvariable = 1
	// it's a blocking call.
	_env->taskScheduler().doEventLoop( &_watch_variable ); 

	// Close our output sinks:
	closeMediaSinks();

	// Teardown, then shutdown, any outstanding RTP/RTCP subsessions
	if ( ( media_subsession != NULL) && ( _rtsp_client != NULL ) )
		_rtsp_client->teardownMediaSession( *_media_session );

	Medium::close( _media_session );

	// Finally, shut down our client:
	Medium::close( _rtsp_client );

	return _error_status;
}


//--------------------------------------------------------------------------
//

void OStreamReceiver::subsessionByeHandler(void* mediaSubSess) {
	// Act now as if the subsession had closed:
	subsessionAfterPlaying( (MediaSubsession*)mediaSubSess );
}


//--------------------------------------------------------------------------
//

void OStreamReceiver::stopReceiving() 
{
	shutdown();
}


//--------------------------------------------------------------------------
//

void OStreamReceiver::checkForPacketArrival( void* ostreamer_receiver_ptr ) 
{
	OStreamReceiver *klass = (OStreamReceiver *)ostreamer_receiver_ptr;

	// Check each mediaSubsession, to see whether it has received data packets:
	unsigned numSubsessionsChecked = 0;
	unsigned numSubsessionsWithReceivedData = 0;
	unsigned numSubsessionsThatHaveBeenSynced = 0;

	MediaSubsessionIterator iter( *(klass)->_media_session);
	MediaSubsession* media_subsession;

	// we will loop between all the subsession of the media session
	// i.e. in multi-stream mode we will have a subsession for each face
	// streamed
	while (( media_subsession = iter.next()) != NULL &&
		klass->_error_status == ERROR_NORMAL_STATUS ) {

			RTPSource* src = media_subsession->rtpSource();

			if (src == NULL) 
				continue;

			++numSubsessionsChecked;

			if ( src->receptionStatsDB().numActiveSourcesSinceLastReset() > 0 ) {
				// At least one data packet has arrived
				++numSubsessionsWithReceivedData;
			}
			if ( src->hasBeenSynchronizedUsingRTCP() ) {
				++numSubsessionsThatHaveBeenSynced;
			}
	}

	unsigned numSubsessionsToCheck = numSubsessionsChecked;

	// No luck, so reschedule this check again, after a delay:
	int uSecsToDelay = 100000; // 100 ms
	klass->_arrival_check_timer_task = 
		klass->_env->taskScheduler().scheduleDelayedTask( uSecsToDelay,
		(TaskFunc*)OStreamReceiver::checkForPacketArrival, 
		klass );
}



//--------------------------------------------------------------------------
//

void OStreamReceiver::startPlayingStreams( void* ostreamer_receiver_ptr ) 
{
	OStreamReceiver *klass = (OStreamReceiver *)ostreamer_receiver_ptr;

	if ( !klass->clientStartPlayingSession() ) {
		*klass->_env << "Failed to start playing session: " << klass->_env->getResultMsg() << "\n";
		klass->shutdown();
		return;
	} else {
		*klass->_env << "Started playing session\n";
	}

	// Figure out how long to delay (if at all) before shutting down, or
	// repeating the playing

	if ( klass->_end_time == 0 ) 
		klass->_end_time = klass->_media_session->playEndTime(); // use SDP end time

	// Watch for incoming packets (if desired):
	klass->checkForPacketArrival( klass );
}




//--------------------------------------------------------------------------
//

void OStreamReceiver::subsessionAfterPlaying( void* media_sub_sess ) {

	// Begin by closing this media subsession:
	MediaSubsession* media_subsession = (MediaSubsession*)media_sub_sess;
	Medium::close( media_subsession->sink );
	media_subsession->sink = NULL;

	// Next, check whether *all* subsessions have now been closed:
	MediaSession& media_session = media_subsession->parentSession();
	MediaSubsessionIterator iter(media_session);
	while ((media_subsession = iter.next()) != NULL) {
		if (media_subsession->sink != NULL) 
			return; // this subsession is still active
	}
}

//--------------------------------------------------------------------------
//

void OStreamReceiver::setupStreams() 
{
	MediaSubsessionIterator iter(*_media_session);
	MediaSubsession *media_subsession;
	bool made_progress = false;

	while ( (media_subsession = iter.next()) != NULL ) {
		if ( media_subsession->clientPortNum() == 0 ) 
			continue; // port # was not set

		if ( !clientSetupSubsession( media_subsession ) ) {
			_error_status = ERROR_FAILED_SETUP_STREAMS;
			*_env << "Failed to setup \"" << media_subsession->mediumName()
				<< "/" << media_subsession->codecName()
				<< "\" subsession: " << _env->getResultMsg() << "\n";
		} else {
			*_env << "Setup \"" << media_subsession->mediumName()
				<< "/" << media_subsession->codecName()
				<< "\" subsession (client ports " << media_subsession->clientPortNum()
				<< "-" << media_subsession->clientPortNum() + 1 << ")\n";
			made_progress = true;
		}
	}
	if ( !made_progress ) {
		shutdown();
		return;
	}
}


//--------------------------------------------------------------------------
// on error returns -1, else the rtsp describe status

int OStreamReceiver::getSDPDescriptionFromURL( char const* url ) {

	_sdp_description = _rtsp_client->describeURL( url );


	/*_sdp_description="v=0\r\n"
		"o=- 1268790462383865 1 IN IP4 192.168.1.101\r\n"
		"s=live Video, streamed by the LIVE555 Media Server\r\n"
		"i=test.live\r\n"
		"t=0 0\r\n"
		"a=tool:LIVE555 Streaming Media v2010.03.08\r\n"
		"a=type:broadcast\r\n"
		"a=control:*\r\n"
		"a=range:npt=0-\r\n"
		"a=x-qt-text-nam:live Video, streamed by the LIVE555 Media Server\r\n"
		"a=x-qt-text-inf:test.live\r\n"
		"m=video 0 RTP/AVP 96\r\n"
		"c=IN IP4 0.0.0.0\r\n"
		"b=AS:64\r\n"
		"a=rtpmap:96 H263-1998/90000\r\n"
		"a=control:track1\r\n";*/
	if ( _sdp_description == NULL ) {
		*_env << "Failed to get a SDP description from URL \"" << url
			<< "\": " << *_env->getResultMsg() << "\n";
		return -1;
	}

	*_env << "Opened URL \"" << url
		<< "\", returning a SDP description:\n" << _sdp_description << "\n";

	return 1;

	//return 0;
}


//--------------------------------------------------------------------------
//

bool OStreamReceiver::createRTSPClient() {

	_rtsp_client = RTSPClient::createNew( *_env );
	if ( _rtsp_client == NULL ) {
		*_env << "Failed to create " << 
			" client: " << _env->getResultMsg() << "\n";
		return false;
	}

	return true;
}


//--------------------------------------------------------------------------
// Create a media session object from this SDP description

bool OStreamReceiver::createMediaSession() {

	// new media session object
	_media_session = MediaSession::createNew( *_env, _sdp_description );

	if ( _media_session == NULL ) {
		*_env << "Failed to create a MediaSession object from the SDP description: " << _env->getResultMsg() << "\n";
		return false;
	}

	return true;
}

