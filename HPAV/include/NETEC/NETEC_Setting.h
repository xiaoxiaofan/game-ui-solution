//NETEC_Setting.h
#ifndef __NETEC_SETTING_H__
#define __NETEC_SETTING_H__

#include <NETEC/NETEC_Export.h>

//��������
class NETEC_API NETEC_Setting
{ 
public:
	NETEC_Setting(void);
	virtual~NETEC_Setting(void);
	
public:
	typedef enum{
		PT_NONE=0,		//�޴���ֱ������
		PT_HTTP_PROXY,	//HTTP����
		PT_SOCK5,		//SOCK5����
		PT_HTTP_TUNNEL,	//HTTP���
		PT_HTTPS_TUNNEL	//HTTPS���
	}PROXY_TYPE;

	typedef enum{
		PT_TCP=0,		//TCP����Э��
		PT_UDP,			//UDP����Э��
		PT_RTP,			//RTP����Э��
		PT_AUDP,		//AUDP����Э��
	}PROTOCOL_TYPE;
	
public:
	//��������ͨѶЭ������
	static void SetSessionProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetSessionProtocolType(void);

	//������Ƶ����Э������
	static void SetAudioProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetAudioProtocolType(void);

	//������Ƶ����Э������
	static void SetVideoProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetVideoProtocolType(void);

	//�������ݴ���Э������
	static void SetDataProtocolType(NETEC_Setting::PROTOCOL_TYPE type);
	static NETEC_Setting::PROTOCOL_TYPE GetDataProtocolType(void);

	//�����Ƿ�ֻʹ��MCU
	static void SetMCUOnly(int nMCUOnly);
	static int GetMCUOnly(void);
	
	//���ô�������
	static void SetProxyType(NETEC_Setting::PROXY_TYPE pt);
	static NETEC_Setting::PROXY_TYPE GetProxyType(void);
	
	//���ô����û�
	static void SetProxyUser(const char* cszUser);
	static const char*GetProxyUser(void);
	
	//���ô�������
	static void SetProxyPassword(const char* cszPassword);
	static const char*GetProxyPassword(void);
	
	//���ô��������
	static void SetProxyHost(const char* cszHost);
	static const char*GetProxyHost(void);
	static void SetProxyPort(unsigned short usPort);
	static unsigned short GetProxyPort(void);

	//�����Ƿ�ʹ���鲥
	static void SetEnableMulticast(int nEnableMulticast);
	static int GetEnableMulticast(void);
};

#endif