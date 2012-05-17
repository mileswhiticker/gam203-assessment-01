#include "Cube.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "RenderLogic.h"
#include "Teapot.h"

RenderLogic::RenderLogic()
:	m_CurDemoNum(0)
,	m_SubDemoNum(0)
{
	//
}

void RenderLogic::Init(Renderer* a_Renderer)
{
	m_Renderer = a_Renderer;

	//old
	//primary demonstration cube
	m_Drawables.push_back(ResMgr::GetInstance().AddCube(true));
	((Cube*)m_Drawables.back())->m_RotatingX = true;
	((Cube*)m_Drawables.back())->m_RotatingY = true;
	((Cube*)m_Drawables.back())->m_RotatingZ = true;
	//second, small cube (used for spot demo)
	m_Drawables.push_back(ResMgr::GetInstance().AddCube(false));
	((Cube*)m_Drawables.back())->xyz_Scale = 0.5f;
	((Cube*)m_Drawables.back())->m_Pos.x = 1;
	((Cube*)m_Drawables.back())->m_Pos.y = 2;
	((Cube*)m_Drawables.back())->m_Pos.z = 0;
	((Cube*)m_Drawables.back())->m_RotatingX = true;
	((Cube*)m_Drawables.back())->m_RotatingY = true;
	((Cube*)m_Drawables.back())->m_RotatingZ = true;
	//teapot (used for spot demo)
	m_Drawables.push_back(ResMgr::GetInstance().AddTeapot(false));
	((Teapot*)m_Drawables.back())->m_Pos.x = -1;
	((Teapot*)m_Drawables.back())->m_Pos.y = -2;
	((Teapot*)m_Drawables.back())->m_Pos.z = -1;

	//new
}

void RenderLogic::CleanUp()
{
	ResMgr resource_manager = ResMgr::GetInstance();
	resource_manager.ClearAllTitles();
	while(m_Titles.size())
	{
		m_Titles.pop_back();
	}
	delete resource_manager.m_pLight;
	while(m_Drawables.size())
	{
		delete m_Drawables.back();
		m_Drawables.pop_back();
	}
}
