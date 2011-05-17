#pragma once

#ifndef WIN32
#include <pthread.h>
#endif

//---------------------------------------------------------------------------------------
//�ٽ�����:���������߳��ٽ���
class AFX_EXT_CLASS KCritSec  
{
public:
	KCritSec();
	virtual ~KCritSec();

	// �����ٽ���
    void Lock(void);

	// �����ٽ���
    void Unlock(void);

protected:

#ifdef WIN32
    CRITICAL_SECTION m_CritSec;
#else
	pthread_mutex_t m_pMutex;
#endif
};
