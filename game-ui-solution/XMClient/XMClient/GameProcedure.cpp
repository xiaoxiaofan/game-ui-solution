#include "stdafx.h"
#include "..\common\TDMath.h"
#include "resource.h"
#include "GameProcedure.h"

const CHAR MAINWINDOW_CLASS[]	= "SM WndClass";
const UINT DEFWINDOW_STYLE		= WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ; 
RECT CGameProcedure::m_rectWindow;
BOOL CGameProcedure::m_bFullScreen = FALSE;
BOOL CGameProcedure::m_bMaximized = TRUE;
BOOL CGameProcedure::m_bMinimized = FALSE;


VOID CGameProcedure::InitStaticMemeber(VOID)
{
	m_rectWindow.left = 200;
	m_rectWindow.top = 100;
	m_rectWindow.right = 1000;
	m_rectWindow.bottom = 700;
	CreateMainWnd();
}

VOID CGameProcedure::CreateMainWnd()
{
	WNDCLASSEX wndClass;
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.lpszClassName = MAINWINDOW_CLASS;
	wndClass.lpfnWndProc = _MainWndProc;
	wndClass.cbClsExtra =0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)NULL;
	wndClass.hCursor = LoadCursor(NULL,(LPCTSTR)IDC_ATTACK);
	wndClass.hIcon = LoadIcon(NULL,(LPCTSTR)IDI_GAME);
	wndClass.hIconSm = LoadIcon(NULL,(LPCTSTR)IDI_SMALL);
	wndClass.hInstance = g_hInstance;
	wndClass.style = 0;
	wndClass.lpszMenuName = NULL;

	RegisterClassEx(&wndClass);

	//´´½¨´°¿Ú
	CHAR szTitle[MAX_PATH];
	_snprintf(szTitle, MAX_PATH, "%s %s (%s %s)", GAME_TITLE, VERSION_INFO, __DATE__, __TIME__);

	HWND hwnd = CreateWindowEx(NULL,MAINWINDOW_CLASS,szTitle,DEFWINDOW_STYLE,m_rectWindow.left,m_rectWindow.top,
		             m_rectWindow.right - m_rectWindow.left,m_rectWindow.bottom - m_rectWindow.top,NULL,NULL,g_hInstance,NULL);

	if (!hwnd)
	{
		return;
	}

	ShowWindow(hwnd,SW_SHOW);
	UpdateWindow(hwnd);
	g_hMainWnd = hwnd;
}

VOID CGameProcedure::DestroyMainWnd()
{
	DestroyWindow(g_hMainWnd);
	UnregisterClass(MAINWINDOW_CLASS,NULL);
	g_hMainWnd = NULL;
}

LRESULT CGameProcedure::MainWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	
	return DefWindowProc(hWnd,message,wParam,lParam);
}

LRESULT CALLBACK CGameProcedure::_MainWndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
	
	switch(message)
	{
	case WM_CLOSE:
		{
			DestroyMainWnd();
		}
		break;
	case WM_DESTROY :
		{
			PostQuitMessage(0);
		}
	    break;
	case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(g_hMainWnd,&ps);
			EndPaint(g_hMainWnd,&ps);
		}
		break;
	case WM_SIZE:
		{
			
		}
		break;
	default:
		break;

	}
	
	return DefWindowProc(hWnd,message,wParam,lParam);

}

VOID CGameProcedure::MainLoop( VOID )
{
	
	MSG msg;
	ZeroMemory(&msg,sizeof(MSG));

	while (GetMessage(&msg,g_hMainWnd,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

VOID CGameProcedure::ReleaseStaticMember( VOID )
{
	
}










	 