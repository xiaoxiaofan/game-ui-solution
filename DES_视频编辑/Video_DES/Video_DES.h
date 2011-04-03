// Video_DES.h : main header file for the Video_DES DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CVideo_DESApp
// See Video_DES.cpp for the implementation of this class
//

class CVideo_DESApp : public CWinApp
{
public:
	CVideo_DESApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
