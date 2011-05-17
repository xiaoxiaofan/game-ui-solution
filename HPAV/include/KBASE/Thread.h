/* KThread base class. 
 * 
 *	Example:
 *	class TestThread:public KThread
 *	{
 *	public:
 *		TestThread(){m_bWantToStop=false;};
 *		virtual~TestThread(){};
 *	public:
 *		bool Start(void){return StartThread();};
 *		void Stop(void){m_bWantToStop=true;WaitForStop();};
 *	protected:
 *		void ThreadProcMain(void)
 *		{
 *			while(!m_bWantToStop)
 *			{
 *				//...
 *				Sleep(1000);
 *			}
 *		};
 *	protected:
 *		bool	m_bWantToStop;
 *	}; 
 */

#pragma once

#ifndef WIN32
  #include <pthread.h>
  #include <semaphore.h>
#endif

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KThread
{
public:
	KThread();
	virtual ~KThread();

	//�����̣߳��ɹ�����true,ʧ�ܷ���false,ֻ���ڸý��̴������߳�������ϵͳ����ʱ�ŷ���false
	bool StartThread(void);

	//�ȴ��߳��˳������ô˺���ǰ������÷�������ȷ�������̺߳������˳���������ô˺���������
	void WaitForStop(void);

	//����߳�ID
#ifdef WIN32
	DWORD GetThreadID(void){return m_dwThreadID;};
#else
	pthread_t GetThreadID(void){return m_thread;};
#endif

protected:
	// ���̺߳������������ڴ˺�����ʵ���߳�Ҫ������
	virtual void ThreadProcMain(void)=0;

#ifdef WIN32
	DWORD	m_dwThreadID;		// �̱߳�ʶ
	HANDLE	m_hThread;			// �߳̾��
	HANDLE	m_evStop;
#else
    pthread_t	m_thread;
    sem_t		m_semWaitForStop;
    bool		m_bThreadStopped;
#endif

private:
	unsigned long ThreadProc(void);
#ifdef WIN32
	static DWORD WINAPI InitThreadProc(PVOID pObj){
		return	((KThread*)pObj)->ThreadProc();
	}
#else
	static void* InitThreadProc(void*pObj){
		((KThread*)pObj)->ThreadProc();
		return 0;
	}
#endif
};

