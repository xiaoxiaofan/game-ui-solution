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


#include "OStreamVideoEncoder.hh"


OStreamVideoEncoder::OStreamVideoEncoder( unsigned int io_buf_size, ostream_encoding_type encoding_type,
						 				  int video_width, int video_height, 
						 				  int fps /* = 25 */,
										  PixelFormat opencv_pix_fmt /*= PIX_FMT_BGR24*/) : 
									_internal_buffer_size( io_buf_size ),
									_encoding_type( encoding_type ),
									_video_width( video_width ), 
									_video_height( video_height ),
									_fps( fps ),
									_opencv_pix_fmt( opencv_pix_fmt )
{
	_initialized = false;
	if ( io_buf_size <= 1 ) {
//		DEBUG_PRINT ("io_buf_size is wrong\n.");
		return;
	}
	
	// allocate the internal buffer
	_internal_buffer = new unsigned char[_internal_buffer_size];
	sws_ctx = NULL;
	
	if ( encoder_initialize () == true ) {;
		_initialized = true;
	}
}

OStreamVideoEncoder::~OStreamVideoEncoder()
{
	// FIXME: destroy
	if ( _internal_buffer )
		delete _internal_buffer;

// etc
//		avcodec_close(c);
//		av_free(c);
	
}

bool OStreamVideoEncoder::open_codec( AVStream *stream )
{
    AVCodec *codec;
    AVCodecContext *codec_context;

    codec_context = stream->codec;

    // NB: codec = AVCodec
    codec = avcodec_find_encoder( codec_context->codec_id );
    if ( !codec ) {
//       	DEBUG_PRINT ("codec not found\n");
		return false;
    }

    // lets open the codec
    if ( avcodec_open( codec_context, codec ) < 0 ) {
		return false;
    }
	
	return true;
}

AVFrame* OStreamVideoEncoder::create_avframe( int pixel_format, int width,int height )
{
    AVFrame *frame;
    unsigned char *picture_buf;
    int pic_size;
    
    frame = avcodec_alloc_frame ();
    if ( !frame )
        return NULL;
	
    pic_size = avpicture_get_size( (PixelFormat)pixel_format, width, height );
    picture_buf = (unsigned char*)calloc( pic_size, sizeof(unsigned char) );
    
	if ( !picture_buf ) {
        av_free( frame );
        return NULL;
    }
	
	// lets fill picture with the picture_buf just created
    avpicture_fill((AVPicture *)frame, picture_buf, (PixelFormat)pixel_format, width, height );
    return frame;
}


AVStream* OStreamVideoEncoder::create_video_stream( AVFormatContext *io_fmt_context, int codec_id )
{
    AVCodecContext *codec_context;
    AVStream *stream;

	// create a new stream given AVFormatContext [which in this case is set to
	// output]
	// With this call it's allocated also c = st->codec, the codec_context
    stream = av_new_stream( io_fmt_context, 0 );
    if ( !stream ) {
//        DEBUG_PRINT ("Could not alloc stream\n");
		return NULL;
    }
    
    // AVCodecContext is a member of AVStream!
    // now we'll setup the parameters of AVCodecContext
    codec_context = stream->codec;
    codec_context->codec_id = (CodecID)codec_id;
    codec_context->codec_type = CODEC_TYPE_VIDEO;


    // sample parameters
    codec_context->bit_rate = 400000;
	
    codec_context->width = _video_width;
    codec_context->height = _video_height;
    codec_context->time_base.den = _fps;
    codec_context->time_base.num = 1;
	
	// intra frame sending every twelve frames
    codec_context->gop_size = 12; 

	switch ( _encoding_type ) {
    	case OSTREAM_ENCODING_MJPEG:
			codec_context->pix_fmt = PIX_FMT_YUVJ420P; 
			break;
		
		case OSTREAM_ENCODING_H263P:
		    codec_context->pix_fmt = PIX_FMT_YUV420P; 
			break;
		
		default:
			codec_context->pix_fmt = PIX_FMT_YUVJ420P;
			break;
	}

    return stream;
}

bool OStreamVideoEncoder::encoder_initialize () 
{
	char *encoding_str;
	// register all codecs
	av_register_all();
	
	switch ( _encoding_type ) {
		case OSTREAM_ENCODING_MJPEG:
			encoding_str = "mjpeg";
			_out_fmt = guess_format ( encoding_str, NULL, NULL);
		
			if( !_out_fmt ) {
//				DEBUG_PRINT( "Could not find suitable output format.\n");
				return false;
			}
		
			break;
		
		case OSTREAM_ENCODING_H263P:
			encoding_str ="h263";
			_out_fmt = guess_format ( encoding_str, NULL, NULL);
		
			if( !_out_fmt ) {
//				DEBUG_PRINT( "Could not find suitable output format.\n");
				return false;
			}

			// specify the sub-codec we want to use. Without this we won't be able
			// to stream H263P not use 640x480 videos
			_out_fmt->video_codec = CODEC_ID_H263P;
		
			break;
		
		default:
//			DEBUG_PRINT ("could not find known OSTREAM_ENCODING type.\n" );
			break;
	}

	_out_fmt_context = av_alloc_format_context ();
	if( !_out_fmt_context ) {
//		DEBUG_PRINT( "Memory error.\n" );
		return false;
	}
	
	// set output format of AVFormatContext
	_out_fmt_context->oformat = _out_fmt;

	// check if we had a correct video_codec 
    if ( _out_fmt->video_codec == CODEC_ID_NONE ) {
//    	DEBUG_PRINT( "CODEC_ID_NONE\n" );
		return false;
	}
	
	// add the stream
	if(!( _video_stream = create_video_stream( _out_fmt_context, _out_fmt->video_codec ) )) {
//		DEBUG_PRINT( "error in adding stream\n" );
		return false;
	}

    // set the output parameters (must be done even if no parameters)
    if ( av_set_parameters( _out_fmt_context, NULL ) < 0 ) {
//        DEBUG_PRINT( "Invalid output format parameters\n" );
        return false;
    }

	// open codec associated with current video_stream
	if ( !open_codec( _video_stream ) ) {
//        DEBUG_PRINT( "could not open codec\n" );		
		return false;
	}
		
	// we should now create the frame on which we can store the converted bytes
	// ready to be encoded
	_ready_to_encode_frame = create_avframe( _video_stream->codec->pix_fmt,this->_video_width,this->_video_height );
    if ( !_ready_to_encode_frame ) {
//        DEBUG_PRINT( "Could not allocate encoded_frame\n" );
		return false;
    }

	// we'll receive IplImage(s). This _opencv_frame will be converted to a stream-compatible
	// AVFrame [see up _ready_to_encode_frame]
	_opencv_frame = NULL;
	
	
	return true;
}
 

const unsigned char* OStreamVideoEncoder::encode_video_frame( IplImage *image, int *out_size )
{
    AVCodecContext *codec_context;
	*out_size = 0;
	
	if ( image == NULL )
		return NULL;
	
	if ( !_initialized ) {
//		DEBUG_PRINT( "initializing class failed.\n" );
		return NULL;
	}

	if( image->imageSize > _internal_buffer_size ) {
//		DEBUG_PRINT( "image_size too big.\n" );
		return NULL;
	}

	
    if ( _opencv_frame ==NULL ) {
		_opencv_frame = create_avframe( _opencv_pix_fmt,image->width,image->height );
	}
	
	codec_context = _video_stream->codec;

	// this is an hack. We just assign the pointer image->imageData to
	// _opencv_frame->data[0] without using a memcpy. This should speed the things up.
	_opencv_frame->data[0] = (uint8_t*)image->imageData;

	avpicture_fill((AVPicture *)_opencv_frame,(uint8_t*)image->imageData,_opencv_pix_fmt,image->width,image->height);

	
	if (sws_ctx==NULL){
		sws_ctx=sws_getContext(image->width,image->height,
			_opencv_pix_fmt,codec_context->width,codec_context->height,
			codec_context->pix_fmt,SWS_FAST_BILINEAR,NULL, NULL, NULL);
	}

	long len = sws_scale(sws_ctx,((AVPicture *)_opencv_frame)->data,((AVPicture *)_opencv_frame)->linesize, 0,
		image->height, ((AVPicture *)_ready_to_encode_frame)->data, ((AVPicture *)_ready_to_encode_frame)->linesize);
	/*/
	int img_convert(AVPicture *dst, int dst_pix_fmt,
    	            const AVPicture *src, int pix_fmt,
        	        int width, int height);
	/*/    
   // img_convert( (AVPicture *)_ready_to_encode_frame, codec_context->pix_fmt, 
	//			(AVPicture *)_opencv_frame, _opencv_pix_fmt, codec_context->width, 
	//			codec_context->height );
	/*/
	int avcodec_encode_video(AVCodecContext *avctx, uint8_t *buf, int buf_size,
                         	const AVFrame *pict);
	/*/
    // encode the image
    *out_size = avcodec_encode_video( codec_context, _internal_buffer, _internal_buffer_size, 
									 _ready_to_encode_frame );

	return _internal_buffer;
}

