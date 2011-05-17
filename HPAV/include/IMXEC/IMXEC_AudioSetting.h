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
	*描述：设置主流视频设备参数
	*输入： nAudioCodecID		-音频编码
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetAudioDevParam(X_AUDIO_CODEC_ID nAudioCodecID);
};

#endif
