// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <vector>
#include <list>
#include <string>
using namespace std;
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <comdef.h>
#include <atlbase.h>
#include <commdlg.h>
#include <tchar.h>
#include <streams.h>
#include <dshow.h>
#include <d3d9.h>
#include <vmr9.h>
#include <tchar.h>


// Local Header Files
#include "MVMUSER.h"
#include "MultiVMR9.h"
#ifndef RELEASE
#define RELEASE(p){ if(p){p->Release(); p=NULL;}}
#endif
#ifndef CHECK_HR
#define CHECK_HR(hr,f){ if( FAILED(hr)){f;throw hr;}}
#endif
void DbgMsg( char* szMessage, ... );

// TODO: reference additional headers your program requires here
