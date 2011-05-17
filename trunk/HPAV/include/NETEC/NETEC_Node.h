//NETEC_Node.h
#ifndef __NETEC_NODE_H__
#define __NETEC_NODE_H__

#include "NETEC_Session.h"
#include "NETEC.h"

//网络节点
class NETEC_API NETEC_Node
{
public:
	NETEC_Node(void);
	virtual~NETEC_Node(void);
public:
	/******************************************************************************
	* SetServerIP
	*描述：设置服务器IP
	*输入：	cszServerIP			-服务器IP
	*输出： 无
	*返回值：无
	*****************************************************************************/
	static void SetServerIP(const char*cszServerIP);
	static const char*GetServerIP(void);

	/******************************************************************************
	* SetServerPort
	*描述：设置服务器端口
	*输入：	usServerPort		-服务器端口
	*输出： 无
	*返回值：无
	*****************************************************************************/
	static void SetServerPort(unsigned short usServerPort);
	static unsigned short GetServerPort(void);

	/******************************************************************************
	* Start
	*描述：启动本节点
	*输入：	无
	*输出： 无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int Start(void);

	/******************************************************************************
	* IsStarted
	*描述：本节点是否已经启动
	*输入：	无
	*输出： 无
	*返回值：如果本节点已经启动，那么返回非0，否则返回0
	*****************************************************************************/
	static int IsStarted(void);

	/******************************************************************************
	* Stop
	*描述：停止本节点
	*输入：	无
	*输出： 无
	*返回值：无
	*****************************************************************************/
	static void Stop(void);

	/******************************************************************************
	* GetNodeID
	*描述：获取本节点的标识
	*输入：	无
	*输出： 无
	*返回值：本节点的标识
	*****************************************************************************/
	static const char*GetNodeID(void);

	/******************************************************************************
	* GetLocalIP
	*描述：获取本机IP
	*输入：	无
	*输出： 无
	*返回值：本地IP
	*****************************************************************************/
	static const char*GetLocalIP(void);

	/******************************************************************************
	* GetLocalPort
	*描述：获取本机的本地端口
	*输入：	无
	*输出： 无
	*返回值：本机的本地端口
	*****************************************************************************/
	static unsigned short GetLocalPort(void);

	/******************************************************************************
	* GetNATIP
	*描述：获取本机的外网的IP
	*输入：	无
	*输出： 无
	*返回值：本机的外网的IP
	*****************************************************************************/
	static const char*GetNATIP(void);

	/******************************************************************************
	* GetNATPort
	*描述：获取本机的外网的端口
	*输入：	无
	*输出： 无
	*返回值：本机的外网的端口
	*****************************************************************************/
	static unsigned short GetNATPort(void);

	/******************************************************************************
	* GetDomain
	*描述：获取所在的域
	*输入：	无
	*输出： 无
	*返回值：所在的域
	*****************************************************************************/
	static const char*GetDomain(void);

	/******************************************************************************
	* GetDomainType
	*描述：获取所在的域的类型
	*输入：	无
	*输出： 无
	*返回值：所在的域的类型
	*****************************************************************************/
	static NETEC::DOMAIN_TYPE GetDomainType(void);

	/******************************************************************************
	* GetMCUID
	*描述：获取连接的MCU标识
	*输入：	无
	*输出： 无
	*返回值：连接的MCU标识
	*****************************************************************************/
	static const char*GetMCUID(void);

	/******************************************************************************
	* GetMCUIP
	*描述：获取连接的MCU的IP地址
	*输入：	无
	*输出： 无
	*返回值：连接的MCU的IP地址
	*****************************************************************************/
	static const char*GetMCUIP(void);

	/******************************************************************************
	* GetMCUType
	*描述：获取连接的MCU的类型
	*输入：	无
	*输出： 无
	*返回值：连接的MCU的类型
	*****************************************************************************/
	static unsigned int GetMCUType(void);

	/******************************************************************************
	* SendDataToNode
	*描述：发送数据给节点
	*输入：	cszNodeID			-节点标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	static int SendDataToNode(unsigned int nFromAgentID,unsigned int nToAgentID,const char*cszNodeID,const char*pData,int nLen);

	/******************************************************************************
	* SendDataToAgent
	*描述：发送数据给网络应用
	*输入：	cszDomain			-网络应用所在的域
			nAgentID			-网络应用标识
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	static int SendDataToAgent(const char*cszDomain,unsigned int nAgentID,const char*pData,int nLen);

	/******************************************************************************
	* SendDataToRouter
	*描述：发送数据给网络路由
	*输入：	cszDomain			-网络路由所在的域
			pData				-要送的数据
			nLen				-要送的数据的长度
	*输出： 无
	*返回值：成功返回0；失败返回-1，表示网络未连通
	*****************************************************************************/
	static int SendDataToRouter(const char*cszDomain,const char*pData,int nLen);

	/******************************************************************************
	* GetConnectStatus
	*描述：获取连接状态
	*输入：	无
	*输出： 无
	*返回值：连接状态
	*****************************************************************************/
	static NETEC_Session::CONNECT_STATUS GetConnectStatus(void);

	/******************************************************************************
	* OnNETEC_NodeConnectStatusChanged
	*描述：网络连接状态的回调
	*输入：	cs					-网络连接状态
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_NodeConnectStatusChanged(NETEC_Session::CONNECT_STATUS cs){};

	/******************************************************************************
	* OnNETEC_NodeReceivedFromAgent
	*描述：收到网络应用数据包的回调
	*输入：	cszDomain				-网络应用所在的域
			nAgentID				-网络应用标识
			pData					-数据
			nLen					-数据长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_NodeReceivedFromAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};

	/******************************************************************************
	* OnNETEC_NodeReceivedFromRouter
	*描述：收到网络路由数据包的回调
	*输入：	cszDomain				-网络路由所在的域
			pData					-数据
			nLen					-数据长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_NodeReceivedFromRouter(const char*cszDomain,const char* pData,int nLen){};

	/******************************************************************************
	* OnNETEC_NodeReceivedFromNode
	*描述：收到网络节点数据包的回调
	*输入：	cszNodeID				-网络节点标识
			pData					-数据
			nLen					-数据长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_NodeReceivedFromNode(const char*cszNodeID,unsigned int nFromAgentID,unsigned int nToAgentID,const char* pData,int nLen){};

	/******************************************************************************
	* OnNETEC_NodeNodeDisconnected
	*描述：网络节点不在线的回调
	*输入：	cszNodeID				-网络节点标识
			pData					-数据
			nLen					-数据长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_NodeNodeDisconnected(const char*cszNodeID,unsigned int nFromAgentID,unsigned int nToAgentID,const char* pData,int nLen){};

	/******************************************************************************
	* OnNETEC_NodeAgentDisconnected
	*描述：网络应用不在线的回调
	*输入：	cszDomain				-网络应用所在的域
			nAgentID				-网络应用标识
			pData					-数据
			nLen					-数据长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_NodeAgentDisconnected(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};

	/******************************************************************************
	* OnNETEC_NodeRouterDisconnected
	*描述：网络路由不在线的回调
	*输入：	cszDomain				-网络路由所在的域
			pData					-数据
			nLen					-数据长度
	*输出： 无
	*返回值：无
	*****************************************************************************/
	virtual void OnNETEC_NodeRouterDisconnected(const char*cszDomain,const char* pData,int nLen){};

	/******************************************************************************
	* OnNETEC_NodeGetUserInfo
	*描述：获取用户信息的回调
	*输入：	cszUserID				-用户标识
	*输出： szNodeID				-用户的网络节点标识
	*返回值：成功返回0；失败返回-1，表示该用户不在线
	*****************************************************************************/
	virtual int OnNETEC_NodeGetUserInfo(const char*cszUserID,char*szNodeID){return -1;};
	
	static void SetLocalUserID(const char*cszLocalUserID);
	static void SetLocalUserName(const char*cszLocalUserName);
};


#endif