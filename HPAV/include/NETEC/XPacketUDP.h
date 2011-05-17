//XPacketUDP.h

#ifndef __XPACKETUDP_H__
#define __XPACKETUDP_H__

#ifndef _WIN32
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <cstdio>
#include <cerrno>
#else
#include <winsock2.h>
#include <ws2tcpip.h>

#ifdef _WIN32_WCE

#else
#include <wspiapi.h>
#endif

struct iovec
{
	int		iov_len;
	char*	iov_base;
};
#endif

#include <NETEC/XSocket.h>

class XPacketUDP
{
public:
	XPacketUDP(SOCKET hSocket,struct sockaddr*addr,int addrlen,unsigned char nAppType,unsigned char nCmd,unsigned short nSeqNo,unsigned long nDstID,const char*pData,int nDataLen);
	XPacketUDP(SOCKET hSocket,const int&af,int nBufLen);
	virtual~XPacketUDP();
public:
	unsigned char GetAppType(void);
	unsigned char GetCmd(void);
	unsigned short GetSeqNo(void);
	unsigned long GetDstID(void);
	char*GetData(void);
	int GetDataLen(void);
	SOCKET GetSocketHandle(void);

	int getaf(void);
	struct sockaddr*getaddr(void);
	int getaddrlen(void);

	int Send(void);
	int Recv(void);
protected:
#define UDPHEADER_LEN	8
	struct UDPHEADER
	{
		unsigned short	nAppType:8;
		unsigned short	nCmd:8;
		unsigned short	nSeqNo;
		unsigned long	nDstID;
	};

	UDPHEADER		m_UDPHeader;
	iovec			m_PacketVector[2];             // The 2-demension vector of UDP packet [header, data]
	char*			m_pData;
	int				m_nDataLen;
	int				m_nBufLen;

	SOCKET			m_hSocket;
	
	struct sockaddr*m_pAddr;
	int				m_nAddrLen;

	struct sockaddr_in m_saIPV4;
	struct sockaddr_in6 m_saIPV6;

	int					m_af;
};



#endif
