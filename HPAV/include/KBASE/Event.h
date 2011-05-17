#pragma once

#ifndef WIN32
#include <pthread.h>
#endif

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KEvent
{
public:
	KEvent(bool bManualReset = false);
	virtual ~KEvent(void);

	//�����κεȴ����߳������¼�����(���ź�)�򲻿���(���ź�)��
	void Set(void);

	//�ȴ��¼����źŻ�ʱ��ulTimeout�Ǻ��룬�������true���¼������ã�����ʱ��
	bool Wait(unsigned long ulTimeout);

	//�����¼�������(���ź�)��
	void Reset(void);

protected:

#ifdef WIN32
	HANDLE m_hEvent;
#else
	pthread_mutex_t m_mutex;
	pthread_cond_t	m_cond;
	int				m_nEvent;
	bool			m_bManualReset;
#endif
};

