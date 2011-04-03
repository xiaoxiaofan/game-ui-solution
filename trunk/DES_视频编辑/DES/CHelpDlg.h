#if !defined(AFX_CHELPDLG_H__E6C357F1_8ED8_45B5_8C90_CA63BCBEC931__INCLUDED_)
#define AFX_CHELPDLG_H__E6C357F1_8ED8_45B5_8C90_CA63BCBEC931__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CHelpDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHelpDlg dialog

class CHelpDlg : public CDialog
{
// Construction
public:
	CHelpDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHelpDlg)
	enum { IDD = IDD_DIALOG_HELP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHelpDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHELPDLG_H__E6C357F1_8ED8_45B5_8C90_CA63BCBEC931__INCLUDED_)
