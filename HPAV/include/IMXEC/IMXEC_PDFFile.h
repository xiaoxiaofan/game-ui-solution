//IMXEC_PDFFile.h
#ifndef __IMXEC_PDFFILE_H__
#define __IMXEC_PDFFILE_H__

#include <IMXEC/IMXEC_Export.h>
#include <windows.h>

//PDF文件显示类
class IMXEC_API IMXEC_PDFFile
{
public:
	IMXEC_PDFFile(void){};
	virtual~IMXEC_PDFFile(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开PDF文件显示
	*输入：	cszPathName	-文件的全路径
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Open(const char*cszPathName)=0;
	
	/******************************************************************************
	* Close
	*描述：关闭PDF文件显示
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Close(void)=0;

	/******************************************************************************
	* GetPageCount
	*描述：获取页数
	*输入：无
	*输出：无
	*返回值：返回页数
	*****************************************************************************/
	virtual int GetPageCount(void)=0;

	/******************************************************************************
	* GetPageSize
	*描述：获取页面大小
	*输入：无
	*输出：	nWidth		-页面宽度
			nHeight		-页面高度
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int GetPageSize(int&nWidth,int&nHeight)=0;

	/******************************************************************************
	* DrawPage
	*描述：画一页
	*输入：	hDC			-Handle to device context.
			nPageIndex	-Page index, zero for the first page.
			x			-Left pixel position of the display area in the device coordination
			y			-Top pixel position of the display area in the device coordination
			cx			-Horizontal size (in pixels) for displaying the page
			cy			-Vertical size (in pixels) for displaying the page
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int DrawPage(HDC hDC,int nPageIndex,int x,int y,int cx,int cy)=0;
	
	
	/******************************************************************************
	* Create
	*描述：创建PDF文件显示实例
	*输入：无
	*输出：无
	*返回值：PDF文件显示实例
	*****************************************************************************/
	static IMXEC_PDFFile*Create(void);
};



#endif
