
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��


#include <string>
#include <vector>
#include <map>


#include "AVBase/AVDefine.h"
#include <afxsock.h>



#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif



#ifdef _DEBUG
#pragma comment(lib,"../lib/Debug/IMXEC.lib")
#pragma comment(lib,"../lib/debug/VIDEC.lib")
#pragma comment(lib,"../lib/debug/AUDEC.lib")
#pragma comment(lib,"../lib/debug/KBASE.lib")
#pragma comment(lib,"../lib/debug/KRTL32.lib")
#pragma comment(lib,"../lib/Debug/KVCL32.lib")
#pragma comment(lib,"../lib/debug/NETEC.lib")
#pragma comment(lib,"liveDll.lib")
#else
#pragma comment(lib,"../lib/release/IMXEC.lib")
#pragma comment(lib,"../lib/release/VIDEC.lib")
#pragma comment(lib,"../lib/release/AUDEC.lib")
#pragma comment(lib,"../lib/release/KBASE.lib")
#pragma comment(lib,"../lib/release/KRTL32.lib")
#pragma comment(lib,"../lib/Release/KVCL32.lib")
#pragma comment(lib,"../lib/release/NETEC.lib")
#endif