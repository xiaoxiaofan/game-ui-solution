#include "StdAfx.h"
#include "MediaCapture.h"


CMediaCapture::CMediaCapture(IMXEC_CapChanCallback& capChanHandle)
	:CAVCapture(capChanHandle)
{
}


CMediaCapture::~CMediaCapture(void)
{
}

int CMediaCapture::OpenMediaVideo( const char*cszMediaFile, int nLoop, int nBitrate, int nBitrateControlType, VIDEC_CODEC_TYPE CodecType )
{
	/*
	CString str;
		str.Format(_T("CMediaCapture::OpenMdeiaVideo:MediaFile=%s, nLoop=%d, nBitrate=%d, nBitrateControlType=%d, CodecType=%d, nSub=%d, nQSub=%d\n"), 
			CA2W(cszMediaFile.c_str()), nLoop, nBitrate, nBitrateControlType, CodecType, nSub, nQSub);
		OutputDebugStr(str);*/
	int nResult = -1;
	if (m_pCapChanDev)
	{
		nResult = m_pCapChanDev->OpenVideoDev(cszMediaFile, nLoop, nBitrate, nBitrateControlType, CodecType);
	}
	
    return nResult;
}
