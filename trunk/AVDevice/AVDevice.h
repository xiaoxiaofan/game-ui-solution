// 下列 ifdef 块是创建使从 DLL 导出更简单的
// 宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 AVDEVICE_EXPORTS
// 符号编译的。在使用此 DLL 的
// 任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将
// AVDEVICE_API 函数视为是从 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifdef AVDEVICE_EXPORTS
#define AVDEVICE_API __declspec(dllexport)
#else
#define AVDEVICE_API __declspec(dllimport)
#endif

#include <streams.h>

// 此类是从 AVDevice.dll 导出的
class AVDEVICE_API CAVDeviceEnum {

public:
	CAVDeviceEnum(void);
	~CAVDeviceEnum(void);

	bool Initalize(void);
	void Release(void);
	void GetAVCount(int& count);
	
    void GetAudioCount(int& count);
	void GetVideoCount(int& count);
	
     void GetAudioName(int nDevID,char * sName,int nBufferSize);
     void GetVideoName(int nDevID,char * sName,int nBufferSize);
	 static CAVDeviceEnum*   GetInstance(void);


private:

     IGraphBuilder*               m_pGraph;
     ICreateDevEnum*              m_pCreateDevEnum;
	 IEnumMoniker*                m_pVideoEm;
	 IEnumMoniker*                m_pAudioEm;
	 static CAVDeviceEnum*        m_pMe;

};



/*----------------------------------------------------------------------------*\
|   ErrMsg - Opens a Message box with a error message in it.  The user can     |
|            select the OK button to continue                                  |
\*----------------------------------------------------------------------------*/

void ErrMsg(LPTSTR szFormat,...);


