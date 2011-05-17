//VIDEC_Player.h
#ifndef __VIDEC_PLAYER_H__
#define __VIDEC_PLAYER_H__


#include <winsock2.h>
#include <windows.h>
#include <VIDEC/VIDEC_Export.h>

class VIDEC_API VIDEC_Player
{
public:
	VIDEC_Player(void){};
	virtual~VIDEC_Player(void){};
public:
	//打开显示窗口
	//hWndParent，显示窗口的父窗口句柄
	//成功返回0，失败返回-1
	virtual int Open(HWND hWndParent,unsigned long*lpnVideoTimestamp=NULL,unsigned long*lpnAudioTimestamp=NULL)=0;
	//关闭显示窗口
	virtual void Close(void)=0;

	//取视频宽度
	virtual int GetVideoWidth(void)=0;
	//取视频高度
	virtual int GetVideoHeight(void)=0;

	//取视频窗口
	virtual HWND GetWnd(void)=0;
	//same as CWnd::IsWindowVisible
	virtual bool IsWindowVisible(void)=0;
	//same as CWnd::SetWindowPos
	virtual bool SetWindowPos(HWND hWndInsertAfter,int x,int y,int cx,int cy,UINT nFlags)=0; 

	virtual double GetAverageFPS(void)=0;

	virtual void SetSynFlag(int nSynFlag)=0;

	virtual bool HasVideo(void)=0;

	virtual int PlayData(void*pPacketData,int nPacketSize)=0;

	//保持当前图象到BMP文件
	virtual bool CaptureToBMPFile(const char*cszFile)=0;
	
	//设置视频属性
	virtual int SetVideoParam(int nBrightness, int nContrast, int nSaturation, int nHue,int nGamma,int nSharpen)=0;

	virtual int SetVideoGammaRGB(int nGammaR,int nGammaG,int nGammaB)=0;
	virtual void SetScreenWnd(int nScreenIndex,int nWndIndex,int nFullScreen)=0;
	virtual VIDEC_Image*GetImage(void)=0;

	static VIDEC_Player*Create(void);
	static void SetMaxDXVAPlayers(unsigned int nCount);

	virtual int GetSupportPreview(void)=0;
};

#endif