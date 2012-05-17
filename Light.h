//////////////////////////////////////////////////////////////////////////
//
// GAM203
// Light class
// Light.h
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#if !defined(LIGHT_H)
#define LIGHT_H

#include <d3d9.h>
#include <d3d9types.h>
#include "D3dx9math.h"

struct D3DXCOLOR;  // #include <d3dx9math.h>

class Light
{
public:
	Light();
	~Light();

	// Light initialisation functions
	void InitOmni();
	void InitSpot();
	void InitDirectional();
	//
	void Update(float a_Dt);
	void SetCircling(float a_Radius);

	// Light modification functions
	void SetPosition(float a_xPos, float a_yPos, float a_zPos);
	void SetPosition(const D3DVECTOR& a_pos);
	void SetDirection(const D3DVECTOR& a_dir);  // Spot / directional only
	void SetAmbient(float a_red, float a_green, float a_blue);
	void SetDiffuse(float a_red, float a_green, float a_blue);
	void SetSpecular(float a_red, float a_green, float a_blue);
	void SetRange(float a_range);  // From 0.0f .. infinite
	void SetAttenuation(float a_attenuationFactor);  // From 0.0f .. infinite
	void SetCone(float a_theta, float a_phi); // Spot lights only

	const D3DLIGHT9& GetLightData() { return m_pLight; }

protected:
	void ResetPos();
	//
	D3DLIGHT9 m_pLight;
	D3DXVECTOR3 m_Pos;
	D3DXVECTOR3 m_CirclePos;
	short xCircleDir;
	short yCircleDir;
	float m_CircleRadius;
};

#endif  // LIGHT_H
