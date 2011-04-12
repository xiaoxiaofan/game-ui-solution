#include "StdAfx.h"

#ifndef _TRACK_H_
#define _TRACK_H_
#include "Track.h"
#include "WVedio.h"
//#include "afximpl.h"
class CWVedio;

#endif /*_TRACK_H_*/
CTrack::CTrack(void)
{
	m_BlackSolidPen = NULL;
	m_HatchBrush = 0;
}
CTrack::~CTrack(void)
{
}
void CTrack::DrawTrackerRect( LPCRECT lpRect, CWnd* pWndClipTo,
	CDC* pDC, CWnd* pWnd )
{
	//更新窗口,消除TRACK时的虚线框
	((CWVedio *)pWnd)->PaintWindow();
	((CWVedio *)pWnd)->SendMessage(WM_MOUSEMOVE);
}

void CTrack::CreatePen()
{
	m_BlackSolidPen = ::CreatePen(PS_SOLID, 5, m_rectColor);
}

void CTrack::Draw(CDC*pDC)
{
	VERIFY(pDC->SaveDC() != 0);
	pDC->SetMapMode(MM_TEXT);
	pDC->SetViewportOrg(0, 0);
	pDC->SetWindowOrg(0, 0);

	CRect rect = m_rect;
	rect.NormalizeRect();

	CPen* pOldPen = NULL;
	CBrush* pOldBrush = NULL;
	CGdiObject* pTemp;
	int nOldROP;

	// draw lines
	if ((m_nStyle & (dottedLine|solidLine)) != 0)
	{	  
		pOldPen = pDC->SelectObject(CPen::FromHandle(m_BlackSolidPen));
		pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
		nOldROP = pDC->SetROP2(R2_COPYPEN);
		rect.InflateRect(+1, +1);   // borders are one pixel outside
		pDC->Rectangle(rect.left, rect.top, rect.right, rect.bottom);
		pDC->SetROP2(nOldROP);
	}

	if ((m_nStyle & (hatchInside|hatchedBorder)) != 0)
	{
		UnrealizeObject(m_HatchBrush);
	}
	if ((m_nStyle & hatchInside) != 0)
	{
		pTemp = pDC->SelectStockObject(NULL_PEN);
		if (pOldPen == NULL)
		{
			pOldPen = (CPen*)pTemp;
		}
		pTemp = pDC->SelectObject(CBrush::FromHandle(m_HatchBrush));
		if (pOldBrush == NULL)
		{
			pOldBrush = (CBrush*)pTemp;
		}
		pDC->SetBkMode(TRANSPARENT);
		nOldROP = pDC->SetROP2(R2_MASKNOTPEN);
		pDC->Rectangle(rect.left+1, rect.top+1, rect.right, rect.bottom);
		pDC->SetROP2(nOldROP);
	}

	if ((m_nStyle & hatchedBorder) != 0)
	{
		pTemp = pDC->SelectObject(CBrush::FromHandle(m_HatchBrush));
		if (pOldBrush == NULL)
			pOldBrush = (CBrush*)pTemp;
		pDC->SetBkMode(OPAQUE);
		CRect rectTrue;
		GetTrueRect(&rectTrue);
		
		pDC->PatBlt(rectTrue.left, rectTrue.top, rectTrue.Width(),rect.top-rectTrue.top, 0x000F0001 /* Pn */);
		pDC->PatBlt(rectTrue.left, rect.bottom,rectTrue.Width(), rectTrue.bottom-rect.bottom, 0x000F0001 /* Pn */);
		pDC->PatBlt(rectTrue.left, rect.top, rect.left-rectTrue.left,rect.Height(), 0x000F0001 /* Pn */);
		pDC->PatBlt(rect.right, rect.top, rectTrue.right-rect.right,rect.Height(), 0x000F0001 /* Pn */);
	}

	if ((m_nStyle & (resizeInside|resizeOutside)) != 0)
	{
		UINT mask = GetHandleMask();
		for (int i = 0; i < 8; ++i)
		{
			if (mask & (1<<i))
			{
				GetHandleRect((TrackerHit)i, &rect);
				//pDC->FillSolidRect(rect, RGB(132, 128, 85));
			}
		}
	}

	if (pOldPen != NULL)
	{
		pDC->SelectObject(pOldPen);
	}
	if (pOldBrush != NULL)
	{
		pDC->SelectObject(pOldBrush);
	}
	VERIFY(pDC->RestoreDC(-1));
}
void CTrack::SetRectColor(COLORREF rectColor)
{
	m_rectColor = rectColor;
	CreatePen();
}