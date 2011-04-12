
// MedioVedioScreenDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CMedioVedioScreenDlg 对话框
class CMedioVedioScreenDlg : public CDialogEx
{
// 构造
public:
	CMedioVedioScreenDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MEDIOVEDIOSCREEN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtFullScreen();
	afx_msg void OnBnClickedButArea();
	afx_msg void OnBnClickedButWndScreen();
	afx_msg void OnBnClickedButStop();
	afx_msg void OnBnClickedButPause();
	afx_msg void OnBnClickedButSetPath();
	afx_msg void OnBnClickedCheckAvi();
	afx_msg void OnStnClickedStaticplace();
	afx_msg void OnClose();

public:
	CEdit   m_FileName;
	CString m_strFileName;
	CEdit   m_FilePath;
	CString m_strFilePath;
	CEdit   m_Rate;
	int     m_nRate;
	CString m_strPlace;
	CStatic m_csPlace;
	CButton m_bCheckAvi;
	BOOL    m_CheckAvi;

public:
	HINSTANCE m_hDLL;
	CPoint m_p1;
	CPoint m_p2;
public:
	BOOL m_IsStop;
 	BOOL m_IsPause;
	int  m_nCount;
	HWND m_GetCurWndHwnd;
	BOOL m_bFlag;
	


	
};
