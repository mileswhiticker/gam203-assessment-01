/////////////////////////////////////////////////////////////////////////
//
// GAM203
// Light class
// Light.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "Light.h"

#include <d3dx9.h>
#include <d3dx9math.h>
#include <iostream>

//
// Constructor
//
Light::Light()
: m_CircleRadius(0.0f)
, xCircleDir(-1)
, yCircleDir(-1)
{
  ZeroMemory(&m_pLight, sizeof(m_pLight));
}

//
// Destructor
//
Light::~Light()
{
}

//
// Initialises this light as an omnidirectional light
//
void Light::InitOmni()
{
	ZeroMemory(&m_pLight, sizeof(m_pLight));
	m_pLight.Type = D3DLIGHT_POINT;
	SetDiffuse(1.0f, 1.0f, 1.0f);
	SetSpecular(1.0f, 1.0f, 1.0f);
	SetRange(20.0f);
	SetAttenuation(1.0f);
	m_Pos.z = -2;
	m_Pos.x = -2;
	m_Pos.y = 0;
	ResetPos();
}

//
// Initialises this light as a spot light
//
void Light::InitSpot()
{
	ZeroMemory(&m_pLight, sizeof(m_pLight));
	m_pLight.Type = D3DLIGHT_SPOT;
	m_pLight.Direction = D3DXVECTOR3(0,-1,0);
	//SetDiffuse(1.0f, 1.0f, 1.0f);
	//SetSpecular(1.0f, 1.0f, 1.0f);
	SetDiffuse(1, 1, 1);
	SetSpecular(1, 1, 1);
	SetRange(20.0f);
	SetAttenuation(1.0f);
	m_pLight.Falloff = 1.0f;
	m_pLight.Theta = 2.0f;
	m_pLight.Phi = 3.0f;
	m_Pos.z = -2;
	m_Pos.x = 0;
	m_Pos.y = 2;
	ResetPos();

	//@TODO: Write me! Set up a spot light (D3DLIGHT_SPOT, remember to call SetCone()) in a similar way to InitOmni()
}

//
// Initialises this light as a directional light (eg. sun)
//
void Light::InitDirectional()
{
	ZeroMemory(&m_pLight, sizeof(m_pLight));
	m_pLight.Type = D3DLIGHT_DIRECTIONAL;
	m_pLight.Direction = D3DXVECTOR3(1,0,0);
	SetDiffuse(1, 1, 1);
	SetSpecular(1, 1, 1);
	SetRange(20.0f);
	SetAttenuation(1.0f);
}

//
// Light modification functions
//
void Light::SetPosition(float a_xPos, float a_yPos, float a_zPos)
{
	m_Pos.x = a_xPos;
	m_Pos.y = a_yPos;
	m_Pos.z = a_zPos;
	ResetPos();
}

void Light::ResetPos()
{
	m_pLight.Position.x = m_Pos.x;
	m_pLight.Position.y = m_Pos.y;
	m_pLight.Position.z = m_Pos.z;
}

void Light::SetPosition(const D3DVECTOR& a_pos)
{
  m_pLight.Position = a_pos;
}

void Light::SetDirection(const D3DVECTOR& a_dir)
{
	m_pLight.Direction = a_dir;
}

void Light::SetAmbient(float a_red, float a_green, float a_blue)
{
	m_pLight.Ambient = D3DXCOLOR(a_red, a_green, a_blue, 1.0f);
}

void Light::SetDiffuse(float a_red, float a_green, float a_blue)
{
	m_pLight.Diffuse = D3DXCOLOR(a_red, a_green, a_blue, 1.0f);
}

void Light::SetSpecular(float a_red, float a_green, float a_blue)
{
	m_pLight.Specular = D3DXCOLOR(a_red, a_green, a_blue, 1.0f);
}

void Light::SetRange(float a_range)
{
	m_pLight.Range = a_range;
}

void Light::SetAttenuation(float a_attenuationFactor)
{
	// MSDN: Typically, an application sets Attenuation0 to 0.0, Attenuation1 to a constant value, and Attenuation2 to 0.0
	m_pLight.Attenuation0 = 0.0f;  // Constant attenuation
	m_pLight.Attenuation1 = a_attenuationFactor;  // Linear attenuation over distance
	m_pLight.Attenuation2 = 0.0f;  // Quadratic attenuation
}

void Light::SetCone(float a_theta, float a_phi)
{
	m_pLight.Theta = a_theta;  // Angle of inner cone (radians away from light direction)
	m_pLight.Phi = a_phi;  // Angle of outer cone (radians away from light direction)
	m_pLight.Falloff = 1.0f;  // MSDN (D3DLIGHT9): For spot lights only; set this to 1.0f and forget about it
}

void Light::Update(float a_Dt)
{
	//short xCircleDir = -1;
	//short yCircleDir = -1;
	return;
	if(m_CircleRadius)
	{
		m_pLight.Position.x = m_CirclePos.x;
		//m_pLight.Position.y = m_CirclePos.y;
		//m_pLight.Position.z = m_CirclePos.z;
		if( (m_CirclePos.x-m_Pos.x) >= m_CircleRadius)
			xCircleDir = -1;
		else if( (m_CirclePos.x-m_Pos.x) <= -m_CircleRadius)
			xCircleDir = 1;
		if( (m_CirclePos.y-m_Pos.y) >= m_CircleRadius)
			yCircleDir = -1;
		else if( (m_CirclePos.y-m_Pos.y) <= -m_CircleRadius)
			yCircleDir = 1;
		m_CirclePos.x += m_CircleRadius*a_Dt*a_Dt*a_Dt*xCircleDir;
		m_CirclePos.y += m_CircleRadius*a_Dt*a_Dt*a_Dt*yCircleDir;
	}
	else
	{
		m_pLight.Position.x = m_Pos.x;
		m_pLight.Position.y = m_Pos.y;
		m_pLight.Position.z = m_Pos.z;
	}
}

void Light::SetCircling(float a_Radius)
{
	//circling across the x and z planes, y remains constant
	m_CircleRadius = a_Radius;
	m_CirclePos.x = -a_Radius;
	m_CirclePos.z = -a_Radius;
	m_CirclePos.y = m_Pos.y;
}