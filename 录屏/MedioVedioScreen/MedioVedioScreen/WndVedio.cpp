// WndVedio.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MedioVedioScreen.h"
#include "WndVedio.h"
#include "afxdialogex.h"


// WndVedio �Ի���

IMPLEMENT_DYNAMIC(WndVedio, CDialog)

WndVedio::WndVedio(CWnd* pParent /*=NULL*/)
	: CDialog(WndVedio::IDD, pParent)
{
	m_CurHwnd    = NULL;      //������Ż�ȡ�Ŀؼ��ľ��
	m_PreHwnd    = NULL;      //���������ǰ��ȡ�Ŀؼ��ľ��
	m_LeftIsDown = FALSE;      //TRUE��ʾ����������
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


// WndVedio ��Ϣ�������


void WndVedio::OnStnClickedCatch()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
/*----------------------------------------------------------------------------------*/
	
	m_CurHwnd = NULL;
	m_PreHwnd = NULL;
	m_LeftIsDown = TRUE;
	 SetCapture();


/*----------------------------------------------------------------------------------*/

}
void WndVedio::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
			/*����ؼ������仯���ҿؼ���Ϊ����*/
			m_hDLL = LoadLibrary(_T("Vedio.dll"));
			if (NULL == m_hDLL)
			{
				MessageBox(_T("DLL�ļ�����ʧ��(lpDrawWindow)"));
				return ;
			}
			lpDrawWindow pDrawWindow = (lpDrawWindow)GetProcAddress(m_hDLL,_T("DrawWindow"));
			if (NULL == pDrawWindow)
			{
				MessageBox(_T("��ȡ(DrawWindow)������ַʧ��"));
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	/*----------------------------------------------------------------------------------*/
	ReleaseCapture();

	typedef void (*lpDrawWindow)(HWND hwnd);
	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("����DLL�ļ�ʧ��"));
		return;
	}
	lpDrawWindow pDrawWindow = (lpDrawWindow)GetProcAddress(m_hDLL,_T("DrawWindow"));
	if (NULL == pDrawWindow)
	{
		MessageBox(_T("��ȡ(DrawWindow)������ַʧ��"));
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
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}
