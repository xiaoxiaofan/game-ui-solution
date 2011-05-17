#pragma once

#define CHINESE_SIMPLIFIED_CODEPAGE 936
#define CHINESE_TRADITIONAL_CODEPAGE 950

#define MAX_LANG_STRING_BUFFER_SIZE	512

AFX_EXT_CLASS CString GetApplicationPath(void);
AFX_EXT_CLASS CString LoadLangString(LPCTSTR lpLangFileName,LPCTSTR lpSec, LPCTSTR lpKey);
AFX_EXT_CLASS unsigned long KGetFileLength(LPCTSTR lpszFileFullName);
AFX_EXT_CLASS CString KGetFileCreateTime(LPCTSTR lpszFileFullName);
AFX_EXT_CLASS CString KGetFileAccessTime(LPCTSTR lpszFileFullName);
AFX_EXT_CLASS CString KGetFileModifyTime(LPCTSTR lpszFileFullName);
AFX_EXT_CLASS CString KGetFileName(const char* cszFileFullName);
AFX_EXT_CLASS void KGetFileExtName(const char* cszFileFullName,char* szFileExtName);

AFX_EXT_CLASS BOOL GetProcessName(DWORD dwProcessID,CString& csProcessName);
AFX_EXT_CLASS BOOL KillProcess(DWORD dwProcessID);
AFX_EXT_CLASS BOOL KillProcess(CString csCurrentProcessName);
AFX_EXT_CLASS DWORD FindMutexProcess(void);

AFX_EXT_CLASS std::string KW2A(CString csUnicodeString);
AFX_EXT_CLASS CString KA2W(const std::string& strAnsiString);

AFX_EXT_CLASS CString GBKSimplified2Big5(CString csGBKSimplified);
AFX_EXT_CLASS CString GB2Big5(unsigned short usCodePage, CString csText);