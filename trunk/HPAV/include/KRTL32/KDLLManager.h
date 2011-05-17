#pragma once

class AFX_EXT_CLASS KDLLManager
{
public:
	KDLLManager(void);
	virtual ~KDLLManager(void);

	virtual bool Load(const std::string& dllname);
	virtual void UnLoad(void);
	virtual void* GetFunction(const std::string& funcname);
	virtual bool HasModule(void);

private:
	HMODULE m_hDLL;
	bool	m_bLoaded;
};
