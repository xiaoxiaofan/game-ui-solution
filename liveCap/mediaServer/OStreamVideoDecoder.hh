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

#ifndef _OSTREAMVIDEODECODER_H_
#define _OSTREAMVIDEODECODER_H_

typedef enum {
	OSTREAM_DECODING_NONE,
	OSTREAM_DECODING_MJPEG,
	OSTREAM_DECODING_H263P,
	OSTREAM_DECODING_MP3

} ostream_decoding_type;

#include <cv.h>
#include <highgui.h>
extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}


/**
 * Decoder video.
 * Utility class with reusable code. Depends on libavcodec/libavformat.
 * Decodes encoded data [h263+, mjpeg] to IplImages or, extendable, to other formats.
 */
class OStreamVideoDecoder
{
public:
	/**
	 * Constructor.
	 * @param io_buf_size Internal buffer size used to store encoded frames.
	 *        This must be <= fMaxSize, or liveMedia libraries will crash.
	 * @param decoding_type ostream_decoding_type parameter.
	 * @param fps Frames Per Second
	 * @param opencv_pix_fmt Speaking about OpenCV and IplImages, they usually 
	 *        set BGR as their main format, but with the new display system, wxImage,
  	 *        it's better to have RGB format, so that we can avoid a conversion.
	 */
	OStreamVideoDecoder( unsigned int io_buf_size, ostream_decoding_type decoding_type,
						 int fps = 25,
						 PixelFormat opencv_pix_fmt = PIX_FMT_BGR24 );

	virtual ~OStreamVideoDecoder();

	/**
	 * Decode a buffer into a IplImage.
	 * @param buf Buffer with encoded data.
	 * @param buf_size Buffer size.
	 * @return A IplImage, which is the next image in the decoded video stream.
	 */
	IplImage* decode_video_frame( unsigned char* buf, int buf_size );

private:		// functions
	/** 
	 * Initialize the decoder.
	 * @return true on success, false on insuccess.
	 */
	bool decoder_initialize ();
	
	/** 
	 * Create an AVFrame.
	 * @param pixel_format Pixel format of the resulting AVFrame. It's mainly used as
	 *        temporary buffer for conversions.
	 * @param frame_width Width of the frame.
	 * @param frame_height Height of the frame.
	 * @return A new AVFrame. 
	 * @see ffmpeg doc.
	 */
	AVFrame* create_avframe( int pixel_format, int frame_width, int frame_height );

private:		// data
	/** Specify whether the class is initialized or not. */
	bool _initialized;
	
	/** Internal buffer used for conversions */
	unsigned char* _internal_buffer;
	int _internal_buffer_size;
	
	/** @see ostream_decoding_type */
	int _decoding_type;
	
	/** Frames Per Second */
	int _fps;
	
	/** @see ffmpeg doc for this struct */
	AVCodec *_codec_decode;
	
	/** @see ffmpeg doc for this struct */	
	AVCodecContext *_codec_context;
	
	/** @see ffmpeg doc for this struct */	
	AVFrame *_decoded_frame;
	
	/** @see ffmpeg doc for this struct */	
	AVFrame *_opencv_ready_frame;
	
	struct SwsContext *sws_ctx;
	/** @see ffmpeg doc for this struct */	
	PixelFormat _opencv_pix_fmt;
};


#endif	//_OSTREAMVIDEODECODER_H_

