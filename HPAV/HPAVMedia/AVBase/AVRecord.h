#pragma once
#include <AVCRecord.h>
#include <kbase/CritSec.h>

class CAVRecordNotify
{
public:
	CAVRecordNotify(void){};
	~CAVRecordNotify(void){};

	virtual bool StartRecordToAVI(const char*cszPathName,int nStandardFormat) = 0;
	virtual void StopRecordToAVI(void) = 0;
	virtual void RequestKeyFrame(void) = 0;
};

class CAVRecord 
{
public:
	CAVRecord(CAVRecordNotify& rNotify);
	~CAVRecord(void);

public:
	void Initlize(void);
	void Release(void);

	BOOL CanRecordToAVI(unsigned char *pData);
	BOOL StartRecord();	                // ¿ªÊ¼Â¼Ïñ
	void StopRecord();		           // Í£Ö¹Â¼Ïñ
	bool IsRecording() const;

	void ChangeRecordType(unsigned char*pPacketData, int nPacketLen);

private:
	CAVRecordNotify&			m_rNotify;
	bool						m_bRecording;
	

};
