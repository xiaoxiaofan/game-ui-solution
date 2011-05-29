// MultiSrcPlayerDlg.h : 头文件
//

#pragma once

#include "afxwin.h"
#include "afxcmn.h"
class CMVMixer;
// CMultiSrcPlayerDlg 对话框
class CMultiSrcPlayerDlg : public CDialog
{
// 构造
public:
	CMVMixer *m_pMixer;
	CMultiSrcPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MULTISRCPLAYER_DIALOG };
	CCritSec m_ObjectLock;
	BITMAPINFO  bminfo ;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	vector<wstring >_DeviceList;
	int _iDeviceNum;
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
	CListBox m_DeviceList;
	afx_msg void OnLbnSelchangeList1();
	//HRESULT MyTransformProc (LPVOID pBits,int Pitch,int width,int height,D3DFORMAT format);
	int ui_alpha;
	int ui_pos_x;
	int ui_pos_y;
	int ui_pos_z;
	int ui_size_w;
	int ui_size_h;
	void UpdateDataVidWnd();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnBnClickedButton4();
	long ui_rW;
	long ui_rH;
	LONGLONG m_llStopAt;
	LONGLONG m_llSeekTo;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnEnChangeEdit10();
	afx_msg void OnEnChangeEdit9();
	int m_iVideoLen;
	afx_msg void OnBnClickedButton10();
	int m_iTransformW;
	int m_iTransformH;
	int m_iTransformP;
	int m_iTransformF;
	CDC _dc;
	afx_msg void OnTimer(UINT nIDEvent);
	
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	CSliderCtrl m_SeekSlider;
//	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMReleasedcaptureSlider2(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_AlphaSlider;
};
