/* KLog.h */

#pragma once

#include "CritSec.h"
#include "Utils.h"
#include <string>

#ifdef WIN32
#define snprintf _snprintf
#endif

//��־����
typedef	enum _LOG_LEVEL
{
	LL_NONE			= 0,	//����ʾ��־��Ϣ
	LL_ERROR		= 1,    //��ʾ������Ϣ����
	LL_INFO     	= 2,    //��ʾ������Ϣ����(ͬʱ��ʾ������Ϣ)
	LL_DEBUG		= 3,    //��ʾ������Ϣ����(ͬʱ��ʾ������Ϣ��������Ϣ)
}LOG_LEVEL;

//---------------------------------------------------------------------------------------
// KLogger��־�ඨ��
class AFX_EXT_CLASS KLogger
{
public:
    KLogger(void);
    virtual ~KLogger();
    
    bool Open(LOG_LEVEL nLevel=LL_NONE);
    void Close(void);
    void Write(const char* fmt,va_list args);

	void SetLevel(LOG_LEVEL nLevel);
    LOG_LEVEL GetLevel(void);

protected:
	LOG_LEVEL		m_nLevel;
};

//---------------------------------------------------------------------------------------
// LOG�ඨ��
class AFX_EXT_CLASS LOG
{
public:
    LOG(void){};
    virtual ~LOG(){};

    static bool START(LOG_LEVEL nLevel);
    static void STOP(void);
	static void SETLEVEL(LOG_LEVEL nLevel);
    static void DBG(const char* fmt,...);
    static void INF(const char* fmt,...);
    static void ERR(const char* fmt,...); 
};