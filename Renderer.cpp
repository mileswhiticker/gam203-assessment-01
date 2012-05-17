/////////////////////////////////////////////////////////////////////////
//
// GAM203
// Renderer class
// Renderer.cpp
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#include "Renderer.h"

#include "Drawable.h"
#include "Light.h"
#include "dxmgr.h"
#include "Timer.h"
#include "Cube.h"

#include <d3d9.h>
#include <d3dx9.h>

#include <iostream>
#include <string>
#include <sstream>

//
// Constructor
//
Renderer::Renderer(IDirect3DDevice9* a_pDevice)
:	m_Timer(new Timer())
,	m_TLeftFPS(1.0f)
,	m_pDevice(a_pDevice)
{
	// Create our camera (view-space) transform for this frame
	D3DXVECTOR3 lookFromPos(0, 0, -10);
	D3DXVECTOR3 lookAtPos(0, 0, 0);
	D3DXVECTOR3 upVec(0, 1, 0);
	D3DXMatrixLookAtLH(&m_WorldToView, &lookFromPos, &lookAtPos, &upVec);

	// Create our projection matrix for this frame
	D3DXMatrixPerspectiveFovLH(&m_ViewToScreen, 3.14f / 4, 1, 1, 5000);

	// Set up common render states
	a_pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	a_pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESS);
	a_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	a_pDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	a_pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(0,0,0));	//ambient lighting will use the already made D3DLIGHT9
	//a_pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);

	//setup default font
	D3DXCreateFont( DXMgr::GetInstance().GetDevice(), 20, 0, FW_BOLD, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_DefaultFont );
}

//
// Destructor
//
Renderer::~Renderer()
{
	//
}

//
// Adds an object to the renderer
// Returns true if successful
//
bool Renderer::AddObject(Drawable* a_pObject)
{
  if (!a_pObject)
  {
    return false;
  }

  //@TODO: assert() that a_pObject isn't already in the list...
  //       It may be helpful to write your own bool Renderer::HasObject(a_pObject).

  m_drawableObjects.push_back(a_pObject);

  return true;
}

//
// Removes an object from the renderer
// Returns true if successful
//
bool Renderer::RemoveObject(Drawable* a_pObject)
{
	// Look for this object in our list
	for (DrawableObjectList::iterator iter = m_drawableObjects.begin(); iter != m_drawableObjects.end(); ++iter)
	{
		Drawable* pElem = *iter;
		if (pElem == a_pObject)
		{
			// Found the object! Remove it from the list
			m_drawableObjects.erase(iter);
			return true;
		}
	}
	return false;  // Not found
}

//
// Adds a light to the renderer
// Returns true if successful
//
bool Renderer::AddLight(Light* a_pLight)
{
	if (!a_pLight)
		return false;
	m_pLights.push_back(a_pLight);
	return true;
}

//
// Removes a light from the renderer
// Returns true if successful
//
bool Renderer::RemoveLight(Light* a_pLight)
{
	// Look for this light in our list
	for (LightList::iterator iter = m_pLights.begin(); iter != m_pLights.end(); ++iter)
	{
		Light* pElem = *iter;
		if (pElem == a_pLight)
		{
			// Found the light! Remove it from the list
			m_pLights.erase(iter);
			return true;
		}
	}
	return false;  // Not found
}

RECT* Renderer::GetTitleRect(std::string a_String)
{
	RECT* rect = new RECT;
	rect->top = 0;
	rect->left = 0;
	rect->right = 0;
	rect->bottom = 0;
	int len = a_String.size()+1;
	wchar_t *wText = new wchar_t[len];
	memset(wText,0,len);
	MultiByteToWideChar(CP_ACP, NULL, a_String.c_str(), -1, wText,len );
	m_DefaultFont->DrawText(NULL, (LPCTSTR)a_String.c_str(), -1, rect, DT_CALCRECT, D3DCOLOR_XRGB(255,255,255));
	return rect;
}

//
// Renders all objects
// Returns true if successful
//
bool Renderer::Render(float a_dt)
{
	if (!m_pDevice)
	{
		return false;
	}

	// Clear backbuffer
	m_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(15, 15, 128), 1.0f, 0);

	//setup viewspace (camera)
	m_pDevice->SetTransform(D3DTS_VIEW, &m_WorldToView);

	//setup view projection matrix
	m_pDevice->SetTransform(D3DTS_PROJECTION, &m_ViewToScreen);

	// Begin rendering
	m_pDevice->BeginScene();

	//work out dt
	float curT = (float)m_Timer->GetTime();
	float dt = curT - (float)m_LastT;
	m_LastT = curT;
	//update temporary output fps
	if(m_TLeftFPS < 0.0f)
	{
		m_TLeftFPS = 1.0f;
		FPS_Temp = 1/(1000*dt);
		//std::cout << dt << " , " << FPS_Temp << std::endl;
	}
	else
	{
		m_TLeftFPS -= 1000*dt;
	}
	//output fps
	std::stringstream ss;
	ss << "FPS:" << FPS_Temp;
	RECT fpsRect;
	fpsRect.bottom = (LONG)0.0;
	fpsRect.top = (LONG)0.0;
	fpsRect.right = (LONG)650.0;
	fpsRect.left = (LONG)650.0;
	m_DefaultFont->DrawTextA(NULL, (LPCSTR)ss.str().c_str(), -1, &fpsRect, DT_CALCRECT, D3DCOLOR_XRGB(255,255,255));
	m_DefaultFont->DrawTextA(NULL, (LPCSTR)ss.str().c_str(), -1, &fpsRect, 0, D3DCOLOR_XRGB(255,255,255));

	DWORD pVal;
	m_pDevice->GetRenderState(D3DRS_LIGHTING,&pVal);
	//setup lighting
	if(pVal == TRUE)
	{
		int curLightId = 0;
		for (LightList::iterator iter = m_pLights.begin(); iter != m_pLights.end(); ++iter)
		{
			Light* pElem = *iter;
			//pElem->Update(FPS_Temp);
			HRESULT result = m_pDevice->SetLight(curLightId, &pElem->GetLightData());
			if(result != D3D_OK)
				return false;
			result = m_pDevice->LightEnable(curLightId, TRUE);
			if(result != D3D_OK)
				return false;
			++curLightId;
			//std::cout << "lighting is enabled" << std::endl;
			/*
			const D3DLIGHT9* light = &pElem->GetLightData();
			std::cout << "	light" << std::endl;
			std::cout << "ambient: " << pElem->GetLightData().Ambient.r << "," << pElem->GetLightData().Ambient.g << "," << pElem->GetLightData().Ambient.b << std::endl;
			std::cout << "specular: " << pElem->GetLightData().Specular.r << "," << pElem->GetLightData().Specular.g << "," << pElem->GetLightData().Specular.b << std::endl;
			std::cout << "diffuse: " << pElem->GetLightData().Diffuse.r << "," << pElem->GetLightData().Diffuse.g << "," << pElem->GetLightData().Diffuse.b << std::endl;
			*/
		}
	}
	else
	{
		int curLightId = 0;
		for (LightList::iterator iter = m_pLights.begin(); iter != m_pLights.end(); ++iter)
		{
			Light* pElem = *iter;
			//pElem->Update(FPS_Temp);
			HRESULT result = m_pDevice->SetLight(curLightId, &pElem->GetLightData());
			if(result != D3D_OK)
				return false;
			result = m_pDevice->LightEnable(curLightId, FALSE);
			if(result != D3D_OK)
				return false;
			//std::cout << "lighting is disabled" << std::endl;
		}
	}

	// Render world
	for (DrawableObjectList::iterator iter = m_drawableObjects.begin(); iter != m_drawableObjects.end(); ++iter)
	{
		Drawable* pElem = *iter;
		pElem->Render(a_dt, m_pDevice);
		/*
		std::cout << "	mat" << std::endl;
		std::cout << "ambient: " << ((Cube*)pElem)->m_Mat.Ambient.r << "," << ((Cube*)pElem)->m_Mat.Ambient.g << "," << ((Cube*)pElem)->m_Mat.Ambient.b << std::endl;
		std::cout << "specular: " << ((Cube*)pElem)->m_Mat.Specular.r << "," << ((Cube*)pElem)->m_Mat.Specular.g << "," << ((Cube*)pElem)->m_Mat.Specular.b << std::endl;
		std::cout << "diffuse: " << ((Cube*)pElem)->m_Mat.Diffuse.r << "," << ((Cube*)pElem)->m_Mat.Diffuse.g << "," << ((Cube*)pElem)->m_Mat.Diffuse.b << std::endl;
		std::cout << "emissive: " << ((Cube*)pElem)->m_Mat.Emissive.r << "," << ((Cube*)pElem)->m_Mat.Emissive.g << "," << ((Cube*)pElem)->m_Mat.Emissive.b << std::endl;
		*/
	}

	//render titles
	for(unsigned short n=0;n<m_Titles.size();n++)
	{
		int len = m_Titles[n]->first.size()+1;
		wchar_t *wText = new wchar_t[len];
		memset(wText,0,len);
		MultiByteToWideChar(CP_ACP, NULL, m_Titles[n]->first.c_str(), -1, wText,len );
		m_DefaultFont->DrawText(NULL, (LPCWSTR)wText, -1, m_Titles[n]->second, 0, D3DCOLOR_XRGB(255,255,255));
	}

	// Finish rendering
	m_pDevice->EndScene();

	// Display the backbuffer
	m_pDevice->Present(NULL, NULL, NULL, NULL);

	m_LastT = m_Timer->GetTime();

	return true;
}

void Renderer::SetRS(D3DRENDERSTATETYPE State,DWORD Value)
{
	m_pDevice->SetRenderState(State, Value);
}

IDirect3DDevice9* Renderer::GetDevice()
{
	return m_pDevice;
}
