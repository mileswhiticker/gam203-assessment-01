#ifndef LINE_H
#define LINE_H

#include "Drawable.h"

#include <d3d9.h>
#include <d3d9types.h>

class Line : public Drawable
{
public:
	Line();
	Line(D3DXVECTOR3 a_Pos,D3DXVECTOR3 a_Vector);
	void SetPos(D3DXVECTOR3 a_Displacement);
	void SetVec(D3DXVECTOR3 a_Vector);
	void SetCol(D3DCOLOR a_Colour);
	//
	D3DXVECTOR3 GetPos();
	D3DXVECTOR3 GetVec();
	//
	void ToggleRotating();
	//
	virtual bool CreateObject(IDirect3DDevice9* a_pDevice);
	virtual void Render(float a_dt, IDirect3DDevice9* a_pDevice);
	//
	struct VertexData
	{
		D3DVECTOR pos;	// XYZ position
		D3DCOLOR col;	// Diffuse colour (aka. 'vert colour')
	};
	static const DWORD VERTEX_FORMAT_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	//
	void Normalise();
	void Zero();		//reset vector to (0,0,0)
	float m_RotVal;
	D3DXMATRIX m_ExtRotation;
	//
	void SetAdd(D3DXVECTOR3 a_Vector);
	D3DXVECTOR3 GetAdd(Line& a_Line);
	D3DXVECTOR3 GetSubtract(Line& a_Line);
	D3DXVECTOR3 GetCrossProduct(Line& a_Line);
	float GetAngleWith(Line& a_Line);
private:
	void UpdateLine();
	bool m_Rotating;
	D3DXMATRIX m_RotationMat;
	//
	D3DXMATRIX m_TranslationMat;
	//
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_Vector;
	D3DCOLOR m_Colour;
};

#endif