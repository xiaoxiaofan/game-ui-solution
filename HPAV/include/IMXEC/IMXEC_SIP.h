//IMXEC_SIP.h
#ifndef __IMXEC_SIP_H__
#define __IMXEC_SIP_H__

#include <IMXEC/IMXEC_Export.h>
#include <IMXEC/IMXEC_VideoSetting.h>
#include <IMXEC/IMXEC_AudioSetting.h>


//SIPЭ��
class IMXEC_API IMXEC_SIP
{
public:
	IMXEC_SIP(void);
	virtual~IMXEC_SIP(void);
public:
	/******************************************************************************
	* AddVirtualLine
	*���������������·
	*���룺	cszUserID		-�û��ʺ�
			cszUserName		-�û�����
			cszPassword		-�û�����
			cszHost			-SIP���������
	*�������
	*����ֵ���ɹ�����>=0[line id]��ʧ�ܷ���-1
	*****************************************************************************/
	static int AddVirtualLine(const char*cszUserID,const char*cszUserName,const char*cszPassword,const char*cszSIPProxy,const char*cszAuthUserID=NULL,const char*cszDomain=NULL);

	/******************************************************************************
	* RemoveVirtualLine
	*������ɾ��������·
	*���룺	nLineID			-��·��ʶ
	*�������
	*����ֵ����
	*****************************************************************************/
	static void RemoveVirtualLine(int nLineID);

	static int SetCurrentVirtualLine(int nLineID);
	static int GetCurrentVirtualLine(void);
	static int IsVirtualLineRegistrationSuccess(int nLineID);
	static int IsCurrentVirtualLineRegistrationSuccess(void);
	static int IsVirtualLineRegistrationError(int nLineID);
	static int IsCurrentVirtualLineRegistrationError(void);
	static const char*GetVirtualLineRegistrationErrorCode(int nLineID);
	static const char*GetCurrentVirtualLineRegistrationErrorCode(void);


	/******************************************************************************
	* SetSIPListenPort
	*���������������˿�
	*���룺	nSIPListenPort			-�����˿�
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetSIPListenPort(unsigned short nSIPListenPort);

	/******************************************************************************
	* SetLocalIP
	*����������ע���ʺ�
	*���룺	cszSIPID		-ע���ʺ�
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetLocalIP(const char*cszLocalIP);

	/******************************************************************************
	* SetRTPBasePort
	*���������������˿�
	*���룺	nRTPBasePort			-RTP��ʼ�˿�
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetRTPBasePort(unsigned short nRTPBasePort);

	/******************************************************************************
	* SetAudioDevParam
	*����������������Ƶ�豸����
	*���룺 nAudioCodecID		-��Ƶ����
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetAudioDevParam(X_AUDIO_CODEC_ID nAudioCodecID);

	/******************************************************************************
	* SetMainVideoDevParam
	*����������������Ƶ�豸����
	*���룺 nDevID				-�豸��ʶ
			nFrameRate			-֡��
			nBitrate			-����
			nVideoCodecType		-��Ƶ����
			nVideoFormatType	-��Ƶ��ʽ
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int SetMainVideoDevParam(int nDevID,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE nVideoCodecType,VIDEO_FORMAT_TYPE nVideoFormatType);

	/******************************************************************************
	* Start
	*����������SIP����
	*���룺��
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int Start(void);

	/******************************************************************************
	* Stop
	*������ֹͣSIP����
	*���룺��
	*�������
	*����ֵ���ɹ�����0��ʧ�ܷ���-1
	*****************************************************************************/
	static int Stop(void);
};




#endif
