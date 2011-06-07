#pragma once


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

const int NUM_VERTICES = 4;

class VideoSource{

public:

	VideoSource();
	~VideoSource();

	void DeleteSurfaces();
	HRESULT AllocateSurfaceBuffer( DWORD dwN );

public:
	DWORD_PTR                                       m_dwID;
	SmartPtr<IVMRSurfaceAllocatorNotify9>           m_lpIVMRSurfAllocNotify;
	std::vector<SmartPtr<IDirect3DSurface9>>        m_surfaces;
	SmartPtr<IDirect3DTexture9>                     m_pTexture;
	CUSTOMVERTEX                                    m_vertices[NUM_VERTICES];
	NORMALIZEDRECT                                  m_rect;

private:
	CCritSec                                        m_ObjectLock;

};