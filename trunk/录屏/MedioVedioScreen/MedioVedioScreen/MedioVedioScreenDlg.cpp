
// MedioVedioScreenDlg.cpp : 实现文件
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

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMedioVedioScreenDlg 对话框




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


// CMedioVedioScreenDlg 消息处理程序

BOOL CMedioVedioScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	GetDlgItem(IDC_BUT_STOP)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUT_PAUSE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTT_FULL_SCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_WND_SCREEN)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUT_AREA)->EnableWindow(TRUE);

	m_nRate = 10;
	m_bCheckAvi.SetCheck(TRUE);
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMedioVedioScreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMedioVedioScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMedioVedioScreenDlg::OnBnClickedButtFullScreen()
{
	// TODO: 在此添加控件通知处理程序代码
	/*-----------------------------------------------------------------------*/

	UpdateData(TRUE);
	if (m_nRate <= 0 ||m_nRate>10)
	{
		MessageBox(_T("【请输入正确的帧数】"));
		return;
	}
	if (m_bCheckAvi.GetCheck() == FALSE)
	{
		MessageBox(_T("请选择录制文件格式"));
		return;
	}
	if (m_strFilePath.IsEmpty())
	{
		MessageBox(_T("文件路径不能为空"));
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
		MessageBox(_T("【DLL文件加载失败(lpStartVedio)】"));
		return;
	}

	lpStartVedio pStartVedio = (lpStartVedio)GetProcAddress(m_hDLL,_T("StartVedio"));
	if (NULL == pStartVedio)
	{
		MessageBox(_T("【pStartVedio函数寻址错误】"));
		FreeLibrary(m_hDLL);
		return ;
	}
	pStartVedio(m_strFilePath,m_strFileName,m_nRate,0,0,FULLSCREEN,NULL);
	m_IsStop = TRUE;

	/*-----------------------------------------------------------------------*/
}


void CMedioVedioScreenDlg::OnBnClickedButArea()
{
	// TODO: 在此添加控件通知处理程序代码
	/*-----------------------------------------------------------------------*/
	UpdateData(TRUE);
	if (m_nRate <= 0||m_nRate>10)
	{
		MessageBox(_T("【请输入正确的帧数】"));
		return;
	}

	if (m_bCheckAvi.GetCheck() == FALSE)
	{
		MessageBox(_T("请选择录制文件格式"));
		return;
	}
	if (m_strFilePath.IsEmpty())
	{
		MessageBox(_T("文件路径不能为空"));
		return;
	}

	/*-----------------------------------------------------------------------*/
	
	typedef void(*lpGetRectPoint)(CPoint& Point1,CPoint& Point2,BOOL& bFlag);
	m_hDLL = LoadLibrary("Vedio.dll");
	if (NULL == m_hDLL)
	{
		MessageBox(_T("加载DLL文件失败(lpGetRectPoint)"));
		return;
	}

	lpGetRectPoint pGetRectPoint = (lpGetRectPoint)GetProcAddress(m_hDLL,_T("GetRect"));
	if (NULL == pGetRectPoint)
	{
		MessageBox(_T("【函数寻址错误(pGetRectPoint)】"));
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
		MessageBox(_T("【DLL文件加载失败(lpStartVedio)】"));
		return;
	}

	lpStartVedio pStartVedio = (lpStartVedio)GetProcAddress(m_hDLL,_T("StartVedio"));
	if (NULL == pStartVedio)
	{
		MessageBox(_T("【pStartVedio函数寻址错误】"));
		FreeLibrary(m_hDLL);
		return ;
	}
	pStartVedio(m_strFilePath,m_strFileName,m_nRate,m_p1,m_p2,AREASCREEN,NULL);
	m_IsStop = TRUE;

	/*-----------------------------------------------------------------------*/

}


void CMedioVedioScreenDlg::OnBnClickedButWndScreen()
{
	// TODO: 在此添加控件通知处理程序代码
	/*-----------------------------------------------------------------------*/
	
	UpdateData(TRUE);
	if (m_nRate <= 0||m_nRate>10)
	{
		MessageBox(_T("【请输入正确的帧数】"));
		return;
	}

	if (m_bCheckAvi.GetCheck() == FALSE)
	{
		MessageBox(_T("请选择录制文件格式"));
		return;
	}
	if (m_strFilePath.IsEmpty())
	{
		MessageBox(_T("文件路径不能为空"));
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
			MessageBox(_T("获取当前窗口句柄错误"));
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
		MessageBox(_T("DLL文件加载失败(arealpStartVedio)"));
		return ;
	}
	lpStartVedio pStartVedio = (lpStartVedio)GetProcAddress(m_hDLL,_T("StartVedio"));
	if (NULL == pStartVedio)
	{
		MessageBox(_T("【StartVedio寻址失败】"));
		FreeLibrary(m_hDLL);
		return ;
	}

	pStartVedio(m_strFilePath,m_strFileName,m_nRate,0,0,WNDSCREEN,m_GetCurWndHwnd);

	m_IsStop = TRUE;

	/*-----------------------------------------------------------------------*/
}


void CMedioVedioScreenDlg::OnBnClickedButStop()
{
	// TODO: 在此添加控件通知处理程序代码

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
		MessageBox(_T("【DLL文件加载失败(lpStopVedio)】"));
		return ;
	}
	lpStopVedio pStopVedio = (lpStopVedio)GetProcAddress(m_hDLL,_T("StopVedio"));
	if (NULL == pStopVedio)
	{
		MessageBox(_T("【pStopVedio寻址失败】"));
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
		MessageBox(_T("【DLL文件加载失败(lpGetFileName)】"));
		return;
	}
	lpGetFileName pGetFileName = (lpGetFileName)GetProcAddress(m_hDLL,_T("GetFileName"));
	if (NULL == pGetFileName)
	{
		MessageBox(_T("【pGetFileName 寻址失败】"));
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
		MessageBox(_T("【DLL文件加载失败(lpGetDiskPlace)】"));
		return;
	}
	lpGetDiskPlace pGetDiskPlace = (lpGetDiskPlace)GetProcAddress(m_hDLL,_T("GetResidualPlace"));
	if (NULL == pGetDiskPlace)
	{
		MessageBox(_T("【pGetDiskPlace】函数寻址失败"));
		FreeLibrary(m_hDLL);
		return;
	}
	m_strPlace = pGetDiskPlace(m_strFilePath);
	CString str;
	str.Format(_T("【磁盘剩余空间大小为】:【%s】"),m_strPlace);
	m_csPlace.SetWindowText(str);

	/*-----------------------------------------------------------------------*/

	m_IsStop = FALSE;
	m_nCount ++;
}


void CMedioVedioScreenDlg::OnBnClickedButPause()
{
	// TODO: 在此添加控件通知处理程序代码
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
			MessageBox(_T("【DLL文件加载失败(lpPauseVedio)】"));
			return ;
		}
		lpPauseVedio pPauseVedio = (lpPauseVedio)GetProcAddress(m_hDLL,"PauseVedio");
		if (NULL == pPauseVedio)
		{
			MessageBox(_T("【pPauseVedio寻址失败】"));
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
			MessageBox(_T("【DLL文件加载失败(lpUnPauseVedio)】"));
			return;
		}
		lpUnPauseVedio pUnPauseVedio = (lpUnPauseVedio)GetProcAddress(m_hDLL,"UnPauseVedio");
		if (NULL == pUnPauseVedio)
		{
			MessageBox(_T("【pUnPauseVedio函数寻址错误】"));
			FreeLibrary(m_hDLL);
			return ;
		}
		
		/*-----------------------------------------------------------------------*/

		pUnPauseVedio();
	}
}


void CMedioVedioScreenDlg::OnBnClickedButSetPath()
{
	// TODO: 在此添加控件通知处理程序代码

	/*-----------------------------------------------------------------------*/

	typedef CString (*lpGetFilePath)();
	m_hDLL = LoadLibrary(_T("Vedio.dll"));
	if (NULL == m_hDLL)
	{
		MessageBox(_T("【DLL文件加载失败(lpGetFilePath)】"));
		return;
	}

	lpGetFilePath pGetFilePath = (lpGetFilePath)GetProcAddress(m_hDLL,_T("GetFilePath"));
	if (NULL == pGetFilePath)
	{
		MessageBox(_T("【pGetFilePath 函数寻址失败)】"));
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
		MessageBox(_T("【DLL文件加载失败(lpGetFileName)】"));
		return;
	}
	lpGetFileName pGetFileName = (lpGetFileName)GetProcAddress(m_hDLL,"GetFileName");
	if (NULL == pGetFileName)
	{
		MessageBox(_T("【pGetFileName 寻址失败】"));
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
		MessageBox(_T("【DLL文件加载失败(lpGetDiskPlace)】"));
		return;
	}
	lpGetDiskPlace pGetDiskPlace = (lpGetDiskPlace)GetProcAddress(m_hDLL,"GetResidualPlace");
	if (NULL == pGetDiskPlace)
	{
		MessageBox(_T("【pGetDiskPlace】函数寻址失败"));
		FreeLibrary(m_hDLL);
		return;
	}
	m_strPlace = pGetDiskPlace(m_strFilePath);
	CString str;
	str.Format(_T("【磁盘剩余空间】:【%s】"),m_strPlace);
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
	// TODO: 在此添加控件通知处理程序代码
}
void CMedioVedioScreenDlg::OnStnClickedStaticplace()
{
	// TODO: 在此添加控件通知处理程序代码
}
void CMedioVedioScreenDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (TRUE == m_IsStop)
	{
		MessageBox(_T("屏幕录制没有关闭"));
		return;
	}

	CDialogEx::OnClose();
}
