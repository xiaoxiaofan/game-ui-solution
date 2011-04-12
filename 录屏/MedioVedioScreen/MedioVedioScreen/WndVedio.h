#pragma once


// WndVedio 对话框

class WndVedio : public CDialog
{
	DECLARE_DYNAMIC(WndVedio)

public:
	WndVedio(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~WndVedio();

// 对话框数据
	enum { IDD = IDD_Vedio };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedCatch();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	HWND  GetWndHwnd();
public:
	HCURSOR    m_MoveCursor;   //移动光标
	HWND       m_CurHwnd;      //用来存放获取的控件的句柄
	HWND       m_PreHwnd;      //用来存放以前获取的控件的句柄
	BOOL       m_LeftIsDown;   //TRUE表示鼠标左键按下
	HINSTANCE  m_hDLL;
	HWND       m_GetCurHwnd;  
	
};
