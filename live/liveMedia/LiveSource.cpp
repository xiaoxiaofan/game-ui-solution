#include "LiveSource.h"
#include <memory.h>
#include <yvals.h>


LiveSource::LiveSource(void)
{
	fTo = new unsigned char[400000];
	fSize = 0;
	_internal_buffer = new unsigned char[40000];
	sws_ctx = NULL;
	
	initialize();
}


LiveSource::~LiveSource(void)
{

}

void LiveSource::setData( unsigned char* pData,int nSize )
{
	

	AVCodecContext *codec_context;

	if ( _frame == NULL ) {
		_frame = create_avframe( 15,600,400);
	}

	_frame->data[0] = (uint8_t*)pData;

	avpicture_fill((AVPicture *)_frame,(uint8_t *)pData,(PixelFormat)15,600,400);

	codec_context = _video_stream->codec;

	if (sws_ctx==NULL){
		sws_ctx=sws_getContext(600,400,
			(PixelFormat)15,codec_context->width,codec_context->height,
			codec_context->pix_fmt,SWS_FAST_BILINEAR,NULL, NULL, NULL);
	}

	long len = sws_scale(sws_ctx,((AVPicture *)_frame)->data,((AVPicture *)_frame)->linesize, 0,
		400, ((AVPicture *)_ready_to_encode_frame)->data, ((AVPicture *)_ready_to_encode_frame)->linesize);

	int currentSize = avcodec_encode_video( codec_context, _internal_buffer, 40000, 
		_ready_to_encode_frame );


	memcpy(fTo + fSize,_internal_buffer,currentSize);

	fSize += currentSize;	

	if (fSize > 300000)
	{
		std::_Mutex mutex;
		mutex._Lock();
		delete fTo;
		fTo = new unsigned char[400000];
		fSize = 0;
		mutex._Unlock();
	}
}

void LiveSource::getData( unsigned char* pData )
{
	std::_Mutex mutex;
	mutex._Lock();
	memcpy(pData,fTo,fSize);
	fSize = 0;
	mutex._Unlock();
}

AVFrame* LiveSource::create_avframe( int pixel_format, int width,int height )
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
	avpicture_fill((AVPicture *)frame, picture_buf,(PixelFormat) pixel_format, width, height );
	return frame;
}

AVStream* LiveSource::create_video_stream( AVFormatContext *io_fmt_context, int codec_id )
{
	AVCodecContext *codec_context;
	AVStream *stream;

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

	codec_context->width = 600;
	codec_context->height = 400;
	codec_context->time_base.den = 25;
	codec_context->time_base.num = 1;

	// intra frame sending every twelve frames
	codec_context->gop_size = 12; 


	codec_context->pix_fmt = PIX_FMT_YUV420P; 

	return stream;
}

bool LiveSource::initialize()
{
	
	av_register_all();
	char *encoding_str ="h263";
	_out_fmt = guess_format ( encoding_str, NULL, NULL);

	if( !_out_fmt ) {
		//				DEBUG_PRINT( "Could not find suitable output format.\n");
		return false;
	}

	// specify the sub-codec we want to use. Without this we won't be able
	// to stream H263P not use 640x480 videos
	_out_fmt->video_codec = CODEC_ID_H263P;

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
	_ready_to_encode_frame = create_avframe( _video_stream->codec->pix_fmt,600,400 );
	if ( !_ready_to_encode_frame ) {
		//        DEBUG_PRINT( "Could not allocate encoded_frame\n" );
		return false;
	}

	// we'll receive IplImage(s). This _opencv_frame will be converted to a stream-compatible
	// AVFrame [see up _ready_to_encode_frame]
	_frame = NULL;


	return true;
}

bool LiveSource::open_codec( AVStream *stream )
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
