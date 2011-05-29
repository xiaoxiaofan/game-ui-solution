#pragma once

#include "afxwin.h"

// CSelCapDevies dialog

class CSelCapDevies : public CDialog
{
	DECLARE_DYNAMIC(CSelCapDevies)

public:
	CSelCapDevies(vector<wstring>*pList,int num,CWnd* pParent = NULL);   // standard constructor
	virtual ~CSelCapDevies();
	vector<wstring>*_pList;
	int _iNum;
	int m_iSel;

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_list;
	afx_msg void OnBnClickedOk();
};
