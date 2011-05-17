//NETEC_MediaChan.h
#ifndef __NETEC_MEDIACHAN_H__
#define __NETEC_MEDIACHAN_H__

#include "NETEC_Export.h"
#include "NETEC_MCU.h"


class NETEC_MediaChanSenderCallback
{
public:
	NETEC_MediaChanSenderCallback(void){};
	virtual~NETEC_MediaChanSenderCallback(void){};
public:
	virtual void OnNETEC_MediaChanSenderCallbackAudChanEnable(void)=0;	//�������ڿ���ѹ��
	virtual void OnNETEC_MediaChanSenderCallbackAudChanDisable(void)=0;
	virtual void OnNETEC_MediaChanSenderCallbackVidChanEnable(void)=0;
	virtual void OnNETEC_MediaChanSenderCallbackVidChanDisable(void)=0;
	virtual void OnNETEC_MediaChanSenderCallbackSubVidChanEnable(void)=0;
	virtual void OnNETEC_MediaChanSenderCallbackSubVidChanDisable(void)=0;
};

class NETEC_API NETEC_MediaChanSender
{
public:
	NETEC_MediaChanSender(void){};
	virtual~NETEC_MediaChanSender(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;

	virtual const char*GetAudChanID(void)=0;
	virtual const char*GetVidChanID(void)=0;
	virtual const char*GetSubVidChanID(void)=0;

	//��Ϊtrueʱ����ѹ����ǰ֡���������Կ�����ʱ
	virtual bool IsVidChanBlocking(void)=0;
	virtual bool IsSubVidChanBlocking(void)=0;

	virtual int StartAudChan(void)=0;
	virtual int WriteAudChanData(const char*pData,int nLen)=0;
	virtual int StopAudChan(void)=0;
	virtual int StartVidChan(void)=0;
	virtual int WriteVidChanData(const char*pData,int nLen)=0;
	virtual int StopVidChan(void)=0;
	virtual int StartSubVidChan(void)=0;
	virtual int WriteSubVidChanData(const char*pData,int nLen)=0;
	virtual int StopSubVidChan(void)=0;

	static NETEC_MediaChanSender*Create(NETEC_MediaChanSenderCallback&rCallback);
};

class NETEC_MediaChanReceiverCallback
{
public:
	NETEC_MediaChanReceiverCallback(void){};
	virtual~NETEC_MediaChanReceiverCallback(void){};
public:
	virtual void OnNETEC_MediaChanReceiverCallbackAudChanData(const char*pData,int nLen)=0;
	virtual void OnNETEC_MediaChanReceiverCallbackVidChanData(const char*pData,int nLen)=0;
	virtual void OnNETEC_MediaChanReceiverCallbackSubVidChanData(const char*pData,int nLen)=0;
};

class NETEC_API NETEC_MediaChanReceiver
{
public:
	NETEC_MediaChanReceiver(void){};
	virtual~NETEC_MediaChanReceiver(void){};
public:
	virtual int Open(const char*cszAudChanID,const char*cszVidChanID,const char*cszSubVidChanID,NETEC_MCU::ROUTE_MODE routeMode=NETEC_MCU::RM_AUTO)=0;
	virtual void Close(void)=0;
	
	virtual int StartAudChan(void)=0;
	virtual int ReceiveAudChan(int nType/*0:�����գ�1:����*/)=0;
	virtual int StopAudChan(void)=0;
	virtual int StartVidChan(void)=0;
	virtual int ReceiveVidChan(int nType/*0:�����գ�1:����*/)=0;
	virtual int StopVidChan(void)=0;
	virtual int StartSubVidChan(void)=0;
	virtual int ReceiveSubVidChan(int nType/*0:�����գ�1:����*/)=0;
	virtual int StopSubVidChan(void)=0;

	static NETEC_MediaChanReceiver*Create(NETEC_MediaChanReceiverCallback&rCallback);
};

//����ͨ���ӿ�
class NETEC_API NETEC_DataChan;
class NETEC_API NETEC_DataChanCallback
{
public:
	NETEC_DataChanCallback(void){};
	virtual~NETEC_DataChanCallback(void){};
public:
	//�յ����ݵĻص����ɽ���㴦��
	virtual void OnNETEC_DataChanCallbackChanData(NETEC_DataChan*pDataChan,const char*pData,int nLen)=0;
	//���ӵ��������Ļص�����������MCU�ɹ���Ļص�
	//������OpenInitiator(unsigned long&ulChanID)������ConnectToMCU(void)ʱ�Żᱻ����
	virtual void OnNETEC_DataChanCallbackChanChanged(NETEC_DataChan*pDataChan,unsigned long ulChanID,const char*cszMCUIP0,const char*cszMCUIP1,const char*cszMCUIP2)=0;
	//P2P����ʧ�ܣ���������MCU,�����˴��ļ������뷽�������뷽P2Pʧ�ܺ�ص�
	//������int OpenAttendant(const char*cszDomain,const char*cszNodeID,unsigned long ulChanID)ʱ�Żᱻ����
	virtual void OnNETEC_DataChanCallbackP2PFailed(NETEC_DataChan*pDataChan)=0;
};

class NETEC_API NETEC_DataChan
{
public:
	NETEC_DataChan(void){};
	virtual~NETEC_DataChan(void){};
public:
	//��Ϊ�����ߴ�����ͨ���ĵ��ýӿ�
	virtual int OpenInitiator(unsigned long&ulChanID)=0;
	//��Ϊ��Ӧ�ߴ�����ͨ���ĵ��ýӿ�
	virtual int OpenAttendant(unsigned long ulChanID,const char*cszMCUIP0,const char*cszMCUIP1,const char*cszMCUIP2)=0;
	//��Ϊ��Ӧ�ߴ�����ͨ���ĵ��ýӿ�
	virtual int OpenAttendant(const char*cszDomain,const char*cszNodeID,unsigned long ulChanID)=0;
	//�ر�����ͨ��
	virtual void Close(void)=0;
	//��ʼ����MCU
	virtual int ConnectToMCU(void)=0;
	//�ı�������ͨ����Ϣ
	virtual int ChangeChan(unsigned long ulChanID,const char*cszMCUIP0,const char*cszMCUIP1,const char*cszMCUIP2)=0;
	//дͨ������
	virtual int WriteChanData(const char*pData,int nLen)=0;
	//ȡͨ��ID
	virtual unsigned long GetChanID(void)=0;
	//��������ͨ��
	static NETEC_DataChan*Create(NETEC_DataChanCallback&rCallback);
};

#endif




