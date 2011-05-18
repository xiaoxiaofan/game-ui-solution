#ifndef LiveSource_h__
#define LiveSource_h__
#include "singleton.hpp"
extern "C" {
#include "libavcodec\avcodec.h"
#include "libavformat\avformat.h"
#include "libswscale\swscale.h"
}

class LiveSource : public SGT::Singleton<LiveSource>
{
public:
	LiveSource(void);
	~LiveSource(void);

	void setData(unsigned char* pData,int nSize);

	void getData(unsigned char* pData);

private:
	AVFrame* create_avframe( int pixel_format, int width,int height );
	AVStream* create_video_stream( AVFormatContext *io_fmt_context, int codec_id );
	bool initialize();
	bool open_codec( AVStream *stream );


private:
	unsigned char* fTo;
	int fSize;
	AVFrame *_frame;
	struct SwsContext *sws_ctx;
	AVOutputFormat *_out_fmt;
	AVFormatContext *_out_fmt_context;
	AVStream *_video_stream;
	AVFrame *_ready_to_encode_frame;

	unsigned char* _internal_buffer;
};


#endif // LiveSource_h__

