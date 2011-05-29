// stdafx.cpp : source file that includes just the standard includes
// MVMUSER.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#ifdef _DEBUG
    void DbgMsg( char* szMessage, ... )
    {
        char szFullMessage[MAX_PATH];
        char szFormatMessage[MAX_PATH];

        // format message
        va_list ap;
        va_start(ap, szMessage);
        _vsnprintf( szFormatMessage, MAX_PATH, szMessage, ap);
        va_end(ap);
        strncat( szFormatMessage, "\n", MAX_PATH);
        strcpy( szFullMessage, "~*~*~*~*~*~ ");
        strcat( szFullMessage, szFormatMessage );
        OutputDebugStringA( szFullMessage );
    }
#else
    void DbgMsg( char* szMessage, ... ){;}
#endif
// TODO: reference any additional headers you need in STDAFX.H
// and not in this file
