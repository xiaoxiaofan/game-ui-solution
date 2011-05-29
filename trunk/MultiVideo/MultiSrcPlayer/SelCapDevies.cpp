// SelCapDevies.cpp : implementation file
//

#include "stdafx.h"
#include "MultiSrcPlayer.h"
#include "SelCapDevies.h"
#include ".\selcapdevies.h"


// CSelCapDevies dialog

IMPLEMENT_DYNAMIC(CSelCapDevies, CDialog)
CSelCapDevies::CSelCapDevies(vector<wstring>*plist,int num,CWnd* pParent )
	: CDialog(CSelCapDevies::IDD, pParent)
{
	_pList = plist;
	_iNum = num;
	m_iSel = -1;
}

CSelCapDevies::~CSelCapDevies()
{
}

void CSelCapDevies::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_list);
}


BEGIN_MESSAGE_MAP(CSelCapDevies, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSelCapDevies message handlers

BOOL CSelCapDevies::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_iSel = -1;
	
	for(int i = 0 ; i<_iNum;i++)
	{
		int size = (int)(*_pList)[i].size();
		wchar_t *str = new wchar_t[size];
		(*_pList)[i].copy(str,size,0);
		str[size -1] = L'\0';
		m_list.AddString(CW2A(str));
		delete []str;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CSelCapDevies::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_iSel = m_list.GetCurSel();
	OnOK();
}
