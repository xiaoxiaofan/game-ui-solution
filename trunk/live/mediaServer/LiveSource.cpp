#include "LiveSource.h"


LiveSource::LiveSource(void)
{
	fTo = NULL;
	fSize = 0;
}


LiveSource::~LiveSource(void)
{
}

void LiveSource::setData( unsigned char* pData,int nSize )
{
	memcpy(fTo,pData,nSize);
}

void LiveSource::getData( unsigned char* pData )
{
	memcpy(pData,fTo,fSize);
}
