#pragma once

#ifdef WIN32
#else
#include <dlfcn.h>
#endif

//---------------------------------------------------------------------------------------
// ��̬���ӿ������
class AFX_EXT_CLASS KDLLManager
{
public:
	KDLLManager(void);
	virtual ~KDLLManager(void);

	//���ض�̬���ӿ�
	virtual bool Load(const char* pDllName);

	//ж�ض�̬���ӿ�
	virtual void UnLoad(void);

	//��ú������
	virtual void* GetFunction(const char* pFunctionName);

private:
#ifdef WIN32
	HMODULE m_hDLL;
#else
	void* m_hDLL;
#endif
};
