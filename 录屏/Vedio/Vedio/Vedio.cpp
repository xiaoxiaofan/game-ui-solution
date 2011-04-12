// Vedio.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "Vedio.h"
#include "VedioScreen.h"
#include "WVedio.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CVedioApp

BEGIN_MESSAGE_MAP(CVedioApp, CWinApp)
END_MESSAGE_MAP()


// CVedioApp ����

CVedioApp::CVedioApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CVedioApp ����

CVedioApp theApp;


// CVedioApp ��ʼ��

BOOL CVedioApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

/*-------------------------------------------------------------------------------------*/

void VDEIODLL_EXPORT_API GetRect(CPoint& Point1,CPoint& Point2,BOOL& bFlag)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE main_hInstance = AfxGetResourceHandle();    //��ȡ��������Դ���
	AfxSetResourceHandle(theApp.m_hInstance);             //��ȡdll������Դ���
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
	TCHAR  szPath[MAX_PATH];                                    //����·������
	BROWSEINFO bwInfo;                                          //����·�������ṹ����Ϣ
	bwInfo.hwndOwner              = NULL;
	bwInfo.pidlRoot               = NULL;
	bwInfo.lpszTitle              = _T("�ļ�����·��");         //�Ի������
	bwInfo.pszDisplayName         = szPath;                     //ѡ���ļ���·��
	bwInfo.ulFlags                = BIF_RETURNONLYFSDIRS;       //���
	bwInfo.lpfn                   = NULL;                       //Ĭ��ֵΪNULL
	bwInfo.lParam                 = NULL;                       //�ص���Ϣ      
	LPITEMIDLIST  lpItemIDList = SHBrowseForFolder(&bwInfo);    //��ʾ�ļ�����Ի���
	if (lpItemIDList)
	{
		if (SHGetPathFromIDList(lpItemIDList,szPath))        //�ж��Ƿ����ļ���·��
		{
			strFilePath = szPath;                   	    //����ļ���·��
		}
	}else
	{
		strFilePath = "";                                    //�ļ���·��Ϊ��
	}
	return strFilePath;
}

/*-------------------------------------------------------------------------------------*/

CString VDEIODLL_EXPORT_API GetFileName(CString strPath,int& nCount)
{
	CString strFileName;
	CFileFind cfFile; //ִ�б����ļ�����
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
	strFileName.Format(_T("��Ƶ%d"),nCount+1);
	return strFileName;
}

/*-------------------------------------------------------------------------------------*/

CString VDEIODLL_EXPORT_API GetResidualPlace(CString strPath)
{ 
	ULARGE_INTEGER   ulTotalSize;       //�����ܿռ��С       
	ULARGE_INTEGER   ulFreeSize;        //����ʣ��ռ��С
	ULARGE_INTEGER   ulAvailLableSize;  //¼���ļ���Ҫ�Ŀռ��С

	CString csStr,strTemp;
	csStr = strPath.Left(3);
	::GetDiskFreeSpaceEx(csStr,&ulTotalSize,&ulFreeSize,&ulAvailLableSize);
	strTemp.Format(_T("%ldM"),ulTotalSize.QuadPart/1024/1024);
	 
	if (ulTotalSize.QuadPart / 1024 /1024 < 500)
	{
		MessageBox(NULL,_T("������ʣ��ռ䲻��1000����������̡�"),_T("��Ϣ��ʾ"),MB_OK);
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
	HINSTANCE main_hInstance = AfxGetResourceHandle();    //��ȡ��������Դ���
	AfxSetResourceHandle(theApp.m_hInstance);             //��ȡdll������Դ���
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

