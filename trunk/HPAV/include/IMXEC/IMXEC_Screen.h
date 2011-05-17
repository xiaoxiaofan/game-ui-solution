//IMXEC_Screen.h
#ifndef __IMXEC_SCREEN_H__
#define __IMXEC_SCREEN_H__

#include <windows.h>

#include <IMXEC/IMXEC_Export.h>

//桌面控制发送回调类
class IMXEC_ScreenTXCallback
{
public:
	IMXEC_ScreenTXCallback(void){};
	virtual~IMXEC_ScreenTXCallback(void){};
public:
	/******************************************************************************
	* OnIMXEC_ScreenTXCallbackConnected
	*描述：桌面控制发送连接成功的回调
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void OnIMXEC_ScreenTXCallbackConnected(void)=0;

	/******************************************************************************
	* OnIMXEC_ScreenTXCallbackDisconnected
	*描述：桌面控制发送连接断开的回调
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void OnIMXEC_ScreenTXCallbackDisconnected(void)=0;
};

//桌面控制发送类
class IMXEC_API IMXEC_ScreenTX
{
public:
	IMXEC_ScreenTX(void){};
	virtual~IMXEC_ScreenTX(void){};
public:
	/******************************************************************************
	* Start
	*描述：启动桌面控制发送
	*输入：	cszPeerNodeID	-接收方的节点标识
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Start(const char*cszPeerNodeID)=0;
	
	/******************************************************************************
	* Stop
	*描述：停止桌面控制发送
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Stop(void)=0;
	
	/******************************************************************************
	* GetScreenID
	*描述：获取桌面控制标识
	*输入：无
	*输出：无
	*返回值：桌面控制标识
	*****************************************************************************/
	virtual unsigned long GetScreenID(void)=0;
	
	/******************************************************************************
	* GetRemoteViewOnly
	*描述：设置远端是否只能看不能控制
	*输入：nViewOnly			-远端是否只能看不能控制【0:可以控制，其他：只能看】
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void SetRemoteViewOnly(int nViewOnly)=0;
	
	/******************************************************************************
	* GetRemoteViewOnly
	*描述：获取远端是否只能看不能控制
	*输入：无
	*输出：无
	*返回值：远端是否只能看不能控制【0:可以控制，其他：只能看】
	*****************************************************************************/
	virtual int GetRemoteViewOnly(void)=0;
	
	/******************************************************************************
	* Create
	*描述：创建桌面控制发送实例
	*输入：rCallback		-桌面控制发送回调实例
	*输出：无
	*返回值：桌面控制发送实例
	*****************************************************************************/
	static IMXEC_ScreenTX*Create(IMXEC_ScreenTXCallback&rCallback);
};

//桌面控制接收回调类
class IMXEC_ScreenRXCallback
{
public:
	IMXEC_ScreenRXCallback(void){};
	virtual~IMXEC_ScreenRXCallback(void){};
public:
	/******************************************************************************
	* OnIMXEC_ScreenRXCallbackConnected
	*描述：桌面控制接收连接成功的回调
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void OnIMXEC_ScreenRXCallbackConnected(void)=0;

	/******************************************************************************
	* OnIMXEC_ScreenRXCallbackDisconnected
	*描述：桌面控制接收连接断开的回调
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void OnIMXEC_ScreenRXCallbackDisconnected(void)=0;

	/******************************************************************************
	* OnIMXEC_ScreenRXCallbackFullScreenChanged
	*描述：桌面控制接收全屏模式改变的回调
	*输入：nFullScreen		-当前是否全屏模式【0：普通窗口模式，非0：全屏模式】
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void OnIMXEC_ScreenRXCallbackFullScreenChanged(int nFullScreen)=0;
};

//桌面控制接收类
class IMXEC_API IMXEC_ScreenRX
{
public:
	IMXEC_ScreenRX(void){};
	virtual~IMXEC_ScreenRX(void){};
public:
	/******************************************************************************
	* Open
	*描述：打开文件接收
	*输入：	cszPeerUserName	-在窗口标题中显示的用户名称
			cszPeerNodeID	-发送方的节点标识
			nScreenID		-桌面控制标识【来自桌面控制发送端】
			cszPeerMCUID	-对方MCU的标识
			cszPeerMCUIP	-对方MCU的IP地址
			nPeerMCUPort	-对方MCU的端口
			cszPeerMCUType	-对方MCU的地址类型
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int Start(const char*cszPeerUserName,const char*cszPeerNodeID,unsigned long nScreenID,const char*cszPeerMCUID,const char*cszPeerMCUIP,unsigned short nPeerMCUPort,const char*cszPeerMCUType)=0;
	
	/******************************************************************************
	* Stop
	*描述：停止桌面控制接收
	*输入：无
	*输出：无
	*返回值：无
	*****************************************************************************/
	virtual void Stop(void)=0;
	
	/******************************************************************************
	* SetFullScreen
	*描述：设置是否全屏模式
	*输入：nFullScreen		-是否全屏模式【0：普通窗口模式，非0：全屏模式】
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetFullScreen(int nFullScreen)=0;
	
	/******************************************************************************
	* SendCtrlEsc
	*描述：发送Ctrl-Esc组合键
	*输入：无
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SendCtrlEsc(void)=0;
	
	/******************************************************************************
	* SendCtrlAltDel
	*描述：发送Ctrl-Alt-Del组合键
	*输入：无
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SendCtrlAltDel(void)=0;
	
	/******************************************************************************
	* SetUse8Bit
	*描述：设置是否使用8位色
	*输入：nUse8Bit		-是否使用8位色【0：不使用8位色，非0：使用8位色】
	*输出：无
	*返回值：成功返回0，失败返回-1
	*****************************************************************************/
	virtual int SetUse8Bit(int nUse8Bit)=0;
	
	/******************************************************************************
	* Create
	*描述：创建桌面控制接收实例
	*输入：rCallback		-桌面控制接收回调实例
	*输出：无
	*返回值：桌面控制接收实例
	*****************************************************************************/
	static IMXEC_ScreenRX*Create(IMXEC_ScreenRXCallback&rCallback);
};

	
/******************************************************************************
* TranslateScreenRXMsg
*描述：捕获桌面控制接收的快捷组合键【Ctrl-Alt-Shilft-F】
*输入：pMsg		-主进程消息
*输出：无
*返回值：成功返回0，失败返回-1
*请在主应用程序的CWinApp::PreTranslateMessage(MSG* pMsg)中调用，比如：

BOOL CScreenRXTestApp::PreTranslateMessage(MSG* pMsg)
{
	TranslateScreenRXMsg(pMsg);

	return CWinApp::PreTranslateMessage(pMsg);
}

*****************************************************************************/
IMXEC_API int TranslateScreenRXMsg(MSG *pMsg);

#endif