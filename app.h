#ifndef APP_H
#define APP_H
/*
#include "Light.h"

#include "Triangle.h"
#include "Cube.h"
#include "Terrain.h"
#include "MeshX.h"
#include "Line.h"
#include "MeshBasic.h"
*/
#include "RenderLogic.h"
#include "ResourceManager.h"

class WndwMgr;
class RenderLogic;
class Timer;
typedef std::pair<std::string, RECT*> Title;

class cApp
{
public:
	cApp(HINSTANCE a_hInst);
	//
	bool update(float a_dt);
	void cleanUp();
	//
	Renderer* m_Renderer;
	//
	Timer* m_Timer;
	bool m_AutoRunThrough;
private:
	float m_CountDown;
	float m_LastT;
	//
	ResMgr& res_manager;
	WndwMgr& window_manager;
	RenderLogic& render_logic;
};

namespace utils
{
	//
}

#endif