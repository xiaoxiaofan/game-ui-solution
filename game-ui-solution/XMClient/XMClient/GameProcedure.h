/****************************************\
*										*
* 			   游戏流程基类				*
*										*
\****************************************/

#pragma once
#include "stdafx.h"

class CGameProcedure 
{

public:	     /// 初始化静态变量
	static VOID		InitStaticMemeber(VOID);
	/// 消息主循环
	static VOID		MainLoop(VOID);
	/// 释放静态变量
	static VOID		ReleaseStaticMember(VOID);

protected:
	
	virtual LRESULT	MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	///创建主窗口
	static VOID		CreateMainWnd(VOID);
	///释放主窗口
	static VOID		DestroyMainWnd(VOID);
	///主窗口消息处理函数
	static LRESULT CALLBACK	_MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

protected:

	//窗口最小化
	static BOOL			m_bMinimized;
	//窗口最大化
	static BOOL			m_bMaximized;
	//窗口全屏化
	static BOOL			m_bFullScreen;
	//窗口位置
	static RECT			m_rectWindow;

};