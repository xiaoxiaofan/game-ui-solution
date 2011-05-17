#pragma once

typedef struct HPLB_VideoSet
{
	int	nVideoDev;				//��Ƶ�豸
	int	nVideoCodec;			//��Ƶ������
	int	nResolution;			//�ֱ���
	int	nFrameRate;				//ͼ��֡��
	int	nBitrate;			    //������
	int	nBitrateControlType;	//�������Ʒ�ʽ
}LBVideoSet, *PLBVideoSet;

typedef struct HPLB_AudioSet
{
	int	nAudioDev;				//��Ƶ�豸
	int	nAudioCodec;			//��Ƶ������
	int	nAudioInType;			//��Ƶ��������
}LBAudioSet, *PLBAudioSet;
