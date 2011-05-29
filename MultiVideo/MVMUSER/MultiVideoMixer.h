//------------------------------------------------------------------------------
// File: MultiVideoMixer.h
//
// 
//
//
//------------------------------------------------------------------------------
#include "MVMUSER.h"

class CMultiVideoMixer
	:public CMVMixer
{
public:
	CMultiVideoMixer();
    ~CMultiVideoMixer();
	//初始化
	HRESULT Initialize(HWND hwnd,UINT Width, UINT Height,D3DFORMAT format,BOOL bBufferInSystemMem);
	HRESULT InitializeEx(HWND hwnd,HWND hwndCpy,UINT Width, UINT Height,D3DFORMAT FinalFormat,BOOL bBufferInSystemMem);
	//销毁
    HRESULT Terminate();
	//
	HRESULT Get3DDevice(IDirect3DDevice9 ** pDevice);
	void Release();
	//得到当前显示数据（全局）
	HRESULT GetData(CSurfaceBuff** ppBuff);
	//全局逐帧回调函数
	HRESULT SetTransformProc(TransformProc   pProc,TransformProc* pOldProc);
	HRESULT GetTransformProc(TransformProc * pProc);
	
	HRESULT ClearSource();
	//初始化视频录像graph
	HRESULT InitCapture(LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName );
	//销毁视频录像graph
	HRESULT TerminateCapture();
	//录像
	HRESULT StartCapture();
	//停止录像
	HRESULT StopCapture();
	//增加媒体文件源
    HRESULT AddMediaFileSource(LPCWSTR Path, DWORD_PTR& dwID, LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	//增加采集设备源
	HRESULT AddCaptureDeviceSource(UINT DeviceId, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace = 0,LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	HRESULT AddCaptureDeviceSource(LPCWSTR Devicename, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace = 0,LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	HRESULT AddCaptureDeviceSource(LPCWSTR Devicename,int index, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace = 0,LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	//增加位图数据源
	HRESULT AddImageDIBSource(LPCVOID pSrcMemory,D3DFORMAT imgtp,long bmWidthBytes,LPRECT rcSrc,DWORD ColorKey,DWORD_PTR& dwID ,LPRECT rcDest = 0);
	HRESULT AddImageDIBSource(UINT id,D3DFORMAT imgtp,LPRECT rcSrc,DWORD ColorKey,DWORD_PTR& dwID ,LPRECT rcDest = 0);
    //删除源
	HRESULT DeleteSource( DWORD_PTR dwID );
	//得到源数目
    HRESULT  GetSourceNum(int * num);
	//得到显示窗口
    HRESULT     GetWindow(HWND *hWnd);
	//设置刷新帧率(显示窗口的帧率,并非源的帧率)
    HRESULT SetFrameRate( int nFPS);
	//得到平均刷新率
	HRESULT GetFrameRateAvg(int *nFPS );
	//得到刷新帧率(显示窗口的帧率,并非源的帧率)
	HRESULT  GetFrameRate(int *nFPS);
	//设置背景颜色
    HRESULT SetBkColor( COLORREF color );
	//设置背景颜色
    HRESULT GetBkColor( COLORREF *color );
	//查看所有源,如果已停止,重新启动该源
    HRESULT LoopSources();
	//逐帧回调函数
	HRESULT SourceSetTransformProc(DWORD_PTR dwID,TransformProc pProc,TransformProc* pOldProc);

	HRESULT SourceGetTransformProc(DWORD_PTR dwID,TransformProc * pProc);

	//得到当前现实数据
	HRESULT SourceGetData(DWORD_PTR dwID,CSurfaceBuff** ppBuff);
	//运行
	HRESULT SourceRun( DWORD_PTR dwID);
	//
	HRESULT  SourceStopWhenReady(DWORD_PTR dwID);
	//停止
	HRESULT SourceStop( DWORD_PTR dwID);
	//停止在指定时间(单位由SetTimeFormat()决定,默认为1/10,000,000秒)
	HRESULT SourceStopAt( DWORD_PTR dwID,LONGLONG llDur);
	//指定时间格式
	HRESULT SourceSetTimeFormat( DWORD_PTR dwID,const GUID *pFormat);
	HRESULT SourceGetTimeFormat( DWORD_PTR dwID, GUID *pFormat);
	//得到当前时间(单位由SetTimeFormat()决定,默认为1/10,000,000秒)
	HRESULT SourceGetTimes( DWORD_PTR dwID,LONGLONG &llCur,LONGLONG &llDur);
	//得到视频长度(单位由SetTimeFormat()决定,默认为1/10,000,000秒)
	HRESULT SourceGetVideoLen( DWORD_PTR dwID,LONGLONG &llLen);
	
	//暂停,只有为媒体文件源时可用
	HRESULT SourcePause( DWORD_PTR dwID);
	//跳到指定时间(单位由SetTimeFormat()决定,默认为1/10,000,000秒),只有为媒体文件源时可用
	HRESULT SourceSeekto(DWORD_PTR dwID,LONGLONG llCur);
	//显示/不显示指定源
	HRESULT SourceShow( DWORD_PTR dwID ,BOOL bVisible);
	//得到在当前窗口中,输出纵横比不变时,最大的输出
	HRESULT SourceGetIdealOutputRect( DWORD_PTR dwID ,LPRECT lprc);
	//得到视频输出实际大小
	HRESULT SourceGetVideoSize( DWORD_PTR dwID ,long *width,long *height);
	//移动源到指定位置(x,y,z)
	HRESULT SourceSetPos( DWORD_PTR dwID ,int x,int y,int cx,int cy,int z);
	//移动源到指定位置
	HRESULT SourceSetPos( DWORD_PTR dwID ,LPRECT lprc,int z);
	//得到源位置
	HRESULT SourceGetPos( DWORD_PTR dwID ,LPRECT lprc,int* z);
	//设置源透明度
	HRESULT SourceSetAlphaValue( DWORD_PTR dwID ,BYTE	AlphaValue);
	//得到源透明度
	HRESULT SourceGetAlphaValue( DWORD_PTR dwID ,BYTE	*AlphaValue);
	//增加采集设备
	HRESULT SourceInitCapture(DWORD_PTR dwID,LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName );

	//删除采集设备
	HRESULT SourceTerminateCapture(DWORD_PTR dwID);
	//录像
	HRESULT SourceStartCapture(DWORD_PTR dwID );
	//停止录像
	HRESULT SourceStopCapture(DWORD_PTR dwID );
	HRESULT UpdateImmediatly();
	//枚举所有支持的视频制式
	//HRESULT EnumVideoFormat(DWORD_PTR dwID );


    // private methods
protected:
	CVMR9Subgraph*   GetSubgraph(  DWORD_PTR dwID  );
    IMultiVMR9Wizard* GetWizard( );
    IMultiVMR9RenderEngine* GetRenderEngine();
    IMultiVMR9MixerControl* GetMixerControl();
    IMultiVMR9UILayer* GetUILayer();


    // private data 
protected:
    list<CVMR9Subgraph*>        m_sources;
    IMultiVMR9Wizard*           m_pWizard;
    IMultiVMR9RenderEngine*     m_pRenderEngine;
    IMultiVMR9MixerControl*     m_pMixerControl;
    IMultiVMR9UILayer*          m_pUILayer;
	IFilterGraph*   m_pCapGraph;		// filter graph
	IMediaControl*  m_pCapMc;			// media control
    HWND                        m_hwndVideo;
};


