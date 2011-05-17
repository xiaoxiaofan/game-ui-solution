//IMXEC_PDFConvert.h
#ifndef __IMXEC_PDFCONVERT_H__
#define __IMXEC_PDFCONVERT_H__

#include <IMXEC/IMXEC_Export.h>

//PDF转换类
class IMXEC_API IMXEC_PDFConvert
{
public:
	typedef enum
	{
		PDF_STATUS_INITIALIZING=0,		//正在初始化
		PDF_STATUS_CONVERTING,			//正在转换
		PDF_STATUS_CONVERT_OK,			//转换成功
		PDF_STATUS_CONVERT_FAILED,		//转换失败
	}PDF_STATUS;
public:
	IMXEC_PDFConvert(void){};
	virtual~IMXEC_PDFConvert(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开PDF文件转化
	*输入：	cszDocPathName		-要转换的文档的全路径
			cszPDFPathName		-转换后的PDF文档的全路径
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Open(const char*cszDocPathName,const char*cszPDFPathName)=0;
	
	/******************************************************************************
	* Close
	*描述：关闭PDF文件转化
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* GetStatus
	*描述：获取状态
	*输入：无
	*输出：无
	*返回值：返回状态
	*****************************************************************************/
	virtual IMXEC_PDFConvert::PDF_STATUS GetStatus(void)=0;
	
	/******************************************************************************
	* Create
	*描述：创建PDF转换实例
	*输入：无
	*输出：无
	*返回值：PDF转换实例
	*****************************************************************************/
	static IMXEC_PDFConvert*Create(void);

	static void SetTempPath(const char*cszTempPath);
};

#endif

