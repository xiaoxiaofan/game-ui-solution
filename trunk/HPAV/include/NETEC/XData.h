//XData.h

#ifndef __XDATA_H__
#define __XDATA_H__

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string>

#ifdef _WIN32
#include <winsock2.h>
#else
#include <NETEC/XAutoLock.h>
#endif
class XData
{
public:
	XData(const void*pData,int nLen);
	virtual~XData(void);
public:
	virtual void AddRef(void);
	virtual void Release(void);

	virtual void*GetData(void);
	virtual int GetLen(void);
protected:
#ifdef _WIN32
#ifdef _WIN32_WCE
    LONG			m_cRef;
#else
    volatile LONG	m_cRef;
#endif
#else
	volatile long	m_cRef;
	XCritSec		m_csRef;
#endif

	void*			m_pData;
	int				m_nDataLen;
};


#endif

