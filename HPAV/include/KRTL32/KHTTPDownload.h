#pragma once

#include "afxinet.h"

#define WM_USER_DOWNLOAD_FILESIZE		WM_USER+3001
#define WM_USER_DOWNLOAD_PROGRESS		WM_USER+3002
#define WM_USER_DOWNLOAD_FINISHED		WM_USER+3003
#define WM_USER_DOWNLOAD_FAILURE		WM_USER+3004

//---------------------------------------------------------------------------------------
// KHTTPDownloadEvent 类定义
class AFX_EXT_CLASS KHTTPDownloadEvent
{
public:
	KHTTPDownloadEvent(){};
	virtual ~KHTTPDownloadEvent(){};

	virtual void OnDownloadFileSize(unsigned long ulFileSize)=0;
	virtual void OnDownloadProgress(unsigned long ulFilePos)=0;
	virtual void OnDownloadFinished(void)=0;
	virtual void OnDownloadFailure(void)=0;
};


//---------------------------------------------------------------------------------------
// KHTTPDownload 类定义
class AFX_EXT_CLASS KHTTPDownload : public CWnd,KThread
{
public:
	KHTTPDownload(KHTTPDownloadEvent& rHTTPDownloadEvent);
	virtual ~KHTTPDownload();

	bool Execute(const std::string& remoteurl,const std::string& localfilefullpath);
	void Release(void);

protected:
	KHTTPDownloadEvent& m_rHTTPDownloadEvent;
	bool				m_bWantToStop;
	CString				m_csRemoteURL;
	CString				m_csLocalFileFullPath;

	void ThreadProcMain(void);
	CString ParseFileName(CString strObject);

	DECLARE_DYNAMIC(KHTTPDownload)
	afx_msg LRESULT OnMsgDownloadFileSize(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDownloadProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDownloadFinished(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgDownloadFailure(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


