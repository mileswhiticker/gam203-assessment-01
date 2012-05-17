//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Cube class
// Cube.h
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#if !defined(CUBE_H)
#define CUBE_H

#include "Drawable.h"

/*
typedef struct _D3DMATERIAL9 {
    D3DCOLORVALUE   Diffuse;        // Diffuse color RGBA //
    D3DCOLORVALUE   Ambient;        // Ambient color RGB //
    D3DCOLORVALUE   Specular;       // Specular 'shininess' //
    D3DCOLORVALUE   Emissive;       // Emissive color RGB //
    float           Power;          // Sharpness if specular highlight //
} D3DMATERIAL9;
*/

class Cube : public Drawable
{
public:
	Cube();
	struct VertexData
	{
		D3DVECTOR pos;	// XYZ position
		D3DVECTOR norm;	// unit vector in facing direction
		D3DCOLOR col;	// Diffuse colour (aka. 'vert colour')    
		FLOAT tu, tv;	// The texture coordinates

	};
	static const DWORD VERTEX_FORMAT_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1;
	//
	virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
	bool CreateObject(IDirect3DDevice9* a_pDevice, LPDIRECT3DTEXTURE9* a_pTex);
	virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice);
	//
	bool ClearTexture();
	//
	D3DXMATRIX m_ModelToWorld;
	bool m_RotatingX;
	bool m_RotatingY;
	bool m_RotatingZ;
	float xRot;
	float yRot;
	float zRot;
	//
	float xyz_Scale;
	D3DXVECTOR3 m_Pos;
	//
	short m_CyclingAmbientDir;
	short m_CyclingDiffuseDir;
	short m_CyclingSpecularDir;
	short m_CyclingEmissiveDir;
	D3DMATERIAL9 m_Mat;
	void ResetMaterial();
	//
	bool m_LoadTex;
private:
	LPDIRECT3DTEXTURE9* m_pTex;
};

#endif  // CUBE_H
