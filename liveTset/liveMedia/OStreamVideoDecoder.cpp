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


#include "OStreamVideoDecoder.hh"


OStreamVideoDecoder::OStreamVideoDecoder( unsigned int io_buf_size, ostream_decoding_type decoding_type,
										 int fps /* = 25 */,
										 PixelFormat opencv_pix_fmt /*= PIX_FMT_BGR24*/) :
_internal_buffer_size( io_buf_size ),
_decoding_type( decoding_type ),
_fps( fps ),
_opencv_pix_fmt( opencv_pix_fmt )

{
	_initialized = false;
	sws_ctx = NULL; 
	_opencv_ready_frame = NULL;
	if ( io_buf_size <= 1 ) {
		//		DEBUG_PRINT ("io_buf_size is wrong\n.");
		return;
	}

	// allocate the internal buffer
	_internal_buffer = new unsigned char[_internal_buffer_size];

	if ( decoder_initialize () == true ) {
		_initialized = true;
	}
}


OStreamVideoDecoder::~OStreamVideoDecoder()
{
	if ( _internal_buffer )
		delete _internal_buffer;

	avcodec_close( _codec_context );
}


bool OStreamVideoDecoder::decoder_initialize ()
{
	// register all codecs
	av_register_all();

	switch ( _decoding_type ) {
		case OSTREAM_DECODING_MJPEG:
			_codec_decode = avcodec_find_decoder( CODEC_ID_MJPEG );
			break;

		case OSTREAM_DECODING_H263P:
			// decoder for h263+ is identified with CODEC_ID_H263
			_codec_decode = avcodec_find_decoder( CODEC_ID_H263 );
			break;

		default:
			//			DEBUG_PRINT ("could not find known OSTREAM_DECODING type.\n" );
			break;
	}

	if ( !_codec_decode ) {
		//    	DEBUG_PRINT( "codec for decoding not found\n" );
		return false;
	}

	_codec_context = avcodec_alloc_context();
	
	/*_codec_context->qmin =2;
	_codec_context->bit_rate = (float)500000*0.7;  
	_codec_context->bit_rate_tolerance=(float)_codec_context->bit_rate/(14);
	_codec_context->time_base.den = 15; 
	_codec_context->time_base.num =1; 
	_codec_context->gop_size = 15*5; */

	_codec_context->width=176;
	_codec_context->height=144;
	_decoded_frame = avcodec_alloc_frame();


	// open it
	if ( avcodec_open( _codec_context, _codec_decode ) < 0 ) {
		//        DEBUG_PRINT( "could not open codec\n" );
		return false;
	}


	return true;
}

AVFrame* OStreamVideoDecoder::create_avframe( int pixel_format, int frame_width, int frame_height )
{
	AVFrame *frame;
	unsigned char *picture_buf;
	int pic_size;

	frame = avcodec_alloc_frame ();
	if ( !frame )
		return NULL;

	pic_size = avpicture_get_size( pixel_format, frame_width, frame_height );
	picture_buf = (unsigned char*)calloc( pic_size, sizeof(unsigned char) );

	if ( !picture_buf ) {
		av_free( frame );
		return NULL;
	}

	// lets fill picture with the picture_buf just created
	avpicture_fill((AVPicture *)frame, picture_buf, pixel_format, frame_width, frame_height );
	return frame;
}

IplImage* OStreamVideoDecoder::decode_video_frame( unsigned char* buf, int buf_size )
{
	int err_status;
	int got_decoded_frame_size;
	IplImage *ipl_image = NULL;

	/* int avcodec_decode_video(AVCodecContext *avctx, AVFrame *picture,
	int *got_picture_ptr,
	uint8_t *buf, int buf_size); */

	err_status = avcodec_decode_video( _codec_context, _decoded_frame, &got_decoded_frame_size,
		buf, buf_size );
	if ( err_status < 0) {
		//    	DEBUG_PRINT( "Error while decoding frame.");
		return NULL;
	}

	// check whether the space for a decoded frame is already allocated or not
	// we should perform this operation just once, and just the first time.
	if ( _opencv_ready_frame == NULL) {
		// this is where a _decoded_frame will be converted.
		// the pixel format shoud be compatible with IplImages obviously
		_opencv_ready_frame = create_avframe( _opencv_pix_fmt, _codec_context->width,
			_codec_context->height );
	}

	if ( got_decoded_frame_size ) {
		switch ( _decoding_type ) {
			case OSTREAM_DECODING_MJPEG:

				if (sws_ctx==NULL){
					sws_ctx=sws_getContext(_codec_context->width,_codec_context->height,
						PIX_FMT_YUVJ420P,_codec_context->width,_codec_context->height,
						_opencv_pix_fmt,SWS_FAST_BILINEAR,NULL, NULL, NULL);
				}


				break;

			case OSTREAM_DECODING_H263P:
				if (sws_ctx==NULL){
					sws_ctx=sws_getContext(_codec_context->width,_codec_context->height,
						PIX_FMT_YUV420P,_codec_context->width,_codec_context->height,
						_opencv_pix_fmt,SWS_FAST_BILINEAR,NULL, NULL, NULL);
				}

				break;

			default:
				//				DEBUG_PRINT ("img_convert doesn't know what to do.\n" );
				break;
		}
		long len = sws_scale(sws_ctx,((AVPicture *)_decoded_frame)->data,((AVPicture *)_decoded_frame)->linesize, 0,
			_codec_context->height, ((AVPicture *)_opencv_ready_frame)->data, ((AVPicture *)_opencv_ready_frame)->linesize);
		// the cvSetData function doesn't do what we want here. It just set the _opencv_ready_frame pointer
		// to the just created ipl_image header. But we want a clean and new allocated ipl_image, so 
		// use the old good memcpy to store the data, and bye bye cv*Data friends.
		ipl_image = cvCreateImage( cvSize( _codec_context->width, _codec_context->height ), IPL_DEPTH_8U, 3 );
		memcpy( ipl_image->imageData, _opencv_ready_frame->data[0], ipl_image->imageSize );
		ipl_image->widthStep = _opencv_ready_frame->linesize[0];
	}

	return ipl_image;
}




