#ifndef DESGroup_h__
#define DESGroup_h__

#include "DESComposition.h"

class CDESSource;

class AFX_EXT_CLASS CDESGroup : public CDESComposition
{
public:
	CDESGroup(CDESTimeLine * inTimeLine);
	~CDESGroup(void);

	bool GetTimeline(CDESTimeLine & outTimeLine);
	bool GetPriority(long * outPriority);

	bool SetMediaType(AM_MEDIA_TYPE * inMediaType);
	bool GetMediaType(AM_MEDIA_TYPE * outMediaType);

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

	bool SetGroupName(BSTR inGroupName);
	bool GetGroupName(BSTR * outGroupName);

protected:
	virtual bool QueryExtraInterfaces(void);
	virtual void ReleaseExtraInterfaces(void);

private:
	void ReleaseSelf(void);
	virtual bool CreateInstance(void);

private:
	BOOL				m_IsVideoGroup;
	IAMTimelineGroup *	m_pInterfaceGroup;

};

#endif // DESGroup_h__


