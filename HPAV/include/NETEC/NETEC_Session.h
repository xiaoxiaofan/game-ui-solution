//NETEC_Session.h
#ifndef __NETEC_SESSION_H__
#define __NETEC_SESSION_H__

#include <NETEC/NETEC_Export.h>

//����Ự
class NETEC_API NETEC_Session
{
public:
	NETEC_Session(void){};
	virtual~NETEC_Session(void){};
public:
	typedef enum{
		CS_CONNECTING=0,		//��������
		CS_FAILED,				//�޷�����
		CS_CONNECTED,			//�Ѿ�����
		CS_DISCONNECTED,		//�Ͽ�����
		CS_BUSY,				//����æ(�ѶϿ�������)
		CS_RECONNECTED,			//�����ɹ�
		CS_IDLE,				//����
		CS_RESTARTED,			//���������ˡ����ӶϿ��ˣ������������������ˣ����ǻ���һ�������ӡ�
	}CONNECT_STATUS;
public:
	//���ӷ�����
	virtual int Connect(const char*cszIP,unsigned short usPort,const char*cszInterface)=0;
	//�Ͽ�����
	virtual void Disconnect(void)=0;
	//�յ�����״̬
	virtual void OnNETEC_SessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0)=0;
};

#endif