//NETEC_Server.h
#ifndef __NETEC_SERVER_H__
#define __NETEC_SERVER_H__

#include "NETEC_Session.h"

//����Server
class NETEC_ServerCallback
{
public:
	NETEC_ServerCallback(void){};
	virtual~NETEC_ServerCallback(void){};
public:
	virtual void OnNETEC_ServerClientConnected(unsigned long ulClientID,const char*cszClientRemoteIP)=0;
	virtual void OnNETEC_ServerClientDisconnected(unsigned long ulClientID)=0;
	virtual void OnNETEC_ServerReceivedFromClient(unsigned long ulClientID,const char*pData,int nLen)=0;

};

class NETEC_API NETEC_Server
{
public:
	NETEC_Server(void){};
	virtual ~NETEC_Server(void){};
public:
	//�������ط���
	virtual int Start(void)=0;
	
	//ֹͣ���ط���
	virtual void Stop(void)=0;

	//��ÿͻ�SESSION��Ŀ
	virtual unsigned int GetClientCount(void)=0;

	//�������ݸ�ָ��������ͻ���
	virtual int SendDataToClient(unsigned int nClientID,const char*pData,int nLen)=0;

	//ǿ�ƶϿ��ͻ���
	virtual void DisconnectClient(unsigned int nClientID)=0;

	static NETEC_Server*Create(NETEC_ServerCallback&rCallback,unsigned short usServerType);
};

#endif