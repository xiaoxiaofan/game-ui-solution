#pragma once


// WndVedio �Ի���

class WndVedio : public CDialog
{
	DECLARE_DYNAMIC(WndVedio)

public:
	WndVedio(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WndVedio();

// �Ի�������
	enum { IDD = IDD_Vedio };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedCatch();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	HWND  GetWndHwnd();
public:
	HCURSOR    m_MoveCursor;   //�ƶ����
	HWND       m_CurHwnd;      //������Ż�ȡ�Ŀؼ��ľ��
	HWND       m_PreHwnd;      //���������ǰ��ȡ�Ŀؼ��ľ��
	BOOL       m_LeftIsDown;   //TRUE��ʾ����������
	HINSTANCE  m_hDLL;
	HWND       m_GetCurHwnd;  
	
};
