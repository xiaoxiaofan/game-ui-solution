// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� AVDEVICE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// AVDEVICE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#pragma once

#include <streams.h>
#include <atlbase.h>
#include "..\include\singleton.hpp"
#include "Export.h"

class AVDEVICE_API AVDeviceEnum : public SGT::Singleton<AVDeviceEnum>
{
public:
	AVDeviceEnum(void);
	~AVDeviceEnum(void);

	bool Initalize(void);
	void Release(void);

	void GetAVCount(int& count);

    void GetAudioCount(int& count);
	void GetVideoCount(int& count);
	
    void GetAudioName(int nDevID,char * sName,int nBufferSize);
    void GetVideoName(int nDevID,char * sName,int nBufferSize);
};






