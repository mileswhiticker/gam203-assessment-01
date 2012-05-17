#include "RenderLogic.h"
#include "ResourceManager.h"
#include <iostream>
#include "Cube.h"
#include "Light.h"

void RenderLogic::ShowNextSubDemo()
{
	short newSubDemo = m_SubDemoNum + 1;
	switch(m_CurDemoNum)
	{
	default:
	case(0):
		{
			//
			newSubDemo = SUBDEMOSTART;
			ShowNextDemo();
			break;
		}
	case(1):
		{
			//colour
			if(newSubDemo > 3)
			{
				newSubDemo = SUBDEMOSTART;
				ShowNextDemo();
				//return;
			}
			break;
		}
	case(2):
		{
			//lighting
			if(newSubDemo > 10)
			{
				newSubDemo = SUBDEMOSTART;
				ShowNextDemo();
				//return;
			}
			break;
		}
	case(3):
		{
			//textures
			if(newSubDemo > 1)
			{
				newSubDemo = SUBDEMOSTART;
				ShowNextDemo();
				//return;
			}
			break;
		}
	case(4):
		{
			//blending
			if(newSubDemo > 3)
			{
				newSubDemo = SUBDEMOSTART;
				ShowNextDemo();
				//return;
			}
			break;
		}
	}
	ShowSubDemo(newSubDemo);
}

void RenderLogic::ShowSubDemo(short a_SubDemoNum)
{
	//std::cout << "attempting to show subdemo " << a_SubDemoNum << std::endl;
	bool success = false;
	ResMgr resource_manager = ResMgr::GetInstance();
	//remove titles except for the main one
	while(m_Titles.size()>1)
	{
		resource_manager.ClearTitle(m_Titles[1]);
		m_Titles.erase(m_Titles.begin()+1);
	}
	//undo settings from old subdemo
	switch(m_CurDemoNum)
	{
	default:
	case(0):
		{
			m_CurDemoNum = 1;
			//fall through
		}
	case(1):
		{
			//Colour
			switch(m_SubDemoNum)
			{
			case(1):
				{
					//
					break;
				}
			case(2):
				{
					resource_manager.EnableGourardShading();
					resource_manager.DisableLighting();
					break;
				}
			case(3):
				{
					//
					resource_manager.DisableLighting();
					break;
				}
			}
			break;
		}
	case(2):
		{
			//Lighting
			switch(m_SubDemoNum)
			{
			case(1):
				{
					//point light
					resource_manager.DisableLighting();
					break;
				}
			case(2):
				{
					//directional light
					//((Cube*)m_Drawables.back())->m_Mat.Ambient = D3DXCOLOR(1,1,1,1);
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					break;
				}
			case(3):
				{
					//spot light
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					resource_manager.Hide(m_Drawables[1]);
					resource_manager.Hide(m_Drawables[2]);
					break;
				}
			case(4):
				{
					//ambient light
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					break;
				}
			case(5):
				{
					//diffuse light
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					break;
				}
			case(6):
				{
					//specular light
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					break;
				}
			case(7):
				{
					//ambient material
					((Cube*)m_Drawables[0])->m_CyclingAmbientDir = 0;
					((Cube*)m_Drawables.front())->ResetMaterial();
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					((Cube*)m_Drawables.front())->m_RotatingX = true;
					((Cube*)m_Drawables.front())->m_RotatingY = true;
					((Cube*)m_Drawables.front())->m_RotatingZ = true;
					break;
				}
			case(8):
				{
					//diffuse material
					((Cube*)m_Drawables[0])->m_CyclingDiffuseDir = 0;
					((Cube*)m_Drawables.front())->ResetMaterial();
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					((Cube*)m_Drawables.front())->m_RotatingX = true;
					((Cube*)m_Drawables.front())->m_RotatingY = true;
					((Cube*)m_Drawables.front())->m_RotatingZ = true;
					break;
				}
			case(9):
				{
					//specular material
					((Cube*)m_Drawables[0])->m_CyclingSpecularDir = 0;
					((Cube*)m_Drawables.front())->ResetMaterial();
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					((Cube*)m_Drawables.front())->m_RotatingX = true;
					((Cube*)m_Drawables.front())->m_RotatingY = true;
					((Cube*)m_Drawables.front())->m_RotatingZ = true;
					break;
				}
			case(10):
				{
					//emissive material
					((Cube*)m_Drawables[0])->m_CyclingEmissiveDir = 0;
					((Cube*)m_Drawables.front())->ResetMaterial();
					resource_manager.m_pLight->InitOmni();
					resource_manager.DisableLighting();
					((Cube*)m_Drawables.front())->m_RotatingX = true;
					((Cube*)m_Drawables.front())->m_RotatingY = true;
					((Cube*)m_Drawables.front())->m_RotatingZ = true;
					break;
				}
			}
			break;
		}
	case(3):
		{
			switch(a_SubDemoNum)
			{
			default:
			case(1):
				{
					//textures
					resource_manager.RemoveCubeTexture(m_Renderer->GetDevice(),(Cube*)m_Drawables.front());
					resource_manager.Hide(m_Drawables[1]);
					resource_manager.Hide(m_Drawables[2]);
					break;
				}
			}
		}
	case(4):
		{
			switch(a_SubDemoNum)
			{
			default:
			case(1):
				{
					//additive blend
					//
					m_Renderer->SetRS(D3DRS_ALPHABLENDENABLE, FALSE);
					//m_Renderer->SetRS(D3DRS_SRCBLEND, D3DBLEND_ONE);
					//m_Renderer->SetRS(D3DRS_SRCBLEND, D3DBLEND_ZERO);
					break;
				}
			case(2):
				{
					//subtractive blend
					break;
				}
			case(3):
				{
					//blend 
					resource_manager.EnableLighting();
					resource_manager.Hide(m_Drawables[1]);
					resource_manager.Hide(m_Drawables[2]);
					//
					m_Renderer->SetRS(D3DRS_ALPHABLENDENABLE, FALSE);
					break;
				}
			}
		}
	}

	//apply settings for new subdemo
	switch(m_CurDemoNum)
	{
	default:
		{
			//
			return;
		}
	case(0):
		{
			//
			break;
		}
	case(1):
		{
			//Colour
			switch(a_SubDemoNum)
			{
			default:
			case(1):
				{
					//Vertex Colour
					m_Titles.push_back(resource_manager.AddTitle("Vertex colour",1,true));
					success = true;
					break;
				}
			case(2):
				{
					//Flat shading
					m_Titles.push_back(resource_manager.AddTitle("Flat shading",1,true));
					resource_manager.EnableLighting();
					resource_manager.EnableFlatShading();
					success = true;
					break;
				}
			case(3):
				{
					//Gourard shading
					m_Titles.push_back(resource_manager.AddTitle("Gourard shading",1,true));
					resource_manager.EnableLighting();
					success = true;
					break;
				}
			}
			break;
		}
	case(2):
		{
			//lighting
			switch(a_SubDemoNum)
			{
			default:
			case(0):
				{
					//
					success = true;
					break;
				}
			case(1):
				{
					//Point lighting
					m_Titles.push_back(resource_manager.AddTitle("Point lighting",1,true));
					resource_manager.EnableLighting();
					success = true;
					break;
				}
			case(2):
				{
					//Directional lighting
					m_Titles.push_back(resource_manager.AddTitle("Directional lighting",1,true));
					resource_manager.m_pLight->InitDirectional();
					resource_manager.EnableLighting();
					success = true;
					break;
				}
			case(3):
				{
					//Spot lighting
					m_Titles.push_back(resource_manager.AddTitle("Spot lighting",1,true));
					resource_manager.m_pLight->InitSpot();
					resource_manager.EnableLighting();
					resource_manager.Show(m_Drawables[1]);
					resource_manager.Show(m_Drawables[2]);
					success = true;
					break;
				}
			case(4):
				{
					//Ambient lighting
					m_Titles.push_back(resource_manager.AddTitle("Ambient lighting",1,true));
					resource_manager.EnableLighting();
					resource_manager.m_pLight->SetAmbient(1,1,1);
					((Cube*)m_Drawables[0])->m_Mat.Ambient = D3DXCOLOR(1,1,1,1);
					resource_manager.m_pLight->SetSpecular(0,0,0);
					resource_manager.m_pLight->SetDiffuse(0,0,0);
					success = true;
					break;
				}
			case(5):
				{
					//Diffuse lighting
					m_Titles.push_back(resource_manager.AddTitle("Diffuse lighting",1,true));
					resource_manager.EnableLighting();
					resource_manager.m_pLight->SetSpecular(0,0,0);
					success = true;
					break;
				}
			case(6):
				{
					//Specular lighting
					m_Titles.push_back(resource_manager.AddTitle("Specular lighting",1,true));
					resource_manager.EnableLighting();
					resource_manager.m_pLight->SetSpecular(2,2,2);
					resource_manager.m_pLight->SetDiffuse(0,0,0);
					success = true;
					break;
				}
			case(7):
				{
					//Ambient material
					resource_manager.EnableLighting();
					m_Titles.push_back(resource_manager.AddTitle("Ambient material",1,true));
					((Cube*)m_Drawables[0])->m_CyclingAmbientDir = 1;
					((Cube*)m_Drawables[0])->m_Mat.Specular = D3DXCOLOR(0,0,0,0);
					((Cube*)m_Drawables[0])->m_Mat.Diffuse = D3DXCOLOR(0,0,0,0);
					((Cube*)m_Drawables[0])->m_Mat.Ambient = D3DXCOLOR(1,1,1,1);
					resource_manager.m_pLight->SetAmbient(1,1,1);
					((Cube*)m_Drawables.front())->m_RotatingX = false;
					((Cube*)m_Drawables.front())->m_RotatingY = false;
					((Cube*)m_Drawables.front())->m_RotatingZ = false;
					success = true;
					break;
				}
			case(8):
				{
					//Diffuse material
					resource_manager.EnableLighting();
					m_Titles.push_back(resource_manager.AddTitle("Diffuse material",1,true));
					((Cube*)m_Drawables[0])->m_CyclingDiffuseDir = 1;
					((Cube*)m_Drawables[0])->m_Mat.Specular = D3DXCOLOR(0,0,0,0);
					resource_manager.m_pLight->SetDiffuse(1,1,1);
					((Cube*)m_Drawables.front())->m_RotatingX = false;
					((Cube*)m_Drawables.front())->m_RotatingY = false;
					((Cube*)m_Drawables.front())->m_RotatingZ = false;
					success = true;
					break;
				}
			case(9):
				{
					//Specular material
					resource_manager.EnableLighting();
					m_Titles.push_back(resource_manager.AddTitle("Specular material",1,true));
					((Cube*)m_Drawables[0])->m_CyclingSpecularDir = 1;
					((Cube*)m_Drawables[0])->m_Mat.Diffuse = D3DXCOLOR(0,0,0,0);
					resource_manager.m_pLight->SetSpecular(1,1,1);
					((Cube*)m_Drawables.front())->m_RotatingX = false;
					((Cube*)m_Drawables.front())->m_RotatingY = false;
					((Cube*)m_Drawables.front())->m_RotatingZ = false;
					success = true;
					break;
				}
			case(10):
				{
					//Emissive material
					resource_manager.EnableLighting();
					m_Titles.push_back(resource_manager.AddTitle("Emissive material",1,true));
					((Cube*)m_Drawables[0])->m_CyclingEmissiveDir = 1;
					((Cube*)m_Drawables[0])->m_Mat.Diffuse = D3DXCOLOR(0,0,0,0);
					((Cube*)m_Drawables[0])->m_Mat.Specular = D3DXCOLOR(0,0,0,0);
					((Cube*)m_Drawables.front())->m_RotatingX = false;
					((Cube*)m_Drawables.front())->m_RotatingY = false;
					((Cube*)m_Drawables.front())->m_RotatingZ = false;
					success = true;
					break;
				}
			}
			break;
		}
	case(3):
		{
			//textures
			switch(a_SubDemoNum)
			{
			default:
			case(1):
				{
					//textures
					resource_manager.EnableLighting();
					resource_manager.ApplyCubeTexture(m_Renderer->GetDevice(),(Cube*)m_Drawables.front());
					((Cube*)m_Drawables.front())->m_RotatingX = true;
					((Cube*)m_Drawables.front())->m_RotatingY = true;
					((Cube*)m_Drawables.front())->m_RotatingZ = true;
					break;
				}
			}
			break;
		}
	case(4):
		{
			//blending
			switch(a_SubDemoNum)
			{
			default:
			case(1):
				{
					//additive blending
					resource_manager.DisableLighting();
					//resource_manager.EnableLighting();
					//resource_manager.m_pLight->SetDiffuse(1,1,1);
					//((Cube*)m_Drawables[0])->m_Mat.Ambient = D3DXCOLOR(1,1,1,1);
					((Cube*)m_Drawables[0])->m_Mat.Diffuse = D3DXCOLOR(1,1,1,1);
					//((Cube*)m_Drawables[0])->m_Mat.Ambient = D3DXCOLOR(0,0,0,0);
					//
					resource_manager.Show(m_Drawables[1]);
					((Cube*)m_Drawables[1])->m_Pos.x = 0.5;
					((Cube*)m_Drawables[1])->m_Pos.y = 0.5;
					((Cube*)m_Drawables[1])->m_Pos.z = -2;
					resource_manager.Show(m_Drawables[2]);
					m_Renderer->SetRS(D3DRS_ALPHABLENDENABLE, TRUE);
					//
					//m_Renderer->SetRS(D3DRS_SRCBLEND, D3DBLEND_ONE);
					//m_Renderer->SetRS(D3DRS_SRCBLEND, D3DBLEND_ZERO);
					m_Renderer->SetRS(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					m_Renderer->SetRS(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
					m_Renderer->SetRS(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					((Cube*)m_Drawables.front())->m_RotatingX = true;
					((Cube*)m_Drawables.front())->m_RotatingY = true;
					((Cube*)m_Drawables.front())->m_RotatingZ = true;
					//
					//m_Renderer->SetRS(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					//
					/*
					m_Renderer->SetRS(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);
					m_Renderer->SetRS(D3DRS_SRCBLENDALPHA, D3DBLEND_ONE);
					m_Renderer->SetRS(D3DRS_DESTBLENDALPHA, D3DBLEND_ZERO);
					*/
					break;
				}
			case(2):
				{
					//subtractive blending
					m_Renderer->SetRS(D3DRS_BLENDOP, D3DBLENDOP_SUBTRACT);
					break;
				}
			case(3):
				{
					//subtractive blending
					m_Renderer->SetRS(D3DRS_BLENDOP, D3DBLENDOP_ADD);
					//
					m_Renderer->SetRS(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
					m_Renderer->SetRS(D3DRS_DESTBLEND, D3DBLEND_DESTALPHA);
					break;
				}
			}
			break;
		}
	}
	if(success)
	{
		//std::cout << "success" << std::endl;
		m_SubDemoNum = a_SubDemoNum;
	}
	return;
}
