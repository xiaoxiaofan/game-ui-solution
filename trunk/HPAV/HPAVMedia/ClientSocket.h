#pragma once
#include "imxec\IMXEC_MediaChannel.h"


// CClientSocket command target

class CClientSocket : public CSocket
{
public:
	CClientSocket(IMXEC_PlayChan& player);
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
	IMXEC_PlayChan&     m_player; 
};


