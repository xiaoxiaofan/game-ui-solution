#include "stdafx.h"
#include "..\common\TDMath.h"
#include "resource.h"


const CHAR MAINWINDOW_CLASS[]	= "XianMu WndClass";

const INT DEFWINDOW_WIDTH		= 800;
const INT DEFWINDOW_HEIGHT		= 600;

const UINT DEFWINDOW_STYLE		= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ; 



VOID CGameProcedure::InitStaticMemeber(VOID)
{

}

VOID CGameProcedure::Init()
{

}

VOID CGameProcedure::CreateMainWnd()
{
	fVector2 fScreenDisplay;
	fScreenDisplay.x = 800;
	fScreenDisplay.y = 600;
	



	SetRect(m_rectWindow,200,100,DEFWINDOW_WIDTH,DEFWINDOW_HEIGHT);
	//------------------------------------------------------
	//注册窗口类
	WNDCLASSEX wcex;
	wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wcex.lpfnWndProc	= (WNDPROC)_MainWndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= g_hInstance;
	wcex.hIcon			= LoadIcon(g_hInstance, (LPCTSTR)IDI_GAME);
	wcex.hCursor		= LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground	= (HBRUSH)NULL; //GetStockObject(WHITE_BRUSH);
	wcex.lpszMenuName	= (LPCTSTR)NULL;
	wcex.lpszClassName	= MAINWINDOW_CLASS;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);

	RegisterClassEx(&wcex);

	//------------------------------------------------------
	//创建窗口
	CHAR szTitle[MAX_PATH];
	_snprintf(szTitle, MAX_PATH, "%s %s (%s %s)", GAME_TITLE, VERSION_INFO, __DATE__, __TIME__);

	HWND hWnd = CreateWindowEx(NULL, MAINWINDOW_CLASS, szTitle, 
		DEFWINDOW_STYLE,
		m_rectWindow.left, m_rectWindow.top, 
		m_rectWindow.right-m_rectWindow.left, 
		m_rectWindow.bottom-m_rectWindow.top,
		NULL, NULL, g_hInstance, NULL);

	if (!hWnd)
	{
		
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	g_hMainWnd = hWnd;
}

VOID CGameProcedure::DestroyMainWnd()
{

}

VOID CGameProcedure::HandlePossibleSizeChange(UINT message, WPARAM wParam, LPARAM lParam)
{

}

VOID CGameProcedure::CloseRequest()
{

}

VOID CGameProcedure::KeepWindowFOV(RECT* pRect, UINT dwChanging, UINT dwAnchor)
{

}

VOID CGameProcedure::Tick()
{
	
}








	 