#pragma once

#include "Thread.h"
#include "CritSec.h"
#include <map>

//---------------------------------------------------------------------------------------
typedef struct _TIMER_EVENT
{
	unsigned long elapse;
	unsigned long timestamp;
	unsigned short flag;
}TIMER_EVENT,*PTIMER_EVENT;

//---------------------------------------------------------------------------------------
typedef std::map<unsigned int,PTIMER_EVENT>	TIMER_EVENT_MAP;

//---------------------------------------------------------------------------------------
class AFX_EXT_CLASS KTimer : public KThread
{
public:
	KTimer(void);
	~KTimer(void);

	/* ������ʱ�� */
	bool StartTimer(void);

	/* ֹͣ��ʱ�� */
	void StopTimer(void);

	/* ���ü�ʱ���¼�: nEventID=�¼�ID; nElapse=�¼����(ms) */
	void SetTimerEvent(unsigned int nEventID,unsigned long ulElapse);

	/* ɾ����ʱ��ʱ��: nEvnetID=ָ��ɾ�����¼�ID */
	void KillTimerEvent(unsigned int nEventID);

protected:
	/* �¼������ص�,�̳и÷��������¼�(�麯��) */
	virtual void OnTimerEvent(unsigned int nEventID){};
	
private:
	bool				m_bWantToStop;
	KCritSec			m_secTimerEvent;
	TIMER_EVENT_MAP		m_mapTimerEvent;

	virtual void ThreadProcMain(void);
	bool ProcessTimerEvent(void);
};
