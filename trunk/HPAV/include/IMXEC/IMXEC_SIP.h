//IMXEC_SIP.h
#ifndef __IMXEC_SIP_H__
#define __IMXEC_SIP_H__

#include <IMXEC/IMXEC_Export.h>
#include <IMXEC/IMXEC_VideoSetting.h>
#include <IMXEC/IMXEC_AudioSetting.h>


//SIP协议
class IMXEC_API IMXEC_SIP
{
public:
	IMXEC_SIP(void);
	virtual~IMXEC_SIP(void);
public:
	/******************************************************************************
	* AddVirtualLine
	*描述：添加虚拟线路
	*输入：	cszUserID		-用户帐号
			cszUserName		-用户名称
			cszPassword		-用户密码
			cszHost			-SIP代理服务器
	*输出：无
	*返回值：成功返回>=0[line id]，失败返回-1
	*****************************************************************************/
	static int AddVirtualLine(const char*cszUserID,const char*cszUserName,const char*cszPassword,const char*cszSIPProxy,const char*cszAuthUserID=NULL,const char*cszDomain=NULL);

	/******************************************************************************
	* RemoveVirtualLine
	*描述：删除虚拟线路
	*输入：	nLineID			-线路标识
	*输出：无
	*返回值：无
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
	*描述：设置侦听端口
	*输入：	nSIPListenPort			-侦听端口
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetSIPListenPort(unsigned short nSIPListenPort);

	/******************************************************************************
	* SetLocalIP
	*描述：设置注册帐号
	*输入：	cszSIPID		-注册帐号
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetLocalIP(const char*cszLocalIP);

	/******************************************************************************
	* SetRTPBasePort
	*描述：设置侦听端口
	*输入：	nRTPBasePort			-RTP开始端口
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetRTPBasePort(unsigned short nRTPBasePort);

	/******************************************************************************
	* SetAudioDevParam
	*描述：设置主流视频设备参数
	*输入： nAudioCodecID		-音频编码
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetAudioDevParam(X_AUDIO_CODEC_ID nAudioCodecID);

	/******************************************************************************
	* SetMainVideoDevParam
	*描述：设置主流视频设备参数
	*输入： nDevID				-设备标识
			nFrameRate			-帧率
			nBitrate			-码流
			nVideoCodecType		-视频编码
			nVideoFormatType	-视频格式
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int SetMainVideoDevParam(int nDevID,int nFrameRate,int nBitrate,VIDEC_CODEC_TYPE nVideoCodecType,VIDEO_FORMAT_TYPE nVideoFormatType);

	/******************************************************************************
	* Start
	*描述：启动SIP服务
	*输入：无
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int Start(void);

	/******************************************************************************
	* Stop
	*描述：停止SIP服务
	*输入：无
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	static int Stop(void);
};




#endif
