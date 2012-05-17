#include "RenderSubDemo.hpp"
#include "ResourceManager.h"
#include "Cube.h"

RenderSubDemo::RenderSubDemo(Cube* a_pCube)
:	m_pCube(a_pCube)
{
	a_pCube->m_Mat.Ambient = D3DXCOLOR(0,0,0,0);
	a_pCube->m_Mat.Specular = D3DXCOLOR(1,1,1,1);
	a_pCube->m_Mat.Diffuse = D3DXCOLOR(1,1,1,1);
}

RenderSubDemo::~RenderSubDemo()
{
	ResMgr res_manager = ResMgr::GetInstance();
	while(Titles.size())
		res_manager.ClearTitle(Titles.at(Titles.size()-1));
}

void RenderSubDemo::Update(float Dt)
{
	//
}

void RenderSubDemo::Enable()
{
	ResMgr resource_manager = ResMgr::GetInstance();
	for(unsigned short i=0;i<Titles.size();i++)
		resource_manager.AddTitle(Titles[i]);
	resource_manager.AddLight(m_pLight);
}

void RenderSubDemo::Disable()
{
	ResMgr resource_manager = ResMgr::GetInstance();
	for(unsigned short i=0;i<Titles.size();i++)
		resource_manager.ClearTitle(Titles[i]);
	resource_manager.RemoveLight(m_pLight);
}
