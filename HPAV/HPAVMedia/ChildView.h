
// ChildView.h : CChildView 类的接口
//


#pragma once
#include "AVBase\AVCapture.h"
#include "AVBase\AVPlayer.h"
#include "AVBase\CamerCapture.h"
#include "VideoDevice.h"


// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 特性
public:
	CCamerCapture*			m_pCamCaptrue;
	CAVPlayer*				m_pAVPalyer;
	CAVCapture*             m_avCap;
	unsigned long           theadHandle;
	CVideoDevice*           videoDev;
// 操作
public:

// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCapture();
	afx_msg void OnRecord();
	afx_msg void OnCompose();
	afx_msg void OnPre();
	afx_msg void OnCaptu();
	afx_msg void OnMyreco();
};

