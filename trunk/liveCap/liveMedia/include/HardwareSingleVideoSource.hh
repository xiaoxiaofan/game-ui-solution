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


#ifndef _HARDWARESINGLEVIDEOSOURCE_H_
#define _HARDWARESINGLEVIDEOSOURCE_H_

// opencv
#include <cv.h>
#include <highgui.h>

#include "BaseInputVideo.hh"
//#include "OStreamConfig.hh"

/**
 * Derived class that implements BaseInputVideo.
 * It uses a single-stream behaviour to retrieve one stream of IplImage(s) from 
 * an hardware device, a webcam or a framegrabber.
 */
class HardwareSingleVideoSource : public BaseInputVideo
{
public:
	/**
	 * Constructor.
	 * @param camera_num Identify the camera between other grabbing inputs devices.
	 */
	HardwareSingleVideoSource( int camera_num );
	virtual ~HardwareSingleVideoSource();
	
	bool init_device ();
	bool is_multi_stream ();
	
	/**
	 * Get the next image in the stream.
	 * Depends on OpenCV grabbing context.
	 * @return The next image in the stream.
	 * @note The returned IplImage* must be freed by the caller.
	 */ 
	IplImage * get_next_frame ();

	/** Redefined virtual function for multi video source. We don't need them here */
	virtual IplImage * get_next_frame_by_stream_id( int stream_id );
	
	/** Redefined virtual function for multi video source. We don't need them here */	
	virtual void add_image_by_stream_id( IplImage *image, int stream_id, char* __unused__, 
										void* callback_data );	
	
private:
	/** Specify whether the class is initialized or not. */					
	bool _initialized;
	
	/** Camera number mapped on system. */
	int _camera_num;
	
	/** OpenCV capture structure. */
	CvCapture *_cam_input;	
};


#endif	//_HARDWARESINGLEVIDEOSOURCE_H_

