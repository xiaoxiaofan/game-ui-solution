// TestDES.h : main header file for the TESTDES application
//

#if !defined(AFX_TESTDES_H__A9D77AF1_C840_429F_A8DA_3EAA9B7E48E8__INCLUDED_)
#define AFX_TESTDES_H__A9D77AF1_C840_429F_A8DA_3EAA9B7E48E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDESApp:
// See TestDES.cpp for the implementation of this class
//

class CTestDESApp : public CWinApp
{
public:
	CTestDESApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDESApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDESApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDES_H__A9D77AF1_C840_429F_A8DA_3EAA9B7E48E8__INCLUDED_)
