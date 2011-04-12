// WndVedio.cpp : 实现文件
//

#include "stdafx.h"
#include "MedioVedioScreen.h"
#include "WndVedio.h"
#include "afxdialogex.h"


// WndVedio 对话框

IMPLEMENT_DYNAMIC(WndVedio, CDialog)

WndVedio::WndVedio(CWnd* pParent /*=NULL*/)
	: CDialog(WndVedio::IDD, pParent)
{
	m_CurHwnd    = NULL;      //用来存放获取的控件的句柄
	m_PreHwnd    = NULL;      //用来存放以前获取的控件的句柄
	m_LeftIsDown = FALSE;      //TRUE表示鼠标左键按下
	m_hDLL       = NULL;
	m_GetCurHwnd = NULL; 
	m_MoveCursor = AfxGetApp()->LoadCursor(IDC_MOVE);
}

WndVedio::~WndVedio()
{
}

void WndVedio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WndVedio, CDialog)
	ON_STN_CLICKED(IDC_CATCH, &WndVedio::OnStnClickedCatch)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// WndVedio 消息处理程序


void WndVedio::OnStnClickedCatch()
{
	// TODO: 在此添加控件通知处理程序代码
/*----------------------------------------------------------------------------------*/
	
	m_CurHwnd = NULL;
	m_PreHwnd = NULL;
	m_LeftIsDown = TRUE;
	 SetCapture();


/*----------------------------------------------------------------------------------*/

}
void WndVedio::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	POINT MousePoint;
	HWND  hWnd;

/*----------------------------------------------------------------------------------*/

	typedef void (*lpDrawWindow)(HWND hwnd);
	if ((m_LeftIsDown)&&(MK_LBUTTON == nFlags))
	{
		::SetCursor(m_MoveCursor);
		GetCursorPos(&MousePoint);
		m_CurHwnd = ::WindowFromPoint(MousePoint);
		if (m_CurHwnd == this->m_hWnd)
		{
			return;
		}
	 
		hWnd = ::GetDlgItem(m_hWnd,IDC_CATCH);
		if ((m_CurHwnd != m_PreHwnd)&&(m_CurHwnd != hWnd))
		{
			/*如果控件发生变化并且控件不为本身*/
			m_hDLL = LoadLibrary(_T("Vedio.dll"));
			if (NULL == m_hDLL)
			{
				MessageBox(_T("DLL文件加载失败(lpDrawWindow)"));
				return ;
			}
			lpDrawWindow pDrawWindow = (lpDrawWindow)GetProcAddress(m_hDLL,_T("DrawWindow"));
			if (NULL == pDrawWindow)
			{
				MessageBox(_T("获取(DrawWindow)函数地址失败"));
				FreeLibrary(m_hDLL);
				return ;
			}
			pDrawWindow(m_CurHwnd);
			m_PreHwnd = m_CurHwnd;
		}
	}

/*----------------------------------------------------------------------------------*/
	
	CDialog::OnMouseMove(nFlags, point);
}


void WndVedio::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	/*----------------------------------------------------------------------------------*/
	ReleaseCapture();

	typedef void (*lpDrawWindow)(HWND hwnd);
	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("加载DLL文件失败"));
		return;
	}
	lpDrawWindow pDrawWindow = (lpDrawWindow)GetProcAddress(m_hDLL,_T("DrawWindow"));
	if (NULL == pDrawWindow)
	{
		MessageBox(_T("获取(DrawWindow)函数地址失败"));
		FreeLibrary(m_hDLL);
		return ;
	}

	if (m_CurHwnd == this->m_hWnd)
	{
		return ;
	}
	if (m_CurHwnd == GetDlgItem(IDC_CATCH)->m_hWnd)
	{
		return ;
	}
	pDrawWindow(m_CurHwnd);

	EndDialog(100);
	/*----------------------------------------------------------------------------------*/
	CDialog::OnLButtonUp(nFlags, point);
}

HWND  WndVedio::GetWndHwnd()
{
	m_GetCurHwnd = m_CurHwnd;
	return m_GetCurHwnd;
}

void WndVedio::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
}
