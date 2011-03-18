/****************************************\
*										*
* 			   ��Ϸ���̻���				*
*										*
\****************************************/

#pragma once


class CGameProcedure 
{
public:	     /// ��ʼ����̬����
	static VOID		InitStaticMemeber(VOID);
	///	��һ����Ϸѭ������
	static VOID		SetActiveProc(CGameProcedure* pToActive);
	///�����ڴ�С�����ı�����
	static VOID		HandlePossibleSizeChange(UINT message, WPARAM wParam, LPARAM lParam);

public:

protected:
	virtual VOID	Init(VOID) = 0;
	virtual VOID	Tick(VOID);
	virtual VOID	Render(VOID) = 0;
	virtual VOID	Release(VOID) = 0;
	virtual VOID	ProcessInput(VOID);
	virtual VOID	CloseRequest(VOID);
	virtual LRESULT	MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	///����������
	static VOID		CreateMainWnd(VOID);
	///�ͷ�������
	static VOID		DestroyMainWnd(VOID);
	///��������Ϣ������
	static LRESULT CALLBACK	_MainWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	///�����ڱ��������ı�ʱ
	/* dwChanging-
	|		WMSZ_LEFT/WMSZ_RIGHT
	|		WMSZ_TOP/WMSZ_BOTTOM
	| dwAnchor-
	|		WMSZ_TOPLEFT    
	|		WMSZ_TOPRIGHT   
	|		WMSZ_BOTTOM     
	|		WMSZ_BOTTOMLEFT 
	|		WMSZ_BOTTOMRIGHT
	*/
	static VOID		KeepWindowFOV(RECT* pRect, UINT dwChanging, UINT dwAnchor);




protected:
	//-------------------------------------------
	//�ڲ����Ʊ���

	//������С��
	static BOOL			m_bMinimized;
	//�������
	static BOOL			m_bMaximized;
	//����ȫ����
	static BOOL			m_bFullScreen;
	//����λ��
	static RECT			m_rectWindow;
	//���ڱ���(3:4=0.75)
	static FLOAT		m_fWindowFOV;
	//Frame<->Client�Ĳ�ֵ
	static RECT			m_rectFCOffset;
	//���ڴ��ڽ���״̬
	static BOOL			m_bActive;
	//��Ⱦ��ͣ
	static BOOL			m_bRenderingPaused;
	//ui�������״̬
	static BOOL			m_bUIHandleInput;

	//���ٿ���
	static FLOAT		m_fFPS;


};