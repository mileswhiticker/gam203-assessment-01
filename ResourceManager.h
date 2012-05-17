#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <list>

#include "Renderer.h"

typedef std::pair<std::string, RECT*> Title;

class Drawable;
class Cube;
class Line;
class Light;
class Teapot;

class ResMgr
{
public:
	static ResMgr& GetInstance()
	{
		static ResMgr* instance = new ResMgr;
		return *instance;
	}
	Cube* AddCube(bool a_Visible);
	Line* AddLine(bool a_Visible);
	Teapot* AddTeapot(bool a_Visible);
	//
	Title* AddTitle(std::string a_String, short a_Pos = 0, bool a_Visible = false);
	void AddTitle(Title* a_pTitle);
	void UpdateRect(Title* a_pTitle);
	bool ClearTitle(Title* a_Title);
	void ClearAllTitles();
	//
	void EnableLighting();
	void DisableLighting();
	Light* m_pLight;
	bool AddLight(Light* a_pLight);
	bool RemoveLight(Light* a_pLight);
	//
	void EnableFlatShading();
	void EnableGourardShading();
	//
	void ApplyCubeTexture(IDirect3DDevice9* a_pDev, Cube* a_pCube);
	void RemoveCubeTexture(IDirect3DDevice9* a_pDev, Cube* a_pCube);
	//
	bool Hide(Drawable* a_pObject);
	bool Show(Drawable* a_pObject);
	//
	void Init(Renderer* a_Renderer);
private:
	ResMgr();
	Renderer* m_Renderer;
	//
	typedef std::list<Drawable*> DrawableObjectList;
	DrawableObjectList m_Visible;
	DrawableObjectList m_Hidden;
};

#endif