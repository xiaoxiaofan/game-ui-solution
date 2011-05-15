#ifndef LiveSource_h__
#define LiveSource_h__


class LiveSource 
{
public:
	LiveSource(void);
	~LiveSource(void);

	static void setData(unsigned char* pData,int nSize);

	static void getData(unsigned char* pData);

private:
	unsigned char* fTo;
	int fSize;
};


#endif // LiveSource_h__

