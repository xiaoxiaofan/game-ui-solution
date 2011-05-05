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

#ifndef _OSTREAMVIDEOENCODER_H_
#define _OSTREAMVIDEOENCODER_H_

#include <cv.h>
#include <highgui.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}
typedef enum {
	OSTREAM_ENCODING_NONE,
	OSTREAM_ENCODING_MJPEG,
	OSTREAM_ENCODING_H263P,
	OSTREAM_ENCODING_MP3

} ostream_encoding_type;

//#include "OStreamConfig.hh"

/**
 * Encoder video.
 * Utility class with reusable code. Depends on libavcodec/libavformat.
 * Encodes a IplImage to encoded data [h263+, mjpeg]or, extendable, to other formats.
 */
class OStreamVideoEncoder
{
public:
		
	/**
	 * Constructor.
	 * @param io_buf_size Internal buffer size used to store encoded frames.
	 *        This must be <= fMaxSize, or liveMedia libraries will crash.
	 *        please note: in case you want to add some new encoding type
	 *        be sure to check all the "switch ( _encoding_type )" lines you'll
	 *        find in the implementation file and to add them the correct parameters.
	 * @param encoding_type ostream_encoding_type parameter.
	 * @param video_width Video width. In a future this parameter can be removed, coz 
	 *        this info is already inside the IplImage.
	 * @param video_height Video height In a future this parameter can be removed, coz 
	 *        this info is already inside the IplImage.
	 * @param fps Frame Per Second
	 * @param opencv_pix_fmt Speaking about OpenCV and IplImages, they usually 
	 *        set BGR as their main format, but with the new display system, wxImage,
  	 *        it's better to have RGB format, so that we can avoid a conversion.
	 */
	OStreamVideoEncoder( unsigned int io_buf_size, ostream_encoding_type encoding_type,
						 int video_width, int video_height, 
						 int fps = 25,
						 PixelFormat opencv_pix_fmt = PIX_FMT_BGR24 );
	virtual ~OStreamVideoEncoder();

	/**
	 * Encode a IplImage to a buffer.
	 * @param image IplImage. This is a "next" frame of a video stream.
	 * @param out_size The size of the encoded buffer.
	 * @return A buffer, which is the next packet of an encoded video stream.
	 * @note The returned buffer should not be modified or worst free. It's the internal
	 *       pointer to a buffer of this class. We act like this for performances
	 *       tasks.
	 */
	const unsigned char* encode_video_frame( IplImage *image, int *out_size );
	
private:		// functions

	/**
	 * Initialize the encoder 
	 * @return true on success, false on insuccess.
	 */
	bool encoder_initialize ();
	
	/** 
	 * Create an AVFrame.
	 * @param pixel_format Pixel format of the resulting AVFrame. It's mainly used as
	 *        temporary buffer for conversions.
	 * @return A new AVFrame. 
	 * @see ffmpeg doc.
	 */
	AVFrame* create_avframe( int pixel_format, int width,int height);
	
	/** 
	 * Create a video stream.
	 * @param io_fmt_context Please refer to ffmpeg doc.
	 * @param codec_id CodecID of ffmpeg.
	 * @return New AVStream.
	 */
	AVStream* create_video_stream( AVFormatContext *io_fmt_context, int codec_id );

	/** Open the codec */
	bool open_codec( AVStream *stream );
	
private:		// data
	/** Specify whether the class is initialized or not. */
	bool _initialized;

	/** @see ffmpeg doc for this struct */		
	AVFrame *_ready_to_encode_frame, *_opencv_frame;
	
	/** @see ffmpeg doc for this struct */	
	AVOutputFormat *_out_fmt;
	
	/** @see ffmpeg doc for this struct */	
	AVFormatContext *_out_fmt_context;
	
	/** @see ffmpeg doc for this struct */	
	AVStream *_video_stream;

	struct SwsContext *sws_ctx;

	/** @see ffmpeg doc for this struct */	
	PixelFormat _opencv_pix_fmt;
	
	/** Internal buffer used for conversions */
	unsigned char* _internal_buffer;
	int _internal_buffer_size;
	
	/** @see ostream_encoding_type */	
	int _encoding_type;

	int _video_height;
	int _video_width;
	int _fps;

};


#endif	//_OSTREAMVIDEOENCODER_H_

