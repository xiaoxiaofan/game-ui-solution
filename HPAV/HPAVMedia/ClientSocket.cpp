// ClientSocket.cpp : implementation file
//

#include "stdafx.h"
#include "HPAVMedia.h"
#include "ClientSocket.h"


// CClientSocket

CClientSocket::CClientSocket(IMXEC_PlayChan&     player)
	: m_player(player)
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket member functions


void CClientSocket::OnReceive(int nErrorCode)
{
	char* buff = new char[10240];
	Receive(buff,10240);
	m_player.PlayVideoData(buff,10240);
	delete buff;
	buff = NULL;
	CSocket::OnReceive(nErrorCode);
}
