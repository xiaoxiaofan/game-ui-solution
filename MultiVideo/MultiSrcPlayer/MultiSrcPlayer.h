// MultiSrcPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMultiSrcPlayerApp:
// �йش����ʵ�֣������ MultiSrcPlayer.cpp
//

class CMultiSrcPlayerApp : public CWinApp
{
public:
	CMultiSrcPlayerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMultiSrcPlayerApp theApp;
