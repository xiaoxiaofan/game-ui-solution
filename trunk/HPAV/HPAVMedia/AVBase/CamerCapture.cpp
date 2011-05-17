#include "StdAfx.h"
#include "CamerCapture.h"
#include "kbase\AutoLock.h"


CCamerCapture::CCamerCapture(IMXEC_CapChanCallback& capChanHandle)
	:CAVCapture(capChanHandle)
{

}


CCamerCapture::~CCamerCapture(void)
{

}

int CCamerCapture::OpenVideo( PLBVideoSet videoSet )
{
	m_pVideoSet = videoSet;

	CString str;
	str.Format(_T("CAVCapture::OpenCamerVideo:nDevID=%d, m_nVideoWidth=%d, m_nVideoHeight=%d, nFrameRate=%d, nBitrate=%d, nBitrateControlType=%d, CodecType=%d\n"), 
		m_pVideoSet->nVideoDev , m_nVideoWidth, m_nVideoHeight, m_pVideoSet->nFrameRate, m_pVideoSet->nBitrate, m_pVideoSet->nBitrateControlType, m_pVideoSet->nVideoCodec);
	OutputDebugString(str);

	int nResult = m_pCapChanDev->OpenVideoDev(m_pVideoSet->nVideoDev, m_nVideoWidth, m_nVideoHeight, m_pVideoSet->nFrameRate,  m_pVideoSet->nBitrate,  m_pVideoSet->nBitrateControlType, (VIDEC_CODEC_TYPE) m_pVideoSet->nVideoCodec);

	return nResult;
}


bool CCamerCapture::StartRecord( void )
{
	if (m_pAVRecord == NULL)
	{
		m_pAVRecord = new CAVRecord(*this);
		m_pAVRecord->Initlize();
	}

	BOOL bRecord = m_pAVRecord->StartRecord();
	if (bRecord)
	{
		SetForceEncodeVideo(1);
		SetForceEncodeAudio(1);
	}

	return bRecord;
}

void CCamerCapture::StopRecord( void )
{
	if (m_pAVRecord)
	{
		if (IsRecording())
		{
			SetForceEncodeVideo(-1);
			SetForceEncodeAudio(-1);
		}
		KAutoLock l(m_csAVRecord);
		m_pAVRecord->StopRecord();
		m_pAVRecord->Release();
		delete m_pAVRecord;
		m_pAVRecord = NULL;
	}
}

bool CCamerCapture::IsRecording( void )
{
	if (m_pAVRecord)
	{
		return m_pAVRecord->IsRecording();
	}
	return false;
}