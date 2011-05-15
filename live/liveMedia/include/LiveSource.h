#ifndef LiveSource_h__
#define LiveSource_h__
#include "singleton.hpp"


class LiveSource : public SGT::Singleton<LiveSource>
{
public:
	LiveSource(void);
	~LiveSource(void);

	void setData(unsigned char* pData,int nSize);

	void getData(unsigned char* pData);

private:
    unsigned char* fTo;
	int fSize;
};


#endif // LiveSource_h__

