
// MedioVedioScreenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MedioVedioScreen.h"
#include "MedioVedioScreenDlg.h"
#include "afxdialogex.h"
#include "WndVedio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define  FULLSCREEN 1
#define  AREASCREEN 2
#define  WNDSCREEN  3

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMedioVedioScreenDlg �Ի���




CMedioVedioScreenDlg::CMedioVedioScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMedioVedioScreenDlg::IDD, pParent)
	, m_strFileName(_T(""))
	, m_strFilePath(_T(""))
	, m_nRate(0)
	, m_strPlace(_T(""))
	, m_CheckAvi(TRUE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_p1 = m_p2 = 0;
	m_IsStop = FALSE;
	m_IsPause = TRUE;
	m_nCount = 0;
	m_GetCurWndHwnd = NULL;
	m_bFlag = TRUE;
}

void CMedioVedioScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_FILE, m_FileName);
	DDX_Text(pDX, IDC_EDIT_FILE, m_strFileName);
	DDX_Control(pDX, IDC_EDIT_PATH, m_FilePath);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strFilePath);
	DDX_Control(pDX, IDC_EDIT_RATE, m_Rate);
	DDX_Text(pDX, IDC_EDIT_RATE, m_nRate);
	DDX_Text(pDX, IDC_STATICPLACE, m_strPlace);
	DDX_Control(pDX, IDC_STATICPLACE, m_csPlace);
	DDX_Control(pDX, IDC_CHECK_AVI, m_bCheckAvi);
	DDX_Check(pDX, IDC_CHECK_AVI, m_CheckAvi);
}

BEGIN_MESSAGE_MAP(CMedioVedioScreenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_FULL_SCREEN, &CMedioVedioScreenDlg::OnBnClickedButtFullScreen)
	ON_BN_CLICKED(IDC_BUT_AREA, &CMedioVedioScreenDlg::OnBnClickedButArea)
	ON_BN_CLICKED(IDC_BUT_WND_SCREEN, &CMedioVedioScreenDlg::OnBnClickedButWndScreen)
	ON_BN_CLICKED(IDC_BUT_STOP, &CMedioVedioScreenDlg::OnBnClickedButStop)
	ON_BN_CLICKED(IDC_BUT_PAUSE, &CMedioVedioScreenDlg::OnBnClickedButPause)
	ON_BN_CLICKED(IDC_BUT_SET_PATH, &CMedioVedioScreenDlg::OnBnClickedButSetPath)
	ON_BN_CLICKED(IDC_CHECK_AVI, &CMedioVedioScreenDlg::OnBnClickedCheckAvi)
	ON_STN_CLICKED(IDC_STATICPLACE, &CMedioVedioScreenDlg::OnStnClickedStaticplace)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMedioVedioScreenDlg ��Ϣ�������

BOOL CMedioVedioScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_MINIMIZE);

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	GetDlgItem(IDC_BUT_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_AREA)->EnableWindow(TRUE);

	m_nRate = 10;
	m_bCheckAvi.SetCheck(TRUE);
	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMedioVedioScreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMedioVedioScreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMedioVedioScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMedioVedioScreenDlg::OnBnClickedButtFullScreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*-----------------------------------------------------------------------*/

	UpdateData(TRUE);
	if (m_nRate <= 0 ||m_nRate>10)
	{
		MessageBox(_T("����������ȷ��֡����"));
		return;
	}
	if (m_bCheckAvi.GetCheck() == FALSE)
	{
		MessageBox(_T("��ѡ��¼���ļ���ʽ"));
		return;
	}
	if (m_strFilePath.IsEmpty())
	{
		MessageBox(_T("�ļ�·������Ϊ��"));
		return;
	}
	/*-----------------------------------------------------------------------*/
	GetDlgItem(IDC_BUT_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_AREA)->EnableWindow(FALSE);
	
	/*-----------------------------------------------------------------------*/

	typedef void (*lpStartVedio)(CString strFilePath,CString strFileName,int nRate,CPoint p1,CPoint p2,int nFlag,HWND GetCurHwnd);

	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpStartVedio)��"));
		return;
	}

	lpStartVedio pStartVedio = (lpStartVedio)GetProcAddress(m_hDLL,_T("StartVedio"));
	if (NULL == pStartVedio)
	{
		MessageBox(_T("��pStartVedio����Ѱַ����"));
		FreeLibrary(m_hDLL);
		return ;
	}
	pStartVedio(m_strFilePath,m_strFileName,m_nRate,0,0,FULLSCREEN,NULL);
	m_IsStop = TRUE;

	/*-----------------------------------------------------------------------*/
}


void CMedioVedioScreenDlg::OnBnClickedButArea()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*-----------------------------------------------------------------------*/
	UpdateData(TRUE);
	if (m_nRate <= 0||m_nRate>10)
	{
		MessageBox(_T("����������ȷ��֡����"));
		return;
	}

	if (m_bCheckAvi.GetCheck() == FALSE)
	{
		MessageBox(_T("��ѡ��¼���ļ���ʽ"));
		return;
	}
	if (m_strFilePath.IsEmpty())
	{
		MessageBox(_T("�ļ�·������Ϊ��"));
		return;
	}

	/*-----------------------------------------------------------------------*/
	
	typedef void(*lpGetRectPoint)(CPoint& Point1,CPoint& Point2,BOOL& bFlag);
	m_hDLL = LoadLibrary("Vedio.dll");
	if (NULL == m_hDLL)
	{
		MessageBox(_T("����DLL�ļ�ʧ��(lpGetRectPoint)"));
		return;
	}

	lpGetRectPoint pGetRectPoint = (lpGetRectPoint)GetProcAddress(m_hDLL,_T("GetRect"));
	if (NULL == pGetRectPoint)
	{
		MessageBox(_T("������Ѱַ����(pGetRectPoint)��"));
		FreeLibrary(m_hDLL);
		return;
	}
	pGetRectPoint(m_p1,m_p2,m_bFlag);

	if (FALSE == m_bFlag)
	{
		return;
	}

	/*-----------------------------------------------------------------------*/


	GetDlgItem(IDC_BUT_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_AREA)->EnableWindow(FALSE);

	

	/*-----------------------------------------------------------------------*/

	typedef void (*lpStartVedio)(CString strFilePath,CString strFileName,int nRate,CPoint p1,CPoint p2,int nFlag,HWND GetCurHwnd);

	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpStartVedio)��"));
		return;
	}

	lpStartVedio pStartVedio = (lpStartVedio)GetProcAddress(m_hDLL,_T("StartVedio"));
	if (NULL == pStartVedio)
	{
		MessageBox(_T("��pStartVedio����Ѱַ����"));
		FreeLibrary(m_hDLL);
		return ;
	}
	pStartVedio(m_strFilePath,m_strFileName,m_nRate,m_p1,m_p2,AREASCREEN,NULL);
	m_IsStop = TRUE;

	/*-----------------------------------------------------------------------*/

}


void CMedioVedioScreenDlg::OnBnClickedButWndScreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*-----------------------------------------------------------------------*/
	
	UpdateData(TRUE);
	if (m_nRate <= 0||m_nRate>10)
	{
		MessageBox(_T("����������ȷ��֡����"));
		return;
	}

	if (m_bCheckAvi.GetCheck() == FALSE)
	{
		MessageBox(_T("��ѡ��¼���ļ���ʽ"));
		return;
	}
	if (m_strFilePath.IsEmpty())
	{
		MessageBox(_T("�ļ�·������Ϊ��"));
		return;
	}

	/*-----------------------------------------------------------------------*/

	WndVedio WndDlg;
	int ret = WndDlg.DoModal();

	if (100 == ret)
	{
		m_GetCurWndHwnd = WndDlg.GetWndHwnd();
		if ( NULL == m_GetCurWndHwnd)
		{
			MessageBox(_T("��ȡ��ǰ���ھ������"));
			return;
		}
	}else if (IDOK == ret)
	{
		return;
	}else if (IDCANCEL == ret)
	{
		return;
	}else if (m_GetCurWndHwnd< 0)
	{
		return;
	}else 
	{
		return;
	}
	
	/*-----------------------------------------------------------------------*/

	GetDlgItem(IDC_BUT_STOP)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_AREA)->EnableWindow(FALSE);
	
	/*-----------------------------------------------------------------------*/

	typedef void (*lpStartVedio)(CString strFilePath,CString strFileName,int nRate,CPoint p1,CPoint p2,int nFlag,HWND GetCurHwnd);

	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("DLL�ļ�����ʧ��(arealpStartVedio)"));
		return ;
	}
	lpStartVedio pStartVedio = (lpStartVedio)GetProcAddress(m_hDLL,_T("StartVedio"));
	if (NULL == pStartVedio)
	{
		MessageBox(_T("��StartVedioѰַʧ�ܡ�"));
		FreeLibrary(m_hDLL);
		return ;
	}

	pStartVedio(m_strFilePath,m_strFileName,m_nRate,0,0,WNDSCREEN,m_GetCurWndHwnd);

	m_IsStop = TRUE;

	/*-----------------------------------------------------------------------*/
}


void CMedioVedioScreenDlg::OnBnClickedButStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*-----------------------------------------------------------------------*/

	GetDlgItem(IDC_BUT_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_AREA)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_SET_PATH)->EnableWindow(TRUE);

	/*-----------------------------------------------------------------------*/

	typedef void (*lpStopVedio)();
	m_hDLL = LoadLibrary("Vedio.dll");
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpStopVedio)��"));
		return ;
	}
	lpStopVedio pStopVedio = (lpStopVedio)GetProcAddress(m_hDLL,_T("StopVedio"));
	if (NULL == pStopVedio)
	{
		MessageBox(_T("��pStopVedioѰַʧ�ܡ�"));
		FreeLibrary(m_hDLL);
		return ;
	}
	pStopVedio();
	m_FileName.GetWindowText(m_strFileName);

	/*-----------------------------------------------------------------------*/

	typedef CString(*lpGetFileName)(CString strFile,int& nCount);
	m_hDLL = LoadLibrary("Vedio.dll");
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpGetFileName)��"));
		return;
	}
	lpGetFileName pGetFileName = (lpGetFileName)GetProcAddress(m_hDLL,_T("GetFileName"));
	if (NULL == pGetFileName)
	{
		MessageBox(_T("��pGetFileName Ѱַʧ�ܡ�"));
		FreeLibrary(m_hDLL);
		return;
	}
	m_strFileName = pGetFileName(m_strFileName,m_nCount);
	m_FileName.SetWindowText(m_strFileName);

	/*-----------------------------------------------------------------------*/

	m_FilePath.GetWindowText(m_strFilePath);
	typedef CString(*lpGetDiskPlace)(CString strPath);
	m_hDLL = LoadLibrary("Vedio.dll");
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpGetDiskPlace)��"));
		return;
	}
	lpGetDiskPlace pGetDiskPlace = (lpGetDiskPlace)GetProcAddress(m_hDLL,_T("GetResidualPlace"));
	if (NULL == pGetDiskPlace)
	{
		MessageBox(_T("��pGetDiskPlace������Ѱַʧ��"));
		FreeLibrary(m_hDLL);
		return;
	}
	m_strPlace = pGetDiskPlace(m_strFilePath);
	CString str;
	str.Format(_T("������ʣ��ռ��СΪ��:��%s��"),m_strPlace);
	m_csPlace.SetWindowText(str);

	/*-----------------------------------------------------------------------*/

	m_IsStop = FALSE;
	m_nCount ++;
}


void CMedioVedioScreenDlg::OnBnClickedButPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	/*-----------------------------------------------------------------------*/

	if (TRUE == m_IsPause)
	{
		/*-----------------------------------------------------------------------*/

		GetDlgItem(IDC_BUT_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_AREA)->EnableWindow(FALSE);
		m_IsPause = FALSE;

		/*-----------------------------------------------------------------------*/

		typedef void (*lpPauseVedio)();
		m_hDLL = LoadLibrary("Vedio.dll");
		if (NULL == m_hDLL)
		{
			MessageBox(_T("��DLL�ļ�����ʧ��(lpPauseVedio)��"));
			return ;
		}
		lpPauseVedio pPauseVedio = (lpPauseVedio)GetProcAddress(m_hDLL,"PauseVedio");
		if (NULL == pPauseVedio)
		{
			MessageBox(_T("��pPauseVedioѰַʧ�ܡ�"));
			FreeLibrary(m_hDLL);
			return ;
		}

		/*-----------------------------------------------------------------------*/

		pPauseVedio();

	} 
	else
	{
		/*-----------------------------------------------------------------------*/

		GetDlgItem(IDC_BUT_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUT_AREA)->EnableWindow(FALSE);
		m_IsPause = TRUE;

		/*-----------------------------------------------------------------------*/

		typedef void (*lpUnPauseVedio)();
		m_hDLL = LoadLibrary("Vedio.dll");
		if (NULL == m_hDLL)
		{
			MessageBox(_T("��DLL�ļ�����ʧ��(lpUnPauseVedio)��"));
			return;
		}
		lpUnPauseVedio pUnPauseVedio = (lpUnPauseVedio)GetProcAddress(m_hDLL,"UnPauseVedio");
		if (NULL == pUnPauseVedio)
		{
			MessageBox(_T("��pUnPauseVedio����Ѱַ����"));
			FreeLibrary(m_hDLL);
			return ;
		}
		
		/*-----------------------------------------------------------------------*/

		pUnPauseVedio();
	}
}


void CMedioVedioScreenDlg::OnBnClickedButSetPath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*-----------------------------------------------------------------------*/

	typedef CString (*lpGetFilePath)();
	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpGetFilePath)��"));
		return;
	}

	lpGetFilePath pGetFilePath = (lpGetFilePath)GetProcAddress(m_hDLL,_T("GetFilePath"));
	if (NULL == pGetFilePath)
	{
		MessageBox(_T("��pGetFilePath ����Ѱַʧ��)��"));
		FreeLibrary(m_hDLL);
		return ;
	}
	m_strFilePath = pGetFilePath();
	m_FilePath.SetWindowText(m_strFilePath);

	/*-----------------------------------------------------------------------*/

	typedef CString (*lpGetFileName)(CString strFile,int& nCount);
	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpGetFileName)��"));
		return;
	}
	lpGetFileName pGetFileName = (lpGetFileName)GetProcAddress(m_hDLL,"GetFileName");
	if (NULL == pGetFileName)
	{
		MessageBox(_T("��pGetFileName Ѱַʧ�ܡ�"));
		FreeLibrary(m_hDLL);
		return;
	}
	m_strFileName = pGetFileName(m_strFileName,m_nCount);
	m_FileName.SetWindowText(m_strFileName);
	m_FilePath.SetWindowText(m_strFilePath);

	/*-----------------------------------------------------------------------*/

		typedef CString (*lpGetDiskPlace)(CString strPath);
	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("��DLL�ļ�����ʧ��(lpGetDiskPlace)��"));
		return;
	}
	lpGetDiskPlace pGetDiskPlace = (lpGetDiskPlace)GetProcAddress(m_hDLL,"GetResidualPlace");
	if (NULL == pGetDiskPlace)
	{
		MessageBox(_T("��pGetDiskPlace������Ѱַʧ��"));
		FreeLibrary(m_hDLL);
		return;
	}
	m_strPlace = pGetDiskPlace(m_strFilePath);
	CString str;
	str.Format(_T("������ʣ��ռ䡿:��%s��"),m_strPlace);
	m_csPlace.SetWindowText(str);

	/*-----------------------------------------------------------------------*/
	m_nCount ++;

	GetDlgItem(IDC_BUT_SET_PATH)->EnableWindow(FALSE);

	/*GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_AREA)->EnableWindow(FALSE);*/

	/*-----------------------------------------------------------------------*/
}


void CMedioVedioScreenDlg::OnBnClickedCheckAvi()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CMedioVedioScreenDlg::OnStnClickedStaticplace()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
void CMedioVedioScreenDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if (TRUE == m_IsStop)
	{
		MessageBox(_T("��Ļ¼��û�йر�"));
		return;
	}

	CDialogEx::OnClose();
}
