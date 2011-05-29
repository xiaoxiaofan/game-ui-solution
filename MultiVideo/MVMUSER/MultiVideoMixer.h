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
	//��ʼ��
	HRESULT Initialize(HWND hwnd,UINT Width, UINT Height,D3DFORMAT format,BOOL bBufferInSystemMem);
	HRESULT InitializeEx(HWND hwnd,HWND hwndCpy,UINT Width, UINT Height,D3DFORMAT FinalFormat,BOOL bBufferInSystemMem);
	//����
    HRESULT Terminate();
	//
	HRESULT Get3DDevice(IDirect3DDevice9 ** pDevice);
	void Release();
	//�õ���ǰ��ʾ���ݣ�ȫ�֣�
	HRESULT GetData(CSurfaceBuff** ppBuff);
	//ȫ����֡�ص�����
	HRESULT SetTransformProc(TransformProc   pProc,TransformProc* pOldProc);
	HRESULT GetTransformProc(TransformProc * pProc);
	
	HRESULT ClearSource();
	//��ʼ����Ƶ¼��graph
	HRESULT InitCapture(LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName );
	//������Ƶ¼��graph
	HRESULT TerminateCapture();
	//¼��
	HRESULT StartCapture();
	//ֹͣ¼��
	HRESULT StopCapture();
	//����ý���ļ�Դ
    HRESULT AddMediaFileSource(LPCWSTR Path, DWORD_PTR& dwID, LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	//���Ӳɼ��豸Դ
	HRESULT AddCaptureDeviceSource(UINT DeviceId, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace = 0,LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	HRESULT AddCaptureDeviceSource(LPCWSTR Devicename, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace = 0,LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	HRESULT AddCaptureDeviceSource(LPCWSTR Devicename,int index, GUID VidType ,UINT Width,UINT Height,int nFPS, DWORD_PTR& dwID,BOOL bUsingColorSpace = 0,LPRECT rcDest = 0,SourceConnectProc ConnectProc = 0);
	//����λͼ����Դ
	HRESULT AddImageDIBSource(LPCVOID pSrcMemory,D3DFORMAT imgtp,long bmWidthBytes,LPRECT rcSrc,DWORD ColorKey,DWORD_PTR& dwID ,LPRECT rcDest = 0);
	HRESULT AddImageDIBSource(UINT id,D3DFORMAT imgtp,LPRECT rcSrc,DWORD ColorKey,DWORD_PTR& dwID ,LPRECT rcDest = 0);
    //ɾ��Դ
	HRESULT DeleteSource( DWORD_PTR dwID );
	//�õ�Դ��Ŀ
    HRESULT  GetSourceNum(int * num);
	//�õ���ʾ����
    HRESULT     GetWindow(HWND *hWnd);
	//����ˢ��֡��(��ʾ���ڵ�֡��,����Դ��֡��)
    HRESULT SetFrameRate( int nFPS);
	//�õ�ƽ��ˢ����
	HRESULT GetFrameRateAvg(int *nFPS );
	//�õ�ˢ��֡��(��ʾ���ڵ�֡��,����Դ��֡��)
	HRESULT  GetFrameRate(int *nFPS);
	//���ñ�����ɫ
    HRESULT SetBkColor( COLORREF color );
	//���ñ�����ɫ
    HRESULT GetBkColor( COLORREF *color );
	//�鿴����Դ,�����ֹͣ,����������Դ
    HRESULT LoopSources();
	//��֡�ص�����
	HRESULT SourceSetTransformProc(DWORD_PTR dwID,TransformProc pProc,TransformProc* pOldProc);

	HRESULT SourceGetTransformProc(DWORD_PTR dwID,TransformProc * pProc);

	//�õ���ǰ��ʵ����
	HRESULT SourceGetData(DWORD_PTR dwID,CSurfaceBuff** ppBuff);
	//����
	HRESULT SourceRun( DWORD_PTR dwID);
	//
	HRESULT  SourceStopWhenReady(DWORD_PTR dwID);
	//ֹͣ
	HRESULT SourceStop( DWORD_PTR dwID);
	//ֹͣ��ָ��ʱ��(��λ��SetTimeFormat()����,Ĭ��Ϊ1/10,000,000��)
	HRESULT SourceStopAt( DWORD_PTR dwID,LONGLONG llDur);
	//ָ��ʱ���ʽ
	HRESULT SourceSetTimeFormat( DWORD_PTR dwID,const GUID *pFormat);
	HRESULT SourceGetTimeFormat( DWORD_PTR dwID, GUID *pFormat);
	//�õ���ǰʱ��(��λ��SetTimeFormat()����,Ĭ��Ϊ1/10,000,000��)
	HRESULT SourceGetTimes( DWORD_PTR dwID,LONGLONG &llCur,LONGLONG &llDur);
	//�õ���Ƶ����(��λ��SetTimeFormat()����,Ĭ��Ϊ1/10,000,000��)
	HRESULT SourceGetVideoLen( DWORD_PTR dwID,LONGLONG &llLen);
	
	//��ͣ,ֻ��Ϊý���ļ�Դʱ����
	HRESULT SourcePause( DWORD_PTR dwID);
	//����ָ��ʱ��(��λ��SetTimeFormat()����,Ĭ��Ϊ1/10,000,000��),ֻ��Ϊý���ļ�Դʱ����
	HRESULT SourceSeekto(DWORD_PTR dwID,LONGLONG llCur);
	//��ʾ/����ʾָ��Դ
	HRESULT SourceShow( DWORD_PTR dwID ,BOOL bVisible);
	//�õ��ڵ�ǰ������,����ݺ�Ȳ���ʱ,�������
	HRESULT SourceGetIdealOutputRect( DWORD_PTR dwID ,LPRECT lprc);
	//�õ���Ƶ���ʵ�ʴ�С
	HRESULT SourceGetVideoSize( DWORD_PTR dwID ,long *width,long *height);
	//�ƶ�Դ��ָ��λ��(x,y,z)
	HRESULT SourceSetPos( DWORD_PTR dwID ,int x,int y,int cx,int cy,int z);
	//�ƶ�Դ��ָ��λ��
	HRESULT SourceSetPos( DWORD_PTR dwID ,LPRECT lprc,int z);
	//�õ�Դλ��
	HRESULT SourceGetPos( DWORD_PTR dwID ,LPRECT lprc,int* z);
	//����Դ͸����
	HRESULT SourceSetAlphaValue( DWORD_PTR dwID ,BYTE	AlphaValue);
	//�õ�Դ͸����
	HRESULT SourceGetAlphaValue( DWORD_PTR dwID ,BYTE	*AlphaValue);
	//���Ӳɼ��豸
	HRESULT SourceInitCapture(DWORD_PTR dwID,LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName );

	//ɾ���ɼ��豸
	HRESULT SourceTerminateCapture(DWORD_PTR dwID);
	//¼��
	HRESULT SourceStartCapture(DWORD_PTR dwID );
	//ֹͣ¼��
	HRESULT SourceStopCapture(DWORD_PTR dwID );
	HRESULT UpdateImmediatly();
	//ö������֧�ֵ���Ƶ��ʽ
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


