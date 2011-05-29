// MultiSrcPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultiSrcPlayer.h"
#include "MultiSrcPlayerDlg.h"
#include ".\multisrcplayerdlg.h"

#include "SelCapDevies.h"

#include "MVMUSER.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//extern HINSTANCE g_hInstance;
// CMultiSrcPlayerDlg 对话框
CMultiSrcPlayerDlg *pThis = 0;
DWORD_PTR G_pdwID =0 ;
LONGLONG G_FRAMES = 0;
DWORD G_TIME = 0;

DWORD_PTR GG_pdwID =0 ;
LONGLONG GG_FRAMES = 0;
DWORD GG_TIME = 0;
CString g_szPath;
//SourceConnectProc
HRESULT ConnectDVProc(DWORD_PTR pdwID,IFilterGraph*   pGraph	,IBaseFilter* pSrcFilter,IBaseFilter * pRender)
{
	HRESULT hr = S_OK;
	IGraphBuilder			*	pGb= NULL;
	ICaptureGraphBuilder2	*	pBuild = NULL;
	IBaseFilter				*	pSmartTee = 0;
	IPin					*	pTeeOutPin = 0;
	IBaseFilter				*	pAviMux = NULL;
	IBaseFilter				*	pFileWriter = NULL;
	IFileSinkFilter			*	pSink= NULL;
	IBaseFilter				*	pAudFt = NULL;
	IConfigAviMux			*	pConfigMux = 0;
	try{
		hr = pGraph->QueryInterface( IID_IGraphBuilder, (void**)&(pGb) );
		if( FAILED(hr))throw hr;if(!pGb)throw  E_OUTOFMEMORY;
		hr = CoCreateInstance(CLSID_CaptureGraphBuilder2, NULL, CLSCTX_INPROC, IID_ICaptureGraphBuilder2, (void **)&pBuild);
		if( FAILED(hr))throw hr;if(!pBuild)throw  E_OUTOFMEMORY;
		hr =pBuild->SetFiltergraph(pGb);
		if( FAILED(hr))throw hr;

		hr = CoCreateInstance(CLSID_SmartTee, 0, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (void **)&pSmartTee);
		if( FAILED(hr))throw hr;if(!pSmartTee)throw  E_OUTOFMEMORY;
		hr = pGraph->AddFilter(pSmartTee, L"Tee");
		if( FAILED(hr))throw hr;

		hr = pBuild->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Interleaved,pSrcFilter,0,pSmartTee);
		if( FAILED(hr))
			hr = pBuild->RenderStream(&PIN_CATEGORY_CAPTURE, &MEDIATYPE_Video,pSrcFilter,0,pSmartTee);
		if (FAILED(hr ))throw hr;

		//采集

		//avi mux
		hr = CoCreateInstance(CLSID_AviDest, 0, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (void **)&pAviMux);
		if( FAILED(hr))throw hr;if(!pAviMux)throw  E_OUTOFMEMORY;
		hr = pGraph->AddFilter(pAviMux, L"Avi Mux");
		if( FAILED(hr))throw hr;

		//File writer
		hr = CoCreateInstance(CLSID_FileWriter, 0, CLSCTX_INPROC_SERVER,IID_IBaseFilter, (void **)&pFileWriter);
		if( FAILED(hr))throw hr;if(!pFileWriter)throw  E_OUTOFMEMORY;
		hr = pGraph->AddFilter(pFileWriter, L"File writer");
		if( FAILED(hr))throw hr;
		hr = pFileWriter->QueryInterface(IID_IFileSinkFilter,(void**)&pSink);
		if( FAILED(hr))throw hr;
		pSink->SetFileName(CT2W(g_szPath),0); 
		RELEASE(pTeeOutPin);
		hr = pBuild->FindPin(pSmartTee, PINDIR_OUTPUT, 0, 0, TRUE, 0, &pTeeOutPin);
		if( FAILED(hr))throw hr;if(!pTeeOutPin)throw  E_OUTOFMEMORY;
	
		hr = pBuild->RenderStream(0, 0,pTeeOutPin,pAviMux,pFileWriter);
		if( FAILED(hr))throw hr;

		//音频采集
		CMediaHelper Helper;
		hr = Helper.GetAudCapDevice(0,&pAudFt);
		if( FAILED(hr) || !pAudFt) throw hr;
		hr = pGraph->AddFilter(pAudFt,L"AudFt");
		
		if( FAILED(hr) ) throw hr;
		if(pAudFt){
			pBuild->RenderStream(0,0,pAudFt,0,pAviMux);
			if( FAILED(hr) ) throw hr;
			hr = pAviMux->QueryInterface(IID_IConfigAviMux, (void**)&pConfigMux);
			if( SUCCEEDED(hr)) {
				pConfigMux->SetMasterStream(1);
			}
		}



		hr = pBuild->FindPin(pSmartTee, PINDIR_OUTPUT, 0, 0, TRUE, 0, &pTeeOutPin);
		if( FAILED(hr))throw hr;if(!pTeeOutPin)throw  E_OUTOFMEMORY;
		hr = pBuild->RenderStream(0, 0,pTeeOutPin,0,pRender);
			if( FAILED(hr))throw hr;

		

		
		



	}catch(HRESULT hr1)
	{
		hr = hr1;

	}
	RELEASE(pGb);
	RELEASE(pGb);
	RELEASE(pBuild);
	RELEASE(pSmartTee);
	RELEASE(pTeeOutPin);
	RELEASE(pAviMux);
	RELEASE(pFileWriter); 
	RELEASE(pSink);
	RELEASE(pAudFt);
	RELEASE(pConfigMux);

	return hr;
}
//回调测试
HRESULT MyTransformProc(DWORD_PTR pdwID,IDirect3DSurface9*  pTexturePrivSurf,REFERENCE_TIME  rtStart, REFERENCE_TIME  rtEnd)
{
	
	CAutoLock Look(&pThis->m_ObjectLock);
	if(pdwID == 0)
	{
		GG_FRAMES++;
		HRESULT				hr = S_OK; 
		//if(GG_FRAMES>20) return S_OK;
		if(GG_TIME ==0)  GG_TIME = GetTickCount();
		
		CSurfaceBuff buff(pTexturePrivSurf,1);

			//****************************处理数据****************************************//
		
		CDC *pDC = pThis->GetDlgItem(IDC_G_transform)->GetDC();
		RECT rc;
		pThis->GetDlgItem(IDC_G_transform)->GetWindowRect(&rc);	
	
		pThis->bminfo.bmiHeader.biBitCount = buff.Pitch()/buff.Width() * 8;
		pThis->bminfo.bmiHeader.biWidth = buff.Width();
		pThis->bminfo.bmiHeader.biHeight = -buff.Height();
		pThis->bminfo.bmiHeader.biSizeImage = buff.Pitch()*buff.Height();
		pDC->SetStretchBltMode(COLORONCOLOR);
		SetDIBitsToDevice(pThis->_dc.GetSafeHdc(),0,0,buff.Width(),buff.Height(),0,0,0,buff.Height(),buff.Bits(),&pThis->bminfo,DIB_RGB_COLORS);
		pDC->StretchBlt(0,0,rc.right - rc.left ,rc.bottom  - rc.top ,&pThis->_dc,0,0,buff.Width(),buff.Height(),SRCCOPY);

		pThis->ReleaseDC(pDC);
		
		//****************************结束处理****************************************//
		
		buff.Release();

		return S_OK;

	}
	if(G_pdwID == pdwID)
	{
		G_FRAMES ++;
		HRESULT				hr; 
		CSurfaceBuff buff(pTexturePrivSurf,1);
		CDC *pDC = pThis->GetDlgItem(IDC_Transform)->GetDC();
					
			//****************************处理数据****************************************//
			RECT rc;
			pThis->GetDlgItem(IDC_Transform)->GetWindowRect(&rc);
			
			pThis->bminfo.bmiHeader.biBitCount = buff.Pitch()/buff.Width() * 8;
			pThis->bminfo.bmiHeader.biWidth = buff.Width();
			pThis->bminfo.bmiHeader.biHeight = buff.Height();
			pThis->bminfo.bmiHeader.biSizeImage = buff.Pitch()*buff.Height();
			pDC->SetStretchBltMode(COLORONCOLOR);
			SetDIBitsToDevice(pThis->_dc.GetSafeHdc(),0,0,buff.Width(),buff.Height(),0,0,0,buff.Height(),buff.Bits(),&pThis->bminfo,DIB_RGB_COLORS);
			pDC->StretchBlt(0,0,rc.right - rc.left ,rc.bottom  - rc.top ,&pThis->_dc,0,buff.Height(),buff.Width(),-buff.Height(),SRCCOPY);
			
			
			//****************************结束处理****************************************//

		pThis->ReleaseDC(pDC);
	

	}
	return S_OK;
}
CMultiSrcPlayerDlg::CMultiSrcPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiSrcPlayerDlg::IDD, pParent)
	, ui_alpha(0)
	, ui_pos_x(0)
	, ui_pos_y(0)
	, ui_pos_z(0)
	, ui_size_w(0)
	, ui_size_h(0)
	, ui_rW(0)
	, ui_rH(0)
	, m_llSeekTo(0)
	, m_llStopAt(0)
	, m_iVideoLen(0)
	, m_iTransformW(0)
	, m_iTransformH(0)
	, m_iTransformP(0)
	, m_iTransformF(0)
	, m_pMixer(0)
{
	bminfo.bmiHeader.biCompression = BI_RGB;
	bminfo.bmiHeader.biPlanes =1;
	bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);;
	bminfo.bmiHeader.biWidth = 0;
	bminfo.bmiHeader.biHeight = 0;
	bminfo.bmiHeader.biBitCount = 32;
	bminfo.bmiHeader.biSizeImage = 0;
	bminfo.bmiHeader.biClrImportant = 0;
	bminfo.bmiHeader.biClrUsed = 0;
	bminfo.bmiHeader.biXPelsPerMeter = 0;
	bminfo.bmiHeader.biYPelsPerMeter = 0;
	pThis = this;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiSrcPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_DeviceList);
	DDX_Text(pDX, IDC_EDIT1, ui_alpha);
	DDX_Text(pDX, IDC_EDIT2, ui_pos_x);
	DDX_Text(pDX, IDC_EDIT3, ui_pos_y);
	DDX_Text(pDX, IDC_EDIT6, ui_pos_z);
	DDX_Text(pDX, IDC_EDIT4, ui_size_w);
	DDX_Text(pDX, IDC_EDIT5, ui_size_h);
	DDX_Text(pDX, IDC_EDIT7, ui_rW);
	DDX_Text(pDX, IDC_EDIT8, ui_rH);
	DDX_Text(pDX, IDC_EDIT9, m_llStopAt);
	DDX_Text(pDX, IDC_EDIT10, m_llSeekTo);
	DDX_Text(pDX, IDC_EDIT11, m_iVideoLen);
	DDX_Text(pDX, IDC_EDIT12, m_iTransformW);
	DDX_Text(pDX, IDC_EDIT13, m_iTransformH);
	DDX_Text(pDX, IDC_EDIT15, m_iTransformP);
	DDX_Text(pDX, IDC_EDIT14, m_iTransformF);
	DDX_Control(pDX, IDC_SLIDER1, m_SeekSlider);
	DDX_Control(pDX, IDC_SLIDER2, m_AlphaSlider);
}

BEGIN_MESSAGE_MAP(CMultiSrcPlayerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_LBN_SELCHANGE(IDC_LIST1, OnLbnSelchangeList1)
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT6, OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT4, OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, OnEnChangeEdit5)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, OnBnClickedButton8)
	ON_EN_CHANGE(IDC_EDIT10, OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT9, OnEnChangeEdit9)
	ON_BN_CLICKED(IDC_BUTTON10, OnBnClickedButton10)
	ON_WM_TIMER()

	ON_BN_CLICKED(IDC_BUTTON11, OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, OnBnClickedButton12)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnNMCustomdrawSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER1, OnNMReleasedcaptureSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER2, OnNMReleasedcaptureSlider2)
END_MESSAGE_MAP()


// CMultiSrcPlayerDlg 消息处理程序

BOOL CMultiSrcPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// TODO: 在此添加额外的初始化代码
	RECT rc;
	GetDlgItem(IDC_VIDWND)->GetWindowRect(&rc);
	HRESULT hr = CreateMVMixer(&m_pMixer,GetDlgItem(IDC_VIDWND)->GetSafeHwnd(),rc.right - rc.left ,rc.bottom - rc.top,D3DFMT_X8R8G8B8,0);
	if(!m_pMixer) {
		MessageBox("err...!");exit(0);
	}

	CMediaHelper help;
	help.EnumVidCapDevice(&_DeviceList,0);
	m_AlphaSlider.SetRange(0,255);
	//help.EnumCapFormat(0,0,0,0,0);
	m_pMixer->SetFrameRate(2500);
	CBitmap bm;
	bm.CreateBitmap(1024,768,1,32,0);
	CDC *pDC =GetDC();
	_dc.CreateCompatibleDC(pDC);
	_dc.SelectObject(&bm);
	ReleaseDC(pDC);
	bm.DeleteObject();
	SetTimer(0,1000,0);
	//m_pMixer->SetTransformProc(MyTransformProc,0);
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMultiSrcPlayerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CMultiSrcPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMultiSrcPlayerDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

void CMultiSrcPlayerDlg::OnDestroy()
{
	CDialog::OnDestroy();
	CMediaHelper help;
	help.ClearVector(&_DeviceList);

	m_pMixer->Release();
	// TODO: Add your message handler code here
}

void CMultiSrcPlayerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CMultiSrcPlayerDlg::OnBnClickedButton1()
{
	
	HRESULT hr;
	DWORD_PTR dw;
	RECT src ;
	RECT drc ;
	CBitmap Cbm ;
	BITMAP bm;
	Cbm.LoadBitmap(IDB_BITMAP1);
	Cbm.GetBitmap(&bm);
	DWORD size = bm.bmWidthBytes * bm.bmHeight *bm.bmBitsPixel/8;
	BYTE *pBuff = new BYTE[size];
	src.left = 0;src.top = 0;src.right = bm.bmWidth;src.bottom = bm.bmHeight;
	Cbm.GetBitmapBits(size,pBuff);
	hr = m_pMixer->AddImageDIBSource(pBuff ,D3DFMT_A8R8G8B8,bm.bmWidthBytes,&src,0xFFFFFFFF,dw);

	delete []pBuff;
	if( FAILED(hr))
    {
        AfxMessageBox(_T("Failed to create MultiVMR9Wizard object.\r\nMake sure you have registered MultiVMR9.dll"),MB_OK,0);
        return ;
    }
		RECT rc = {0,0,0,0};
		m_pMixer->SourceGetIdealOutputRect(dw,&rc);
		m_pMixer->SourceSetPos(dw,&rc,0);

	int item = m_DeviceList.AddString("DIB");
	m_DeviceList.SetItemData(item,dw);
	m_pMixer->SourceRun(dw);

	//m_pMixer->SourceSetTransformProc(dw,MyTransformProc,0);
}

void CMultiSrcPlayerDlg::OnBnClickedButton2()
{
	CSelCapDevies dlg(&_DeviceList,_DeviceList.size());
	if(dlg.DoModal() != IDOK)return;
	if(dlg.m_iSel <0)return;
	HRESULT hr;
	DWORD_PTR dw;
	hr = m_pMixer->AddCaptureDeviceSource(dlg.m_iSel,MEDIASUBTYPE_RGB555,720,576,25,dw,0);
	if( FAILED(hr))
    {
        AfxMessageBox(_T("Failed to create MultiVMR9Wizard object.\r\nMake sure you have registered MultiVMR9.dll"),MB_OK,0);
        return ;
    }
	RECT rc = {0,0,0,0};
	m_pMixer->SourceGetIdealOutputRect(dw,&rc);
	m_pMixer->SourceSetPos(dw,&rc,0);
	int size =  _DeviceList[dlg.m_iSel].size();
	wchar_t *pstr = new wchar_t[size+1];

	_DeviceList[dlg.m_iSel].copy(pstr,size);
	pstr[size]=L'\0';
	int item = m_DeviceList.AddString(CW2A(pstr));
	delete []pstr;
	m_DeviceList.SetItemData(item,dw);
	m_pMixer->SourceRun(dw);
	
	//m_pMixer->SourceSetTransformProc(dw,MyTransformProc,0);
}

void CMultiSrcPlayerDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CMultiSrcPlayerDlg::OnBnClickedButton3()
{
	 CFileDialog file(TRUE, NULL, NULL,OFN_FILEMUSTEXIST,
        _T("Media Files (*.asf;*.avi;*.mpg;*.mpeg;*.wmv)|*.asf;*.avi;*.mpg;*.mpeg;*.wmv|All Files (*.*)|*.*\0\0"),
        NULL);
    if( IDOK == file.DoModal())
	{
		HRESULT hr;
		DWORD_PTR dw;
		CString str = file.GetPathName();
		RECT rc = {0,0,0,0};
		hr = m_pMixer->AddMediaFileSource(CA2W(str),dw );
		m_pMixer->SourceGetIdealOutputRect(dw,&rc);
		m_pMixer->SourceSetPos(dw,&rc,0);
		if( FAILED(hr))
		{
			AfxMessageBox(_T("Failed to create MultiVMR9Wizard object.\r\nMake sure you have registered MultiVMR9.dll"),MB_OK,0);
			return ;
		}
		int item = m_DeviceList.AddString(str);
		m_DeviceList.SetItemData(item,dw);
		m_pMixer->SourceRun(dw);
		//if(!G_pdwID)
		//m_pMixer->SourceSetTransformProc(dw,MyTransformProc,0);
	}
	
}
void CMultiSrcPlayerDlg::UpdateDataVidWnd()
{
	UpdateData(1);
	int sel = m_DeviceList.GetCurSel();
	if(sel<0) return;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_pMixer->SourceSetPos(dw,ui_pos_x,ui_pos_y,ui_size_w,ui_size_h,ui_pos_z);
	m_pMixer->SourceSetAlphaValue(dw,ui_alpha);
	
}
void CMultiSrcPlayerDlg::OnLbnSelchangeList1()
{
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	G_FRAMES = 0;
	G_TIME = GetTickCount();
	G_pdwID = dw;
	
	m_pMixer->SourceGetPos(dw,&rc,&z);
	ui_pos_x = rc.left;
	ui_pos_y = rc.top  ;
	ui_pos_z = z;
	ui_size_h = rc.bottom - rc.top;
	ui_size_w = rc.right - rc.left;
	m_pMixer->SourceGetVideoSize(dw,&ui_rW,&ui_rH);
	BYTE alpha = 0;
	m_pMixer->SourceGetAlphaValue(dw,&alpha);
	ui_alpha = alpha;
	LONGLONG llCur,llDur;
	m_pMixer->SourceGetTimes(dw,llCur,llDur),
	m_llSeekTo = llCur/400000L;
	m_llStopAt = llDur/400000L;
	m_pMixer->SourceGetTimes(dw,llCur,llDur),
	m_pMixer->SourceGetVideoLen(dw,llDur),
	m_iVideoLen = llDur/400000L;
	
	m_AlphaSlider.SetPos(ui_alpha);
	m_SeekSlider.SetRange(0,m_iVideoLen,1);
	m_SeekSlider.SetPos(m_llSeekTo);
	//m_SeekSlider.SetPos(m_llSeekTo);
	UpdateData(0);
}

void CMultiSrcPlayerDlg::OnEnChangeEdit1()
{
	UpdateDataVidWnd();
}

void CMultiSrcPlayerDlg::OnEnChangeEdit2()
{
	UpdateDataVidWnd();
}

void CMultiSrcPlayerDlg::OnEnChangeEdit3()
{
UpdateDataVidWnd();}

void CMultiSrcPlayerDlg::OnEnChangeEdit6()
{
UpdateDataVidWnd();}

void CMultiSrcPlayerDlg::OnEnChangeEdit4()
{
UpdateDataVidWnd();}

void CMultiSrcPlayerDlg::OnEnChangeEdit5()
{
UpdateDataVidWnd();}

void CMultiSrcPlayerDlg::OnBnClickedButton4()
{
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_pMixer->DeleteSource(dw);
	m_DeviceList.DeleteString(sel);

}

void CMultiSrcPlayerDlg::OnBnClickedButton5()
{
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_pMixer->SourceRun(dw);
}

void CMultiSrcPlayerDlg::OnBnClickedButton6()
{
int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_pMixer->SourcePause(dw);
}

void CMultiSrcPlayerDlg::OnBnClickedButton7()
{
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_pMixer->SourceStop(dw);
}

void CMultiSrcPlayerDlg::OnBnClickedButton9()
{
int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_pMixer->SourceSeekto(dw,m_llSeekTo*400000L);
}

void CMultiSrcPlayerDlg::OnBnClickedButton8()
{
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_pMixer->SourceStopAt(dw,m_llStopAt*400000L);
}

void CMultiSrcPlayerDlg::OnEnChangeEdit10()
{
	UpdateData();
}

void CMultiSrcPlayerDlg::OnEnChangeEdit9()
{
	UpdateData();
}

void CMultiSrcPlayerDlg::OnBnClickedButton10()
{
	HRESULT hr;
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;

	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	CDC *pDC = GetDlgItem(IDC_BMP)->GetDC();

	CSurfaceBuff * pBuff = 0;
	hr = m_pMixer->SourceGetData(dw,&pBuff);
	//if(pBuff->GetFormat() == D3DFMT_X8R8G8B8 || pBuff->GetFormat() == D3DFMT_A8R8G8B8)
	//{	
		CAutoLock Look(&m_ObjectLock);
		pThis->bminfo.bmiHeader.biBitCount  = pBuff->Pitch()/pBuff->Width() *8;
		pThis->bminfo.bmiHeader.biWidth		= pBuff->Width();
		pThis->bminfo.bmiHeader.biHeight	= -pBuff->Height();
		pThis->bminfo.bmiHeader.biSizeImage = pBuff->Size();
		pDC->SetStretchBltMode(COLORONCOLOR);
		RECT rc;
		GetDlgItem(IDC_BMP)->GetWindowRect(&rc);
		SetDIBitsToDevice(pThis->_dc.GetSafeHdc(),0,0,pBuff->Width(),pBuff->Height(),0,0,0,pBuff->Height(),pBuff->Bits(),&bminfo,DIB_RGB_COLORS);
		pDC->StretchBlt(0,0,rc.right - rc.left ,rc.bottom  - rc.top ,&_dc,0,0,pBuff->Width(),pBuff->Height(),SRCCOPY);
	//}
	RELEASE(pBuff);
	ReleaseDC(pDC);
}

void CMultiSrcPlayerDlg::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	

	CString str ;
	str.Format("%d",m_iTransformW);
	GetDlgItem(IDC_EDIT12)->SetWindowText(str);
	str.Format("%d",m_iTransformH);
	GetDlgItem(IDC_EDIT13)->SetWindowText(str);
	str.Format("%d",m_iTransformF);
	GetDlgItem(IDC_EDIT14)->SetWindowText(str);
	str.Format("%d",m_iTransformP);
	GetDlgItem(IDC_EDIT15)->SetWindowText(str);

	str.Format("%d",G_FRAMES);
	GetDlgItem(IDC_EDIT16)->SetWindowText(str);
	DWORD time = GetTickCount() - G_TIME;
	if(time)
	{
		str.Format("%d",G_FRAMES*1000/time);
		GetDlgItem(IDC_EDIT17)->SetWindowText(str);
	}

	str.Format("%d",GG_FRAMES);
	GetDlgItem(IDC_EDIT22)->SetWindowText(str);
	time = GetTickCount() - GG_TIME;
	if(time)
	{
		str.Format("%d",GG_FRAMES*1000/time);
		GetDlgItem(IDC_EDIT23)->SetWindowText(str);
	}

	//int sel = m_DeviceList.GetCurSel();
	//if(sel >=0 )
	//{
	//	RECT rc;
	//	int z = 0;
	//	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	//	G_FRAMES = 0;
	//	G_TIME = GetTickCount();
	//	G_pdwID = dw;
	//	
	//	m_pMixer->SourceGetPos(dw,&rc,&z);
	//	ui_pos_x = rc.left;
	//	ui_pos_y = rc.top  ;
	//	ui_pos_z = z;
	//	ui_size_h = rc.bottom - rc.top;
	//	ui_size_w = rc.right - rc.left;
	//	m_pMixer->SourceGetVideoSize(dw,&ui_rW,&ui_rH);

	//	BYTE alpha = 0;
	//	m_pMixer->SourceGetAlphaValue(dw,&alpha);
	//	ui_alpha = alpha;
	//	LONGLONG llCur,llDur;
	//	m_pMixer->SourceGetTimes(dw,llCur,llDur),
	//	m_llSeekTo = llCur/400000L;
	//	m_llStopAt = llDur/400000L;
	//	m_pMixer->SourceGetTimes(dw,llCur,llDur),
	//	m_pMixer->SourceGetVideoLen(dw,llDur),
	//	m_iVideoLen = llDur/400000L;
	//	
	//	m_SeekSlider.SetRange(0,m_iVideoLen,1);
	//	m_SeekSlider.SetPos(m_llSeekTo);
	//	
	//	UpdateData(0);
	//}


	CDialog::OnTimer(nIDEvent);
}


void CMultiSrcPlayerDlg::OnBnClickedButton11()
{
		HRESULT hr;
		
		CDC *pDC = GetDlgItem(IDC_BMP2)->GetDC();
		D3DFORMAT format;
		CSurfaceBuff* pbuff = 0;
		hr = m_pMixer->GetData(&pbuff);
		if(FAILED(hr) || !pbuff) return ;
		
	CAutoLock Look(&m_ObjectLock);
	pThis->bminfo.bmiHeader.biBitCount  = pbuff->Pitch() /pbuff->Width()*8;
	pThis->bminfo.bmiHeader.biWidth		= pbuff->Width();
	pThis->bminfo.bmiHeader.biHeight	= -pbuff->Height();
	pThis->bminfo.bmiHeader.biSizeImage = pbuff->Size();
	pDC->SetStretchBltMode(COLORONCOLOR);
	RECT rc;
	GetDlgItem(IDC_BMP2)->GetWindowRect(&rc);
	SetDIBitsToDevice(pThis->_dc.GetSafeHdc(),0,0,pbuff->Width(),pbuff->Height(),0,0,0,pbuff->Height(),pbuff->Bits()			,&bminfo,DIB_RGB_COLORS);
	pDC->StretchBlt(0,0,rc.right - rc.left ,rc.bottom  - rc.top ,&_dc,0,0,pbuff->Width(),pbuff->Height(),SRCCOPY);

RELEASE(pbuff);

		ReleaseDC(pDC);
}

void CMultiSrcPlayerDlg::OnBnClickedButton12()
{
	static DWORD_PTR dwCaping = 0;
	int sel = m_DeviceList.GetCurSel();
	RECT rc;
	int z = 0;
	/*if(sel<0)
	{
		DWORD_PTR dw = m_DeviceList.GetItemData(sel);
		CString str;
		str.Format("e:\\%d11111.avi",dw);
		HRESULT hr = m_pMixer->InitCapture(CA2W(str),L"XviD MPEG-4 Codec",0,0);
		
		hr = m_pMixer->StartCapture();
		if(FAILED(hr))MessageBox("err!!!!!!!!!!!!!");
	}*/
	HRESULT hr = S_OK;
	static bool flag = true;
	if (flag)
	{
		
		hr = m_pMixer->InitCapture(CA2W("C:\\wuban.avi"),L"MJPEG Compressor",0,0);

		hr = m_pMixer->StartCapture();
		GetDlgItem(IDC_BUTTON12)->SetWindowText("停止录像");
		flag = false;
	}else
	{
		hr = m_pMixer->StopCapture();
		GetDlgItem(IDC_BUTTON12)->SetWindowText("开始录像");
		flag = true;
	}


	if(sel >= 0 )
	{
		
		DWORD_PTR dw = m_DeviceList.GetItemData(sel);
		HRESULT hr = S_OK;
		if(dwCaping == 0){

			CString name;
			m_DeviceList.GetText(sel,name);
			CString str;
			CFileDialog FileDialog(0,"avi",0,OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXPLORER,"avi (*.avi)|*.avi||",NULL,0);
			if(FileDialog.DoModal()==IDCANCEL) return;
			m_pMixer->DeleteSource( dw );
			g_szPath = FileDialog.GetPathName();
			hr = m_pMixer->AddCaptureDeviceSource((LPCWSTR )CT2W(name),MEDIASUBTYPE_RGB555,720,576,25,dw,0,0,ConnectDVProc);
			if(FAILED(hr))return ;
			hr = m_pMixer->SourceRun(dw);
			if(FAILED(hr))return ;
			GetDlgItem(IDC_BUTTON12)->SetWindowText("停止录像");
			m_DeviceList.SetItemData(sel,dw);
			dwCaping = dw;
		}
		else if(dw == dwCaping)
		{	
			CString name;
			m_DeviceList.GetText(sel,name);
			m_pMixer->DeleteSource( dw );
			hr = m_pMixer->AddCaptureDeviceSource((LPCWSTR )CT2W(name),MEDIASUBTYPE_RGB555,720,576,25,dw,0,0,0);
			if(FAILED(hr))return ;
			hr = m_pMixer->SourceRun(dw);
			if(FAILED(hr))return ;
			GetDlgItem(IDC_BUTTON12)->SetWindowText("开始录像");
			dwCaping = 0;
		}
	
	}
	
}

//void CMultiSrcPlayerDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//
//	//int sel = m_DeviceList.GetCurSel();
//	//if(sel<0)return;
//	//RECT rc;
//	//int z = 0;
//	//DWORD_PTR dw = m_DeviceList.GetItemData(sel);
//	//m_llSeekTo = m_SeekSlider.GetPos();
//	//m_pMixer->SourceSeekto(dw,m_llSeekTo*400000L);
//	//UpdateData(0);
//
//	
//	*pResult = 0;
//}

void CMultiSrcPlayerDlg::OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;
	RECT rc;
	int z = 0;
	DWORD_PTR dw = m_DeviceList.GetItemData(sel);
	m_llSeekTo = m_SeekSlider.GetPos();
	m_pMixer->SourceSeekto(dw,m_llSeekTo*400000L);
	UpdateData(0);

	*pResult = 0;
}

void CMultiSrcPlayerDlg::OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult)
{
	int sel = m_DeviceList.GetCurSel();
	if(sel<0)return;

	DWORD_PTR dw = m_DeviceList.GetItemData(sel);

	ui_alpha =m_AlphaSlider.GetPos(); 
	m_pMixer->SourceSetAlphaValue(dw,ui_alpha);
	UpdateData(0);
	*pResult = 0;
}
