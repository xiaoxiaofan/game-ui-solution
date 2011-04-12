// WVedio.cpp : 实现文件
//

#include "stdafx.h"
#include "Vedio.h"
#include "WVedio.h"
#include "afxdialogex.h"


// CWVedio 对话框

IMPLEMENT_DYNAMIC(CWVedio, CDialog)

CWVedio::CWVedio(CWnd* pParent /*=NULL*/)
	: CDialog(CWVedio::IDD, pParent)
{
	/*--------------------------------------------------------------*/

	//初始化像皮筋类
	m_rectTracker.m_nStyle=CRectTracker::resizeInside|CRectTracker::solidLine;  
	m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);

	/*--------------------------------------------------------------*/
	//设置矩形颜色

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

	//获取屏幕分辩率
	m_xScreen = GetSystemMetrics(SM_CXSCREEN);
	m_yScreen = GetSystemMetrics(SM_CYSCREEN);

	//截取屏幕到位图中
	CRect rect(0, 0,m_xScreen,m_yScreen);
	m_pBitmap=CBitmap::FromHandle(CopyScreenToBitmap(&rect));

	//一定要初始化m_rgn，
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


// CWVedio 消息处理程序

BOOL CWVedio::OnInitDialog()
{

	// 	把对化框设置成全屏顶层窗口
	/*------------------------------------------------------------------*/
	 SetWindowPos(&wndTopMost,0,0,m_xScreen,m_yScreen,SWP_SHOWWINDOW);
	/*------------------------------------------------------------------*/
	/*SetWindowPos(&wndTopMost,0,0,500 ,500 ,SWP_SHOWWINDOW);*/
	return TRUE;
}
void CWVedio::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


BOOL CWVedio::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	/*------------------------------------------------------------------*/

	//设置改变截取矩形大小时光标
	if (pWnd == this && m_rectTracker.SetCursor(this, nHitTest)) 
	{

		return TRUE; 
	}
	else
	{
		//设置彩色光标
		SetCursor(m_hCursor);
		return TRUE;
	}

	/*------------------------------------------------------------------*/
}


BOOL CWVedio::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此处添加消息处理程序代码

	if(m_bShowMsg&&m_bFirstDraw)
	{
		CRect rect;
		m_rectTracker.GetTrueRect(&rect);
		DrawMessage(rect);
	}

	////画出像皮筋矩形
	if(m_bFirstDraw == TRUE)
	{
		m_rectTracker.Draw(&dc);
	}
	CDialog::OnPaint();

	// 不为绘图消息调用 CDialog::OnPaint()
}


void CWVedio::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*------------------------------------------------------------------*/
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);

	m_bShowMsg=TRUE;
	//判断击中位置
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int nHitTest;
	nHitTest=m_rectTracker.HitTest(point);

	if(nHitTest==8)
	{
		CopyScreenToBitmap(m_rectTracker.m_rect,TRUE);
		CString str;
		//调整选择矩形，使其为从左上到右下的坐标

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(m_bFirstDraw)
	{
		//如果已经截取矩则清除截取矩形
		m_bFirstDraw=FALSE;
		m_rectTracker.m_rect.SetRect(-1,-1,-1,-1);
		PaintWindow();
	}
	else
	{
		//关闭程序
		m_bFlag = FALSE;
		EndDialog(100);
	}

	CDialog::OnRButtonDown(nFlags, point);
}
HBITMAP CWVedio::CopyScreenToBitmap(LPRECT lpRect,BOOL bSave)  //考贝桌面到位图 
{
	HDC hScrDC, hMemDC;      
	// 屏幕和内存设备描述表
	HBITMAP    hBitmap, hOldBitmap;   
	// 位图句柄
	int       nX, nY, nX2, nY2;      
	// 选定区域坐标
	int       nWidth, nHeight;

	// 确保选定区域不为空矩形
	if (IsRectEmpty(lpRect))
		return NULL;
	//为屏幕创建设备描述表
	hScrDC = CreateDC("DISPLAY", NULL, NULL, NULL);

	//为屏幕设备描述表创建兼容的内存设备描述表
	hMemDC = CreateCompatibleDC(hScrDC);
	// 获得选定区域坐标
	nX = lpRect->left;
	nY = lpRect->top;
	nX2 = lpRect->right;
	nY2 = lpRect->bottom;

	//确保选定区域是可见的
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
	// 创建一个与屏幕设备描述表兼容的位图
	hBitmap = CreateCompatibleBitmap
		(hScrDC, nWidth, nHeight);
	// 把新位图选到内存设备描述表中
	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hBitmap);
	// 把屏幕设备描述表拷贝到内存设备描述表中
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
	//得到屏幕位图的句柄
	//清除 
	DeleteDC(hScrDC);
	DeleteDC(hMemDC);
	// 返回位图句柄
	if(bSave)
	{
		if (OpenClipboard()) 
		{
			//清空剪贴板
			EmptyClipboard();
			//把屏幕内容粘贴到剪贴板上,
			//hBitmap 为刚才的屏幕位图句柄
			SetClipboardData(CF_BITMAP, hBitmap);
			//关闭剪贴板
			CloseClipboard();
		}
	}
	return hBitmap;
}
void CWVedio::DrawMessage(CRect &inRect)      //显示截取矩形信息
{
	//截取矩形大小信息离鼠标间隔
	const int space = 3;
	//设置字体颜色大小
	CClientDC dc(this);
	CPoint pt;
	CPen pen(PS_SOLID,1,RGB(147,147,147));
	dc.SetTextColor(RGB(0,0,0));
	CFont font;
	font.CreatePointFont(150,_T("楷体"));
	dc.SelectObject(&font);

	//得到字体宽度和高度
	GetCursorPos(&pt);
	dc.SetBkMode(TRANSPARENT);
	TEXTMETRIC tm;
	int charHeight;
	CSize size;
	int	lineLength;
	dc.GetTextMetrics(&tm);
	charHeight = tm.tmHeight+tm.tmExternalLeading;
	size=dc.GetTextExtent(_T("区域截取消息提示"),lstrlen(_T("区域截取消息提示")));
	lineLength=size.cx;

	//初始化矩形, 以保证写下六行文字
	CRect rect(pt.x+space,pt.y-charHeight*6-space,pt.x+lineLength+space,pt.y-space);

	int x = GetDeviceCaps(dc, HORZRES);
	int y = GetDeviceCaps(dc, VERTRES);

	//创建临时矩形
	CRect rectTemp;
	//当矩形到达桌面边缘时调整方向和大小
	if((pt.x+rect.Width())>=x)
	{
		//桌面上方显示不下矩形
		rectTemp=rect;
		rectTemp.left=rect.left-rect.Width()-space*2;
		rectTemp.right=rect.right-rect.Width()-space*2;;
		rect=rectTemp;
	}

	if((pt.y-rect.Height())<=0)
	{
		//桌面右方显示不下矩形
		rectTemp=rect;
		rectTemp.top=rect.top+rect.Height()+space*2;;
		rectTemp.bottom=rect.bottom+rect.Height()+space*2;;
		rect=rectTemp;
	}

	//创建空画刷画矩形
	dc.SelectObject((HBRUSH)GetStockObject(NULL_BRUSH));
	dc.Rectangle(rect);
	rect.top+=2;
	//在矩形中显示文字
	CString string(_T("用鼠标左键双击"));
	dc.TextOut(rect.left,rect.top,string);

	string=_T("选择的矩形区域");
	dc.TextOut(rect.left,rect.top+charHeight,string);

	string=_T("可以进行录制");
	dc.TextOut(rect.left,rect.top+charHeight*2,string);

	string =_T("用鼠标右键单击选");
	dc.TextOut(rect.left,rect.top+charHeight*3,string);

	string=_T("择的矩形区域可以");
	dc.TextOut(rect.left,rect.top+charHeight*4,string);

	string=_T("进行从新选择区域");
	dc.TextOut(rect.left,rect.top+charHeight*5,string);
}
void CWVedio::PaintWindow()              //重画窗口 
{
	Invalidate();
}


void CWVedio::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//m_bFlag = FALSE;
	CDialog::OnRButtonUp(nFlags, point);
}

void CWVedio::GetPoint(CPoint& Point1,CPoint& Point2,BOOL& bFlag)
{
	Point1 = m_pStart;
	Point2 = m_pEnd;
	bFlag  = m_bFlag;
}