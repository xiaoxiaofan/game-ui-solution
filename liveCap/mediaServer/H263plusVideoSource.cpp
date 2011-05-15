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


#include "H263plusVideoSource.hh"

H263plusVideoSource*
H263plusVideoSource::createNew( UsageEnvironment& env, BaseInputVideo* input_video, int stream_id /* = 0 */,
							    int frame_rate /* = 25*/, int encoder_internal_buf_size /*= 1000000*/ ) 
{
	return new H263plusVideoSource( env, input_video, stream_id, frame_rate, encoder_internal_buf_size );
}

H263plusVideoSource::H263plusVideoSource ( UsageEnvironment& env, BaseInputVideo* input_video, int stream_id,
										  int frame_rate, int encoder_internal_buf_size ) 
										  : FramedSource( env ), 
										_input_video( input_video ),
										_fps( frame_rate ), 
										_encoder_internal_buf_size( encoder_internal_buf_size ),
										_stream_id( stream_id ),
										s(-1)
{
	_initialized = false;
	_video_encoder = NULL;
	// set the max output packet buffer size
	OutPacketBuffer::maxSize = OUTPUT_PACKET_BUFFER_MAXSIZE;
	_receiveSoket = 0;

	_encoded_frame = NULL;

	
	_frame_rate_millis = 1000/frame_rate;

	// initialize device
	if ( _input_video->init_device () == true )
		_initialized = true;
}

H263plusVideoSource::~H263plusVideoSource()
{
	if ( _video_encoder )
		delete _video_encoder;
	_video_encoder = NULL;

	_initialized = false;
	// DO *NOT* delete _input_video; otherwise in multi stream mode you'll have a crash
}

void H263plusVideoSource::startCapture() 
{
	IplImage* current_frame;
	fPreferredFrameSize = 0;

	if ( _input_video->is_multi_stream () ) {
		if ( (current_frame = _input_video->get_next_frame_by_stream_id ( _stream_id )) == NULL ) {
//			DEBUG_PRINT ("id #%d :_input_video->get_next_frame_by_stream_id = NULL\n", _stream_id );
		}
	}
	else if ( (current_frame = _input_video->get_next_frame ()) == NULL ) {
//		DEBUG_PRINT ("_input_video->get_next_frame = NULL\n");
	}

	// we cannot proceed with encoding or something else. Just exit here
	if ( current_frame == NULL ) {
		fFrameSize = fPreferredFrameSize = 0;
		_encoded_frame = NULL;
		return;
	}
	gettimeofday( &fLastCaptureTime, &Idunno );

	// proceed with encoding
	if ( _video_encoder == NULL ) {
		// encoder is NULL, create it.
		_video_encoder = new OStreamVideoEncoder( 1000000, (ostream_encoding_type)OSTREAM_ENCODING_H263P,
							 	176, 144, _fps );
	}

	int h263p_frame_size;
	_encoded_frame = _video_encoder->encode_video_frame( current_frame, &h263p_frame_size );
	
	if ( h263p_frame_size > _encoder_internal_buf_size || _encoded_frame == NULL ) {
//		DEBUG_PRINT ("Error: the h263+ frame to stream is too big or NULL.\n");
		fPreferredFrameSize = 0;
		_encoded_frame = NULL;
		return;
	}
		
    if ( h263p_frame_size <= 0 || (unsigned int)h263p_frame_size  > fMaxSize ) {
//		DEBUG_PRINT ("Error: the h263+ frame to stream is too big.\n");
		fPreferredFrameSize = 0;
		_encoded_frame = NULL;
		return;
	}

	fPreferredFrameSize = h263p_frame_size;

	cvReleaseImage( &current_frame );
}

//--------------------------------------------------------------------------
// 

void H263plusVideoSource::doGetNextFrame() {
	// let the cpu breath.
	cvWaitKey( _frame_rate_millis );

	deliverFrame();
}

//--------------------------------------------------------------------------
//

void H263plusVideoSource::deliverFrame() {
	//
	// This would be called when new frame data is available from the device.
	// This function should deliver the next frame of data from the device,
	// using the following parameters (class members):
	// 'in' parameters (these should *not* be modified by this function):
	//     fTo: The frame data is copied to this address.
	//         (Note that the variable "fTo" is *not* modified.  Instead,
	//          the frame data is copied to the address pointed to by "fTo".)
	//     fMaxSize: This is the maximum number of bytes that can be copied
	//         (If the actual frame is larger than this, then it should
	//          be truncated, and "fNumTruncatedBytes" set accordingly.)
	// 'out' parameters (these are modified by this function):
	//     fFrameSize: Should be set to the delivered frame size (<= fMaxSize).
	//     fNumTruncatedBytes: Should be set iff the delivered frame would have been
	//         bigger than "fMaxSize", in which case it's set to the number of bytes
	//         that have been omitted.
	//     fPresentationTime: Should be set to the frame's presentation time
	//         (seconds, microseconds).
	//     fDurationInMicroseconds: Should be set to the frame's duration, if known.

	// Start capturing the next frame:
	startCapture();
	if ( fPreferredFrameSize <= 14 || _encoded_frame == NULL ) {
		if ( _input_video->is_multi_stream() ) {
			nextTask()  = envir().taskScheduler().scheduleDelayedTask( 0, (TaskFunc*)afterGetting,
							  										this );
			return;
		}
		else {
			handleClosure(this);
			return;
		}
	}

	
	fPresentationTime = fLastCaptureTime;


	fFrameSize = (fPreferredFrameSize);
	memcpy(fTo, _encoded_frame, fFrameSize );

	if ( fFrameSize == fMaxSize ) {
	}

	// After delivering the data, switch to another task, and inform
	// the reader that he has data:
	nextTask()  = envir().taskScheduler().scheduleDelayedTask( 0, (TaskFunc*)afterGetting,
						  										this);
}


