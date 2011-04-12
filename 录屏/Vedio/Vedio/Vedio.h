// Vedio.h : Vedio DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "resource.h"		// 主符号
#include <Vfw.h>
#include <MMSystem.h>

#pragma comment (lib,"vfw32.lib")
#pragma comment (lib,"winmm.lib")
#include <cmath>
using namespace std;

// CVedioApp
// 有关此类实现的信息，请参阅 Vedio.cpp

/*------------------------------------------------------------------------------------------*/

#define VDEIODLL_EXPORT_API __declspec(dllexport)

/*------------------------------------------------------------------------------------------*/
extern "C"
{
	void VDEIODLL_EXPORT_API GetRect(CPoint& Point1,CPoint& Point2,BOOL& bFlag);
}
/*------------------------------------------------------------------------------------------*/

extern "C"
{
	CString VDEIODLL_EXPORT_API GetFilePath();
}
/*------------------------------------------------------------------------------------------*/
extern "C"
{
	CString VDEIODLL_EXPORT_API GetFileName(CString strPath,int& nCount);
}
/*------------------------------------------------------------------------------------------*/

extern "C"
{
	void VDEIODLL_EXPORT_API StartVedio(CString strFilePath,CString strFileName,int nRate,
		CPoint Point1,CPoint Point2,int nFlag,HWND GetCurHwnd);
}

/*------------------------------------------------------------------------------------------*/
extern "C"
{
	void VDEIODLL_EXPORT_API StopVedio();
}

/*------------------------------------------------------------------------------------------*/

extern "C"
{
	void VDEIODLL_EXPORT_API PauseVedio();
}

/*------------------------------------------------------------------------------------------*/

extern "C"
{
	void VDEIODLL_EXPORT_API UnPauseVedio();
}


/*------------------------------------------------------------------------------------------*/

extern "C"
{
	CString VDEIODLL_EXPORT_API GetResidualPlace(CString strPath);
}

/*------------------------------------------------------------------------------------------*/

extern "C"
{
	void   VDEIODLL_EXPORT_API DrawWindow(HWND hwnd/*,CDC*pDC*/);
}

/*------------------------------------------------------------------------------------------*/


class CVedioApp : public CWinApp
{
public:
	CVedioApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
