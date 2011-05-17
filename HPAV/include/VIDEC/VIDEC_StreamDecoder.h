//VIDEC_StreamDecoder.h
#ifndef __VIDEC_STREAMDECODER_H__
#define __VIDEC_STREAMDECODER_H__

#include "VIDEC_Export.h"

class VIDEC_API VIDEC_StreamDecoder
{
public:
	VIDEC_StreamDecoder(void){};
	virtual~VIDEC_StreamDecoder(void){};
public:
	//�򿪽�����
	//�ɹ�����0�����򷵻�-1
	virtual int Open(void)=0;
	//�رս�����
	virtual void Close(void)=0;
	//���룬�����PacketData�Ǻ���VIDEC����ͷ������
	//���YUV[4:2:0]��ͼ���ͼ��Ŀ�͸�
	//�ɹ�����0�����򷵻�-1
	virtual int Decode(void*pPacketData,int nPacketLen,void**ppYUVData,int&nWidth,int&nHeight)=0;
	//����������
	static VIDEC_StreamDecoder*Create(void);
};

#endif
