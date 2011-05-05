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


#ifndef _BASEINPUTVIDEO_H_
#define _BASEINPUTVIDEO_H_

#include <cv.h>
#include <highgui.h>

/**
 * Base abstract class for input videos.
 * It will be the base class [interface] for retrieving IplImages from a phisical device
 * or [in our case] from a face tracking buffer [e.g multi faces detected]
 */

class BaseInputVideo
{
public:
	BaseInputVideo();
	virtual ~BaseInputVideo();

	/** Init device.\  It can be a webcam, a framegrabber or simpler a buffered class */
	virtual bool init_device () = 0;
	
	/**
	 * Determine if the derived class is of type multi-stream or single-stream.
	 * @return true if the class is multistream, false if it's singlestream.
	 */	
	virtual bool is_multi_stream () = 0;
	
	//
	// single-stream implementable functions
	//
	
	/**
	 * Function that grabs the "next" frame in a stream, a file or a webcam.
	 * @return the IplImage grabbed from the stream.
	 * @note the returned IplImage* must be freed by the caller
	 */
	virtual IplImage * get_next_frame () = 0;

	//
	// multi-stream implementable functions
	//
	
	/**
	 * Retrieves an IplImage from a chosen stream.
	 * @param stream_id The number of the stream we want to get the image from.
	 * @return The next IplImage, if available, of the specified stream_id.
	 * @note the returned IplImage* must be freed by the caller
	 */	
	virtual IplImage * get_next_frame_by_stream_id( int stream_id ) = 0;

	/**
	 * Adds an image to a chosen stream.
	 * @param image The IplImage we want to add to the stream.
	 * @param stream_id The stream number we want to add the image to. There can be multiple streams.
	 * @param __unused__ Unused param. Can be NULL. It's let here for compatibility with OmniStuff callbacks.
	 * @param callback_data Class pointer to be able to access to its members.
	 * @note We'll *not* take an internal copy of image in our list, but only it's 
	 *       pointer. So don't free the image when you call this function.
	 *       If we have num streams, stream_id will range from 0 to num-1.
	 */
	static void 
		add_image_by_stream_id( IplImage* image, 	
								int stream_id, 		
								char* __unused__, 	
								void* callback_data	);

	
protected:
	// the program flow will be something like that for multi-stream mode:
	//
    // Device ===(grab IplImage)====> BufferedImageMultiVideoSource ====> parsing callback function
    //                                                                       (can be external)
    //                                                                          ||
    //                                 add_image_by_stream_id() <===============++
    //                                 add_image_by_stream_id() <===============++                 
    //                                 add_image_by_stream_id() <===============++
    //                                                                          ... 	
	//
	// In our case we have:
    //     OStream                      streamer_ctrl                                OmniStuff
    //       |                               |                                           |
    //       |>    parsable_image_cb  ------>|                                           |
    //       |                               |>register_all_image_callbacks    ------->  |
    //       |                               |>OmniAlgoSimpleDetection_loop () ------->  |
	//       |                                                                           |
	//       |                                                                           |
    //       |<-----------------------------------------------   add_image_by_stream_id <|
	//
	//
	// The add_image_by_stream_id will add a parsed image to a buffer of BufferedImageMultiVideoSource.
	// I.e. the added images could be tracked/detected faces. Then the MJPEGVideoSource
	// and H263plusVideoSource classes will take case of sending the buffers on the net
	// when available.
	
	/**
	 * Callback typedef.
	 * @param image Image grabbed hardware source 
	 * @param this_klass_callback_data A BaseInputVideo's subclass "this" pointer.
	 * @param callback_data Usually an instance to "this" so that the source object can be reached 
	 *        from outside, and for example, call add_image_by_stream_id ().
	 * @typedef on_parsable_image_cb
	 */
	typedef void (on_parsable_image_cb)( IplImage* image, 				
										 void* this_klass_callback_data,
										 void* callback_data );
};


#endif	//_BASEINPUTVIDEO_H_

