#include "RenderDemo.hpp"
#include "Drawable.h"
#include "RenderSubDemo.hpp"
#include "Cube.h"

#include <iostream>

RenderDemo::RenderDemo()
{
	CurSubDemo = 0;
}

RenderDemo::~RenderDemo()
{
	while(SubDemos.size())
	{
		delete SubDemos.at(SubDemos.size()-1);
		SubDemos.pop_back();
	}
}

void RenderDemo::Enable()
{
	//show m_pCube
}

void RenderDemo::Disable()
{
	//hide m_pCube
}

bool RenderDemo::ShowNextSubDemo()
{
	SubDemos[CurSubDemo]->Disable();
	CurSubDemo++;
	if(CurSubDemo < SubDemos.size())
	{
		SubDemos[CurSubDemo]->Enable();
		return true;
	}
	else
	{
		CurSubDemo = 1;
		SubDemos[CurSubDemo]->Enable();
		return true;
	}
	return false;
}

bool RenderDemo::ShowPreviousSubDemo()
{
	SubDemos[CurSubDemo]->Disable();
	CurSubDemo--;
	if(CurSubDemo > -1)
	{
		SubDemos[CurSubDemo]->Enable();
		return true;
	}
	return false;
}
