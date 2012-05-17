/////////////////////////////////////////////////////////////////////////
//
// GAM203
// Drawable base class
// Drawable.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "Drawable.h"

#include <d3dx9.h>

//
// Constructor
//
Drawable::Drawable()
:	m_pVertexBuf(NULL)
,	m_pIndexBuf(NULL)
{
	D3DXMatrixIdentity(&m_worldMatrix);
}

//
// Destructor
//
Drawable::~Drawable()
{
	// Clean up our vertex buffer
	if (m_pVertexBuf)
	{
		m_pVertexBuf->Release();
		m_pVertexBuf = NULL;
	}

	// Clean up our index buffer
	if (m_pIndexBuf)
	{
		m_pIndexBuf->Release();
		m_pIndexBuf = NULL;
	}
}

bool Drawable::ReleaseObject()
{
	m_pVertexBuf->Release();
	m_pVertexBuf = NULL;
	m_pIndexBuf->Release();
	m_pIndexBuf = NULL;
	return true;
}
