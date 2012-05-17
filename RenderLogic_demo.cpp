#include "RenderLogic.h"
#include "ResourceManager.h"
#include <iostream>

void RenderLogic::ShowNextDemo()
{
	short newDemo = m_CurDemoNum + 1;
	ShowSubDemo(SUBDEMOSTART);
	//std::cout << "newDemo: " << newDemo << std::endl;
	if(newDemo > 5)
	{
		newDemo--;
	}
	ShowDemo(newDemo);
}

void RenderLogic::ShowDemo(short a_NewDemoNum)
{
	//std::cout << "attempting to show demo " << a_NewDemoNum << std::endl;
	bool success = false;
	ResMgr resource_manager = ResMgr::GetInstance();
	//remove all titles first
	resource_manager.ClearAllTitles();
	m_Titles.erase(m_Titles.begin(),m_Titles.end());
	//undo settings from old demo
	switch(m_CurDemoNum)
	{
	default:
	case(0):
		{
			a_NewDemoNum = 1;
			//fall through
		}
	case(1):
		{
			//Colour
			break;
		}
	case(2):
		{
			//Lighting
			break;
		}
	case(3):
		{
			//Texturing
			resource_manager.Hide(m_Drawables[1]);
			resource_manager.Hide(m_Drawables[2]);
			break;
		}
	case(4):
		{
			//Blending
			resource_manager.Hide(m_Drawables[1]);
			resource_manager.Hide(m_Drawables[2]);
			break;
		}
	}
	//apply settings for the new demo
	switch(a_NewDemoNum)
	{
	default:
	case(0):
		{
			a_NewDemoNum = 1;
			//fall through
		}
	case(1):
		{
			//Colour
			m_Titles.push_back(resource_manager.AddTitle("Colour",0,true));
			success = true;
			break;
		}
	case(2):
		{
			//Lighting
			m_Titles.push_back(resource_manager.AddTitle("Lighting",0,true));
			success = true;
			break;
		}
	case(3):
		{
			//Texturing
			m_Titles.push_back(resource_manager.AddTitle("Texturing",0,true));
			resource_manager.Show(m_Drawables[1]);
			resource_manager.Show(m_Drawables[2]);
			success = true;
			break;
		}
	case(4):
		{
			//Blending
			m_Titles.push_back(resource_manager.AddTitle("Blending",0,true));
			resource_manager.Show(m_Drawables[1]);
			resource_manager.Show(m_Drawables[2]);
			success = true;
			break;
		}
	}
	if(success)
	{
		m_CurDemoNum = a_NewDemoNum;
		ShowSubDemo(SUBDEMOSTART);
	}
	return;
}
