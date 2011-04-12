// Vedio.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "Vedio.h"
#include "VedioScreen.h"
#include "WVedio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: 如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CVedioApp

BEGIN_MESSAGE_MAP(CVedioApp, CWinApp)
END_MESSAGE_MAP()


// CVedioApp 构造

CVedioApp::CVedioApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CVedioApp 对象

CVedioApp theApp;


// CVedioApp 初始化

BOOL CVedioApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

/*-------------------------------------------------------------------------------------*/

void VDEIODLL_EXPORT_API GetRect(CPoint& Point1,CPoint& Point2,BOOL& bFlag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE main_hInstance = AfxGetResourceHandle();    //获取主程序资源句柄
	AfxSetResourceHandle(theApp.m_hInstance);             //获取dll程序资源句柄
	CWVedio Dlg;
	int ret = Dlg.DoModal();
	if (ret == 100)
	{
		Dlg.GetPoint(Point1,Point2,bFlag);
	}
}

/*-------------------------------------------------------------------------------------*/

CString VDEIODLL_EXPORT_API GetFilePath()
{
	CString strFilePath;
	TCHAR  szPath[MAX_PATH];                                    //保存路径变量
	BROWSEINFO bwInfo;                                          //保存路径变量结构体信息
	bwInfo.hwndOwner              = NULL;
	bwInfo.pidlRoot               = NULL;
	bwInfo.lpszTitle              = _T("文件保存路径");         //对话框标题
	bwInfo.pszDisplayName         = szPath;                     //选择文件夹路径
	bwInfo.ulFlags                = BIF_RETURNONLYFSDIRS;       //标记
	bwInfo.lpfn                   = NULL;                       //默认值为NULL
	bwInfo.lParam                 = NULL;                       //回调消息      
	LPITEMIDLIST  lpItemIDList = SHBrowseForFolder(&bwInfo);    //显示文件浏览对话框
	if (lpItemIDList)
	{
		if (SHGetPathFromIDList(lpItemIDList,szPath))        //判断是否获得文件夹路径
		{
			strFilePath = szPath;                   	    //获得文件夹路径
		}
	}else
	{
		strFilePath = "";                                    //文件夹路径为空
	}
	return strFilePath;
}

/*-------------------------------------------------------------------------------------*/

CString VDEIODLL_EXPORT_API GetFileName(CString strPath,int& nCount)
{
	CString strFileName;
	CFileFind cfFile; //执行本地文件查找
	int i = 0;
	if (strPath.Right(1) != "\\")
	{
		strPath += _T("\\*.avi");
	}else
	{
		strPath += _T("*.avi");
	}

	BOOL bf = cfFile.FindFile(strPath);
	while (bf)
	{
		bf = cfFile.FindNextFile();
		CString cstrFileName;
		cstrFileName = cfFile.GetFileName();
		nCount++;
	}
	strFileName.Format(_T("视频%d"),nCount+1);
	return strFileName;
}

/*-------------------------------------------------------------------------------------*/

CString VDEIODLL_EXPORT_API GetResidualPlace(CString strPath)
{ 
	ULARGE_INTEGER   ulTotalSize;       //磁盘总空间大小       
	ULARGE_INTEGER   ulFreeSize;        //磁盘剩余空间大小
	ULARGE_INTEGER   ulAvailLableSize;  //录像文件需要的空间大小

	CString csStr,strTemp;
	csStr = strPath.Left(3);
	::GetDiskFreeSpaceEx(csStr,&ulTotalSize,&ulFreeSize,&ulAvailLableSize);
	strTemp.Format(_T("%ldM"),ulTotalSize.QuadPart/1024/1024);
	 
	if (ulTotalSize.QuadPart / 1024 /1024 < 500)
	{
		MessageBox(NULL,_T("【磁盘剩余空间不足1000，请整理磁盘】"),_T("消息提示"),MB_OK);
	} 
	else
	{
		return strTemp;
	}
	return strTemp;
}

/*-------------------------------------------------------------------------------------*/

void VDEIODLL_EXPORT_API DrawWindow(HWND hwnd)
{
	RECT rect;

	::GetWindowRect(hwnd, &rect);
	HDC hdc = ::GetDC(0);
	::SetROP2(hdc, R2_NOT);

	MoveToEx(hdc, rect.left, rect.top, NULL);
	LineTo(hdc, rect.right, rect.top);
	MoveToEx(hdc, rect.right, rect.top, NULL);
	LineTo(hdc, rect.right, rect.bottom);
	MoveToEx(hdc, rect.right, rect.bottom, NULL);
	LineTo(hdc, rect.left, rect.bottom);
	MoveToEx(hdc, rect.left, rect.bottom, NULL);
	LineTo(hdc, rect.left, rect.top);
	MoveToEx(hdc, rect.left + 1, rect.top + 1, NULL);
	LineTo(hdc, rect.right + 1, rect.top + 1);
	MoveToEx(hdc, rect.right - 1, rect.top + 1, NULL);
	LineTo(hdc, rect.right - 1, rect.bottom - 1);
	MoveToEx(hdc, rect.right - 1, rect.bottom -1 , NULL);
	LineTo(hdc, rect.left + 1, rect.bottom - 1);
	MoveToEx(hdc, rect.left + 1, rect.bottom - 1, NULL);
	LineTo(hdc, rect.left + 1, rect.top + 1);

	MoveToEx(hdc, rect.left + 2, rect.top + 2, NULL);
	LineTo(hdc, rect.right + 2, rect.top + 2);
	MoveToEx(hdc, rect.right - 2, rect.top + 2, NULL);
	LineTo(hdc, rect.right - 2, rect.bottom - 2);
	MoveToEx(hdc, rect.right - 2, rect.bottom -2 , NULL);
	LineTo(hdc, rect.left + 2, rect.bottom - 2);
	MoveToEx(hdc, rect.left + 2, rect.bottom - 2, NULL);
	LineTo(hdc, rect.left + 2, rect.top + 2);
}

/*-------------------------------------------------------------------------------------*/

VedioScreen* lpVeioScreen = NULL;

/*-------------------------------------------------------------------------------------*/


void VDEIODLL_EXPORT_API StartVedio(CString strFilePath,CString strFileName,int nRate,
	CPoint Point1,CPoint Point2,int nFlag,HWND GetCurHwnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE main_hInstance = AfxGetResourceHandle();    //获取主程序资源句柄
	AfxSetResourceHandle(theApp.m_hInstance);             //获取dll程序资源句柄
	if(NULL == lpVeioScreen)
	{
		lpVeioScreen = new VedioScreen(strFilePath,strFileName,nRate,Point1,Point2,nFlag,GetCurHwnd);
		lpVeioScreen->StartVedio();
	}
}

/*-------------------------------------------------------------------------------------*/

void VDEIODLL_EXPORT_API StopVedio()
{
	if (NULL != lpVeioScreen)
	{
		if (TRUE == lpVeioScreen->StopVedio())
		{
			delete lpVeioScreen;
			lpVeioScreen = NULL;
		}
	}
}

/*-------------------------------------------------------------------------------------*/

void VDEIODLL_EXPORT_API PauseVedio()
{
	lpVeioScreen->PauseVedio();
}

/*-------------------------------------------------------------------------------------*/

void VDEIODLL_EXPORT_API UnPauseVedio()
{
	lpVeioScreen->UnPauseVedio();
}

/*-------------------------------------------------------------------------------------*/

