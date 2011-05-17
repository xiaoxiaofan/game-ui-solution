// XThreadBase.h: interface for the CAVThreadclass.
//
//////////////////////////////////////////////////////////////////////

#ifndef __XTHREADBASE_H__
#define __XTHREADBASE_H__

#include <NETEC/NETEC_Export.h>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#else
#include <semaphore.h>
#include <pthread.h>
#endif

class NETEC_API XThreadBase
{
public:
	XThreadBase(void);
	virtual ~XThreadBase(void);
public:
	bool StartThread(void);
	void WaitForStop(void);

	/*
	�˺���ֻ�����ڲ�����
	*/
#ifdef _WIN32
	static DWORD WINAPI InitThreadProc(PVOID pObj){
		return	((XThreadBase*)pObj)->ThreadProc();
	}
#else
	static void* InitThreadProc(void*pObj){
		((XThreadBase*)pObj)->ThreadProc();
		return 0;
	}
#endif
	/*
	�˺���ֻ�����ڲ�����
	*/
	unsigned long ThreadProc(void);

protected:
	/*
	���̺߳������������ڴ˺�����ʵ���߳�Ҫ������
	*/
	virtual void ThreadProcMain(void)=0;
protected:
#ifdef _WIN32
	DWORD	m_dwThreadID;		// �̱߳�ʶ
	HANDLE	m_hThread;			// �߳̾��
	HANDLE	m_evStop;
#else
    pthread_t	m_thread;
    sem_t		m_semWaitForStop;
    bool		m_bThreadStopped;
#endif
};

#endif
