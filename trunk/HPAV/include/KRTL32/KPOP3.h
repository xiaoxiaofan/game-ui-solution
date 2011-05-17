#pragma once

#define SOCKET int
#define SOCKADDR sockaddr

class AFX_EXT_CLASS KPOP3Connection;

class AFX_EXT_CLASS KPOP3Message
{
public:
  KPOP3Message();
  ~KPOP3Message();

	LPCSTR GetMessageText() const { return m_pszMessage; };
	CString GetHeader() const;
	CString GetHeaderItem(const CString& sName, int nItem = 0) const;
	CString GetBody() const;
	LPCSTR  GetRawBody() const;
	CString GetSubject() const { return GetHeaderItem(_T("Subject")); }
	CString GetFrom() const		 { return GetHeaderItem(_T("From")); }
	CString GetDate() const		 { return GetHeaderItem(_T("Date")); }
	CString GetReplyTo() const;

	char* m_pszMessage;
	friend class CPop3Connection;
};

class AFX_EXT_CLASS KPOP3Socket
{
public:
	KPOP3Socket();
	~KPOP3Socket();

	BOOL  Create();
	BOOL  Connect(LPCTSTR pszHostAddress, int nPort = 110);
	BOOL  Send(LPCSTR pszBuf, int nBuf);
	void  Close();
	int   Receive(LPSTR pszBuf, int nBuf);
	BOOL  IsReadible(BOOL& bReadible);

protected:
	//BOOL Connect(const sockaddr* lpSockAddr, int nSockAddrLen);
	SOCKET m_hSocket;
	friend class CPop3Connection;
};
  
class AFX_EXT_CLASS KPOP3Connection
{
public:
	KPOP3Connection();
	~KPOP3Connection();

	BOOL    Connect(LPCTSTR pszHostName, LPCTSTR pszUser, LPCTSTR pszPassword, int nPort = 110);
	BOOL    Disconnect();
	BOOL    Statistics(int& nNumberOfMails, int& nTotalMailSize);
	BOOL    Delete(int nMsg);
	BOOL    GetMessageSize(int nMsg, DWORD& dwSize);
	BOOL    GetMessageID(int nMsg, CString& sID);
	BOOL    Retrieve(int nMsg, KPOP3Message& message);
	BOOL    GetMessageHeader(int nMsg, KPOP3Message& message);
	BOOL    Reset();
	BOOL    UIDL();
	BOOL    Noop();
	CString GetLastCommandResponse() const { return m_sLastCommandResponse; };
	DWORD   GetTimeout() const { return m_dwTimeout; };
	void    SetTimeout(DWORD dwTimeout) { m_dwTimeout = dwTimeout; };

protected:
	virtual BOOL ReadStatResponse(int& nNumberOfMails, int& nTotalMailSize);
	virtual BOOL ReadCommandResponse();
	virtual BOOL ReadListResponse(int nNumberOfMails);
	virtual BOOL ReadUIDLResponse(int nNumberOfMails);
	virtual BOOL ReadReturnResponse(KPOP3Message& message, DWORD dwSize);
	virtual BOOL ReadResponse(LPSTR pszBuffer, int nInitialBufSize, LPSTR pszTerminator, 
						LPSTR* ppszOverFlowBuffer, int nGrowBy=4096);
	BOOL  List();
	LPSTR GetFirstCharInResponse(LPSTR pszData) const;

	KPOP3Socket  m_Pop;
	int          m_nNumberOfMails;
	BOOL         m_bListRetrieved;
	BOOL         m_bStatRetrieved;
	BOOL         m_bUIDLRetrieved;
	CDWordArray  m_msgSizes;
	CStringArray m_msgIDs;
	BOOL         m_bConnected;
	CString      m_sLastCommandResponse;
	DWORD        m_dwTimeout;
};
