#include "MathLogic.h"

#include "WindowManager.h"
#include "ResourceManager.h"
#include "Line.h"
#include "utils.h"
#include "Matrices.h"

#include <iostream>
#include <time.h>

typedef std::pair<std::string, RECT*> Title;

MathLogic::MathLogic()
:	m_CurDemoNum(0)
,	m_SubDemoNum(0)
,	debugLine(NULL)
,	m_QuatT(0.0f)
,	m_QuatTCoeff(-1.0f)
{
	//DRAWABLES HERE WILL NOT WORK ffs
	//add shit to Init() if you want it initialized with the class
}

bool MathLogic::Init()
{
	//demo 0 (default demo)
	m_DemoDrawables.push_back(std::vector<Drawable*>());

	//demo 1 (vectors) - starting demo
	m_DemoDrawables.push_back(std::vector<Drawable*>());
	//m_DemoTitles.push_back(ResMgr::GetInstance().AddTitle("default title",0,true));
	//m_DemoTitles.push_back(ResMgr::GetInstance().AddTitle("	info",1,true));

	//line 1
	m_DemoDrawables.back().push_back(ResMgr::GetInstance().AddLine(false));
	((Line*)m_DemoDrawables.back().back())->SetCol(D3DCOLOR_XRGB(0,0,255));
	((Line*)m_DemoDrawables.back().back())->SetVec(D3DXVECTOR3(-1,1,0));
	//line 2
	m_DemoDrawables.back().push_back(ResMgr::GetInstance().AddLine(false));
	((Line*)m_DemoDrawables.back().back())->SetCol(D3DCOLOR_XRGB(0,255,0));
	((Line*)m_DemoDrawables.back().back())->SetVec(D3DXVECTOR3(1,1,0));
	//resultant
	m_DemoDrawables.back().push_back(ResMgr::GetInstance().AddLine(false));
	((Line*)m_DemoDrawables.back().back())->SetCol(D3DCOLOR_XRGB(255,1,1));
	//no need to initialize the resultant vector

	//x axis
	m_DemoDrawables.back().push_back(ResMgr::GetInstance().AddLine(false));
	((Line*)m_DemoDrawables.back().back())->SetCol(D3DCOLOR_XRGB(255,255,255));
	((Line*)m_DemoDrawables.back().back())->SetVec(D3DXVECTOR3(1,0,0));
	//y axis
	m_DemoDrawables.back().push_back(ResMgr::GetInstance().AddLine(false));
	((Line*)m_DemoDrawables.back().back())->SetCol(D3DCOLOR_XRGB(255,255,255));
	((Line*)m_DemoDrawables.back().back())->SetVec(D3DXVECTOR3(0,1,0));
	//z axis
	m_DemoDrawables.back().push_back(ResMgr::GetInstance().AddLine(false));
	((Line*)m_DemoDrawables.back().back())->SetCol(D3DCOLOR_XRGB(255,255,255));
	((Line*)m_DemoDrawables.back().back())->SetVec(D3DXVECTOR3(0,0,1));

	//demo 2 (matrices)
	m_DemoDrawables.push_back(std::vector<Drawable*>());
	m_DemoDrawables.back().push_back((Drawable*)ResMgr::GetInstance().AddCube(false));
	m_DemoDrawables.back().push_back((Drawable*)ResMgr::GetInstance().AddCube(false));

	//demo 3 (Orientation and Angular Displacement)
	m_DemoDrawables.push_back(std::vector<Drawable*>());
	m_DemoDrawables.back().push_back((Drawable*)ResMgr::GetInstance().AddCube(false));
	//all done through titles

	std::vector< std::vector<float> > matrix1;
	for(short y=0;y<4;y++)
	{
		matrix1.push_back(std::vector<float>());
		for(short x=0;x<4;x++)
		{
			matrix1[y].push_back(1.0f);
		}
	}
	std::vector<std::vector<float>> matrix2;
	for(short y=0;y<4;y++)
	{
		matrix2.push_back(std::vector<float>());
		for(short x=0;x<4;x++)
		{
			matrix2[y].push_back(0.0f);
		}
	}
	for(short n=0;n<4;n++)
	{
		matrix2[n][n] = 2.0f;
	}
	std::vector<std::vector<float>> resultant = Matrix::Multiply(matrix1,matrix2);
	for(short y=0;y<4;y++)
	{
		for(short x=0;x<4;x++)
		{
			std::cout << resultant[y][x] << ",";
		}
		std::cout << std::endl;
	}

	return true;
}

void MathLogic::ToggleDebugLine()
{
	if(!ResMgr::GetInstance().Show((Drawable*)debugLine))
		ResMgr::GetInstance().Hide((Drawable*)debugLine);
}

void MathLogic::RandomisePrimaryMatrix()
{
	if(m_CurDemoNum != 2)
		return;
	srand((unsigned int)time(0));
	for(unsigned short y=0;y<m_Matrices.size();y++)
	{
		for(unsigned short x=0;x<m_Matrices.size();x++)
		{
			m_Matrices[0]->at(y)[x] = (float)(rand()%10) + ((float)(rand()%10))/10.0f;
		}
	}
}

void MathLogic::RandomiseSecondaryMatrix()
{
	if(m_CurDemoNum != 2)
		return;
	srand((unsigned int)time(0));
	for(unsigned short n=0;n<m_Matrices.size();n++)
	{
		m_Matrices[1]->at(n)[n] = (float)(rand()%10) + ((float)(rand()%10))/10.0f;
	}
}

void MathLogic::RandomiseRotVal(short a_Axis)
{
	switch(a_Axis)
	{
	default:
	case(0):
		{
			m_RotValX = (float)(rand()%3) + ((float)(rand()%100))/100.0f;
			break;
		}
	case(1):
		{
			m_RotValY = (float)(rand()%3) + ((float)(rand()%100))/100.0f;
			break;
		}
	case(2):
		{
			m_RotValZ = (float)(rand()%3) + ((float)(rand()%100))/100.0f;
			break;
		}
	}
}
