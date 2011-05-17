//IMXEC_VideoSetting.h
#ifndef __IMXEC_VIDEO_SETTING_H__
#define __IMXEC_VIDEO_SETTING_H__

#include <IMXEC/IMXEC_Export.h>
#include <VIDEC/VIDEC.h>
#include <VIDEC/VIDEC_CodecDef.h>

typedef enum {
	VIDEO_FORMAT_QCIF=0,
	VIDEO_FORMAT_CIF,
	VIDEO_FORMAT_4CIF,
	VIDEO_FORMAT_16CIF,
	VIDEO_FORMAT_720I,
	VIDEO_FORMAT_720P,
	VIDEO_FORMAT_1080I,
	VIDEO_FORMAT_1080P,
	VIDEO_FORMAT_QVGA,
	VIDEO_FORMAT_VGA,
	VIDEO_FORMAT_SVGA,
	VIDEO_FORMAT_XGA,
	VIDEO_FORMAT_SXGA,
	VIDEO_FORMAT_COUNT
}VIDEO_FORMAT_TYPE;


class IMXEC_API IMXEC_VideoSetting
{
public:
	IMXEC_VideoSetting(void);
	virtual~IMXEC_VideoSetting(void);
public:
	/******************************************************************************
	* SetMainVideoDevParam
	*����������������Ƶ�豸����
	*���룺 nDevID				-�豸��ʶ
			nFrameRate			-֡��
			nBitrate			-����
			nVideoCodecType		-��Ƶ����
			nVideoFormatType	-��Ƶ��ʽ
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetMainVideoDevParam(int nDevID,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE nVideoCodecType,VIDEO_FORMAT_TYPE nVideoFormatType);

	/******************************************************************************
	* SetSecondVideoDevParam
	*���������ø�����Ƶ�豸����
	*���룺 nDevID				-�豸��ʶ
			nFrameRate			-֡��
			nBitrate			-����
			nVideoCodecType		-��Ƶ����
			nVideoFormatType	-��Ƶ��ʽ
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetSecondVideoDevParam(int nDevID,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE nVideoCodecType,VIDEO_FORMAT_TYPE nVideoFormatType);
};

#endif
