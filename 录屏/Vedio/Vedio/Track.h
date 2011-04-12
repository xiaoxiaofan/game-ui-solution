#pragma once
#include "afxext.h"
class CTrack :
	public CRectTracker
{
public:
	CTrack(void);
	~CTrack(void);
	virtual void DrawTrackerRect( LPCRECT lpRect, CWnd* pWndClipTo,
		CDC* pDC, CWnd* pWnd );
public:
	void SetRectColor(COLORREF rectColor);
	void CreatePen();
	void Draw(CDC*pDC);
public:
	//��ǰ���ο����ɫ
	COLORREF m_rectColor;
	HPEN m_BlackSolidPen;
	HBRUSH m_HatchBrush;
};

