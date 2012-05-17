#include "MathLogic.h"
#include "ResourceManager.h"

#include <iostream>
#include <time.h>

void MathLogic::ShowNextDemo()
{
	short newDemoNum = m_CurDemoNum + 1;
	if(newDemoNum > 3)
		newDemoNum = 1;
	ShowDemo(newDemoNum);
	//
}

bool MathLogic::ShowDemo(short a_DemoNum)
{
	//std::cout << "loading demo " << a_DemoNum << std::endl;
	ResMgr& resource_manager = ResMgr::GetInstance().GetInstance();
	if((unsigned short)a_DemoNum < m_DemoDrawables.size())
	{
		//hide previous demo drawables
		for(unsigned short n=0;n<m_DemoDrawables[m_CurDemoNum].size();n++)
		{
			resource_manager.Hide(m_DemoDrawables[m_CurDemoNum][n]);
		}
		//clear previous demo titles
		resource_manager.ClearAllTitles();
		while(m_DemoTitles.size())
		{
			m_DemoTitles.erase(m_DemoTitles.begin());
		}
		//show next demo
		switch(a_DemoNum)
		{
		default:
		case(0):
			{
				//m_DemoTitles.push_back(resource_manager.AddTitle("Welcome to the Maths Demo!",0,true));
				break;
			}
		case(1):
			{
				m_DemoTitles.push_back(resource_manager.AddTitle("Vectors",0,true));
				resource_manager.Show(m_DemoDrawables[1][3]);
				resource_manager.Show(m_DemoDrawables[1][4]);
				resource_manager.Show(m_DemoDrawables[1][5]);
				//std::cout << "main vector title added" << std::endl;
				break;
			}
		case(2):
			{
				m_DemoTitles.push_back(resource_manager.AddTitle("Matrices"));
				//cubes to show matrix operations on
				resource_manager.Show(m_DemoDrawables[2][0]);
				resource_manager.Show(m_DemoDrawables[2][1]);
				//setup matrices
				m_Matrices.push_back(new std::vector< std::vector<float> >());
				m_Matrices.back()->resize(4);
				for(short n=0;n<4;n++)
					m_Matrices.back()->at(n).resize(4);
				m_Matrices.push_back(new std::vector<std::vector<float>>);
				m_Matrices.back()->resize(4);
				for(short n=0;n<4;n++)
					m_Matrices.back()->at(n).resize(4);
				m_Matrices.push_back(new std::vector<std::vector<float>>);
				m_Matrices.back()->resize(4);
				for(short n=0;n<4;n++)
					m_Matrices.back()->at(n).resize(4);
				m_Matrices.push_back(new std::vector<std::vector<float>>);
				m_Matrices.back()->resize(4);
				for(short n=0;n<4;n++)
					m_Matrices.back()->at(n).resize(4);
				//initialize first two with random values
				srand((unsigned int)time(0));
				for(short y=0;y<4;y++)
				{
					for(short x=0;x<4;x++)
					{
						m_Matrices[0]->at(y)[x] = (float)(rand()%10) + ((float)(rand()%10))/10.0f;
						m_Matrices[1]->at(y)[x] = (float)(rand()%10) + ((float)(rand()%10))/10.0f;
					}
				}
				//second two matrices will be updated with matrix operations

				/*
				m_DemoTitles.push_back(resource_manager.AddTitle("Scaling",1,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("Determinant: ",2,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("Is the matrix orthogonal: ",3,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("Is the transformation linear: ",4,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 1",7,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",8,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 2",9,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",10,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("Resultant matrix",11,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",12,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("Inverse matrix",13,true));
				m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",14,true));
				*/
				break;
			}
		case(3):
			{
				m_DemoTitles.push_back(resource_manager.AddTitle("Orientation and Angular Displacement"));
				resource_manager.Show(m_DemoDrawables[3][0]);
				break;
			}
			//
		}
		m_CurDemoNum = a_DemoNum;

		//std::cout << "loading demo " << a_DemoNum << " success" << std::endl;
		//load first subdemo
		m_SubDemoNum = 0;
		ShowSubDemo(1);
		return true;
	}
	//std::cout << "failed to lead demo " << a_DemoNum << std::endl;
	return false;
}
