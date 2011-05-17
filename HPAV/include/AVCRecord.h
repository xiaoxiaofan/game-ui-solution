#ifndef __AVC_RECORD_H__
#define	__AVC_RECORD_H__

#ifndef SUPPORT_VERSION_62	//Ϊͬʱ����AvconPlayer��HPRecord
	#include "../include/AVCFileDefine.h"
#endif

#define		SEEK_EVENT_BEGIN			1
#define		SEEK_EVENT_END				2

// ��·��¼��ӿ�
class IAVCRecordSingleStream
{
public:	
	virtual void WriteData(char* pData, int nLen, bool bKeyFrame) = 0;
	virtual void NotifyStreamClose() = 0;
	virtual void WriteData(char* pData, int nLen, bool bKeyFrame, unsigned long timestamp) = 0;
};

// ¼�񹤳��ӿ��¼�
class IAVCRecordFactoryEvent
{
public:
	virtual	void OnAVCRecordFactoryEvent_FullFile() = 0;
};

// ¼�񹤳��ӿ�
class IAVCRecordFactory
{
public:
	virtual	bool Connect(const char* strAVCFile, PAVC_FILE_HEADER pafh) = 0;
	virtual void ReleaseConnections() = 0;
	virtual bool CreateRecordSingleStream(char frameType, unsigned long ulSessionID, int nChannel, IAVCRecordSingleStream **ppSingleStream) = 0;
	virtual	bool IsFullFile() = 0;
//{{add by yry at 2004.8
	virtual void  PauseClickTimeFrame() = 0;
	virtual	bool  IsPause()=0;
//}}add end
	// + 20081127 Jee
	// �����������Զ�ѡ���ļ���ʽ��Ĭ��Ϊ�Զ�ѡ��
	// �ڵ���Connect�󣬵���IAVCRecordSingleStream::WriteDataǰ��Ч
	virtual void SetAutoDetected(bool bAuto)=0;

	// ȡ�ļ�ԭ�����е���չ��
	virtual const char* GetRealExt()=0;
	//
};

// Seek�¼�
class IAVCReadEvent
{
public:
	virtual	void OnAVCSeekEvent_Seek(int nEvent) = 0;
	virtual	void OnAVCSeekEvent_NewStream(char frame_type, unsigned short sequence, unsigned long session_id, int channel) = 0;
	virtual	void OnAVCSeekEvent_StreamData(int nIndex, PAVC_DATA_FRAME pdf, char* pData, int nLen) = 0;
};

// AVC�ļ����ӿ�
class IAVCReadFactory
{
public:
	virtual	bool Connect(const char* strAVCFile, IAVCReadEvent* pEvent) = 0;
	virtual void ReleaseConnections() = 0;
	virtual int ReadNextFrame(PAVC_DATA_FRAME padf, char** ppData) = 0;
	virtual bool Seek(unsigned long ulSeekTime) = 0;
	virtual bool IsReadOver() = 0;
	virtual unsigned long GetDuration() = 0;
	virtual unsigned long GetPosition() = 0;
	virtual bool IsBuffering(void) = 0;
	virtual void SetBufferTime(unsigned long ulBufferTime) = 0;
};

// Seek�¼�
class IAVCEditEvent
{
public:
};

// AVC�ļ����ӿ�
class IAVCEditFactory
{
public:
	virtual	bool Connect(const char* strAVCFile, IAVCEditEvent* pEvent) = 0;
	virtual void ReleaseConnections() = 0;
	virtual unsigned long GetDuration() = 0;
};

//�޸�
class IRecoverEvent
{
public:
	virtual void OnRecoverEvent(unsigned long ulParam1,unsigned long ulParam2)=0;
};

class IRecoverFactory
{
public:
	virtual	bool Connect(const char* strAVFFile,IRecoverEvent* pEvent)=0;
	virtual void ReleaseConnection()=0;
	virtual bool StartRecover()=0;
	virtual unsigned long GetRecoverRange()=0;
	virtual unsigned long GetCurRecoverPos()=0;
};

bool AFX_EXT_CLASS CreateAVCRecordFactory(IAVCRecordFactory** ppARF, IAVCRecordFactoryEvent* pEvent);
bool AFX_EXT_CLASS CreateAVCReadFactory(IAVCReadFactory** ppARF);
bool AFX_EXT_CLASS CreateAVCEditFactory(IAVCEditFactory** ppAEF);
AFX_EXT_CLASS bool CreateAVCRecoverFactory(IRecoverFactory** ppARF);

AFX_EXT_CLASS IAVCRecordFactory* CreateAVFileWrite(unsigned long fourcc, IAVCRecordFactoryEvent *pEvent);
#endif
