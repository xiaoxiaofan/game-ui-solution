//NETEC_UDTIO.h
#ifndef __NETEC_UDTIO_H__
#define __NETEC_UDTIO_H__

#ifndef UDTSOCKET
typedef int UDTSOCKET;
#endif

class NETEC_UDTIONotify
{
public:
	NETEC_UDTIONotify(void){};
	virtual~NETEC_UDTIONotify(void){};
public:
	virtual bool OnNETEC_UDTIONotifyConnected(unsigned long ulType,const void*pData,int nLen,UDTSOCKET hSocket)=0;
};

class NETEC_UDTIO
{
public:
	NETEC_UDTIO(void){};
	virtual~NETEC_UDTIO(void){};
public:
	virtual void ReleaseConnections(void)=0;
	virtual unsigned short GetUDTPort(void)=0;
};

NETEC_UDTIO*NETEC_UDTIOCreate(NETEC_UDTIONotify&rNETEC_UDTIONotify,unsigned short usUDTPort);

#endif