#pragma once

typedef struct HPLB_VideoSet
{
	int	nVideoDev;				//视频设备
	int	nVideoCodec;			//视频编码器
	int	nResolution;			//分辨率
	int	nFrameRate;				//图像帧率
	int	nBitrate;			    //比特率
	int	nBitrateControlType;	//码流控制方式
}LBVideoSet, *PLBVideoSet;

typedef struct HPLB_AudioSet
{
	int	nAudioDev;				//音频设备
	int	nAudioCodec;			//音频编码器
	int	nAudioInType;			//音频输入类型
}LBAudioSet, *PLBAudioSet;
