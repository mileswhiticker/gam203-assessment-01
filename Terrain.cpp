//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Terrain class
// Terrain.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "Terrain.h"

#include <d3dx9math.h>

#include <assert.h>
#include <stdlib.h>

static const float TERRAIN_WIDTH_X = 16.0f;
static const float TERRAIN_WIDTH_Z = 16.0f;

Terrain::~Terrain()
{
  if (m_pHeightData)
  {
    delete m_pHeightData;
    m_pHeightData = NULL;
  }

  if (m_pVertData)
  {
    delete m_pVertData;
    m_pVertData = NULL;
  }

  if (m_pIndexData)
  {
    delete m_pIndexData;
    m_pIndexData = NULL;
  }
}

bool Terrain::CreateObject(IDirect3DDevice9* a_pDevice)
{
  if (!a_pDevice)
  {
    return false;  // No device passed in
  }

  //@HACK: Set up some hacked terrain data
  m_gridSizeX = 16;
  m_gridSizeZ = 16;

  m_vertCount = m_gridSizeX * m_gridSizeZ;
  m_indexCount = (m_gridSizeX - 1) * (m_gridSizeZ - 1) * 6;
  m_primCount = m_indexCount / 3;

	// Create our height map data
	if (!CreateHeightMap())
	{
		return false;
	}

  // Create a vertex buffer
  HRESULT result = a_pDevice->CreateVertexBuffer(sizeof(VertexData) * m_vertCount, 0, VERTEX_FORMAT_FVF, D3DPOOL_DEFAULT, &m_pVertexBuf, NULL);
  if (result != D3D_OK)
  {
    return false;
  }

  // Create an index buffer
  a_pDevice->CreateIndexBuffer(sizeof(unsigned short) * m_indexCount, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIndexBuf, NULL);
  if (result != D3D_OK)
  {
    // Clean up before return
    m_pVertexBuf->Release();
    m_pVertexBuf = NULL;
    return false;
  }

  // Create terrain vertex data
  m_pVertData = new VertexData[m_vertCount];

	for (long posZ = 0; posZ < m_gridSizeZ; ++posZ)
	{
		for (long posX = 0; posX < m_gridSizeX; ++posX)
		{
			const long vertIndex = posZ * m_gridSizeX + posX;
			VertexData& vert = m_pVertData[vertIndex];

			vert.pos = D3DXVECTOR3(posX * TERRAIN_WIDTH_X / (m_gridSizeX - 1), m_pHeightData[vertIndex], posZ * TERRAIN_WIDTH_Z / (m_gridSizeZ - 1));
			vert.norm = D3DXVECTOR3(0.0f,1.0f,0.0f);
			vert.col = D3DCOLOR_ARGB(255, rand() % 100 + 100, rand() % 100 + 150, rand() % 50 + 50);
		}
	}

  // Create terrain index data
  m_pIndexData = new unsigned short[m_indexCount];
  long curIndex = 0;

  for (short posZ = 0; posZ < m_gridSizeZ - 1; ++posZ)
  {
    for (short posX = 0; posX < m_gridSizeX - 1; ++posX)
    {
      const unsigned short startVertIndex = posZ * m_gridSizeX + posX;

      // First triangle
      m_pIndexData[curIndex++] = startVertIndex;
      m_pIndexData[curIndex++] = startVertIndex + m_gridSizeX;
      m_pIndexData[curIndex++] = startVertIndex + 1;

      // Second triangle
      m_pIndexData[curIndex++] = startVertIndex + 1;
      m_pIndexData[curIndex++] = startVertIndex + m_gridSizeX;
      m_pIndexData[curIndex++] = startVertIndex + m_gridSizeX + 1;
    }
  }

  // Ensure we stored exactly as many values as expected
  assert(curIndex == m_indexCount);

  // Copy vertex data into vertex buffer
  // Don't bother checking the return value of Lock(), assume it works :/
  void* pLockedData = NULL;
  m_pVertexBuf->Lock(0, sizeof(VertexData) * m_vertCount, &pLockedData, 0);
  memcpy(pLockedData, m_pVertData, sizeof(VertexData) * m_vertCount);
  m_pVertexBuf->Unlock();
  pLockedData = NULL;

  // Copy index data into index buffer
  // Don't bother checking the return value of Lock(), assume it works :/
  m_pIndexBuf->Lock(0, sizeof(short) * m_indexCount, &pLockedData, 0);
  memcpy(pLockedData, m_pIndexData, sizeof(short) * m_indexCount);
  m_pIndexBuf->Unlock();
  pLockedData = NULL;

  return true;
}

void Terrain::Render(float a_dt, IDirect3DDevice9* a_pDevice)
{
  if (a_pDevice && m_pVertexBuf && m_pIndexBuf)
  {
    // Set up a material to use
    D3DMATERIAL9 mtl;
    ZeroMemory(&mtl, sizeof(mtl));
    mtl.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    //mtl.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//mtl.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//mtl.Emissive = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
    a_pDevice->SetMaterial(&mtl);

    a_pDevice->SetTexture(0, NULL);  // No texture

    // Set our world matrix
    D3DXMATRIX modelToWorld;
    D3DXMatrixIdentity(&modelToWorld);  // Position us at world origin
    D3DXMatrixTranslation(&modelToWorld, -TERRAIN_WIDTH_X / 2, -5, 2);  // Hack: overwrite our position set above

    a_pDevice->SetTransform(D3DTS_WORLD, &modelToWorld);

    // Tell DirectX about the vertex data
    a_pDevice->SetStreamSource(0, m_pVertexBuf, 0, sizeof(VertexData));
    a_pDevice->SetFVF(VERTEX_FORMAT_FVF);

    // Tell DirectX about the index data
    a_pDevice->SetIndices(m_pIndexBuf);

    // Draw the terrain
    a_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vertCount, 0, m_primCount);
  }
}

//
// Generates a height map with the current class settings
//
bool Terrain::CreateHeightMap()
{
  assert(m_gridSizeX > 1 && m_gridSizeZ > 1);
  if (!(m_gridSizeX > 1 && m_gridSizeZ > 1))
  {
    return false;
  }

  // Clean up if memory was already allocated
  if (m_pHeightData)
  {
    delete m_pHeightData;
    m_pHeightData = NULL;
  }

  // Allocate new memory for height values
  m_pHeightData = new float[m_vertCount];
  if (!m_pHeightData)
  {
    return false;
  }

  // Fill with random values
  for (long gridIndex = 0; gridIndex < m_vertCount; ++gridIndex)
  {
    const float RANDOM_HEIGHT = 8.0f;
    const float HEIGHT_OFFSET = -RANDOM_HEIGHT / 2;
    m_pHeightData[gridIndex] = RANDOM_HEIGHT * (float)rand() / RAND_MAX + HEIGHT_OFFSET;
  }

  SmoothHeightMap();

  return true;
}

//
// Smooths out values in height map
//
void Terrain::SmoothHeightMap()
{
	//have this passed in as a param later
	long passes = 5;

	//loop for number of passes specified
	while(passes--)
	{
		//new, smoothed heightmap
		float* newHeightMap = new float[m_vertCount];
		//loop through heightmap, smoothing each vertex as we go
		for (long gridIndex = 0; gridIndex < m_vertCount; gridIndex++)
		{
			//get average height of surrounding vertices
			short numAdj = 0;
			float sumAdj = 0;
			//above left
			if((gridIndex + m_gridSizeX - 1) < m_vertCount && (gridIndex + m_gridSizeX - 1) > 0)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex + m_gridSizeX - 1];
			}
			//above
			if((gridIndex + m_gridSizeX) < m_vertCount)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex + m_gridSizeX];
			}
			//above right
			if((gridIndex + m_gridSizeX + 1) < m_vertCount)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex + m_gridSizeX + 1];
			}
			//left
			if((gridIndex - 1) > 0)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex - 1];
			}
			//right
			if((gridIndex + 1) < m_vertCount)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex + 1];
			}
			//below left
			if((gridIndex - m_gridSizeX - 1) > 0)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex - m_gridSizeX - 1];
			}
			//below
			if((gridIndex - m_gridSizeX) > 0)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex - m_gridSizeX];
			}
			//below right
			if((gridIndex - m_gridSizeX + 1) > 0)
			{
				numAdj++;
				sumAdj += m_pHeightData[gridIndex - m_gridSizeX + 1];
			}
			float averageAdj = sumAdj / (float)numAdj;

			//store average height of this vertex and average height of surrounding vertices in the new heightmap
			newHeightMap[gridIndex] = (averageAdj + m_pHeightData[gridIndex]) / 2;
		}
		delete m_pHeightData;
		m_pHeightData = newHeightMap;
	}
}

void Terrain::calculateNormals()
{
	//
}