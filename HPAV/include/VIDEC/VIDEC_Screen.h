//VIDEC_Screen.h
#ifndef __VIDEC_SCREEN_H__
#define __VIDEC_SCREEN_H__

#include "VIDEC_Export.h"
#include "VIDEC.h"

class VIDEC_API VIDEC_Screen
	: public VIDEC_CapDev
{
public:
	VIDEC_Screen(void){};
	virtual~VIDEC_Screen(void){};
public:
	virtual int Open(int x,int y,int cx,int cy,int nFrameRate/*0-30|0:Manual*/,int nBitCount/*16|24|32*/)=0;
	virtual void Close(void)=0;
	virtual int Reset(int x,int y,int cx,int cy,int nFrameRate/*0-30|0:Manual*/,int nBitCount/*16|24|32*/)=0;

	virtual int Move(int x,int y)=0;
	virtual int GetRect(int& x,int& y,int& cx,int& cy)=0;
	virtual int EnableCursor(bool bEnable=true)=0;

	virtual int RequestFrame(void)=0;

	/******************************************************************************
	* SetScreenWnd
	*����������������Ļ����λ��
	*���룺	nScreenIndex	-��Ļ��
			nWndIndex		-���ں�
			nFullScreen		-�Ƿ�ȫ����ʾ��0����ͨ��ʾ����0��ȫ����ʾ��
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void SetScreenWnd(int nScreenIndex,int nWndIndex,int nFullScreen)=0;

	static VIDEC_Screen*Create(void);
};

#endif
