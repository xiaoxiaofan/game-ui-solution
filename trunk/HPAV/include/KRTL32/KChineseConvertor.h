#pragma once

#define CHINESE_SIMPLIFIED 936
#define CHINESE_TRADITIONAL 950

class AFX_EXT_CLASS KChineseConvertor
{
public:
	KChineseConvertor(void);
	virtual ~KChineseConvertor(void);
	CString GBKSimplified2Big5(CString csGBKSimplified);
};


