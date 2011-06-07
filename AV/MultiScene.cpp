#include "StdAfx.h"
#include "MultiScene.h"
#include <math.h>
#include <yvals.h>


#define D3DFVF_CUSTOMVERTEX ( D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )



CMultiScene::CMultiScene(void)
	: m_pTexture(NULL)
	, m_pD3Device(NULL)
{
	m_vertices[0].position = CUSTOMVERTEX1::Position(-1.0f,  1.0f, 0.0f); // top left
	m_vertices[1].position = CUSTOMVERTEX1::Position(-1.0f, -1.0f, 0.0f); // bottom left
	m_vertices[2].position = CUSTOMVERTEX1::Position( 1.0f,  1.0f, 0.0f); // top right
	m_vertices[3].position = CUSTOMVERTEX1::Position( 1.0f, -1.0f, 0.0f); // bottom right

	// set up diffusion:
	m_vertices[0].color = 0xffffffff;
	m_vertices[1].color = 0xff0000ff;
	m_vertices[2].color = 0xffffffff;
	m_vertices[3].color = 0xff0000ff;

	// set up texture coordinates
	m_vertices[0].tu = 0.0f; m_vertices[0].tv = 0.0f; // low left
	m_vertices[1].tu = 0.0f; m_vertices[1].tv = 1.0f; // high left
	m_vertices[2].tu = 1.0f; m_vertices[2].tv = 0.0f; // low right
	m_vertices[3].tu = 1.0f; m_vertices[3].tv = 1.0f; // high right
	
}


CMultiScene::~CMultiScene(void)
{

}


HRESULT CMultiScene::DrawScene() 
{
	HRESULT hr = S_OK;

	if( m_vertexBuffer == NULL )
	{
		return D3DERR_INVALIDCALL;
	}
	
	m_pD3Device->SetRenderTarget(0,m_pRenderTarget);

	m_pD3Device->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
		D3DCOLOR_XRGB(0,0,0), 1.0f, 0L );

	std::list<DWORD_PTR>::iterator start,it,end;
	start = m_pVSIDs.begin();
	end = m_pVSIDs.end();
	//VideoSource* pSrc = NULL;

	for (it = start;it!=end; it++ )
	{
		//m_pMultiAllocotar->GetTexture((DWORD_PTR)*it,&m_pTexture);
		//m_pMultiAllocotar->GetVideoSourceInfo((DWORD_PTR)*it,&pSrc);

		void* pData;
		FAIL_RET( m_vertexBuffer->Lock(0,sizeof(m_vertices), &pData,0) );
		memcpy(pData,m_vertices,sizeof(m_vertices));                            
		FAIL_RET( m_vertexBuffer->Unlock());  

		FAIL_RET( m_pD3Device->BeginScene() );
		FAIL_RET( m_pD3Device->SetTexture( 0,m_pTexture));
		FAIL_RET(hr = m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE));
		FAIL_RET(hr = m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE));
		FAIL_RET(hr = m_pD3Device->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE));
		FAIL_RET(hr = m_pD3Device->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE));
		
		FAIL_RET( m_pD3Device->SetStreamSource(0, m_vertexBuffer, 0, sizeof(CUSTOMVERTEX1)));            //set next source ( NEW )
		FAIL_RET( m_pD3Device->SetFVF( D3DFVF_CUSTOMVERTEX ) );
		FAIL_RET( m_pD3Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,(LPVOID)m_vertices,sizeof(m_vertices[0])));  //draw quad 
		FAIL_RET( m_pD3Device->SetTexture( 0, NULL));
	

		/*
		m_pD3Device->SetStreamSource( 0, m_vertexBuffer, 0, sizeof(CUSTOMVERTEX) );
			m_pD3Device->SetFVF( D3DFVF_CUSTOMVERTEX );
			m_pD3Device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );*/
	
	
	
		FAIL_RET( m_pD3Device->EndScene());
	}

	
 
	m_pD3Device->Present(NULL,NULL,NULL,NULL);
	return hr;
}

HRESULT CMultiScene::CreateDevice(HWND hwnd)
{
	m_Hwnd = hwnd;
	HRESULT hr = S_OK;
	m_p3D.Attach(Direct3DCreate9(D3D_SDK_VERSION));

	D3DDISPLAYMODE dm;
	hr = m_p3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp, sizeof(pp));
	pp.Windowed = TRUE;
	pp.hDeviceWindow = hwnd;
	pp.SwapEffect = D3DSWAPEFFECT_COPY;
	pp.BackBufferFormat = dm.Format;

	m_pD3Device = NULL;

	FAIL_RET( m_p3D->CreateDevice(  D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		m_Hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING | 
		D3DCREATE_MULTITHREADED,
		&pp,
		&m_pD3Device));

	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE));
	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_LIGHTING, FALSE));
	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE));
	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA));
	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA));
	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE));
	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_ALPHAREF, 0x10));
	FAIL_RET(hr = m_pD3Device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER));

	FAIL_RET(hr = m_pD3Device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP));
	FAIL_RET(hr = m_pD3Device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP));
	FAIL_RET(hr = m_pD3Device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR));
	FAIL_RET(hr = m_pD3Device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR));
	FAIL_RET(hr = m_pD3Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR));
	


	m_vertexBuffer = NULL;

	m_pD3Device->CreateVertexBuffer(3*sizeof(CUSTOMVERTEX),0,D3DFVF_CUSTOMVERTEX,D3DPOOL_DEFAULT,& m_vertexBuffer, NULL );
	
	m_pD3Device->GetRenderTarget(0,&m_pRenderTarget);

	m_pMultiAllocotar = new CMultiAllocotar(*this);

	return S_OK;
}

void CMultiScene::Get3DDevice( IDirect3DDevice9 **ppDevice )
{
	ASSERT(ppDevice);
	if(m_pD3Device)
	{
		*ppDevice = m_pD3Device;
		(*ppDevice)->AddRef();
	}
	else
	{
		*ppDevice = NULL;
	}
	return;
}

void CMultiScene::SetTexture( IDirect3DTexture9 *pTexture )
{
	ASSERT(pTexture);
	m_pTexture = pTexture;
}

void CMultiScene::GetWindow( HWND& hwnd )
{
	hwnd = m_Hwnd;
}

HRESULT CMultiScene::AddVideoSource( IBaseFilter* pVMRFilter,DWORD_PTR& pdwID )
{
	return m_pMultiAllocotar->Attach(pVMRFilter,D3DFMT_A8R8G8B8,pdwID);
}

void CMultiScene::AddVideoID( DWORD_PTR videoId )
{
	m_pVSIDs.push_back(videoId);
}

void CMultiScene::SetPosition( DWORD_PTR dwID,int x,int y,int cx,int cy )
{
	 NORMALIZEDRECT nr;
	 ZeroMemory(&nr,sizeof(NORMALIZEDRECT));
	 RECT rc;
	 ::GetClientRect(m_Hwnd,&rc);

	nr.left   = (float)x /((float)rc.right - (float)rc.left);
	nr.right  = (float)(x+cx) /((float)rc.right - (float)rc.left);
	nr.top    = (float)y /((float)rc.bottom - (float)rc.top);
	nr.bottom = (float)(y+cy) /((float)rc.bottom - (float)rc.top);

	m_pMultiAllocotar->SetRect(dwID,nr);
}
