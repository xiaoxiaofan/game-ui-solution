#pragma once

//---------------------------------------------------------------------------------------
// KBuffer�������ඨ��
class AFX_EXT_CLASS KBuffer  
{
public:
	KBuffer(void);
	virtual ~KBuffer(void);

	/* ���û��������� */
	virtual bool SetBuffer(const void* pBufferData,size_t nBufferSize);

	/* ��ȡ����������ָ�� */
	virtual unsigned char* GetBuffer(void);

	/* ��ȡ���������ݴ�С */
	virtual size_t GetSize(void);

	/* ����������ѹ�� */
	virtual bool Compress(void);

	/* ���������ݽ�ѹ�� */
	virtual bool Decompress(void);

protected:
	unsigned char*	m_pBufferData;	//����������ָ��
	size_t			m_nBufferSize;	//��������Ч���ݴ�С	
	size_t			m_nBufferBound;	//�������߽�
};

//---------------------------------------------------------------------------------------
// KBufferEx�������ඨ��
class AFX_EXT_CLASS KBufferEx : public KBuffer
{
public:
	KBufferEx(void){};
	virtual ~KBufferEx(void){};

	/* ���û��������� */
	virtual bool SetBuffer(unsigned long ulID,const void* pBufferData,size_t nBufferSize)
	{
		m_ulID = ulID;
		return KBuffer::SetBuffer(pBufferData,nBufferSize);
	}

	virtual unsigned long GetID(void)
	{
		return m_ulID;
	}

protected:
	unsigned long	m_ulID;
};