//IMXEC_PDFConvert.h
#ifndef __IMXEC_PDFCONVERT_H__
#define __IMXEC_PDFCONVERT_H__

#include <IMXEC/IMXEC_Export.h>

//PDFת����
class IMXEC_API IMXEC_PDFConvert
{
public:
	typedef enum
	{
		PDF_STATUS_INITIALIZING=0,		//���ڳ�ʼ��
		PDF_STATUS_CONVERTING,			//����ת��
		PDF_STATUS_CONVERT_OK,			//ת���ɹ�
		PDF_STATUS_CONVERT_FAILED,		//ת��ʧ��
	}PDF_STATUS;
public:
	IMXEC_PDFConvert(void){};
	virtual~IMXEC_PDFConvert(void){};
public:
	/******************************************************************************
	* Open
	*��������PDF�ļ�ת��
	*���룺	cszDocPathName		-Ҫת�����ĵ���ȫ·��
			cszPDFPathName		-ת�����PDF�ĵ���ȫ·��
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int Open(const char*cszDocPathName,const char*cszPDFPathName)=0;
	
	/******************************************************************************
	* Close
	*�������ر�PDF�ļ�ת��
	*���룺��
	*�������
	*����ֵ����
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* GetStatus
	*��������ȡ״̬
	*���룺��
	*�������
	*����ֵ������״̬
	*****************************************************************************/
	virtual IMXEC_PDFConvert::PDF_STATUS GetStatus(void)=0;
	
	/******************************************************************************
	* Create
	*����������PDFת��ʵ��
	*���룺��
	*�������
	*����ֵ��PDFת��ʵ��
	*****************************************************************************/
	static IMXEC_PDFConvert*Create(void);

	static void SetTempPath(const char*cszTempPath);
};

#endif

