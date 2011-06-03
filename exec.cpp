#include "stdafx.h"
#include "exec.h"
#include <strsafe.h>

void ErrMsg(LPTSTR szFormat,...)
{
	static TCHAR szBuffer[2048]={0};
	const size_t NUMCHARS = sizeof(szBuffer) / sizeof(szBuffer[0]);
	const int LASTCHAR = NUMCHARS - 1;

	// Format the input string
	va_list pArgs;
	va_start(pArgs, szFormat);

	// Use a bounded buffer size to prevent buffer overruns.  Limit count to
	// character size minus one to allow for a NULL terminating character.
	HRESULT hr = StringCchVPrintf(szBuffer, NUMCHARS - 1, szFormat, pArgs);
	va_end(pArgs);

	// Ensure that the formatted string is NULL-terminated
	szBuffer[LASTCHAR] = TEXT('\0');

	MessageBox(NULL, szBuffer, NULL,
		MB_OK | MB_ICONEXCLAMATION | MB_TASKMODAL);
}
