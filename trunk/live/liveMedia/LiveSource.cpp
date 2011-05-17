#include "LiveSource.h"
#include <memory.h>


LiveSource::LiveSource(void)
{
	fTo = new unsigned char[40000];
	fSize = 0;
}


LiveSource::~LiveSource(void)
{
}

void LiveSource::setData( unsigned char* pData,int nSize )
{
	if ((fSize + nSize) > 40000)
	{
		delete fTo;
		fTo = new unsigned char[40000];
		fSize = 0;
	}
	memcpy(fTo + fSize,pData,nSize);
	fSize += nSize;
}

void LiveSource::getData( unsigned char* pData )
{
	memcpy(pData,fTo,fSize);
	fSize = 0;
}
