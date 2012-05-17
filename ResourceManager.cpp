#include "ResourceManager.h"
#include "WindowManager.h"

#include "Cube.h"
#include "Line.h"
#include "Light.h"
#include "Teapot.h"
#include "D3dx9tex.h"

#include <iostream>

typedef std::pair<std::string, RECT*> Title;

ResMgr::ResMgr()
:	m_Renderer(NULL)
{
	//no hacky stuff here that requires rendering will work, use Init() instead
}

void ResMgr::Init(Renderer* a_Renderer)
{
	m_Renderer = a_Renderer;
	//add an omnidirectional light
	/*
	*/
	m_pLight = new Light();
	m_pLight->InitOmni();
	m_pLight->SetPosition(-2,0,-2);
	//m_pLight->SetCircling(3.0f);
	m_Renderer->AddLight(m_pLight);
}

Cube* ResMgr::AddCube(bool a_Visible)
{
	if(!m_Renderer)
		return NULL;

	DrawableObjectList* list;
	if(a_Visible)
		list = &m_Visible;
	else
		list = &m_Hidden;

	list->push_back(new Cube());
	if( !list->back()->CreateObject(DXMgr::GetInstance().GetDevice()) )
	{
		delete list->back();
		list->pop_back();
		return NULL;
	}
	if(a_Visible)
		m_Renderer->AddObject(list->back());
	return (Cube*)list->back();
}

Line* ResMgr::AddLine(bool a_Visible)
{
	if(!m_Renderer)
		return NULL;

	DrawableObjectList* list;
	if(a_Visible)
		list = &m_Visible;
	else
		list = &m_Hidden;

	list->push_back(new Line(D3DXVECTOR3(0,0,0),D3DXVECTOR3(1,1,0)));
	if( !list->back()->CreateObject(DXMgr::GetInstance().GetDevice()) )
	{
		delete list->back();
		list->pop_back();
		return NULL;
	}
	if(a_Visible)
		m_Renderer->AddObject(list->back());
	return (Line*)list->back();
}

Teapot* ResMgr::AddTeapot(bool a_Visible)
{
	if(!m_Renderer)
		return NULL;

	DrawableObjectList* list;
	if(a_Visible)
		list = &m_Visible;
	else
		list = &m_Hidden;

	list->push_back(new Teapot());
	if( !list->back()->CreateObject(DXMgr::GetInstance().GetDevice()) )
	{
		delete list->back();
		list->pop_back();
		return NULL;
	}
	if(a_Visible)
		m_Renderer->AddObject(list->back());
	return (Teapot*)list->back();
}

void ResMgr::UpdateRect(Title* a_pTitle)
{
	delete a_pTitle->second;
	a_pTitle->second = m_Renderer->GetTitleRect(a_pTitle->first);
}

void ResMgr::AddTitle(Title* a_pTitle)
{
	m_Renderer->m_Titles.push_back(a_pTitle);
}

Title* ResMgr::AddTitle(std::string a_String, short a_Pos, bool a_Visible)
{
	//std::vector< std::pair<std::string, RECT> > m_Titles;
	RECT* rect = m_Renderer->GetTitleRect(a_String);
	switch(a_Pos)
	{
	default:
	case(0):
		{
			//first from top left corner
			break;
		}
	case(1):
		{
			//second going down
			rect->top += 19;
			rect->bottom += 19;
			break;
		}
	case(2):
		{
			//third
			rect->top += 38;
			rect->bottom += 38;
			break;
		}
	case(3):
		{
			//fourth
			rect->top += 57;
			rect->bottom += 57;
			break;
		}
	case(4):
		{
			//fifth
			rect->top += 76;
			rect->bottom += 76;
			break;
		}
	case(5):
		{
			//sixth
			rect->top += 95;
			rect->bottom += 95;
			break;
		}
	case(6):
		{
			//seventh
			rect->top += 114;
			rect->bottom += 114;
			break;
		}
	case(7):
		{
			//title 1
			rect->top += 200;
			rect->bottom += 200;
			rect->left += 200;
			rect->right += 200;
			break;
		}
	case(8):
		{
			//matrix 1
			rect->top += 219;
			rect->bottom += 219;
			rect->left += 200;
			rect->right += 200;
			break;
		}
	case(9):
		{
			//title 2
			rect->top += 200;
			rect->bottom += 200;
			rect->left += 500;
			rect->right += 500;
			break;
		}
	case(10):
		{
			//matrix 2
			rect->top += 219;
			rect->bottom += 219;
			rect->left += 500;
			rect->right += 500;
			break;
		}
	case(11):
		{
			//title 3
			rect->top += 500;
			rect->bottom += 500;
			rect->left += 200;
			rect->right += 200;
			break;
		}
	case(12):
		{
			//matrix 3
			rect->top += 519;
			rect->bottom += 519;
			rect->left += 200;
			rect->right += 200;
			break;
		}
	case(13):
		{
			//title 4
			rect->top += 500;
			rect->bottom += 500;
			rect->left += 500;
			rect->right += 500;
			break;
		}
	case(14):
		{
			//matrix 4
			rect->top += 519;
			rect->bottom += 519;
			rect->left += 500;
			rect->right += 500;
			break;
		}
	}
	Title* title = new std::pair<std::string,RECT*>(a_String, rect);
	m_Renderer->m_Titles.push_back(title);
	return title;
}

void ResMgr::ClearAllTitles()
{
	//std::cout << "	num of titles to clear: " << m_Renderer->m_Titles.size() << std::endl;
	while(m_Renderer->m_Titles.size())
	{
		//std::cout << "	" << n << "clearing title: '" << m_Renderer->m_Titles[0]->first.c_str() << "'" << std::endl;
		ClearTitle(m_Renderer->m_Titles[0]);
	}
}

bool ResMgr::ClearTitle(Title* a_pTitle)
{
	for(unsigned short n=0;n<m_Renderer->m_Titles.size();n++)
	{
		if( !m_Renderer->m_Titles[n]->first.compare(a_pTitle->first) )
		{
			RECT* firstRect = m_Renderer->m_Titles[n]->second;
			RECT* secondRect = a_pTitle->second;
			if(firstRect->bottom == secondRect->bottom && firstRect->top == secondRect->top && firstRect->left == secondRect->left && firstRect->right == secondRect->right)
			{
				//std::cout << "	title '" << m_Renderer->m_Titles[n]->first.c_str() << "' cleared" << std::endl;
				delete m_Renderer->m_Titles[n]->second;
				m_Renderer->m_Titles[n]->second = NULL;
				delete m_Renderer->m_Titles[n];
				m_Renderer->m_Titles[n] = NULL;
				m_Renderer->m_Titles.erase(m_Renderer->m_Titles.begin()+n);
				return true;
			}
		}
	}
	//std::cout << "	title '" << a_pTitle->first.c_str() << "' failed to clear" << std::endl;
	return false;
	//
}

bool ResMgr::Show(Drawable *a_pObject)
{
	// Look for this object in our list
	for (DrawableObjectList::iterator iter = m_Hidden.begin(); iter != m_Hidden.end(); ++iter)
	{
		Drawable* pElem = *iter;
		if (pElem == a_pObject)
		{
			// Found the object! Move it to the visible list
			m_Hidden.erase(iter);
			m_Visible.push_back(pElem);
			m_Renderer->AddObject(pElem);
			std::cout << "" << std::endl;
			return true;
		}
	}
	return false;
}

bool ResMgr::Hide(Drawable *a_pObject)
{
	m_Renderer->RemoveObject(a_pObject);
	// Look for this object in our list
	for (DrawableObjectList::iterator iter = m_Visible.begin(); iter != m_Visible.end(); ++iter)
	{
		Drawable* pElem = *iter;
		if (pElem == a_pObject)
		{
			// Found the object! Move it to the visible list
			m_Visible.erase(iter);
			m_Hidden.push_back(pElem);
			return true;
		}
	}
	return false;
}

void ResMgr::DisableLighting()
{
	//
	m_Renderer->SetRS(D3DRS_LIGHTING,FALSE);
}

void ResMgr::EnableLighting()
{
	m_Renderer->SetRS(D3DRS_LIGHTING,TRUE);
}

bool ResMgr::AddLight(Light* a_pLight)
{
	return m_Renderer->AddLight(a_pLight);
}

bool ResMgr::RemoveLight(Light* a_pLight)
{
	return m_Renderer->RemoveLight(a_pLight);
}

void ResMgr::EnableFlatShading()
{
	m_Renderer->SetRS(D3DRS_SHADEMODE, D3DSHADE_FLAT);
}

void ResMgr::EnableGourardShading()
{
	m_Renderer->SetRS(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
}

void ResMgr::ApplyCubeTexture(IDirect3DDevice9* a_pDev, Cube* a_pCube)
{
	//std::cout << "ResMgr::ApplyCubeTexture()" << std::endl;
	IDirect3DTexture9* g_pTex = NULL;
	if( FAILED(D3DXCreateTextureFromFile(a_pDev, L"ace.png",&g_pTex)) )
	{
		std::cout << "Could not load cube texture." << std::endl;
	}
	if(g_pTex && a_pCube)
	{
		std::cout << "Cube texture loaded." << std::endl;
		a_pCube->CreateObject(a_pDev,&g_pTex);
		//g_pTex->Release();
	}
}

void ResMgr::RemoveCubeTexture(IDirect3DDevice9* a_pDev, Cube* a_pCube)
{
	a_pCube->ClearTexture();
	a_pCube->ReleaseObject();
	a_pCube->CreateObject(a_pDev);
}
