#pragma once

#include "KPOP3.h"

AFX_EXT_CLASS enum
{
	MAIL_TEST=0,
	MAIL_COUNT=1,
};

#define WM_USER_MAIL_TEST				WM_USER + 31001
#define WM_USER_MAIL_COUNTSIZE			WM_USER + 31002

class AFX_EXT_CLASS IMailCheckerNotify
{
public:
	IMailCheckerNotify(void){};
	virtual ~IMailCheckerNotify(void){};

	//事件:连接测试
	virtual void OnMailTest(BOOL bSuccess)=0;
	//事件:获取邮件数及大小
	virtual void OnMailCountSize(int nCount,int nSize)=0;
};

class AFX_EXT_CLASS KMailChecker : public CWnd, public KThread
{
public:
	KMailChecker(IMailCheckerNotify& rMailCheckerNotify);
	virtual ~KMailChecker(void);

	IMailCheckerNotify& m_rMailCheckerNotify;

	char m_szUser[60];
	char m_szPass[60];
	char m_szAddr[60];
	int m_nPort;
	unsigned long m_ulTimeOut;

	bool Create(void);
	void Close(void);
	bool Check(unsigned char ucType,const char* cszUser,const char* cszPass,const char* cszAddr,unsigned short usPort=110,unsigned long ulTimeOut=2000);

protected:
	DECLARE_DYNAMIC(KMailChecker)
	afx_msg LRESULT OnMailTestMsg(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMailCountSizeMsg(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	unsigned char	m_ucType;
	KPOP3Connection m_POP3;
	KCritSec		m_CritSec;
	void ThreadProcMain(void);
};

