/********************************************************************

		   �ļ���  :    DESBaseInterface.h
           ����ʱ��:    2011/4/3 8:57
		   �ļ�����:    
           ����    :    ���
           ����    :    http://blog.csdn.net/w495081611
		   ��ϵ    :    wuban1011@gmail.com

********************************************************************/

#ifndef DESBaseInterface_h__
#define DESBaseInterface_h__

/******************************************************************** 

		  ����    :    CDESBaseInterface 
		  ��������:     
		  �����ռ�:     
		  ����    :    ��� 
		  ����ʱ��:    2011/4/3 8:58 
          ������  :    

********************************************************************/

class AFX_EXT_CLASS CDESBaseInterface
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


#endif // DESBaseInterface_h__

