#pragma once
#include <d3d9.h>
#include <time.h>

// Common files
#include "SmartPtr.h"

const int NUM_VERTICES = 4;

class CMultiScene
{

public:
	CMultiScene(void);
	~CMultiScene(void);

	HRESULT Init();

	HRESULT DrawScene();

	void SetTexture(IDirect3DTexture9 *pTexture);

	void Get3DDevice(IDirect3DDevice9 **ppDevice);

	HRESULT CreateDevice(HWND hwnd);

	void GetWindow(HWND& hwnd);
protected:
	
	
private:

	struct CUSTOMVERTEX
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
	

	/*
	struct CUSTOMVERTEX
		{
			FLOAT x, y, z, rhw; // The transformed position for the vertex.
			DWORD color;        // The vertex color.
		};*/
	


	CCritSec                                  m_ObjectLock;
	CUSTOMVERTEX                              m_vertices[NUM_VERTICES];
	SmartPtr<IDirect3DVertexBuffer9>          m_vertexBuffer;
	SmartPtr<IDirect3DTexture9>               m_pTexture;
	SmartPtr<IDirect3DDevice9>                m_pD3Device;
	SmartPtr<IDirect3D9>                      m_p3D;
	SmartPtr<IDirect3DSurface9>               m_pRenderTarget;
	HWND                                      m_Hwnd;
};

