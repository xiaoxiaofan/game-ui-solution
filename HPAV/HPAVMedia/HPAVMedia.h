
// HPAVMedia.h : HPAVMedia Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CHPAVMediaApp:
// �йش����ʵ�֣������ HPAVMedia.cpp
//

class CHPAVMediaApp : public CWinApp
{
public:
	CHPAVMediaApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHPAVMediaApp theApp;
