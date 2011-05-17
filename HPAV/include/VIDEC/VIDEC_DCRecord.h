//VIDEC_DCRecord.h
#ifndef __VIDEC_DCRECORD_H__
#define __VIDEC_DCRECORD_H__

#include "VIDEC_Export.h"

class VIDEC_API VIDEC_DCRecord
{
public:
	VIDEC_DCRecord(void){};
	virtual~VIDEC_DCRecord(void){};
public:
	//��
	//HDC hDC:Ҫ�ɼ���DC
	//int x,int y,int cx,int cy:Ҫ�ɼ�������x,y��λ�ƣ�cx,xy�ǿ��
	virtual int Open(HDC hDC,int x,int y,int cx,int cy,const char*cszPathName,int nFrameRate=5,int nQuality=3,int nBitrateControlType=VIDEC_BITRATE_CONTROL_CQP)=0;
	//�ر�
	virtual void Close(void)=0;
	//�ɼ�һ֡
	virtual void CaptureFrame(void)=0;
	//�Ƿ�ѹ�����
	virtual bool IsDone(void)=0;

	//��������
	static VIDEC_DCRecord*Create(void);
};

#endif