//
// CDESMediaDetector.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESMediaDetector__
#define __H_CDESMediaDetector__

class CDESMediaDetector
{
private:
	IMediaDet *        mDetector;

public:
	CDESMediaDetector();
	~CDESMediaDetector();

	bool Initialize(void);  // Must be invoked!!

	bool put_Filename(const char * inFileName);
	bool get_Filename(char * outFileName);
	bool put_Filter(IUnknown * inSourceFilter);
	bool get_Filter(IUnknown ** outSourceFilter);
	bool put_CurrentStream(long inStreamIndex);
	bool get_CurrentStream(long * outStreamIndex);
	bool get_OutputStreams(long * outStreamCount);
	bool get_StreamLength(double * outLength);
	bool get_StreamType(GUID * outType);
	bool get_StreamTypeB(BSTR * outType);
	bool get_StreamMediaType(AM_MEDIA_TYPE * outMediaType);
	bool get_FrameRate(double * outFrameRate);

	bool EnterBitmapGrabMode(double inStreamTime);
	bool GetSampleGrabber(ISampleGrabber ** outGrabber);
	bool GetBitmapBits(double inStreamTime, long * outBufferSize, 
		char * ioBuffer, long inWidth, long inHeight);
	bool WriteBitmapBits(double inStreamTime, long inWidth, 
		long inHeight, const char * inFilename);
};

#endif // __H_CDESMediaDetector__