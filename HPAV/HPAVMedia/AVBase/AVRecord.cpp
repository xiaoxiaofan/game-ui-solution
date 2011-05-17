#include "stdafx.h"
#include "AVRecord.h"
#include <AVCRecord.h>
#include <videc/VIDEC.h>
#include <videc/VIDEC_Header.h>
#include <AVCFileDefine.h>
#include <audec/AUDEC_Header.h>
#include <KRTL32/Func.h>
#include <kbase/AutoLock.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CAVRecord::CAVRecord(CAVRecordNotify& rNotify)
	: m_rNotify(rNotify)
	, m_bRecording(false)
{

}

CAVRecord::~CAVRecord(void)
{
}

void CAVRecord::Initlize(void)
{

}

void CAVRecord::Release(void)
{

}

// 判断是否支持录制为AVI
BOOL CAVRecord::CanRecordToAVI(unsigned char *pData)
{
	VIDEC_CODEC_TYPE type = (VIDEC_CODEC_TYPE)VIDEC_HEADER_EXT_GET_CODEC_ID((void*)pData);

	if( type == VIDEC_CODEC_HIKH || type == VIDEC_CODEC_AH400 || type == VIDEC_CODEC_DH264)
	{
		return FALSE;
	}

	return TRUE;
}

// 开始录像
BOOL CAVRecord::StartRecord(void)
{
	if (IsRecording())
	{
		return TRUE;
	}

	CString recordName;
	SYSTEMTIME systime;
	GetLocalTime(&systime);
	recordName.Format(_T("%4d%02d%02d%02d%02d%02d"),systime.wYear, systime.wMonth, systime.wDay,systime.wHour,systime.wMinute,systime.wSecond);
	CString recordPath;
	recordPath += _T("C:\\");
	recordName += _T(".avi");
	bool bRecord;
	bRecord = m_rNotify.StartRecordToAVI(CW2A(recordPath + recordName), 1);
	m_bRecording = bRecord;
	return bRecord;
}

// 停止录像
void CAVRecord::StopRecord()
{
	m_rNotify.StopRecordToAVI();
	m_bRecording = false;

}

bool CAVRecord::IsRecording() const
{
	return m_bRecording;
}


void CAVRecord::ChangeRecordType(unsigned char*pPacketData, int nPacketLen)
{
	if (!IsRecording())
	{
		return;
	}

	bool bKeyFrame = VIDEC_HEADER_EXT_GET_KEYFRAME((void*)pPacketData);
	if(!bKeyFrame)
	{
		return;
	}
	return;
}