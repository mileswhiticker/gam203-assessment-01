#include "Line.h"

Line::Line(D3DXVECTOR3 a_Pos,D3DXVECTOR3 a_Vector)
:	m_Pos(a_Pos)
,	m_Vector(a_Vector)
,	m_Colour (D3DCOLOR_ARGB(255, 255, 255, 255))
,	m_Rotating(false)
,	m_RotVal(0.0f)
{
	//
	D3DXMatrixRotationYawPitchRoll(&m_ExtRotation,0.0f,0.0f,0.0f);
}

Line::Line()
:	m_Pos(D3DXVECTOR3(0,0,0))
,	m_Vector(D3DXVECTOR3(0,0,0))
,	m_Colour (D3DCOLOR_ARGB(255, 255, 255, 255))
,	m_Rotating(false)
,	m_RotVal(0.0f)
{
	//
	D3DXMatrixRotationYawPitchRoll(&m_ExtRotation,0.0f,0.0f,0.0f);
}

void Line::SetPos(D3DXVECTOR3 a_Pos)
{
	m_Pos = a_Pos;
	UpdateLine();
}

void Line::SetVec(D3DXVECTOR3 a_Vector)
{
	m_Vector = a_Vector;
	UpdateLine();
}

void Line::SetCol(D3DCOLOR a_Colour)
{
	m_Colour = a_Colour;
	UpdateLine();
}

void Line::UpdateLine()
{
	VertexData verts[2];
	verts[0].pos = m_Pos;
	verts[0].col = m_Colour;

	verts[1].pos = m_Pos + m_Vector;
	verts[1].col = m_Colour;

	void* pLockedData = NULL;
	m_pVertexBuf->Lock(0, sizeof(VertexData) * 2, &pLockedData, 0);
	memcpy(pLockedData, verts, sizeof(VertexData) * 2);
	m_pVertexBuf->Unlock();
}


bool Line::CreateObject(IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		return false;  // No device passed in, eh what?
	}

	// Create a vertex buffer
	HRESULT result = a_pDevice->CreateVertexBuffer(sizeof(VertexData) * 2, 0, VERTEX_FORMAT_FVF, D3DPOOL_DEFAULT, &m_pVertexBuf, NULL);
	if (result != D3D_OK)
	{
		return false;
	}

	// Create an index buffer
	a_pDevice->CreateIndexBuffer(sizeof(short) * 2, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuf, NULL);
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
	VertexData verts[2];
	verts[0].pos = m_Pos;
	verts[0].col = m_Colour;

	verts[1].pos = m_Vector;
	verts[1].col = m_Colour;

	//set up indices
	short indices[2];
	indices[0] = 0;
	indices[1] = 1;

	// Copy vertex data into vertex buffer
	// Don't bother checking the return value of Lock(), assume it works :/
	void* pLockedData = NULL;
	m_pVertexBuf->Lock(0, sizeof(VertexData) * 2, &pLockedData, 0);
	memcpy(pLockedData, verts, sizeof(VertexData) * 2);
	m_pVertexBuf->Unlock();
	pLockedData = NULL;

	m_pIndexBuf->Lock(0, sizeof(short) * 2, &pLockedData, 0);
	memcpy(pLockedData, indices, sizeof(short) * 2);
	m_pIndexBuf->Unlock();
	pLockedData = NULL;

	return true;
}

//
// Draw this object
//
void Line::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
	if (a_pDevice && m_pVertexBuf && m_pIndexBuf)
	{
		// Create a translation matrix
		//D3DXMATRIX translationMat;
		D3DXMatrixTranslation(&m_TranslationMat, -1, -1, -1);

		// Create a matrix that rotates our vertices around the Y axis (up)
		//D3DXMATRIX rotationMat;
		if(m_Rotating)
			m_RotVal += 0.01f;
		D3DXMatrixRotationY(&m_RotationMat, m_RotVal);

		// Calculate our world transform - a combination of a rotation and a translation
		// We can combine these into one matrix by multiplying them together (order is important!)
		// We apply the rotation THEN the translation
		D3DXMATRIX modelToWorld;
		D3DXMatrixMultiply(&modelToWorld, &m_RotationMat, &m_ExtRotation);
		D3DXMatrixMultiply(&modelToWorld, &modelToWorld, &m_TranslationMat);

		// Set the world transform for this object
		a_pDevice->SetTransform(D3DTS_WORLD, &modelToWorld);

		// Tell DirectX about the vertex data
		a_pDevice->SetStreamSource(0, m_pVertexBuf, 0, sizeof(VertexData));
		a_pDevice->SetFVF(VERTEX_FORMAT_FVF);

		// Tell DirectX about the index data
		a_pDevice->SetIndices(m_pIndexBuf);

		// Draw the poly; we have only 1 primitive to draw here (see final argument)
		// D3DPT_TRIANGLELIST looks for triangles, so it reads indices in sets of 3
		a_pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, 2, 0, 1);
	}
}

void Line::ToggleRotating()
{
	m_Rotating = !m_Rotating;
}

D3DXVECTOR3 Line::GetPos()
{
	return m_Pos;
}

D3DXVECTOR3 Line::GetVec()
{
	return m_Vector;
}

void Line::Normalise()
{
	//tbd
	UpdateLine();
}

void Line::Zero()
{
	m_Vector = D3DXVECTOR3(0.0f,0.0f,0.0f);
	UpdateLine();
}

void Line::SetAdd(D3DXVECTOR3 a_Vector)
{
	m_Vector.x += a_Vector.x;
	m_Vector.y += a_Vector.y;
	m_Vector.z += a_Vector.z;
	UpdateLine();
}

D3DXVECTOR3 Line::GetAdd(Line& a_Line)
{
	D3DXVECTOR3 result = m_Vector;
	D3DXVECTOR3 other = a_Line.GetVec();
	result.x += other.x;
	result.y += other.y;
	result.z += other.z;
	return result;
}

D3DXVECTOR3 Line::GetSubtract(Line& a_Line)
{
	D3DXVECTOR3 result = m_Vector;
	D3DXVECTOR3 other = a_Line.GetVec();
	result.x -= other.x;
	result.y -= other.y;
	result.z -= other.z;
	return result;
}

D3DXVECTOR3 Line::GetCrossProduct(Line& a_Line)
{
	D3DXVECTOR3 result = D3DXVECTOR3(0.0f,0.0f,0.0f);
	D3DXVECTOR3 other = a_Line.GetVec();
	result.x = m_Vector.y * other.z - other.y * m_Vector.z;
    result.y = m_Vector.x * other.z - other.x * m_Vector.z;
    result.z = m_Vector.x * other.y - other.x * m_Vector.y;
	return result;
}

float Line::GetAngleWith(Line& a_Line)
{
	D3DXVECTOR3 other = a_Line.GetVec();
	float firstLength = sqrt(m_Vector.x*m_Vector.x + m_Vector.y*m_Vector.y + m_Vector.z*m_Vector.z);
	float secondLength = sqrt(other.x*other.x + other.y*other.y + other.z*other.z);
	float dotProduct = m_Vector.x*other.x + m_Vector.y*other.y + m_Vector.z*other.z;
	float angle = acos( dotProduct / (firstLength * secondLength) );
	return angle;
}
