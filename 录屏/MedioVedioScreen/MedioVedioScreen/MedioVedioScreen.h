
// MedioVedioScreen.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMedioVedioScreenApp:
// �йش����ʵ�֣������ MedioVedioScreen.cpp
//

class CMedioVedioScreenApp : public CWinApp
{
public:
	CMedioVedioScreenApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMedioVedioScreenApp theApp;