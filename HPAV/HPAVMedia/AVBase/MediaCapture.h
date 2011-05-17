#pragma once
#include "AVCapture.h"

class CMediaCapture : public CAVCapture
{
public:
	CMediaCapture(IMXEC_CapChanCallback& capChanHandle);
	~CMediaCapture(void);

	int OpenMediaVideo(const char*cszMediaFile, int nLoop, int nBitrate, int nBitrateControlType, VIDEC_CODEC_TYPE CodecType);
};

