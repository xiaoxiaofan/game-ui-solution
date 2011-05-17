/**********************************************************
 * Name: KUtils.h
 * Author: zhouxiaochuan@gmail.com
 * Date: 2007-03-15
 **********************************************************/

#pragma once

#include <string>
#include <algorithm>
#include <map>
#include <list>

#ifdef WIN32
#include <process.h>
typedef long pid_t;
#define getpid	_getpid
#define unlink	_unlink
#else
#include <unistd.h>
#endif

/* ����ָ�����(����int)�����ַ��� */
typedef std::map<int,std::string> STRING_MAP;
typedef std::map<std::string,std::string> STRING_MAP_EX;

/* �����Ƚ��ȳ�˳�򱣴��ַ��� */
typedef std::list<std::string> STRING_LIST;

/* �����ʼ������,�ڻ�ȡ���������֮ǰ���ô˺������г�ʼ�� */
AFX_EXT_CLASS void InitRandom(void);

/* ��ȡ�����
 * nNumber: �������Χ���ֵ */
AFX_EXT_CLASS int Random(int nNumber);

/* ��ȡ��ǰʱ��(����millisecond) */
AFX_EXT_CLASS unsigned long GetTimeStamp(void);

/* ��ȡ��ǰʱ��(΢��microsecond) */
AFX_EXT_CLASS unsigned long GetMicroTimeStamp(void);

/* ��ͣ(����):���������� */
AFX_EXT_CLASS void Pause(unsigned long ulMS);

/* BASE64���� */
AFX_EXT_CLASS void Base64Encode(const std::string& InBuffer,std::string& OutBuffer);

/* BASE64���� */
AFX_EXT_CLASS void Base64Decode(const std::string& InBuffer,std::string& OutBuffer);

/* �������ļ�����BASE64���� */
AFX_EXT_CLASS size_t Base64EncodeFromFile(const std::string& filename,std::string& encodedstr);

/* ���ַ���BASE64���뱣�浽�ļ��� */
AFX_EXT_CLASS void Base64DecodeToFile(const std::string& encodedstr,const std::string& filename);

/* �ַ�����дת�� */
AFX_EXT_CLASS std::string UPPERCASE(const std::string& source);

/* �ַ���Сдת�� */
AFX_EXT_CLASS std::string LOWERCASE(const std::string& source);

/* ����ַ���������пո� */
AFX_EXT_CLASS std::string TRIMLEFT(const std::string& source, const char* chars2remove);

/* ����ַ����ұ����пո� */
AFX_EXT_CLASS std::string TRIMRIGHT(const std::string& source, const char* chars2remove);

/* ����ַ����������пո� */
AFX_EXT_CLASS std::string TRIMSPACE(const std::string& source);

/* ����ת�� */
AFX_EXT_CLASS std::string LONG2STR(long value);
AFX_EXT_CLASS std::string ULONG2STR(unsigned long value);
AFX_EXT_CLASS std::string INT2STR(int value);
AFX_EXT_CLASS std::string UINT2STR(unsigned int value);
AFX_EXT_CLASS std::string SHORT2STR(short value);
AFX_EXT_CLASS std::string USHORT2STR(unsigned short value);
AFX_EXT_CLASS std::string BYTE2STR(unsigned char value);
AFX_EXT_CLASS std::string BOOL2STR(bool value);
AFX_EXT_CLASS std::string DOUBLE2STR(double value);

AFX_EXT_CLASS long STR2LONG(const std::string& value);
AFX_EXT_CLASS unsigned long STR2ULONG(const std::string& value);
AFX_EXT_CLASS int STR2INT(const std::string& value);
AFX_EXT_CLASS unsigned int STR2UINT(const std::string& value);
AFX_EXT_CLASS short STR2SHORT(const std::string& value);
AFX_EXT_CLASS unsigned short STR2USHORT(const std::string& value);
AFX_EXT_CLASS unsigned char STR2BYTE(const std::string& value);
AFX_EXT_CLASS bool STR2BOOL(const std::string& value);
AFX_EXT_CLASS double STR2DOUBLE(const std::string& value);

AFX_EXT_CLASS unsigned short BOOL2USHORT(bool value);
AFX_EXT_CLASS bool USHORT2BOOL(unsigned short value);

AFX_EXT_CLASS std::string ULONG2HEX(unsigned long value);
AFX_EXT_CLASS unsigned long HEX2ULONG(const std::string& value);

AFX_EXT_CLASS std::string NONULLSTR(const char* value);

/* �ַ����ָ� */
AFX_EXT_CLASS STRING_MAP StrSplit(const std::string& data,const std::string& token);
AFX_EXT_CLASS STRING_MAP_EX StrSplitEx(const std::string& data,const std::string& token);
AFX_EXT_CLASS bool URLSplit(const std::string& url,std::string& protocol,std::string& serveraddr,unsigned short& serverport,std::string& filepath);

/* ��ȡ�ļ���С */
AFX_EXT_CLASS unsigned long GetFileSize(const std::string& strFileFullPath);

/* ɾ���ļ� */
AFX_EXT_CLASS bool DeleteFile(const std::string& strFileFullPath);

/* ��ñ�����ID */
AFX_EXT_CLASS pid_t GetProcessID(void);

/* ѹ���ַ��� */
AFX_EXT_CLASS bool Compress(const char* pSourceData,int nSourceLen,char* pDestData,int& nDestLen);

/* ��ѹ�ַ��� */
AFX_EXT_CLASS bool UnCompress(const char* pSourceData,int nSourceLen,char* pDestData,int& nDestLen);

#ifdef WIN32
/********************************************************************
 * ��ͨ���ַ��������UTF8�ַ���
 ********************************************************************/
AFX_EXT_CLASS std::string U2A(CString csUnicodeString);

/********************************************************************
 * ��UTF8�ַ��������ͨ���ַ���
 ********************************************************************/
AFX_EXT_CLASS CString A2U(const std::string& strAnsiString);
#endif

/* ���IP������ nBitȡ32/16/12/8... */
AFX_EXT_CLASS unsigned long GetBitMask(unsigned int nBit);

/********************************************************************
 * Ȩ�������
 * Ȩ�����Գ����ͱ�ʾ,��������λ�趨ÿһλȨ��ֵ,1Ϊtrue,0Ϊfalse
 * Ȩ��λ��˳��ӵ�λ(1)����λ(20)��������.
 ********************************************************************/

/* ����Ȩ��λ
 * ulPrivilege:		����Ȩ����
 * ucBit:			Ȩ��λ(ȡֵ��Χ1-20)
 * bEnabled:		Ȩ��ֵ
 * <RETURN>:		����Ȩ�޺����Ȩ���� */
AFX_EXT_CLASS unsigned long SetPrivilege(unsigned long ulPrivilege,unsigned char ucBit,bool bEnabled);

/* ���Ȩ��λ
 * ulPrivilege:		Ȩ����
 * ucBit:			Ȩ��λ(ȡֵ��Χ1-20)
 * <RETURN>:		Ȩ��ֵ */
AFX_EXT_CLASS bool GetPrivilege(unsigned long ulPrivilege,unsigned char ucBit);
