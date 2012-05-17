#ifndef RENDERLOGIC_H
#define RENDERLOGIC_H

#include "Renderer.h"
#include <vector>

#define DEMOSTART 1
#define SUBDEMOSTART 1

class Drawable;

typedef std::pair<std::string, RECT*> Title;

class RenderLogic
{
public:
	static RenderLogic& GetInstance()
	{
		static RenderLogic* instance = new RenderLogic();
		return *instance;
	}
	//
	void ShowDemo(short a_NewDemoNum);
	void ShowSubDemo(short a_SubDemoNum);
	void ShowNextDemo();
	//these two are called by the keypress callbacks
	void ShowNextSubDemo();
	void ShowPreviousSubDemo();
	//
	void Init(Renderer* a_Renderer);
	void CleanUp();
private:
	RenderLogic();
	Renderer* m_Renderer;
	//
	std::vector<Title*> m_Titles;
	//
	short m_CurDemoNum;			//colours, lighting, textures etc
	short m_SubDemoNum;			//shading, lighting types, etc
	//
	std::vector<Drawable*> m_Drawables;
};

#endif