//NETEC_Router.h
#ifndef __NETEC_ROUTER_H__
#define __NETEC_ROUTER_H__

#include "NETEC.h"
#include "NETEC_Session.h"

//����·��
class NETEC_API NETEC_Router
{
public:
	NETEC_Router(void);
	virtual ~NETEC_Router(void);
public:	
	//�������ط���
	virtual int Start(void);
	//ֹͣ���ط���
	virtual void Stop(void);

	//���ñ�����
	virtual void SetLocalDomain(const char*cszDomain="",NETEC::DOMAIN_TYPE DomainType=NETEC::BROTHER);

	virtual NETEC::DOMAIN_TYPE GetDomainType(void);
	virtual const char*GetDomain(void);

	/******************************************************************************
	* OnNETEC_RouterAgentLogin
	*������Agent��¼�ص�
	*���룺	nAgentID			-Agent���ڲ���ʶ
			cszAgentPassword	-Agent������
			cszAgentVersion		-Agent�İ汾
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_RouterAgentLogin(unsigned int nAgentID,const char*cszAgentPassword,const char* cszAgentVersion){};
	
	/******************************************************************************
	* OnNETEC_RouterAgentLogout
	*������Agent�˳��ص�
	*���룺	nAgentID			-Agent�ı�ʶ
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_RouterAgentLogout(unsigned int nAgentID){};
	
	/******************************************************************************
	* SetAgentLoginSuccessful
	*������֪ͨAgent��¼�ɹ�
	*���룺	nAgentID			-Agent�ı�ʶ
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int SetAgentLoginSuccessful(unsigned int nAgentID);
	
	/******************************************************************************
	* SetAgentLoginErrorID
	*������֪ͨAgent����Agent�����ڵ��µ�¼ʧ��
	*���룺	nAgentID			-Agent�ı�ʶ
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int SetAgentLoginErrorID(unsigned int nAgentID);
	
	/******************************************************************************
	* SetAgentLoginErrorPassword
	*������֪ͨAgent������������µ�¼ʧ��
	*���룺	nAgentID			-Agent�ı�ʶ
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int SetAgentLoginErrorPassword(unsigned int nAgentID);

	virtual int SendDataToAgent(unsigned int nAgentID,const char*pData);

	/******************************************************************************
	* OnNETEC_RouterMCULogin
	*������MCU��¼�ص�
	*���룺	cszMCUID			-MCU�ı�ʶ
			cszPassword			-MCU������
			cszVersion			-MCU�İ汾
			nMCUType			-MCU������
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_RouterMCULogin(const char*cszMCUID,const char*cszMCUPassword,const char*cszMCUVersion,const char*cszUserData,unsigned int nMCUType){};
	
	/******************************************************************************
	* OnNETEC_RouterMCULogout
	*������MCU�˳��ص�
	*���룺	cszMCUID			-MCU�ı�ʶ
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_RouterMCULogout(const char*cszMCUID){};
	
	/******************************************************************************
	* OnNETEC_RouterMCUUpdateIP
	*������MCUIP��ַ���»ص�
	*���룺	cszMCUID			-MCU�ı�ʶ
			cszIP				-MCU��IP
			usPort				-MCU�Ķ˿�
			cszIPType			-MCU��IP����
			nActive				-MCU��IP�Ƿ�
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_RouterMCUUpdateIP(const char*cszMCUID,const char*cszIP,unsigned short usPort,const char*cszIPType,int nActive){};
	
	/******************************************************************************
	* OnNETEC_RouterMCUUserCount
	*������MCU�û����ı�Ļص�
	*���룺	cszMCUID			-MCU�ı�ʶ
			nUserCount			-MCU��ǰ�û���
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_RouterMCUUserCountChanged(const char*cszMCUID,unsigned int nUserCount){};
	
	/******************************************************************************
	* OnNETEC_RouterRecvdDataFromMCU
	*������MCU�û����ı�Ļص�
	*���룺	cszMCUID			-MCU�ı�ʶ
			cszData				-����ָ��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_RouterRecvdDataFromMCU(const char*cszMCUID,const char*cszData){};
	
	/******************************************************************************
	* SetMCULoginSuccessful
	*������֪ͨMCU��¼�ɹ�
	*���룺	cszMCUID			-MCU�ı�ʶ
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int SetMCULoginSuccessful(const char*cszMCUID);
	
	/******************************************************************************
	* SetMCULoginErrorID
	*������֪ͨMCU����MCU�����ڵ��µ�¼ʧ��
	*���룺	cszMCUID			-MCU�ı�ʶ
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int SetMCULoginErrorID(const char*cszMCUID);
	
	/******************************************************************************
	* SetMCULoginErrorPassword
	*������֪ͨMCU������������µ�¼ʧ��
	*���룺	cszMCUID			-MCU�ı�ʶ
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int SetMCULoginErrorPassword(const char*cszMCUID);
	
	/******************************************************************************
	* SetMCULoginErrorUserCode
	*������֪ͨMCU�����û����ݵ��µ�¼ʧ��
	*���룺	cszMCUID			-MCU�ı�ʶ
			cszUserCode			-�û�����
	*����� ��
	*����ֵ�����ط�0Ϊ�ǣ�����Ϊ��
	*****************************************************************************/
	virtual int SetMCULoginErrorUserCode(const char*cszMCUID,const char*cszUserCode);

	//�ӷ������ݰ�������
	virtual int SendToChildDomain(const char*cszDomain,const char* pData,int nLen);
	//�������յ������ݰ��ص�
	virtual void OnNETEC_RouterReceivedFromChildDomain(const char*cszDomain,const char* pData,int nLen){};
	//����Ͽ����ӵĻص�
	virtual void OnNETEC_RouterChildDomainDisconnected(const char*cszDomain){};
	
	//���Ӹ���
	virtual int ConnectToParentDomain(const char*cszParentHost,unsigned short usParentPort,const char*cszInterface);
	//�Ͽ��븸�������
	virtual void DisconnectFromParentDomain(void);
	//�ӷ������ݰ�������
	virtual int SendToParentDomain(const char* pData,int nLen);
	//��Domain�յ������ݰ��ص�
	virtual void OnNETEC_RouterReceivedFromParentDomain(const char*cszParentDomain,const char* pData,int nLen){};
	//�յ��ֵ��������״̬
	virtual void OnNETEC_RouterParentDomainSessionConnectStatus(NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0){};

	//�������ӶϿ��Ļص�
	virtual void OnNETEC_RouterBrotherDomainDisconnected(const char*cszBrotherDomain){};

	//�����ֵ���
	//����ֵ���ֻ�и����������ֵ���
	virtual int AddBrotherDomain(const char*cszBrotherDomain,const char*cszBrotherHost,unsigned short usBrotherPort,const char*cszInterface);
	//ɾ���ֵ���
	virtual int RemoveBrotherDomain(const char*cszBrotherDomain);
	//�������ݸ��ֵ���
	virtual int SendToBrotherDomain(const char*cszBrotherDomain,const char*pData,int nLen);
	//���ֵ����յ������ݰ��ص�
	virtual void OnNETEC_RouterReceivedFromBrotherDomain(const char*cszBrotherDomain,const char* pData,int nLen){};
	//�յ��ֵ��������״̬
	virtual void OnNETEC_RouterBrotherDomainSessionConnectStatus(const char*cszBrotherDomain,NETEC_Session::CONNECT_STATUS cs,int nErrorCode=0){};

	//������ڵ��յ������ݰ��ص�
	virtual void OnNETEC_RouterReceivedFromNode(const char*cszDomain,const char*cszNodeID,const char* pData,int nLen){};
	//����ڵ��뱾����Ӧ�öϿ����ӵĻص�
	virtual void OnNETEC_RouterNodeDisconnected(const char*cszDomain,const char*cszNodeID,const char*pData,int nLen){};

	/******************************************************************************
	* SendDataToNode
	*�������������ݸ�ָ��������ڵ�
	*���룺	cszNodeID			-����ڵ��ʶ
			pData				-Ҫ�͵�����
			nLen				-Ҫ�͵����ݵĳ���
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1����ʾ����δ��ͨ
	*****************************************************************************/
	virtual int SendDataToNode(const char*cszNodeID,const char*pData,int nLen);

	//����һ��·���յ������ݰ��ص�
	virtual void OnNETEC_RouterReceivedFromRouter(const char*cszDomain,const char* pData,int nLen){};
	//��һ��·���뱾����Ӧ�öϿ����ӵĻص�
	virtual void OnNETEC_RouterRouterDisconnected(const char*cszDomain,const char*pData,int nLen){};

	/******************************************************************************
	* SendDataToRouter
	*�������������ݸ�ָ����·��
	*���룺	cszDomain			-·�ɵ�����
			pData				-Ҫ�͵�����
			nLen				-Ҫ�͵����ݵĳ���
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1����ʾ����δ��ͨ
	*****************************************************************************/
	virtual int SendDataToRouter(const char*cszDomain,const char*pData,int nLen);
};

#endif
