//NETEC_Client.h
#ifndef __NETEC_CLIENT_H__
#define __NETEC_CLIENT_H__

#include "NETEC_Session.h"

//����Ӧ�÷���
class NETEC_API NETEC_ClientCallback
{
public:
	NETEC_ClientCallback(void){};
	virtual~NETEC_ClientCallback(void){};
public:
	//�յ�����״̬
	virtual void OnNETEC_SessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0){};

	//����������Ӧ���յ������ݰ��ص�
	virtual void OnNETEC_ClientReceivedFromServer(const char* pData,int nLen){};
};

class NETEC_API NETEC_Client
{
public:
	NETEC_Client(void){};
	virtual~NETEC_Client(void){};
public:
	//���ӷ�����
	virtual int Connect(unsigned short nServerType,const char*cszIP,unsigned short usPort,const char*cszInterface)=0;
	//�Ͽ�����
	virtual void Disconnect(void)=0;

	//�������ݸ�ָ��������Server
	virtual int SendDataToServer(const char*pData,int nLen)=0;

	virtual unsigned int GetClientID(void)=0;

	//ȡ���ص�ַ
	virtual const char*GetLocalIP(void)=0;

	//ȡ������ַ
	virtual const char*GetNATIP(void)=0;

	static NETEC_Client*Create(NETEC_ClientCallback&rCallback);
};

#endif