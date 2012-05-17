#include "MathLogic.h"

#include <iostream>

#include "Line.h"
#include "ResourceManager.h"
#include "Matrices.h"
#include "Cube.h"

void MathLogic::ShowNextSubDemo()
{
	short newSubDemoNum = m_SubDemoNum + 1;
	switch(m_CurDemoNum)
	{
	default:
	case(0):
		{
			newSubDemoNum = 1;
			break;
		}
	case(1):
		{
			if(m_SubDemoNum == 4)
			{
				newSubDemoNum = 1;
				ShowDemo(2);
			}
			break;
		}
	case(2):
		{
			if(m_SubDemoNum == 6)
			{
				newSubDemoNum = 1;
				ShowDemo(3);
			}
			break;
		}
	case(3):
		{
			if(m_SubDemoNum == 1)
			{
				newSubDemoNum = 1;
				ShowDemo(1);
			}
			break;
		}
	}
	//std::cout << "demo " << m_CurDemoNum << std::endl;
	ShowSubDemo(newSubDemoNum);
}

bool MathLogic::ShowSubDemo(short a_SubDemoNum)
{
	//std::cout << "loading subdemo " << a_SubDemoNum << " from subdemo " << m_SubDemoNum << std::endl;
	ResMgr& resource_manager = ResMgr::GetInstance().GetInstance();
	if((unsigned short)a_SubDemoNum <= m_DemoDrawables[1].size())
	{
		switch(m_CurDemoNum)
		{
		case(1):
			{
				//vectors
				//undo settings from the old subdemo
				switch(m_SubDemoNum)
				{
				case(0):
					{
						//default - display nothing
						resource_manager.Show(m_DemoDrawables[m_CurDemoNum][0]);
						resource_manager.Show(m_DemoDrawables[m_CurDemoNum][1]);
						resource_manager.Show(m_DemoDrawables[m_CurDemoNum][2]);
						break;
					}
				case(1):
					{
						//vector addition
						resource_manager.ClearTitle(m_DemoTitles[1]);
						m_DemoTitles.erase(m_DemoTitles.begin()+1);
						break;
					}
				case(2):
					{
						//vector subtraction
						resource_manager.ClearTitle(m_DemoTitles[1]);
						m_DemoTitles.erase(m_DemoTitles.begin()+1);
						break;
					}
				case(3):
					{
						//vector cross product
						resource_manager.ClearTitle(m_DemoTitles[1]);
						m_DemoTitles.erase(m_DemoTitles.begin()+1);
						break;
					}
				case(4):
					{
						//angle between two vectors
						resource_manager.Show(m_DemoDrawables[m_CurDemoNum][2]);
						resource_manager.ClearTitle(m_DemoTitles[2]);
						m_DemoTitles.erase(m_DemoTitles.begin()+2);
						resource_manager.ClearTitle(m_DemoTitles[1]);
						m_DemoTitles.erase(m_DemoTitles.begin()+1);
						break;
					}
				}

				//std::cout << "	applying subdemo " << a_SubDemoNum << std::endl;
				//apply settings for the new subdemo
				switch(a_SubDemoNum)
				{
				case(0):
					{
						//default - display nothing
						resource_manager.Hide(m_DemoDrawables[m_CurDemoNum][0]);
						resource_manager.Hide(m_DemoDrawables[m_CurDemoNum][1]);
						resource_manager.Hide(m_DemoDrawables[m_CurDemoNum][2]);
						while(m_DemoTitles.size()>1)
						{
							resource_manager.ClearTitle(m_DemoTitles[1]);
							m_DemoTitles.erase(m_DemoTitles.begin()+1);
						}
						break;
					}
				case(1):
					{
						//vector addition
						m_DemoTitles.push_back(resource_manager.AddTitle("Vector addition",1,true));
						break;
					}
				case(2):
					{
						//vector subtraction
						m_DemoTitles.push_back(resource_manager.AddTitle("Vector subtraction",1,true));
						break;
					}
				case(3):
					{
						//vector cross product
						m_DemoTitles.push_back(resource_manager.AddTitle("Vector cross product",1,true));
						break;
					}
				case(4):
					{
						//angle between two vectors
						resource_manager.Hide(m_DemoDrawables[m_CurDemoNum][2]);
						m_DemoTitles.push_back(resource_manager.AddTitle("Angle between two vectors",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("#angle",2,true));
						break;
					}
				}
				m_SubDemoNum = a_SubDemoNum;
				//std::cout << "loading subdemo " << a_SubDemoNum << " success" << std::endl;
				return true;
			}
		case(2):
			{
				//matrices
				//undo settings from the old subdemo
				while(m_DemoTitles.size()>1)
				{
					resource_manager.ClearTitle(m_DemoTitles[1]);
					m_DemoTitles.erase(m_DemoTitles.begin()+1);
				}
				switch(m_SubDemoNum)
				{
				default:
				case(0):
					{
						//
						break;
					}
				case(1):
					{
						//scaling
						break;
					}
				case(2):
					{
						//
						m_Scene->m_UseOrtho = false;
						break;
					}
				case(3):
					{
						//orthographic projection
						//m_Scene->m_ProjectionMat = NULL;
						break;
					}
				case(4):
					{
						//reflection
						break;
					}
				case(6):
					{
						//translation
						((Cube*)m_DemoDrawables[2][0])->m_RotatingX = false;
						((Cube*)m_DemoDrawables[2][0])->m_RotatingY = false;
						((Cube*)m_DemoDrawables[2][1])->m_RotatingX = false;
						((Cube*)m_DemoDrawables[2][1])->m_RotatingY = false;
						break;
					}
				}
				//apply settings for the new subdemo
				switch(a_SubDemoNum)
				{
				default:
				case(0):
					{
						//
						break;
					}
				case(1):
					{
						//Scaling
						std::vector<std::vector<float>>* matrix = m_Matrices.at(1);
						for(unsigned short y=0;y<matrix->size();y++)
						{
							for(unsigned short x=0;x<matrix->size();x++)
							{
								matrix->at(y)[x] = 0.0f;
							}
						}
						for(short n=0;n<4;n++)
						{
							matrix->at(n)[n] = 2.0f;//(float)(rand()%10) + ((float)(rand()%10))/10.0f;
						}
						m_DemoTitles.push_back(resource_manager.AddTitle("Scaling",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Determinant: ",2,true));
						m_DemoTitles[2]->second->right += 75;
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the resultant orthogonal: ",3,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the transformation linear: ",4,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix",7,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",8,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Scaling Matrix",9,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",10,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Resultant matrix",11,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",12,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Inverse matrix",13,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",14,true));
						m_DemoTitles.back()->second->bottom += 60;
						break;
					}
				case(2):
					{
						//Orthogonal Projection
						m_DemoTitles.push_back(resource_manager.AddTitle("Orthogonal Projection",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Determinant: ",2,true));
						m_DemoTitles[2]->second->right += 75;
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the matrix orthogonal: ",3,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the transformation linear: ",4,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 1",7,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",8,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 2",9,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",10,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Resultant matrix",11,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",12,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Inverse matrix",13,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",14,true));
						m_DemoTitles.back()->second->bottom += 60;
						//
						m_Scene->m_UseOrtho = true;
						D3DXMATRIX ortho;
						Matrix::Identity(&ortho);
						Matrix::ProjectOrthographic(&ortho,5,5,-10,10);
						//m_Scene->m_ProjectionMat = &ortho;
						break;
					}
				case(3):
					{
						//Perspective Projection
						m_DemoTitles.push_back(resource_manager.AddTitle("Perspective Projection",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Determinant: ",2,true));
						m_DemoTitles[2]->second->right += 75;
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the matrix orthogonal: ",3,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the transformation linear: ",4,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 1",7,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",8,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 2",9,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",10,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Resultant matrix",11,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",12,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Inverse matrix",13,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",14,true));
						m_DemoTitles.back()->second->bottom += 60;
						break;
					}
				case(4):
					{
						//Reflection
						m_RotValX = 0.0f;//(float)(rand()%10) + ((float)(rand()%100))/100.0f;
						m_RotValY = 0.0f;//(float)(rand()%10) + ((float)(rand()%100))/100.0f;
						m_RotValZ = (float)(rand()%3) + ((float)(rand()%100))/100.0f;
						//((Cube*)m_DemoDrawables[2][0])->m_RotatingX = true;
						m_DemoTitles.push_back(resource_manager.AddTitle("Reflection",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Determinant: ",2,true));
						m_DemoTitles[2]->second->right += 75;
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the matrix orthogonal: ",3,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the transformation linear: ",4,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 1",7,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",8,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 2",9,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",10,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Resultant matrix",11,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",12,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Inverse matrix",13,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",14,true));
						m_DemoTitles.back()->second->bottom += 60;
						break;
					}
				case(5):
					{
						//Shearing
						m_DemoTitles.push_back(resource_manager.AddTitle("Shearing",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Determinant: ",2,true));
						m_DemoTitles[2]->second->right += 75;
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the matrix orthogonal: ",3,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the transformation linear: ",4,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 1",7,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",8,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 2",9,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",10,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Resultant matrix",11,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",12,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Inverse matrix",13,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",14,true));
						m_DemoTitles.back()->second->bottom += 60;
						break;
					}
				case(6):
					{
						//Translation
						((Cube*)m_DemoDrawables[2][0])->m_RotatingX = true;
						((Cube*)m_DemoDrawables[2][1])->m_RotatingX = true;
						m_DemoTitles.push_back(resource_manager.AddTitle("Translation",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Determinant: ",2,true));
						m_DemoTitles[2]->second->right += 75;
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the matrix orthogonal: ",3,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Is the transformation linear: ",4,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 1",7,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",8,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Matrix 2",9,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",10,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Resultant matrix",11,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",12,true));
						m_DemoTitles.back()->second->bottom += 60;
						m_DemoTitles.push_back(resource_manager.AddTitle("Inverse matrix",13,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("- - - - \n- - - - \n- - - - \n- - - - ",14,true));
						m_DemoTitles.back()->second->bottom += 60;
						break;
					}
				}
				//std::cout << "loading subdemo " << a_SubDemoNum << " success" << std::endl;
				m_SubDemoNum = a_SubDemoNum;
				return true;
			}
			case(3):
			{
				//quaternions
				//remove settings from old subdemo
				while(m_DemoTitles.size()>1)
				{
					resource_manager.ClearTitle(m_DemoTitles[1]);
					m_DemoTitles.erase(m_DemoTitles.begin()+1);
				}
				switch(a_SubDemoNum)
				{
				default:
				case(0):
					{
						//
						break;
					}
				case(1):
					{
						m_RotValX = (float)(rand()%3) + ((float)(rand()%100))/100.0f;
						m_RotValY = (float)(rand()%3) + ((float)(rand()%100))/100.0f;
						m_RotValZ = (float)(rand()%3) + ((float)(rand()%100))/100.0f;
						m_DemoTitles.push_back(resource_manager.AddTitle("Orientation and Angular Displacement"));
						m_DemoTitles.push_back(resource_manager.AddTitle("Quat. 1: a + bi + cj + dk",1,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Quat. 2: a + bi + cj + dk",2,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Resultant Quat.: a + bi + cj + dk",3,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Euler angle: ",4,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("t: ",5,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("Rotation matrix",7,true));
						m_DemoTitles.push_back(resource_manager.AddTitle("----\n----\n----\n----",8,true));
						break;
					}
				}
				//std::cout << "loading subdemo " << a_SubDemoNum << " success" << std::endl;
				m_SubDemoNum = a_SubDemoNum;
				return true;
			}
		}
	}
	//std::cout << "failed to load subdemo " << a_SubDemoNum << std::endl;
	return false;
}
