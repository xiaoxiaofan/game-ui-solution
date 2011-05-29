//------------------------------------------------------------------------------
// File: VMR9Subgraph.h
//
// Desc: DirectShow sample code - MultiVMR9 MultiPlayer sample
//
// Copyright (c) Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------

#ifndef VMR9SUBGRAPH_HEADER
#define VMR9SUBGRAPH_HEADER

#pragma once


// This class represents a subgraph with VMR9 to be attached to the wizard
// This sample supports only media files, but any DirectShow filter graph
// with VMR9 can be used.

class CVMR9Subgraph
{
public:
	
    CVMR9Subgraph();
    ~CVMR9Subgraph();
    // public methods
	HRESULT BuildAndRender(LPCVOID pSrcMemory,UINT ImgTp,long bmWidthBytes,LPRECT rcSrc,DWORD ColorKey, IMultiVMR9Wizard* pWizard );
	HRESULT BuildAndRender(UINT id,UINT imgtp,LPRECT rcSrc,DWORD ColorKey, IMultiVMR9Wizard* pWizard );
    HRESULT BuildAndRender(LPCWSTR lpPath, IMultiVMR9Wizard* pWizard ,SourceConnectProc ConnectProc);
	HRESULT BuildAndRender(IBaseFilter* pCap, GUID VidType ,UINT Width,UINT Height,int nFPS,IMultiVMR9Wizard* pWizard ,BOOL bUsingColorSpace,SourceConnectProc ConnectProc);
	//����������ɼ�
	HRESULT AddCaptureFilter(LPCWSTR lpPath ,LPCWSTR pszVidComName,LPCWSTR lpszAudDevice ,LPCWSTR pszAudComName ,IMultiVMR9Wizard* pWizard );
	HRESULT DelCaptureFilter();
    HRESULT Run();
    HRESULT Pause();
    HRESULT Stop();
	HRESULT StartCapture();
	HRESULT StopCapture();
    HRESULT SetTime( LONGLONG llCur,LONGLONG llDur = 0);
	HRESULT StopWhenReady();
	HRESULT StopAt( LONGLONG llDur);
   // HRESULT DestroyGraph(IFilterGraph* pGraph);
 
	HRESULT CheckConnection(IBaseFilter* pFt);
	HRESULT GetVideoLen( LONGLONG &llLen);
	//HRESULT GetDIB(  long *pBufferSize,LPVOID pDIBImage);
    DWORD_PTR GetID(){ return m_dwID;};
    OAFilterState GetState();
    HRESULT GetTimes( LONGLONG & llCur, LONGLONG & llDur);
	HRESULT SetTimeFormat( const GUID *pFormat);
	HRESULT GetTimeFormat( GUID *pFormat);
	UINT m_GraphType;

private:
    // private members

private:
    // private data
	IFilterGraph*   m_pGraph;		// filter graph
   //IBaseFilter*    m_pVMR;			// VMR9
    IMediaControl*  m_pMc;			// media control
    IMediaSeeking*  m_pMs;			// media seeking
	//���ڴ������Դfilter��ʹ�ò�ͬ��IGraphBuilder����ʹ�ɼ�����ʾ�����첽���У��ɼ�������ʾ���У�
	IFilterGraph*   m_pCapGraph;		// filter graph
	IMediaControl*  m_pCapMc;			// media control
	SourceConnectProc m_ConnectProc;
	UINT m_DeviceId;//�������Ƶ�ɼ�Դ��m_DeviceId��ʾ�豸��
    DWORD_PTR m_dwID;   // actual cookie identifying the subgraph; assigned in
                        // IMultiVMR9Wizard::Attach
	
};

#endif

