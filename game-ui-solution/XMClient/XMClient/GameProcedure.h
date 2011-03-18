/****************************************\
*										*
* 			   游戏流程基类				*
*										*
\****************************************/

#pragma once


class CGameProcedure 
{
public:	     /// 初始化静态变量
	static VOID		InitStaticMemeber(VOID);
	///	将一个游戏循环激活
	static VOID		SetActiveProc(CGameProcedure* pToActive);
	///处理窗口大小发生改变的情况
	static VOID		HandlePossibleSizeChange(UINT message, WPARAM wParam, LPARAM lParam);

public:

protected:
	virtual VOID	Init(VOID) = 0;
	virtual VOID	Tick(VOID);
	virtual VOID	Render(VOID) = 0;
	virtual VOID	Release(VOID) = 0;
	virtual VOID	ProcessInput(VOID);
	virtual VOID	CloseRequest(VOID);
	virtual LRESULT	MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	///创建主窗口
	static VOID		CreateMainWnd(VOID);
	///释放主窗口
	static VOID		DestroyMainWnd(VOID);
	///主窗口消息处理函数
	static LRESULT CALLBACK	_MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	///处理窗口比例发生改变时
	/* dwChanging-
	|		WMSZ_LEFT/WMSZ_RIGHT
	|		WMSZ_TOP/WMSZ_BOTTOM
	| dwAnchor-
	|		WMSZ_TOPLEFT    
	|		WMSZ_TOPRIGHT   
	|		WMSZ_BOTTOM     
	|		WMSZ_BOTTOMLEFT 
	|		WMSZ_BOTTOMRIGHT
	*/
	static VOID		KeepWindowFOV(RECT* pRect, UINT dwChanging, UINT dwAnchor);




protected:
	//-------------------------------------------
	//内部控制变量

	//窗口最小化
	static BOOL			m_bMinimized;
	//窗口最大化
	static BOOL			m_bMaximized;
	//窗口全屏化
	static BOOL			m_bFullScreen;
	//窗口位置
	static RECT			m_rectWindow;
	//窗口比例(3:4=0.75)
	static FLOAT		m_fWindowFOV;
	//Frame<->Client的差值
	static RECT			m_rectFCOffset;
	//窗口处于焦点状态
	static BOOL			m_bActive;
	//渲染暂停
	static BOOL			m_bRenderingPaused;
	//ui获得输入状态
	static BOOL			m_bUIHandleInput;

	//桢速控制
	static FLOAT		m_fFPS;


};