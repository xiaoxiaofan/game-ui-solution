#include "LiveSource.h"


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
	if (fSize > 40000)
	{

	}
	memcpy(fTo + fSize,pData,nSize);
	fSize += nSize;
}

void LiveSource::getData( unsigned char* pData )
{
	memcpy(pData,fTo,fSize);
	fSize = 0;
}
