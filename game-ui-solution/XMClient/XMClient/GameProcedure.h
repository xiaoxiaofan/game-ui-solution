/****************************************\
*										*
* 			   ��Ϸ���̻���				*
*										*
\****************************************/

#pragma once
#include "stdafx.h"

class CGameProcedure 
{

public:	     /// ��ʼ����̬����
	static VOID		InitStaticMemeber(VOID);
	/// ��Ϣ��ѭ��
	static VOID		MainLoop(VOID);
	/// �ͷž�̬����
	static VOID		ReleaseStaticMember(VOID);

protected:
	
	virtual LRESULT	MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	///����������
	static VOID		CreateMainWnd(VOID);
	///�ͷ�������
	static VOID		DestroyMainWnd(VOID);
	///��������Ϣ������
	static LRESULT CALLBACK	_MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	

protected:

	//������С��
	static BOOL			m_bMinimized;
	//�������
	static BOOL			m_bMaximized;
	//����ȫ����
	static BOOL			m_bFullScreen;
	//����λ��
	static RECT			m_rectWindow;

};