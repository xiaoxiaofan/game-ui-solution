// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� AVDEVICE_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// AVDEVICE_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef AVDEVICE_EXPORTS
#define AVDEVICE_API __declspec(dllexport)
#else
#define AVDEVICE_API __declspec(dllimport)
#endif

#include <streams.h>

// �����Ǵ� AVDevice.dll ������
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


