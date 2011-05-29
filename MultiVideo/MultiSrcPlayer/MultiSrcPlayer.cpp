// MultiSrcPlayer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MultiSrcPlayer.h"
#include "MultiSrcPlayerDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMultiSrcPlayerApp

BEGIN_MESSAGE_MAP(CMultiSrcPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMultiSrcPlayerApp ����

CMultiSrcPlayerApp::CMultiSrcPlayerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMultiSrcPlayerApp ����

CMultiSrcPlayerApp theApp;


// CMultiSrcPlayerApp ��ʼ��

BOOL CMultiSrcPlayerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    // Verify that the VMR9 is present on this system
   
	CMultiSrcPlayerDlg dlg;
	
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}
	CoUninitialize();
	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
#ifdef _DEBUG
    void DbgMsg( char* szMessage, ... )
    {
        char szFullMessage[MAX_PATH];
        char szFormatMessage[MAX_PATH];

        // format message
        va_list ap;
        va_start(ap, szMessage);
        _vsnprintf( szFormatMessage, MAX_PATH, szMessage, ap);
        va_end(ap);
        strncat( szFormatMessage, "\n", MAX_PATH);
        strcpy( szFullMessage, "~*~*~*~*~*~ ");
        strcat( szFullMessage, szFormatMessage );
        OutputDebugStringA( szFullMessage );
    }
#else
    void DbgMsg( char* szMessage, ... ){;}
#endif