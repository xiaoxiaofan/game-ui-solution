//NETEC_Session.h
#ifndef __NETEC_SESSION_H__
#define __NETEC_SESSION_H__

#include <NETEC/NETEC_Export.h>

//网络会话
class NETEC_API NETEC_Session
{
public:
	NETEC_Session(void){};
	virtual~NETEC_Session(void){};
public:
	typedef enum{
		CS_CONNECTING=0,		//正在连接
		CS_FAILED,				//无法连接
		CS_CONNECTED,			//已经连接
		CS_DISCONNECTED,		//断开连接
		CS_BUSY,				//网络忙(已断开正重连)
		CS_RECONNECTED,			//重连成功
		CS_IDLE,				//空闲
		CS_RESTARTED,			//连接重置了【连接断开了，并且又重新连接上了，但是换了一个新连接】
	}CONNECT_STATUS;
public:
	//连接服务器
	virtual int Connect(const char*cszIP,unsigned short usPort,const char*cszInterface)=0;
	//断开连接
	virtual void Disconnect(void)=0;
	//收到连接状态
	virtual void OnNETEC_SessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0)=0;
};

#endif