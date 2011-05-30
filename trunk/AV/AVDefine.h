#pragma once

#define FAIL_RET(x) do { if( FAILED( hr = ( x  ) ) ) \
	return hr; } while(0)