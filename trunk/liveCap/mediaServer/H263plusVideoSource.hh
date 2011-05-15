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


#ifndef _H263PLUSVIDEOSOURCE_H_
#define _H263PLUSVIDEOSOURCE_H_


// livemedia
#include <GroupsockHelper.hh>
#include <liveMedia.hh>
#include <JPEGVideoSource.hh>

// opencv
#include <cv.h>
#include <highgui.h>

#include <time.h>

//#include "OStreamConfig.hh"
#include "BaseInputVideo.hh"
#include "OStreamVideoEncoder.hh"


/** Set a default maximum h263+ frame size of 500K bytes. */
#define OUTPUT_PACKET_BUFFER_MAXSIZE	512000

/**
 * H263plus video encapsulator.
 * This class will take IplImages from a video source and then will encode them into
 * h263+ packets, incapsulating then into RTPs frames.
 * This class will subclass the event-driven library LiveMedia.
 * Derives FramedSource.
 */
class H263plusVideoSource : public FramedSource
{
public:
		
	/**
 	 * Static method.
	 * @param env UsageEnvironment, see LiveMedia doc. here
	 *        http://www.live555.com/liveMedia/public/doxygen/html
	 * @param input_video A BaseInputVideo class, can be a MultiVideoSource or a 
	 *        SingleVideoSource kind of class.
	 * @param stream_id Stream id that will identify this H263plusVideoSource 
	 *        incapsulator class. It defaults to 0.
	 * @param frame_rate Frames Per Second value. Number of frames per time unit.
	 * @param encoder_internal_buf_size Encoder internal buffer size. Memory to alloc
	 *        for encoding purposes. Defaults to 1000000.
	 * @return New instance of H263plusVideoSource.
	 * @see MJPEGVideoSource
 	 */
	static H263plusVideoSource*
		createNew( UsageEnvironment& env, BaseInputVideo* input_video, int stream_id = 0,
				  int frame_rate = 25, int encoder_internal_buf_size = 1000000 );
	
protected:
	/**
 	 * Constructor.
	 * @see createNew
 	 */
	H263plusVideoSource( UsageEnvironment& env, BaseInputVideo* input_video, int stream_id,
						 int frame_rate, int encoder_internal_buf_size );
	virtual ~H263plusVideoSource();
	
private:		// functions
	/**
 	 * Inherited function.\  Used to process next frame to send.
 	 */
	void doGetNextFrame();

	/** Provides RTP encapsulation. */
	void deliverFrame();
	
	/** Captures a IplImage and encode it to a h263+ buffer. */
	void  startCapture();
	
private:		// data
	/** Specify whether the class is initialized or not. */
	bool _initialized;
	
	/** Frames per second. */	
	int _fps;
	
	/** Equals at 1000/frame_rate */	
	int _frame_rate_millis;	
	int _receiveSoket;
	SOCKET s;
	
	/** size of current frame to send */
	unsigned int fPreferredFrameSize;

	/**
	 * Holds the pointer of the internal_buffer of OStreamVideoEncoder.
	 * In this particular H263plus case it will contain a varying packet size before 
	 * it's sending.
	 */
	const unsigned char* _encoded_frame;

	/** Contains the last capture time. Useful for internal packet ordering. */ 
	struct timeval fLastCaptureTime;
	
	/** Size of the internal buffer used for encoding. */
	int _encoder_internal_buf_size;
	
	/** Stream id. */
	int _stream_id;
	
	/** BaseInputVideo class instance pointer. */
	BaseInputVideo *_input_video;
	
	/** OStreamVideoEncoder class instance pointer. */
	OStreamVideoEncoder *_video_encoder;

#ifdef __LINUX__
	struct timezone Idunno;
#else
	int Idunno;
#endif
	
};


#endif	//_H263PLUSVIDEOSOURCE_H_

