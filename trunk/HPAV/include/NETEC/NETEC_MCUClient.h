//NETEC_MCUClient.h
#ifndef __NETEC_MCUCLIENT_H__
#define __NETEC_MCUCLIENT_H__

#include <NETEC/NETEC_Export.h>
#include "NETEC_Session.h"

#define NETEC_MCU_FOR_CLIENT_ID		32000

class NETEC_API NETEC_MCUClient
{
public:
	NETEC_MCUClient(void);
	virtual~NETEC_MCUClient(void);
public:
	static int SetMCUID(const char*cszMCUID);
	static int SetMCUIP(const char*cszMCUIP);
	static int SetMCUPort(unsigned short usMCUPort);
	static const char*GetMCUID(void);
	static const char*GetMCUIP(void);
	static unsigned short GetMCUPort(void);
	static const char*GetLocalIP(void);
	static unsigned short GetLocalPort(void);
	static const char*GetNATIP(void);
	static unsigned short GetNATPort(void);
	static void SetTimeout(unsigned long ulTimeout/*ms*/);
	static NETEC_Session::CONNECT_STATUS GetStatus(void);
	static int Start(void);
	static int IsStarted(void);
	static void Stop(void);

	static int CallOutInvite(const char*cszCallID,const char*cszNumber,unsigned long ulAudioID);
	static int CallOutBye(const char*cszCallID);
};

#endif