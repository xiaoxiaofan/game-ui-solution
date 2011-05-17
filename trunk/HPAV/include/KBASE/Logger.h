/* KLog.h */

#pragma once

#include "CritSec.h"
#include "Utils.h"
#include <string>

#ifdef WIN32
#define snprintf _snprintf
#endif

//日志级别
typedef	enum _LOG_LEVEL
{
	LL_NONE			= 0,	//不显示日志信息
	LL_ERROR		= 1,    //显示错误信息级别
	LL_INFO     	= 2,    //显示运行信息级别(同时显示错误信息)
	LL_DEBUG		= 3,    //显示调试信息级别(同时显示错误信息和运行信息)
}LOG_LEVEL;

//---------------------------------------------------------------------------------------
// KLogger日志类定义
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
// LOG类定义
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