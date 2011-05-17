//NETEC_Core.h
#ifndef __NETEC_CORE_H__
#define __NETEC_CORE_H__

#include <NETEC/NETEC_Export.h>
#include <NETEC/XSocket.h>

class NETEC_API NETEC_Core
{
public:
	NETEC_Core(void);
	virtual~NETEC_Core(void);
public:
	//������������ں�
	//�ɹ�����0��ʧ�ܷ��ش�����
	static int Start(unsigned short usPort=0,bool bHTTPPort=false,bool bAnyUDPPort=false,bool bHasMCU=true);
	//ֹͣ��������ں�
	static void Stop(void);

	static unsigned short GetUDPPort(void);
	static const char*GetLocalIP(void);
	static SOCKET GetSocketHandle(const char*cszLocalIP);

	static void SetUpdateFilePath(const char*cszFilePath);
	static bool HasMCU(void);
	static bool IsMCUClient(void);
	static bool IsMCUServer(void);
};

#endif
