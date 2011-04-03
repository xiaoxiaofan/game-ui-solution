/********************************************************************

		   文件名  :    DESBaseInterface.h
           创建时间:    2011/4/3 8:57
		   文件描述:    
           作者    :    吴办
           博客    :    http://blog.csdn.net/w495081611
		   联系    :    wuban1011@gmail.com

********************************************************************/

#pragma once

/******************************************************************** 

		  类名    :    CDESBaseInterface 
		  基类名称:     
		  命名空间:     
		  作者    :    吴办 
		  创建时间:    2011/4/3 8:58 
          类描述  :    

********************************************************************/

class CDESBaseInterface
{
public:
	CDESBaseInterface(void);
	~CDESBaseInterface(void);

	bool SetOwner(IAMTimelineObj * inOwner);
	IAMTimelineObj * GetOwner(void);

	virtual bool QueryInterfaceSelf(void) = 0;
	virtual void ReleaseInterface(void) = 0;

protected:
	IAMTimelineObj *   m_OwnerObject;

private:
	void ReleaseSelf(void);
};

