#include "StdAfx.h"
#include "VideoSource.h"



VideoSource::VideoSource()
	: m_lpIVMRSurfAllocNotify(NULL)
{
	m_vertices[0].position = CUSTOMVERTEX::Position(-1.0f,  1.0f, 0.0f); // top left
	m_vertices[1].position = CUSTOMVERTEX::Position(-1.0f, -1.0f, 0.0f); // bottom left
	m_vertices[2].position = CUSTOMVERTEX::Position( 1.0f,  1.0f, 0.0f); // top right
	m_vertices[3].position = CUSTOMVERTEX::Position( 1.0f, -1.0f, 0.0f); // bottom right

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
VideoSource::~VideoSource()
{
	
}


void VideoSource::DeleteSurfaces()
{
	CAutoLock Lock(&m_ObjectLock);

	for( size_t i = 0; i < m_surfaces.size(); ++i ) 
	{
		m_surfaces[i] = NULL;
	}
}

HRESULT VideoSource::AllocateSurfaceBuffer( DWORD dwN )
{
	return S_OK;
}



