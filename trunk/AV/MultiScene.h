#pragma once
#include <d3d9.h>
#include <time.h>
#include "VideoSource.h"
#include "MultiAllocotar.h"

class CMultiAllocotar;

class CMultiScene
{

public:
	CMultiScene(void);
	~CMultiScene(void);

	HRESULT Init();

	//绘制场景
	HRESULT DrawScene();

	//得到纹理
	void SetTexture(IDirect3DTexture9 *pTexture);

	void Get3DDevice(IDirect3DDevice9 **ppDevice);

	//设置位置
	void SetPosition(DWORD_PTR dwID,int x,int y,int cx,int cy);

	HRESULT AddVideoSource(IBaseFilter* pVMRFilter,DWORD_PTR& pdwID);

	void AddVideoID(DWORD_PTR videoId);

	HRESULT CreateDevice(HWND hwnd);

	void GetWindow(HWND& hwnd);
protected:
	
	
private:
	/*
	struct CUSTOMVERTEX
		{
			FLOAT x, y, z, rhw; // The transformed position for the vertex.
			DWORD color;        // The vertex color.
		};*/
	struct CUSTOMVERTEX1
	{
		struct Position {
			Position() : 
		x(0.0f),y(0.0f),z(0.0f) {            
		};
		Position(float x_, float y_, float z_) :
		x(x_),y(y_),z(z_) {
		};
		float x,y,z;
		};

		Position    position; // The position
		D3DCOLOR    color;    // The color
		FLOAT       tu, tv;   // The texture coordinates
	};

	CUSTOMVERTEX1                             m_vertices[NUM_VERTICES];
	CCritSec                                  m_ObjectLock;
	SmartPtr<IDirect3DVertexBuffer9>          m_vertexBuffer;
	SmartPtr<IDirect3DTexture9>               m_pTexture;
	SmartPtr<IDirect3DDevice9>                m_pD3Device;
	SmartPtr<IDirect3D9>                      m_p3D;
	SmartPtr<IDirect3DSurface9>               m_pRenderTarget;
	SmartPtr<CMultiAllocotar>                 m_pMultiAllocotar;
	HWND                                      m_Hwnd;
	std::list<DWORD_PTR>                      m_pVSIDs;
};

