#ifndef LiveSource_h__
#define LiveSource_h__


class LiveSource
{
public:
	LiveSource(void);
	~LiveSource(void);

	void setData(unsigned char* pData,int nSize);

	void getData(unsigned char* pData,int nSize);

private:
	unsigned char* fTo;
	int fSize;
};


#endif // LiveSource_h__

