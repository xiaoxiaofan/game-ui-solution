#pragma once


#include "resource.h"
// CWVedio 对话框
#include "Track.h"
class CWVedio : public CDialog
{
	DECLARE_DYNAMIC(CWVedio)

public:
	CWVedio(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CWVedio();
	virtual BOOL OnInitDialog();
// 对话框数据
	enum { IDD = IDD_WVEDIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);

public:
	int m_xScreen;
	int m_yScreen;
	BOOL m_bShowMsg;                //显示截取矩形大小信息
	BOOL m_bDraw;                   //是否为截取状态
	BOOL m_bFirstDraw;              //是否为首次截取
	BOOL m_bQuit;                   //是否为退出
	CPoint m_startPt;				//截取矩形左上角
	CPoint m_endPt;                 //结束点
	CTrack m_rectTracker;          //像皮筋类
	CBrush m_brush;					//
	HCURSOR m_hCursor;              //光标
	CBitmap * m_pBitmap;            //背景位图
	CRgn m_rgn;						//背景擦除区域
public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect,BOOL bSave=FALSE);   //考贝桌面到位图                      //显示操作提示信息
	void DrawMessage(CRect &inRect);       //显示截取矩形信息
	void PaintWindow();               //重画窗口 
	void GetPoint(CPoint& Point1,CPoint& Point2,BOOL& bFlag);
public:
	BOOL m_IsUp;
	CPoint m_pStart;
	CPoint m_pEnd; 
	BOOL   m_bFlag;
	
};
