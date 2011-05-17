//RTOU.h
#ifndef __RTOU_H__
#define __RTOU_H__

#include <NETEC/NETEC_Export.h>


#define RTOU_MTU	1248

#ifdef _WIN32
#include <winsock2.h>
#ifndef __INLINE__
#define __INLINE__ _inline
#endif
#else
#ifndef SOCKET
#define SOCKET int
#endif
#ifndef INVALID_SOCKET
#define INVALID_SOCKET -1
#endif
#ifndef __INLINE__
#define __INLINE__ inline
#endif
#endif

typedef struct tagRTOUADDR
{
	SOCKET			hSocket;
	struct sockaddr*addr;
	int				addrlen;

	tagRTOUADDR(void)
		: hSocket(INVALID_SOCKET)
		, addr(0)
		, addrlen(0)
	{
	};
	tagRTOUADDR(SOCKET _hSocket,struct sockaddr*_addr,int _addrlen)
		: hSocket(_hSocket)
		, addr(_addr)
		, addrlen(_addrlen)
	{
	};
}RTOUADDR,*PRTOUADDR;


//RTOU_Core ÿ������ֻ����һ��ʵ��

class RTOU_CoreCallback
{
public:
	RTOU_CoreCallback(void){};
	virtual~RTOU_CoreCallback(void){};
public:
	//������Ҫ���͵�ָ����IP��ַ�������ⲿ����ͷ
	virtual void OnRTOU_CoreCallbackSendingPacket(const RTOUADDR&rRTOUAddr,unsigned char*pPacketData,int nPacketLen)=0;
};

class NETEC_API RTOU_Core
{
public:
	RTOU_Core(void){};
	virtual~RTOU_Core(void){};
public:
	//��
	virtual int Open(void)=0;
	//�ر�
	virtual void Close(void)=0;

	//�����Զ��RTOU_Core���ص����ݰ�
	virtual int ProcessRecvdPacket(const RTOUADDR&rRTOUAddr,unsigned char*pPacketData,int nPacketLen)=0;

	//�����ڲ�ѭ��
	virtual bool DoTick(void)=0;

	virtual void UpdateRTOUAddr(const RTOUADDR&rRTOUAddr)=0;

	//����RTOU_Core,�������������Ѿ���һ��ʵ������ô��������NULL
	static RTOU_Core*Create(RTOU_CoreCallback&rCallback,int nHeaderMargin=0);
	
	//ȡ������ָ��IP��ַ������ʱ��
	static unsigned long GetRTT(const RTOUADDR&rRTOUAddr);
	//ȡ������ָ��IP��ַ�Ķ�����
	static int GetTXPacketLossRate(const RTOUADDR&rRTOUAddr);
	//ȡָ��IP��ַ�������Ķ�����
	static int GetRXPacketLossRate(const RTOUADDR&rRTOUAddr);
	//ȡ������ָ��IP��ַ�İ��ش���
	static int GetTXPacketRetransferRate(const RTOUADDR&rRTOUAddr);
	//ȡָ��IP��ַ�������İ��ش���
	static int GetRXPacketRetransferRate(const RTOUADDR&rRTOUAddr);
	//ȡ������ָ��IP��ַ����ʱ����
	static unsigned long GetTXDelayVariation(const RTOUADDR&rRTOUAddr);
	//ȡָ��IP��ַ����������ʱ����
	static unsigned long GetRXDelayVariation(const RTOUADDR&rRTOUAddr);
};


class NETEC_API RTOU_RTSPSession;
class RTOU_RTSPSessionCallback
{
public:
	RTOU_RTSPSessionCallback(void){};
	virtual~RTOU_RTSPSessionCallback(void){};
public:
	//�����ݰ�Ҫ����
	virtual void OnRTOU_RTSPSessionCallbackSendingPacket(RTOU_RTSPSession*pRTOU_RTSPSession,unsigned char*pPacketData,int nPacketLen)=0;
	//�յ���ɵ�����֡
	virtual void OnRTOU_RTSPSessionCallbackRecvdFrame(RTOU_RTSPSession*pRTOU_RTSPSession,unsigned char*pFrameData,int nFrameLen)=0;
};

class NETEC_API RTOU_RTSPSession
{
public:
	RTOU_RTSPSession(void){};
	virtual~RTOU_RTSPSession(void){};
public:
	//��
	virtual int Open(void)=0;
	//�ر�
	virtual void Close(void)=0;

	virtual bool DoTick(void)=0;
	//�Ƿ����д
	virtual bool IsWritable(void)=0;
	//д����֡
	virtual int WriteFrame(unsigned char*pFrameData,int nFrameLen)=0;
	//�����յ������ݰ�
	virtual int ProcessRecvdPacket(unsigned char*pPacketData,int nPacketLen)=0;
	//���ô���
	virtual int SetMaxBandwidth(int nMaxBandwidth)=0;
	//����RTT
	virtual void UpdateRTT(unsigned long nRTT)=0;
	//���·��Ͷ�����
	virtual void UpdateTXPacketLossRate(int nTXPacketLossRate)=0;

	//����RTSPSessuion
	static RTOU_RTSPSession*Create(RTOU_RTSPSessionCallback&rCallback,const RTOUADDR&rRTOUAddr,int nMaxBandwidth,int nMTU=RTOU_MTU,int nHeaderMargin=0);
};


class RTOU_JitterBufferCallback
{
public:
	RTOU_JitterBufferCallback(void){};
	virtual~RTOU_JitterBufferCallback(void){};
public:
	virtual void OnRTOU_JitterBufferCallbackRecvdPacket(unsigned short usSeq,unsigned long ulRTPTimeMS,const unsigned char*pPacketData,int nPacketLen)=0;
};

class NETEC_API RTOU_JitterBuffer
{
public:
	RTOU_JitterBuffer(void){};
	virtual~RTOU_JitterBuffer(void){};
public:
	virtual int Open(void)=0;
	virtual void Close(void)=0;

	virtual int ProcessRecvdPacket(unsigned short usSeq,unsigned long ulRTPTimeMS,const unsigned char*pPacketData,int nPacketLen)=0;
	virtual bool DoTick(void)=0;

	virtual int GetTXPacketLossRate(void)=0;
	virtual unsigned long GetRXLostPacketCount(void)=0;

	//����RTPSessuion
	static RTOU_JitterBuffer*Create(RTOU_JitterBufferCallback&rCallback,const RTOUADDR&rRTOUAddr);
};


#endif