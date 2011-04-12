// WVedio.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Vedio.h"
#include "WVedio.h"
#include "afxdialogex.h"


// CWVedio �Ի���

IMPLEMENT_DYNAMIC(CWVedio, CDialog)

CWVedio::CWVedio(CWnd* pParent /*=NULL*/)
	: CDialog(CWVedio::IDD, pParent)
{
	/*--------------------------------------------------------------*/

	//��ʼ����Ƥ����
	m_rectTracker.m_nStyle=CRectTracker::resizeInside|CRectTracker::solidLine;  
	m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);

	/*--------------------------------------------------------------*/
	//���þ�����ɫ

	m_rectTracker.SetRectColor(RGB(255,0,0));

	/*--------------------------------------------------------------*/

	m_hCursor=AfxGetApp()->LoadCursor(IDC_CURSOR2);  
	m_bDraw=FALSE;
	m_bFirstDraw=FALSE;
	m_bQuit=FALSE;
	m_bShowMsg=FALSE;
	m_IsUp = TRUE;
	m_bFlag = TRUE;

	/*--------------------------------------------------------------*/

	//��ȡ��Ļ�ֱ���
	m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	m_yScreen = GetSystemMetrics(SM_CYSCREEN);

	//��ȡ��Ļ��λͼ��
	CRect rect(0, 0,m_xScreen,m_yScreen);
	m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(&rect));

	//һ��Ҫ��ʼ��m_rgn��
	m_rgn.CreateRectRgn(0,0,50,50);

	/*--------------------------------------------------------------*/

}

CWVedio::~CWVedio()
{
}

void CWVedio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CWVedio, CDialog)
	ON_BN_CLICKED(IDOK, &CWVedio::OnBnClickedOk)
	ON_WM_SETCURSOR()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// CWVedio ��Ϣ�������

BOOL CWVedio::OnInitDialog()
{

	// 	�ѶԻ������ó�ȫ�����㴰��
	/*------------------------------------------------------------------*/
	 SetWindowPos(&wndTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
	/*------------------------------------------------------------------*/
	/*SetWindowPos(&wndTopMost,0,0,500 ,500 ,SWP_SHOWWINDOW);*/
	return TRUE;
}
void CWVedio::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


BOOL CWVedio::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	/*------------------------------------------------------------------*/

	//���øı��ȡ���δ�Сʱ���
	if (pWnd == this && m_rectTracker.SetCursor(this, nHitTest)) 
	{

		return TRUE; 
	}
	else
	{
		//���ò�ɫ���
		SetCursor(m_hCursor);
		return TRUE;
	}

	/*------------------------------------------------------------------*/
}


BOOL CWVedio::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	BITMAP bmp;
	m_pBitmap->GetBitmap(&bmp);

	CDC dcCompatible;

	dcCompatible.CreateCompatibleDC(pDC);
	dcCompatible.SelectObject(m_pBitmap);

	CRect rect;
	GetClientRect(&rect);
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&dcCompatible,0,0,SRCCOPY);
	return TRUE;
}


void CWVedio::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������

	if(m_bShowMsg&&m_bFirstDraw)
	{
		CRect rect;
		m_rectTracker.GetTrueRect(&rect);
		DrawMessage(rect);
	}

	////������Ƥ�����
	if(m_bFirstDraw == TRUE)
	{
		m_rectTracker.Draw(&dc);
	}
	CDialog::OnPaint();

	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}


void CWVedio::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*------------------------------------------------------------------*/
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);

	m_bShowMsg=TRUE;
	//�жϻ���λ��
	if(nHitTest<0)
	{
		if(!m_bFirstDraw)
		{
			m_startPt = point;
			m_bDraw = TRUE;
			PaintWindow();
		}
	}
	else
	{
		if(m_bFirstDraw)
		{
			m_rectTracker.Track(this,point,TRUE);
			SendMessage(WM_LBUTTONUP,NULL,NULL);
			PaintWindow();
		}
	}
	/*------------------------------------------------------------------*/
	CDialog::OnLButtonDown(nFlags, point);
}

void CWVedio::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*------------------------------------------------------------------*/
	m_bShowMsg=FALSE;

	if (m_bDraw == TRUE)
	{
		m_endPt = point;
		m_bDraw=FALSE;
	}

	PaintWindow();
	/*------------------------------------------------------------------*/
	CDialog::OnLButtonUp(nFlags, point);
}

void CWVedio::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);

	if(nHitTest==8)
	{
		CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);
		CString str;
		//����ѡ����Σ�ʹ��Ϊ�����ϵ����µ�����

		if(m_endPt.y - m_startPt.y > 0)
		{
			if (m_endPt.x - m_startPt.x > 0)
			{
				m_pStart = m_startPt;
				m_pEnd  = m_endPt;
			}else
			{
				m_pStart.x = m_endPt.x;
				m_pStart.y = m_startPt.y;
				m_pEnd.x  = m_startPt.x;
				m_pEnd.y  = m_endPt.y;
			}
		}
		else
		{
			if (m_endPt.x - m_startPt.x > 0)
			{
				m_pStart.x = m_startPt.x;
				m_pStart.y = m_endPt.y;
				m_pEnd.x  = m_endPt.x;
				m_pEnd.y  = m_startPt.y;
			}else
			{
				m_pStart = m_endPt;
				m_pEnd = m_startPt;
			}
		}
		EndDialog(100); 
	}
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CWVedio::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bDraw)
	{
		m_rectTracker.m_rect.SetRect(m_startPt.x+1,m_startPt.y+1,point.x,point.y);
		m_bFirstDraw = TRUE;
		PaintWindow();
	}
	CDialog::OnMouseMove(nFlags, point);
}


void CWVedio::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(m_bFirstDraw)
	{
		//����Ѿ���ȡ���������ȡ����
		m_bFirstDraw=FALSE;
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		PaintWindow();
	}
	else
	{
		//�رճ���
		m_bFlag = FALSE;
		EndDialog(100);
	}

	CDialog::OnRButtonDown(nFlags, point);
}
HBITMAP CWVedio::CopyScreenToBitmap(LPRECT lpRect,BOOL bSave)  //�������浽λͼ 
{
	HDC hScrDC, hMemDC;      
	// ��Ļ���ڴ��豸������
	HBITMAP    hBitmap, hOldBitmap;   
	// λͼ���
	int       nX, nY, nX2, nY2;      
	// ѡ����������
	int       nWidth, nHeight;

	// ȷ��ѡ������Ϊ�վ���
	if (IsRectEmpty(lpRect))
		return NULL;
	//Ϊ��Ļ�����豸������
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);

	//Ϊ��Ļ�豸�����������ݵ��ڴ��豸������
	hMemDC = CreateCompatibleDC(hScrDC);
	// ���ѡ����������
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	//ȷ��ѡ�������ǿɼ���
	if (nX < 0)
		nX = 0;
	if (nY < 0)
		nY = 0;
	if (nX2 > m_xScreen)
		nX2 = m_xScreen;
	if (nY2 > m_yScreen)
		nY2 = m_yScreen;
	nWidth = nX2 - nX;
	nHeight = nY2 - nY;
	// ����һ������Ļ�豸��������ݵ�λͼ
	hBitmap = CreateCompatibleBitmap
		(hScrDC, nWidth, nHeight);
	// ����λͼѡ���ڴ��豸��������
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// ����Ļ�豸�����������ڴ��豸��������
	if(bSave)
	{
		CDC dcCompatible;
		dcCompatible.CreateCompatibleDC(CDC::FromHandle(hMemDC));
		dcCompatible.SelectObject(m_pBitmap);
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,dcCompatible, nX, nY, SRCCOPY);
	}
	else
	{
		BitBlt(hMemDC, 0, 0, nWidth, nHeight,hScrDC, nX, nY, SRCCOPY);
	}

	hBitmap = (HBITMAP)SelectObject(hMemDC, hOldBitmap);
	//�õ���Ļλͼ�ľ��
	//��� 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// ����λͼ���
	if(bSave)
	{
		if (OpenClipboard()) 
		{
			//��ռ�����
			EmptyClipboard();
			//����Ļ����ճ������������,
			//hBitmap Ϊ�ղŵ���Ļλͼ���
			SetClipboardData(CF_BITMAP, hBitmap);
			//�رռ�����
			CloseClipboard();
		}
	}
	return hBitmap;
}
void CWVedio::DrawMessage(CRect &inRect)      //��ʾ��ȡ������Ϣ
{
	//��ȡ���δ�С��Ϣ�������
	const int space = 3;
	//����������ɫ��С
	CClientDC dc(this);
	CPoint pt;
	CPen pen(PS_SOLID,1,RGB(147,147,147));
	dc.SetTextColor(RGB(0,0,0));
	CFont font;
	font.CreatePointFont(150,_T("����"));
	dc.SelectObject(&font);

	//�õ������Ⱥ͸߶�
	GetCursorPos(&pt);
	dc.SetBkMode(TRANSPARENT);
	TEXTMETRIC tm;
	int charHeight;
	CSize size;
	int	lineLength;
	dc.GetTextMetrics(&tm);
	charHeight = tm.tmHeight+tm.tmExternalLeading;
	size=dc.GetTextExtent(_T("�����ȡ��Ϣ��ʾ"),lstrlen(_T("�����ȡ��Ϣ��ʾ")));
	lineLength=size.cx;

	//��ʼ������, �Ա�֤д����������
	CRect rect(pt.x+space,pt.y-charHeight*6-space,pt.x+lineLength+space,pt.y-space);

	int x = GetDeviceCaps(dc, HORZRES);
	int y = GetDeviceCaps(dc, VERTRES);

	//������ʱ����
	CRect rectTemp;
	//�����ε��������Եʱ��������ʹ�С
	if((pt.x+rect.Width())>=x)
	{
		//�����Ϸ���ʾ���¾���
		rectTemp=rect;
		rectTemp.left=rect.left-rect.Width()-space*2;
		rectTemp.right=rect.right-rect.Width()-space*2;;
		rect=rectTemp;
	}

	if((pt.y-rect.Height())<=0)
	{
		//�����ҷ���ʾ���¾���
		rectTemp=rect;
		rectTemp.top=rect.top+rect.Height()+space*2;;
		rectTemp.bottom=rect.bottom+rect.Height()+space*2;;
		rect=rectTemp;
	}

	//�����ջ�ˢ������
	dc.SelectObject((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.Rectangle(rect);
	rect.top+=2;
	//�ھ�������ʾ����
	CString string(_T("��������˫��"));
	dc.TextOut(rect.left,rect.top,string);

	string=_T("ѡ��ľ�������");
	dc.TextOut(rect.left,rect.top+charHeight,string);

	string=_T("���Խ���¼��");
	dc.TextOut(rect.left,rect.top+charHeight*2,string);

	string =_T("������Ҽ�����ѡ");
	dc.TextOut(rect.left,rect.top+charHeight*3,string);

	string=_T("��ľ����������");
	dc.TextOut(rect.left,rect.top+charHeight*4,string);

	string=_T("���д���ѡ������");
	dc.TextOut(rect.left,rect.top+charHeight*5,string);
}
void CWVedio::PaintWindow()              //�ػ����� 
{
	Invalidate();
}


void CWVedio::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//m_bFlag = FALSE;
	CDialog::OnRButtonUp(nFlags, point);
}

void CWVedio::GetPoint(CPoint& Point1,CPoint& Point2,BOOL& bFlag)
{
	Point1 = m_pStart;
	Point2 = m_pEnd;
	bFlag  = m_bFlag;
}