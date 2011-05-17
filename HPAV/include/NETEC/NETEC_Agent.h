//NETEC_Agent.h
#ifndef __NETEC_AGENT_H__
#define __NETEC_AGENT_H__

#include "NETEC_Session.h"

//����Ӧ�÷���
class NETEC_AgentCallback
{
public:
	NETEC_AgentCallback(void){};
	virtual~NETEC_AgentCallback(void){};
public:
	//����ڵ��뱾����Ӧ�öϿ����ӵĻص�
	virtual void OnNETEC_AgentNodeDisconnected(const char*cszDomain,const char*cszNodeID,const char*pData,int nLen){};

	//����������Ӧ���յ������ݰ��ص�
	virtual void OnNETEC_AgentReceivedFromAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};
	
	//������ڵ��յ������ݰ��ص�
	virtual void OnNETEC_AgentReceivedFromNode(const char*cszDomain,const char*cszNodeID,const char* pData,int nLen){};

	//ָ����Agent������
	virtual void OnNETEC_AgentAgentDisconnected(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};

	//ָ����Router������
	virtual void OnNETEC_AgentRouterDisconnected(const char*cszDomain){};

	//������ڵ��յ������ݰ��ص�
	virtual void OnNETEC_AgentReceivedFromRouter(const char* pData,int nLen){};

	//ָ����MCU������
	virtual void OnNETEC_AgentMCUDisconnected(const char*cszMCUID){};

	/******************************************************************************
	* OnNETEC_AgentConnectStatusChanged
	*����������״̬�ı�Ļص�
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_AgentConnectStatusChanged(void){};

	/******************************************************************************
	* OnNETEC_AgentLoginSuccessful
	*��������¼�ɹ��Ļص�
	*���룺	��
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual void OnNETEC_AgentLoginSuccessful(void){};
	
	/******************************************************************************
	* OnNETEC_AgentLoginError
	*��������¼ʧ�ܵĻص�
	*���룺	��
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual void OnNETEC_AgentLoginError(void){};

	//����������Ӧ���յ������ݰ��ص�
	virtual void OnNETEC_AgentCastFromAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen){};
};

class NETEC_API NETEC_Agent
{
public:
	NETEC_Agent(void){};
	virtual~NETEC_Agent(void){};
public:
	/******************************************************************************
	* SetServerIP
	*���������÷�����IP
	*���룺	cszServerIP			-������IP
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void SetServerIP(const char*cszServerIP)=0;

	/******************************************************************************
	* SetServerPort
	*���������÷������˿�
	*���룺	usServerPort		-�������˿�
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void SetServerPort(unsigned short usServerPort)=0;

	/******************************************************************************
	* SetLocalIP
	*���������ñ���IP���������ӷ�����
	*���룺	cszLocalIP			-������IP
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void SetLocalIP(const char*cszLocalIP)=0;

	/******************************************************************************
	* SetPassword
	*���������õ�����������֤������
	*���룺	cszPassword			-����
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void SetPassword(const char*cszPassword)=0;

	/******************************************************************************
	* SetVersion
	*���������ð汾
	*���룺	cszVersion			-�汾
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void SetVersion(const char*cszVersion)=0;

	/******************************************************************************
	* Start
	*����������
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int Start(void)=0;

	/******************************************************************************
	* IsStarted
	*�������Ƿ��Ѿ�����
	*���룺	��
	*����� ��
	*����ֵ������Ѿ���������ô���ط�0�����򷵻�0
	*****************************************************************************/
	virtual int IsStarted(void)=0;

	/******************************************************************************
	* Stop
	*������ֹͣ
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void Stop(void)=0;

	/******************************************************************************
	* SendDataToAgent
	*�������������ݸ�ָ��������Ӧ��
	*���룺	cszDomain			-����Ӧ�����ڵ���
			nAgentID			-����Ӧ�ñ�ʶ
			pData				-Ҫ�͵�����
			nLen				-Ҫ�͵����ݵĳ���
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1����ʾ����δ��ͨ
	*****************************************************************************/
	virtual int SendDataToAgent(const char*cszDomain,unsigned int nAgentID,const char* pData,int nLen)=0;

	/******************************************************************************
	* SendDataToNode
	*�������������ݸ�ָ��������ڵ�
	*���룺	cszNodeID			-����ڵ��ʶ
			pData				-Ҫ�͵�����
			nLen				-Ҫ�͵����ݵĳ���
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1����ʾ����δ��ͨ
	*****************************************************************************/
	virtual int SendDataToNode(const char*cszNodeID,const char*pData,int nLen)=0;

	/******************************************************************************
	* GetDomain
	*��������ȡ���ڵ���
	*���룺	��
	*����� ��
	*����ֵ�����ڵ���
	*****************************************************************************/
	virtual const char*GetDomain(void)=0;

	/******************************************************************************
	* GetAgentID
	*��������ȡ����Ӧ�ñ�ʶ
	*���룺	��
	*����� ��
	*����ֵ������Ӧ�ñ�ʶ
	*****************************************************************************/
	virtual unsigned int GetAgentID(void)=0;

	/******************************************************************************
	* GetConnectStatus
	*��������ȡ����״̬
	*���룺	��
	*����� ��
	*����ֵ������״̬
	*****************************************************************************/
	virtual NETEC_Session::CONNECT_STATUS GetConnectStatus(void)=0;

	/******************************************************************************
	* GetLoginSuccessful
	*��������ȡ�Ƿ��¼�ɹ�
	*���룺	��
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int GetLoginSuccessful(void)=0;
	
	/******************************************************************************
	* GetLoginError
	*��������ȡ�Ƿ��¼ʧ��
	*���룺	��
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int GetLoginError(void)=0;

	/******************************************************************************
	* GetLoginErrorID
	*��������ȡ�Ƿ������ʺŴ����µ�¼ʧ��
	*���룺	��
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int GetLoginErrorID(void)=0;

	/******************************************************************************
	* GetLoginErrorPassword
	*��������ȡ�Ƿ�������������µ�¼ʧ��
	*���룺	��
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int GetLoginErrorPassword(void)=0;

	/******************************************************************************
	* GetLoginErrorDuplication
	*��������ȡ�Ƿ�������ͬ�ʺ��ѵ�¼���µ�¼ʧ��
	*���룺	��
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int GetLoginErrorDuplication(void)=0;

	static NETEC_Agent*Create(NETEC_AgentCallback&rCallback,unsigned int nAgentID);

	/******************************************************************************
	* CastDataToAgent
	*�������㲥���ݸ�ָ��������Ӧ��
	*���룺	nAgentID			-����Ӧ�ñ�ʶ
			pData				-Ҫ�͵�����
			nLen				-Ҫ�͵����ݵĳ���
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1����ʾ����δ��ͨ
	*****************************************************************************/
	virtual int CastDataToAgent(unsigned int nAgentID,const char* pData,int nLen)=0;
};

#endif