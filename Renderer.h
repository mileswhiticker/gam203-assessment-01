/////////////////////////////////////////////////////////////////////////
//
// GAM203
// Renderer class
// Renderer.h
// 
// Scott Taylor
// Qantm College
//
//////////////////////////////////////////////////////////////////////////

#if !defined(RENDERER_H)
#define RENDERER_H

#include <list>
#include <d3d9.h>
#include <d3d9types.h>
#include <D3dx9core.h>

#include <vector>

class Timer;
class Drawable;
class Light;
struct IDirect3DDevice9;

class Renderer
{
public:
	Renderer(IDirect3DDevice9* a_pDevice);
	~Renderer();
	bool Render(float a_dt);
	//
	bool AddObject(Drawable* a_pObject);
	bool RemoveObject(Drawable* a_pObject);
	//
	bool AddLight(Light* a_pLight);
	bool RemoveLight(Light* a_pLight);
	//
	RECT* GetTitleRect(std::string a_String);
	std::vector< std::pair<std::string, RECT*>* > m_Titles;
	//
	void SetRS(D3DRENDERSTATETYPE State,DWORD Value);
	IDirect3DDevice9* GetDevice();
	//
	float FPS;
private:
	IDirect3DDevice9* m_pDevice;
	//
	typedef std::list<Drawable*> DrawableObjectList;
	DrawableObjectList m_drawableObjects;
	//
	typedef std::list<Light*> LightList;
	LightList m_pLights;
	//
	D3DXMATRIX m_WorldToView;
	D3DXMATRIX m_ViewToScreen;
	//
	LPD3DXFONT m_DefaultFont;
	Timer* m_Timer;
	float m_LastT;
	float m_TLeftFPS;
	float FPS_Temp;
};

#endif  // RENDERER_H

