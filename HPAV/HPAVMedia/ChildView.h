
// ChildView.h : CChildView ��Ľӿ�
//


#pragma once
#include "AVBase\AVCapture.h"
#include "AVBase\AVPlayer.h"
#include "AVBase\CamerCapture.h"


// CChildView ����

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:
	CCamerCapture*			m_pCamCaptrue;
	CAVPlayer*				m_pAVPalyer;
	CAVCapture*             m_avCap;
	unsigned long           theadHandle;
// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCapture();
	afx_msg void OnRecord();
	afx_msg void OnCompose();
};
