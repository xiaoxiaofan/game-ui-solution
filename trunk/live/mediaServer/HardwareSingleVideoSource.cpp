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


#include "HardwareSingleVideoSource.hh"


HardwareSingleVideoSource::HardwareSingleVideoSource( int camera_num ) : BaseInputVideo(),
			_camera_num( camera_num )
{
	_initialized = false;
}

HardwareSingleVideoSource::~HardwareSingleVideoSource()
{
	if ( _cam_input != NULL )
		cvReleaseCapture( &_cam_input );
	_cam_input = NULL;

	_initialized = false;
}

bool HardwareSingleVideoSource::init_device ( ) 
{

	if ( _initialized == true )
		return true;

  if ( (_cam_input = cvCaptureFromCAM( _camera_num )) == NULL ) {
//		DEBUG_PRINT( "Error initializing webcam device\n" );
 		return false;
  }
	
	_initialized = true;
	return true;
}

IplImage * HardwareSingleVideoSource::get_next_frame ()
{
	IplImage *tmp_image;
	IplImage *res_image;
	
	if ( !_initialized ) {
		// try to initialize the device. If it returns false then we'll return NULL
		if ( init_device () == false )
			return NULL;
	}
	
	if( !cvGrabFrame( _cam_input )) {
//		DEBUG_PRINT( "Error getting frame from webcam\n" );
		return NULL;
	}
	
    tmp_image = cvRetrieveFrame( _cam_input );

	res_image = cvCreateImage( cvGetSize( tmp_image ), 8, 3 );
	
	// make a copy of the image so that it can be freed later.
	cvCopy( tmp_image, res_image, 0 );
	return res_image;
}

IplImage * HardwareSingleVideoSource::get_next_frame_by_stream_id( int stream_id ) 
{ 
	return NULL; 
}

void HardwareSingleVideoSource::add_image_by_stream_id( IplImage *image, int stream_id, 
								   char* __unused__, void* callback_data  ) 
{
}

bool HardwareSingleVideoSource::is_multi_stream() 
{
	return false;
}
