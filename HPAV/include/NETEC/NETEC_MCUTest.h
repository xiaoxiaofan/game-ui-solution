//NETEC_MCUTest.h
#ifndef __NETEC_MCUTEST_H__
#define __NETEC_MCUTEST_H__

#include <NETEC/NETEC_Export.h>

class NETEC_API NETEC_MCUTest
{
public:
	NETEC_MCUTest(void){};
	virtual~NETEC_MCUTest(void){};
public:
	/******************************************************************************
	* Start
	*����������MCU����
	*���룺	��
	*����� ��
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	virtual int Start(void);

	/******************************************************************************
	* Stop
	*������ֹͣMCU����
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void Stop(void);

	/******************************************************************************
	* AddMCU
	*���������Ҫ���Ե�MCU��IP��ַ�Ͷ˿�
	*���룺	cszMCUIP			-MCU��IP��ַ
			usMCUPort			-MCU�Ķ˿�
	*����� ��
	*����ֵ���ɹ����ز��Ա�ʶ��ʧ�ܷ���0
	*****************************************************************************/
	virtual unsigned long AddMCU(const char*cszMCUIP,unsigned short usMCUPort);
	
	/******************************************************************************
	* OnNETEC_MCUTestBegin
	*������MCU��ʼ���ԵĻص�
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_MCUTestBegin(void)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestBegin
	*������MCUĳ����ַ��ʼ���ԵĻص�
	*���룺	ulTestID			-���Ա�ʶ
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_MCUTestBegin(unsigned long ulTestID)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestTXBitrateChanged
	*������MCUĳ����ַ���д���ı�Ļص�
	*���룺	ulTestID			-���Ա�ʶ
			nBitrate			-���д���kbps��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_MCUTestTXBitrateChanged(unsigned long ulTestID,int nBitrate)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestTXBitrateChanged
	*������MCUĳ����ַ���д���ı�Ļص�
	*���룺	ulTestID			-���Ա�ʶ
			nBitrate			-���д���kbps��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_MCUTestRXBitrateChanged(unsigned long ulTestID,int nBitrate)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestRTTChanged
	*������MCUĳ����ַ����ʱ��ı�Ļص�
	*���룺	ulTestID			-���Ա�ʶ
			nRTT				-����ʱ�䡾���롿
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_MCUTestRTTChanged(unsigned long ulTestID,unsigned long nRTT)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestEnd
	*������MCUĳ����ַ�������ԵĻص�
	*���룺	ulTestID			-���Ա�ʶ
			nMinTXBitrate		-��С���д���kbps��
			nMaxTXBitrate		-������д���kbps��
			nAvgTXBitrate		-ƽ�����д���kbps��
			nMinRXBitrate		-��С���д���kbps��
			nMaxRXBitrate		-������д���kbps��
			nAvgRXBitrate		-ƽ�����д���kbps��
			nMinRTT				-��С����ʱ�䡾���롿
			nMaxRTT				-�������ʱ�䡾���롿
			nAvgRTT				-ƽ������ʱ�䡾���롿
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_MCUTestEnd(unsigned long ulTestID,int nMinTXBitrate,int nMaxTXBitrate,int nAvgTXBitrate,int nMinRXBitrate,int nMaxRXBitrate,int nAvgRXBitrate,unsigned long nMinRTT,unsigned long nMaxRTT,unsigned long nAvgRTT)=0;
	
	/******************************************************************************
	* OnNETEC_MCUTestEnd
	*������MCU�������ԵĻص�
	*���룺	��
	*����� ��
	*����ֵ����
	*****************************************************************************/
	virtual void OnNETEC_MCUTestEnd(void)=0;
};


#endif
