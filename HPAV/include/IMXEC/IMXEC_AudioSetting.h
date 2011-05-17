//IMXEC_AudioSetting.h
#ifndef __IMXEC_AUDIO_SETTING_H__
#define __IMXEC_AUDIO_SETTING_H__

#include <IMXEC/IMXEC_Export.h>
#include <AUDEC/AUDEC_CodecID.h>
#include <winsock2.h>
#include <windows.h>

class IMXEC_API IMXEC_AudioSetting
{
public:
	IMXEC_AudioSetting(void);
	virtual~IMXEC_AudioSetting(void);
public:
	/******************************************************************************
	* SetAudioDevParam
	*����������������Ƶ�豸����
	*���룺 nAudioCodecID		-��Ƶ����
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetAudioDevParam(X_AUDIO_CODEC_ID nAudioCodecID);
};

#endif
