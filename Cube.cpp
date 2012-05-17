/////////////////////////////////////////////////////////////////////////
//
// GAM203
// Cube class
// Cube.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "Cube.h"

#include <iostream>
#include <d3d9.h>
#include <d3d9types.h>
#include <d3dx9.h>
#include <D3dx9math.h>

static const int VERTEX_COUNT = 24;
static const int INDEX_COUNT = 36;	//formerly 8
static const int PRIM_COUNT = 12;

Cube::Cube()
:	m_CyclingAmbientDir(0)
,	m_CyclingDiffuseDir(0)
,	m_CyclingSpecularDir(0)
,	m_CyclingEmissiveDir(0)
,	m_pTex(NULL)
{
	//
}

//
// Sets up this Cube object with some data
// Returns true if successful
// Also maps tex uvs
//
bool Cube::CreateObject(IDirect3DDevice9* a_pDevice, LPDIRECT3DTEXTURE9* a_pTex)
{
	if (!a_pDevice || !a_pTex)
	{
		return false;
	}
	//std::cout << "Cube::CreateObject()" << std::endl;
	m_pTex = a_pTex;
	a_pDevice->SetTexture(0,*m_pTex);

	//initialize object settings
	ResetMaterial();
	xRot = 0;
	yRot = 0;
	zRot = 0;
	m_RotatingX = false;
	m_RotatingY = false;
	m_RotatingZ = false;
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Pos.z = 0;
	xyz_Scale = 1.0f;
	D3DXMatrixIdentity(&m_ModelToWorld);

	// Create a vertex buffer
	HRESULT result = a_pDevice->CreateVertexBuffer(sizeof(VertexData) * VERTEX_COUNT, 0, VERTEX_FORMAT_FVF,	D3DPOOL_DEFAULT, &m_pVertexBuf, NULL);
	if (result != D3D_OK)
	{
		return false;
	}

	// Create an index buffer
	a_pDevice->CreateIndexBuffer(sizeof(short) * INDEX_COUNT, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuf, NULL);
	if (result != D3D_OK)
	{
		// Index buffer creation failed, but vertex buffer was created! Clean it up before we return
		m_pVertexBuf->Release();
		m_pVertexBuf = NULL;
		return false;
	}

	// Create a set of vertices
	VertexData vertices[VERTEX_COUNT];

	// Set up vertex positions
	vertices[0].pos = D3DXVECTOR3(-1,-1,1);		//left bottom back
	vertices[0].norm = D3DXVECTOR3(0,0,1);
	vertices[1].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[1].norm = D3DXVECTOR3(0,0,1);
	vertices[2].pos = D3DXVECTOR3(-1,1,1);		//left top back
	vertices[2].norm = D3DXVECTOR3(0,0,1);
	vertices[3].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[3].norm = D3DXVECTOR3(0,0,1);
	
	vertices[4].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[4].norm = D3DXVECTOR3(0,0,-1);
	vertices[5].pos = D3DXVECTOR3(-1,1,-1);		//left top front
	vertices[5].norm = D3DXVECTOR3(0,0,-1);
	vertices[6].pos = D3DXVECTOR3(1,-1,-1);		//right bottom front
	vertices[6].norm = D3DXVECTOR3(0,0,-1);
	vertices[7].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[7].norm = D3DXVECTOR3(0,0,-1);	
	
	vertices[8].pos = D3DXVECTOR3(-1,1,-1);		//left top back
	vertices[8].norm = D3DXVECTOR3(0,1,0);
	vertices[9].pos = D3DXVECTOR3(-1,1,1);		//left top front
	vertices[9].norm = D3DXVECTOR3(0,1,0);
	vertices[10].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[10].norm = D3DXVECTOR3(0,1,0);
	vertices[11].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[11].norm = D3DXVECTOR3(0,1,0);	
	
	vertices[12].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[12].norm = D3DXVECTOR3(0,-1,0);
	vertices[13].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	vertices[13].norm = D3DXVECTOR3(0,-1,0);
	vertices[14].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back
	vertices[14].norm = D3DXVECTOR3(0,-1,0);
	vertices[15].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[15].norm = D3DXVECTOR3(0,-1,0);	
	
	vertices[16].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	vertices[16].norm = D3DXVECTOR3(1,0,0);
	vertices[17].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[17].norm = D3DXVECTOR3(1,0,0);
	vertices[18].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[18].norm = D3DXVECTOR3(1,0,0);
	vertices[19].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[19].norm = D3DXVECTOR3(1,0,0);	
	
	vertices[20].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[20].norm = D3DXVECTOR3(-1,0,0);
	vertices[21].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back
	vertices[21].norm = D3DXVECTOR3(-1,0,0);
	vertices[22].pos = D3DXVECTOR3(-1,1,-1);	//left top front
	vertices[22].norm = D3DXVECTOR3(-1,0,0);
	vertices[23].pos = D3DXVECTOR3(-1,1,1);		//left top back
	vertices[23].norm = D3DXVECTOR3(-1,0,0);

	//set default vertex colours
	for (int i = 0; i < VERTEX_COUNT; ++i)
	{
		vertices[i].col = D3DCOLOR_XRGB(100,100,100);
	}

	//create uv data
	vertices[0].tu = 0.0f;		//left bottom back
	vertices[0].tv = 1.0f;
	vertices[1].tu = 1.0f;		//right bottom back
	vertices[1].tv = 1.0f;
	vertices[2].tu = 0.0f;		//left top back
	vertices[2].tv = 0.0f;
	vertices[3].tu = 1.0f;		//right top back
	vertices[3].tv = 0.0f;
	
	vertices[4].tu = 0.0f;		//left bottom front
	vertices[4].tv = 1.0f;
	vertices[5].tu = 0.0f;		//left top front
	vertices[5].tv = 0.0f;
	vertices[6].tu = 1.0f;		//right bottom front
	vertices[6].tv = 1.0f;
	vertices[7].tu = 1.0f;		//right top front
	vertices[7].tv = 0.0f;
	
	vertices[8].tu = 0.0f;		//left top back
	vertices[8].tv = 0.0f;
	vertices[9].tu = 0.0f;		//left top front
	vertices[9].tv = 1.0f;
	vertices[10].tu = 1.0f;		//right top front
	vertices[10].tv = 1.0f;
	vertices[11].tu = 1.0f;		//right top back
	vertices[11].tv = 0.0f;
	
	vertices[12].tu = 0.0f;		//left bottom front
	vertices[12].tv = 0.0f;
	vertices[13].tu = 1.0f;		//right bottom front
	vertices[13].tv = 0.0f;
	vertices[14].tu = 0.0f;		//left bottom back
	vertices[14].tv = 1.0f;
	vertices[15].tu = 1.0f;		//right bottom back
	vertices[15].tv = 1.0f;
	
	vertices[16].tu = 0.0f;		//right bottom front
	vertices[16].tv = 1.0f;
	vertices[17].tu = 0.0f;		//right top front
	vertices[17].tv = 0.0f;
	vertices[18].tu = 1.0f;		//right bottom back
	vertices[18].tv = 1.0f;
	vertices[19].tu = 1.0f;		//right top back
	vertices[19].tv = 0.0f;
	
	vertices[20].tu = 1.0f;		//left bottom front
	vertices[20].tv = 1.0f;
	vertices[21].tu = 0.0f;		//left bottom back
	vertices[21].tv = 1.0f;
	vertices[22].tu = 1.0f;		//left top front
	vertices[22].tv = 0.0f;
	vertices[23].tu = 0.0f;		//left top back
	vertices[23].tv = 0.0f;

	// Create a data set of indices
	short indices[] = 
	{
		0, 1, 2,	// side 1
		2, 1, 3,
		4, 5, 6,	// side 2
		6, 5, 7,
		8, 9, 10,	// side 3
		10, 9, 11,
		12, 13, 14,	// side 4
		14, 13, 15,
		16, 17, 18,	// side 5
		18, 17, 19,
		20, 21, 22,	// side 6
		22, 21, 23,
	};

	// Copy vertex data into vertex buffer
	void* pLockedData = NULL;
	m_pVertexBuf->Lock(0, sizeof(VertexData) * VERTEX_COUNT, &pLockedData, 0);
	memcpy(pLockedData, vertices, sizeof(VertexData) * VERTEX_COUNT);
	m_pVertexBuf->Unlock();
	pLockedData = NULL;

	// Copy index data into index buffer
	m_pIndexBuf->Lock(0, sizeof(short) * INDEX_COUNT, &pLockedData, 0);
	memcpy(pLockedData, indices, sizeof(short) * INDEX_COUNT);
	m_pIndexBuf->Unlock();
	pLockedData = NULL;

	return true;
}

//
// Sets up this Cube object with some data
// Returns true if successful
//
bool Cube::CreateObject(IDirect3DDevice9* a_pDevice)
{
	if (!a_pDevice)
	{
		return false;
	}
	//initialize object settings
	ResetMaterial();
	xRot = 0;
	yRot = 0;
	zRot = 0;
	m_RotatingX = false;
	m_RotatingY = false;
	m_RotatingZ = false;
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_Pos.z = 0;
	xyz_Scale = 1.0f;
	D3DXMatrixIdentity(&m_ModelToWorld);

	// Create a vertex buffer
	HRESULT result = a_pDevice->CreateVertexBuffer(sizeof(VertexData) * VERTEX_COUNT, 0, VERTEX_FORMAT_FVF,	D3DPOOL_DEFAULT, &m_pVertexBuf, NULL);
	if (result != D3D_OK)
	{
		return false;
	}

	// Create an index buffer
	a_pDevice->CreateIndexBuffer(sizeof(short) * INDEX_COUNT, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuf, NULL);
	if (result != D3D_OK)
	{
		// Index buffer creation failed, but vertex buffer was created! Clean it up before we return
		m_pVertexBuf->Release();
		m_pVertexBuf = NULL;
		return false;
	}

	// Create a set of vertices
	VertexData vertices[VERTEX_COUNT];

	// Set up vertex positions
	/*
	vertices[0].pos = D3DXVECTOR3(-1,1,1);	//left top back
	vertices[3].pos = D3DXVECTOR3(-1,1,-1);	//left top front
	vertices[4].pos = D3DXVECTOR3(1,1,1);	//right top back
	vertices[7].pos = D3DXVECTOR3(1,1,-1);	//right top front

	vertices[1].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back 
	vertices[2].pos = D3DXVECTOR3(-1,-1,-1);//left bottom front
	vertices[5].pos = D3DXVECTOR3(1,-1,1);	//right bottom back
	vertices[6].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	*/
	vertices[0].pos = D3DXVECTOR3(-1,-1,1);		//left bottom back
	vertices[0].norm = D3DXVECTOR3(0,0,1);
	vertices[1].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[1].norm = D3DXVECTOR3(0,0,1);
	vertices[2].pos = D3DXVECTOR3(-1,1,1);		//left top back
	vertices[2].norm = D3DXVECTOR3(0,0,1);
	vertices[3].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[3].norm = D3DXVECTOR3(0,0,1);
	
	vertices[4].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[4].norm = D3DXVECTOR3(0,0,-1);
	vertices[5].pos = D3DXVECTOR3(-1,1,-1);		//left top front
	vertices[5].norm = D3DXVECTOR3(0,0,-1);
	vertices[6].pos = D3DXVECTOR3(1,-1,-1);		//right bottom front
	vertices[6].norm = D3DXVECTOR3(0,0,-1);
	vertices[7].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[7].norm = D3DXVECTOR3(0,0,-1);	
	
	vertices[8].pos = D3DXVECTOR3(-1,1,-1);		//left top back
	vertices[8].norm = D3DXVECTOR3(0,1,0);
	vertices[9].pos = D3DXVECTOR3(-1,1,1);		//left top front
	vertices[9].norm = D3DXVECTOR3(0,1,0);
	vertices[10].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[10].norm = D3DXVECTOR3(0,1,0);
	vertices[11].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[11].norm = D3DXVECTOR3(0,1,0);	
	
	vertices[12].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[12].norm = D3DXVECTOR3(0,-1,0);
	vertices[13].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	vertices[13].norm = D3DXVECTOR3(0,-1,0);
	vertices[14].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back
	vertices[14].norm = D3DXVECTOR3(0,-1,0);
	vertices[15].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[15].norm = D3DXVECTOR3(0,-1,0);	
	
	vertices[16].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	vertices[16].norm = D3DXVECTOR3(1,0,0);
	vertices[17].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[17].norm = D3DXVECTOR3(1,0,0);
	vertices[18].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[18].norm = D3DXVECTOR3(1,0,0);
	vertices[19].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[19].norm = D3DXVECTOR3(1,0,0);	
	
	vertices[20].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[20].norm = D3DXVECTOR3(-1,0,0);
	vertices[21].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back
	vertices[21].norm = D3DXVECTOR3(-1,0,0);
	vertices[22].pos = D3DXVECTOR3(-1,1,-1);	//left top front
	vertices[22].norm = D3DXVECTOR3(-1,0,0);
	vertices[23].pos = D3DXVECTOR3(-1,1,1);		//left top back
	vertices[23].norm = D3DXVECTOR3(-1,0,0);

	//set vertex colours
	for (int i = 0; i < VERTEX_COUNT; ++i)
	{
		int r = rand()%255;
		vertices[i].col = D3DCOLOR_ARGB(125,rand()%255,rand()%255,rand()%255);
	}

	// Create a data set of indices
	short indices[] = 
	{
		0, 1, 2,	// side 1
		2, 1, 3,
		4, 5, 6,	// side 2
		6, 5, 7,
		8, 9, 10,	// side 3
		10, 9, 11,
		12, 13, 14,	// side 4
		14, 13, 15,
		16, 17, 18,	// side 5
		18, 17, 19,
		20, 21, 22,	// side 6
		22, 21, 23,
	};
	/*
	//front
	indices[30] = 2;
	indices[31] = 3;
	indices[32] = 7;
	
	indices[33] = 7;
	indices[34] = 6;
	indices[35] = 2;

	//left
	indices[0] = 2;
	indices[1] = 1;
	indices[2] = 0;
	
	indices[3] = 0;
	indices[4] = 3;
	indices[5] = 2;

	//back
	indices[6] = 4;
	indices[7] = 0;
	indices[8] = 1;
	
	indices[9] = 1;
	indices[10] = 5;
	indices[11] = 4;

	//right
	indices[12] = 6;
	indices[13] = 7;
	indices[14] = 4;
	
	indices[15] = 4;
	indices[16] = 5;
	indices[17] = 6;

	//top
	indices[18] = 3;
	indices[19] = 0;
	indices[20] = 4;
	
	indices[21] = 4;
	indices[22] = 7;
	indices[23] = 3;

	//bottom
	indices[24] = 5;
	indices[25] = 1;
	indices[26] = 2;
	
	indices[27] = 2;
	indices[28] = 6;
	indices[29] = 5;
	*/

	// Copy vertex data into vertex buffer
	void* pLockedData = NULL;
	m_pVertexBuf->Lock(0, sizeof(VertexData) * VERTEX_COUNT, &pLockedData, 0);
	memcpy(pLockedData, vertices, sizeof(VertexData) * VERTEX_COUNT);
	m_pVertexBuf->Unlock();
	pLockedData = NULL;

	// Copy index data into index buffer
	m_pIndexBuf->Lock(0, sizeof(short) * INDEX_COUNT, &pLockedData, 0);
	memcpy(pLockedData, indices, sizeof(short) * INDEX_COUNT);
	m_pIndexBuf->Unlock();
	pLockedData = NULL;

	return true;
}

//
// Draw this object
//
void Cube::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
	if (m_pVertexBuf && m_pIndexBuf)
	{
		//automatic material property cycling
		if(m_CyclingAmbientDir)
		{
			m_Mat.Ambient.r += a_dt*m_CyclingAmbientDir;
			m_Mat.Ambient.g += a_dt*m_CyclingAmbientDir;
			m_Mat.Ambient.b += a_dt*m_CyclingAmbientDir;
			if(m_Mat.Ambient.r < 0 || m_Mat.Ambient.r > 1)
			{
				m_CyclingAmbientDir *= -1;
				m_Mat.Ambient.r += a_dt*m_CyclingAmbientDir;
				m_Mat.Ambient.g += a_dt*m_CyclingAmbientDir;
				m_Mat.Ambient.b += a_dt*m_CyclingAmbientDir;
			}
		}
		if(m_CyclingDiffuseDir)
		{
			m_Mat.Diffuse.r += a_dt*m_CyclingDiffuseDir;
			m_Mat.Diffuse.g += a_dt*m_CyclingDiffuseDir;
			m_Mat.Diffuse.b += a_dt*m_CyclingDiffuseDir;
			if(m_Mat.Diffuse.r < 0 || m_Mat.Diffuse.r > 1)
			{
				m_CyclingDiffuseDir *= -1;
				m_Mat.Diffuse.r += a_dt*m_CyclingDiffuseDir;
				m_Mat.Diffuse.g += a_dt*m_CyclingDiffuseDir;
				m_Mat.Diffuse.b += a_dt*m_CyclingDiffuseDir;
			}
		}
		if(m_CyclingSpecularDir)
		{
			m_Mat.Specular.r += a_dt*m_CyclingSpecularDir;
			m_Mat.Specular.g += a_dt*m_CyclingSpecularDir;
			m_Mat.Specular.b += a_dt*m_CyclingSpecularDir;
			if(m_Mat.Specular.r < 0 || m_Mat.Specular.r > 1)
			{
				m_CyclingSpecularDir *= -1;
				m_Mat.Specular.r += a_dt*m_CyclingSpecularDir;
				m_Mat.Specular.g += a_dt*m_CyclingSpecularDir;
				m_Mat.Specular.b += a_dt*m_CyclingSpecularDir;
			}
		}
		if(m_CyclingEmissiveDir)
		{
			m_Mat.Emissive.r += a_dt*m_CyclingEmissiveDir;
			m_Mat.Emissive.g += a_dt*m_CyclingEmissiveDir;
			m_Mat.Emissive.b += a_dt*m_CyclingEmissiveDir;
			if(m_Mat.Emissive.r < 0 || m_Mat.Emissive.r > 1)
			{
				m_CyclingEmissiveDir *= -1;
				m_Mat.Emissive.r += a_dt*m_CyclingEmissiveDir;
				m_Mat.Emissive.g += a_dt*m_CyclingEmissiveDir;
				m_Mat.Emissive.b += a_dt*m_CyclingEmissiveDir;
			}
		}

		//apply cube material
		a_pDevice->SetMaterial(&m_Mat);

		//apply cube texture (should only exist if uv coords mapped successully)
		/*
		if(m_pTex)
			a_pDevice->SetTexture( 0, *m_pTex );
			*/

		D3DXMatrixIdentity(&m_ModelToWorld);

		//apply cube scaling
		D3DXMATRIX scaleMat;
		D3DXMatrixIdentity(&scaleMat);
		D3DXMatrixScaling(&scaleMat,xyz_Scale,xyz_Scale,xyz_Scale);
		D3DXMatrixMultiply(&m_ModelToWorld, &m_ModelToWorld, &scaleMat);

		// automatic cube rotation
		D3DXMATRIX rotationMat;
		D3DXMatrixIdentity(&rotationMat);
		if(m_RotatingX)
			xRot += 0.01f;
			D3DXMatrixRotationX(&rotationMat,xRot);
		D3DXMatrixMultiply(&m_ModelToWorld, &m_ModelToWorld, &rotationMat);
		if(m_RotatingY)
			yRot += 0.01f;
			D3DXMatrixRotationY(&rotationMat,yRot);
		D3DXMatrixMultiply(&m_ModelToWorld, &m_ModelToWorld, &rotationMat);
		if(m_RotatingZ)
			zRot += 0.01f;
			D3DXMatrixRotationZ(&rotationMat,zRot);
		D3DXMatrixMultiply(&m_ModelToWorld, &m_ModelToWorld, &rotationMat);

		//apply translation
		D3DXMATRIX transMat;
		D3DXMatrixIdentity(&transMat);
		D3DXMatrixTranslation(&transMat,m_Pos.x,m_Pos.y,m_Pos.z);
		D3DXMatrixMultiply(&m_ModelToWorld, &m_ModelToWorld, &transMat);

		a_pDevice->SetTransform(D3DTS_WORLD, &m_ModelToWorld);

		// Tell D3D about our vertex data
		a_pDevice->SetStreamSource(0, m_pVertexBuf, 0, sizeof(VertexData));
		a_pDevice->SetFVF(VERTEX_FORMAT_FVF);

		// Draw using index buffer
		a_pDevice->SetIndices(m_pIndexBuf);

		a_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, VERTEX_COUNT, 0, PRIM_COUNT);
	}
}

void Cube::ResetMaterial()
{
	ZeroMemory(&m_Mat,sizeof(m_Mat));
	m_Mat.Specular = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1);
	m_Mat.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1);
}

/*
void Cube::CalculateNormals()
{
	// Set up vertex positions
	vertices[0].pos = D3DXVECTOR3(-1,1,1);	//left top back
	vertices[3].pos = D3DXVECTOR3(-1,1,-1);	//left top front
	vertices[4].pos = D3DXVECTOR3(1,1,1);	//right top back
	vertices[7].pos = D3DXVECTOR3(1,1,-1);	//right top front

	vertices[1].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back 
	vertices[2].pos = D3DXVECTOR3(-1,-1,-1);//left bottom front
	vertices[5].pos = D3DXVECTOR3(1,-1,1);	//right bottom back
	vertices[6].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	vertices[0].pos = D3DXVECTOR3(-1,-1,1);		//left bottom back
	vertices[0].norm = D3DXVECTOR3(0,0,1);
	vertices[1].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[1].norm = D3DXVECTOR3(0,0,1);
	vertices[2].pos = D3DXVECTOR3(-1,1,1);		//left top back
	vertices[2].norm = D3DXVECTOR3(0,0,1);
	vertices[3].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[3].norm = D3DXVECTOR3(0,0,1);
	
	vertices[4].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[4].norm = D3DXVECTOR3(0,0,-1);
	vertices[5].pos = D3DXVECTOR3(-1,1,-1);		//left top front
	vertices[5].norm = D3DXVECTOR3(0,0,-1);
	vertices[6].pos = D3DXVECTOR3(1,-1,-1);		//right bottom front
	vertices[6].norm = D3DXVECTOR3(0,0,-1);
	vertices[7].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[7].norm = D3DXVECTOR3(0,0,-1);	
	
	vertices[8].pos = D3DXVECTOR3(-1,1,-1);		//left top back
	vertices[8].norm = D3DXVECTOR3(0,1,0);
	vertices[9].pos = D3DXVECTOR3(-1,1,1);		//left top front
	vertices[9].norm = D3DXVECTOR3(0,1,0);
	vertices[10].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[10].norm = D3DXVECTOR3(0,1,0);
	vertices[11].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[11].norm = D3DXVECTOR3(0,1,0);	
	
	vertices[12].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[12].norm = D3DXVECTOR3(0,-1,0);
	vertices[13].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	vertices[13].norm = D3DXVECTOR3(0,-1,0);
	vertices[14].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back
	vertices[14].norm = D3DXVECTOR3(0,-1,0);
	vertices[15].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[15].norm = D3DXVECTOR3(0,-1,0);	
	
	vertices[16].pos = D3DXVECTOR3(1,-1,-1);	//right bottom front
	vertices[16].norm = D3DXVECTOR3(1,0,0);
	vertices[17].pos = D3DXVECTOR3(1,1,-1);		//right top front
	vertices[17].norm = D3DXVECTOR3(1,0,0);
	vertices[18].pos = D3DXVECTOR3(1,-1,1);		//right bottom back
	vertices[18].norm = D3DXVECTOR3(1,0,0);
	vertices[19].pos = D3DXVECTOR3(1,1,1);		//right top back
	vertices[19].norm = D3DXVECTOR3(1,0,0);	
	

	vertices[20].pos = D3DXVECTOR3(-1,-1,-1);	//left bottom front
	vertices[20].norm = D3DXVECTOR3(-1,0,0);
	vertices[21].pos = D3DXVECTOR3(-1,-1,1);	//left bottom back
	vertices[21].norm = D3DXVECTOR3(-1,0,0);
	vertices[22].pos = D3DXVECTOR3(-1,1,-1);	//left top front
	vertices[22].norm = D3DXVECTOR3(-1,0,0);
	vertices[23].pos = D3DXVECTOR3(-1,1,1);		//left top back
	vertices[23].norm = D3DXVECTOR3(-1,0,0);		

	//calculate normals
	vertices[0].norm = D3DXVECTOR3(-1,1,1);
	vertices[3].norm = D3DXVECTOR3(-1,1,-1);
	vertices[4].norm = D3DXVECTOR3(1,1,1);
	vertices[7].norm = D3DXVECTOR3(1,1,-1);

	vertices[1].norm = D3DXVECTOR3(-1,-1,1);
	vertices[2].norm = D3DXVECTOR3(-1,-1,-1);
	vertices[5].norm = D3DXVECTOR3(1,-1,1);
	vertices[6].norm = D3DXVECTOR3(1,-1,-1);
}
*/

bool Cube::ClearTexture()
{
	m_pTex = NULL;
	return true;
}
