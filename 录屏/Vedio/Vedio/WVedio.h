#pragma once


#include "resource.h"
// CWVedio �Ի���
#include "Track.h"
class CWVedio : public CDialog
{
	DECLARE_DYNAMIC(CWVedio)

public:
	CWVedio(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CWVedio();
	virtual BOOL OnInitDialog();
// �Ի�������
	enum { IDD = IDD_WVEDIO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
	BOOL m_bShowMsg;                //��ʾ��ȡ���δ�С��Ϣ
	BOOL m_bDraw;                   //�Ƿ�Ϊ��ȡ״̬
	BOOL m_bFirstDraw;              //�Ƿ�Ϊ�״ν�ȡ
	BOOL m_bQuit;                   //�Ƿ�Ϊ�˳�
	CPoint m_startPt;				//��ȡ�������Ͻ�
	CPoint m_endPt;                 //������
	CTrack m_rectTracker;          //��Ƥ����
	CBrush m_brush;					//
	HCURSOR m_hCursor;              //���
	CBitmap * m_pBitmap;            //����λͼ
	CRgn m_rgn;						//������������
public:
	HBITMAP CopyScreenToBitmap(LPRECT lpRect,BOOL bSave=FALSE);   //�������浽λͼ                      //��ʾ������ʾ��Ϣ
	void DrawMessage(CRect &inRect);       //��ʾ��ȡ������Ϣ
	void PaintWindow();               //�ػ����� 
	void GetPoint(CPoint& Point1,CPoint& Point2,BOOL& bFlag);
public:
	BOOL m_IsUp;
	CPoint m_pStart;
	CPoint m_pEnd; 
	BOOL   m_bFlag;
	
};
