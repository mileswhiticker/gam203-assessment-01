//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Terrain class
// Terrain.h
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#if !defined(TERRAIN_H)
#define TERRAIN_H

#include "Drawable.h"

#include <d3d9.h>
#include <d3d9types.h>

class Terrain : public Drawable
{
public:
	// Vertex format we will use to describe our vertices (must match FVF format below)
	struct VertexData
	{
		D3DVECTOR pos;		// XYZ position
		D3DVECTOR norm;		// vertex normal
		D3DCOLOR col;		// Diffuse colour (aka. 'vert colour')
	};

	// DirectX's way of identifying what's in our vertex structure (we bitwise OR these values)
	static const DWORD VERTEX_FORMAT_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

	virtual ~Terrain();

public:
	virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
	virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice);

private:
	bool CreateHeightMap();
	void SmoothHeightMap();

protected:
	void calculateNormals();
	float* m_pHeightData;
	int m_gridSizeX;
	int m_gridSizeZ;

	long m_vertCount;
	long m_indexCount;
	long m_primCount;

	VertexData* m_pVertData;
	unsigned short* m_pIndexData;
};

#endif  // TERRAIN_H

