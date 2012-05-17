//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Triangle class
// Triangle.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "Triangle.h"

#include <d3dx9.h>

// Hack: number of vertices and indices we will use
static const int TRI_VERTEX_COUNT = 3;
static const int TRI_INDEX_COUNT = 3;

//
// Sets up this drawable object with some data
// Returns true if successful
//
bool Triangle::CreateObject(IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		return false;  // No device passed in, eh what?
	}

	// Create a vertex buffer
	HRESULT result = a_pDevice->CreateVertexBuffer(sizeof(VertexData) * TRI_VERTEX_COUNT, 0, VERTEX_FORMAT_FVF,	D3DPOOL_DEFAULT, &m_pVertexBuf, NULL);
	if (result != D3D_OK)
	{
		return false;
	}

	// Create an index buffer
	a_pDevice->CreateIndexBuffer(sizeof(short) * TRI_INDEX_COUNT, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuf, NULL);
	if (result != D3D_OK)
	{
		// Index buffer creation failed, but vertex buffer was created! Clean it up before we return
		m_pVertexBuf->Release();
		m_pVertexBuf = NULL;
		return false;
	}

	// Create an array of vertex data on the stack
	// Note: Polygon "winding" is important here - must be clockwise!
	//       If your polys are not appearing, try disabling backface culling
	VertexData verts[TRI_VERTEX_COUNT];
	verts[0].pos = D3DXVECTOR3(-1, 1, 0);
	/* This helper class D3DXVECTOR3 (above) is the same as:
	verts[0].pos.x = -1;
	verts[0].pos.y = 1;
	verts[0].pos.z = 0; */
	verts[0].col = D3DCOLOR_XRGB(0, 0, 255);

	verts[1].pos = D3DXVECTOR3(1, 0, 0);
	verts[1].col = D3DCOLOR_XRGB(0, 255, 0);

	verts[2].pos = D3DXVECTOR3(-1, -1, 0);
	verts[2].col = D3DCOLOR_XRGB(255, 0, 0);

	// Create an array of index data on the stack
	short indices[TRI_INDEX_COUNT];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	// Copy vertex data into vertex buffer
	// Don't bother checking the return value of Lock(), assume it works :/
	void* pLockedData = NULL;
	m_pVertexBuf->Lock(0, sizeof(VertexData) * TRI_VERTEX_COUNT, &pLockedData, 0);
	memcpy(pLockedData, verts, sizeof(VertexData) * TRI_VERTEX_COUNT);
	m_pVertexBuf->Unlock();
	pLockedData = NULL;

	// Copy index data into index buffer
	// Don't bother checking the return value of Lock(), assume it works :/
	m_pIndexBuf->Lock(0, sizeof(short) * TRI_INDEX_COUNT, &pLockedData, 0);
	memcpy(pLockedData, indices, sizeof(short) * TRI_INDEX_COUNT);
	m_pIndexBuf->Unlock();
	pLockedData = NULL;

	return true;
}

//
// Draw this object
//
void Triangle::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
  if (a_pDevice && m_pVertexBuf && m_pIndexBuf)
  {
    // Create a translation matrix
    D3DXMATRIX translationMat;
    D3DXMatrixTranslation(&translationMat, 2, 0, 0);  // Translate to the right

    // Create a matrix that rotates our vertices around the Y axis (up)
    D3DXMATRIX rotationMat;
    D3DXMatrixRotationY(&rotationMat, 1.0f);  // <-- some arbitrary angle in radians

    // Calculate our world transform - a combination of a rotation and a translation
    // We can combine these into one matrix by multiplying them together (order is important!)
    // We apply the rotation THEN the translation
    D3DXMATRIX modelToWorld;
    D3DXMatrixMultiply(&modelToWorld, &rotationMat, &translationMat);

    // Set the world transform for this object
    a_pDevice->SetTransform(D3DTS_WORLD, &modelToWorld);

    // Tell DirectX about the vertex data
    a_pDevice->SetStreamSource(0, m_pVertexBuf, 0, sizeof(VertexData));
    a_pDevice->SetFVF(VERTEX_FORMAT_FVF);

    // Tell DirectX about the index data
    a_pDevice->SetIndices(m_pIndexBuf);

    // Draw the poly; we have only 1 primitive to draw here (see final argument)
    // D3DPT_TRIANGLELIST looks for triangles, so it reads indices in sets of 3
    a_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, TRI_VERTEX_COUNT, 0, 1);
  }
}


