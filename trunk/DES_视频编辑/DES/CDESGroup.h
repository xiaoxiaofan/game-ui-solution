//
// CDESGroup.h
//
//
// DirectShow Editing Services Demo Application, by Qiming Lu
//     You can use these source codes without any limitations.
//     Send your feedback to me if you'd like to :)
//     Blog: http://jemylu.spaces.live.com/
//     Post Center: http://post.baidu.com/f?kw=%C2%BD%C6%E4%C3%F7
//     Messager: luqiming26@hotmail.com
//

#ifndef __H_CDESGroup__
#define __H_CDESGroup__

#include "CDESComposition.h"

class CDESSource;
class CDESGroup : public CDESComposition
{
private:
	BOOL                 mIsVideoGroup;
	IAMTimelineGroup *   mInterfaceGroup;

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

public:
	CDESGroup(CDESTimeLine * inTimeLine);
	~CDESGroup();

	bool GetTimeline(CDESTimeLine & outTimeLine);
	bool GetPriority(long * outPriority);

	bool SetMediaType(AM_MEDIA_TYPE * inMediaType);
	bool GetMediaType(AM_MEDIA_TYPE * outMediaType);
	// An easy way to set group type
	bool SetGroupType(BOOL inIsVideo);
	bool GetGroupType(BOOL * outIsVideo);

	bool SetOutputFPS(double inFPS);
	bool GetOutputFPS(double * outFPS);
	bool SetPreviewMode(BOOL inIsPreview);
	bool GetPreviewMode(BOOL * outIsPreview);
	bool SetOutputBuffering(int inBufferCount);
	bool GetOutputBuffering(int * outBufferCount);

	bool SetSmartRecompressFormat(long * inFormat);
	bool GetSmartRecompressFormat(long ** outFormat);
	bool IsSmartRecompressFormatSet(BOOL * outIsSmart);
	bool SetRecompFormatFromSource(CDESSource & inSource);

	// Application-defined information
	bool SetGroupName(BSTR inGroupName);
	bool GetGroupName(BSTR * outGroupName);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);
};

#endif // __H_CDESGroup__