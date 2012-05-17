#include <sstream>
#include <iostream>

#include "MathLogic.h"
#include "Line.h"
#include "ResourceManager.h"
#include "Matrices.h"
#include "Cube.h"

void MathLogic::Update(float a_DeltaT)
{
	ResMgr& resource_manager = ResMgr::GetInstance();
	switch(m_CurDemoNum)
	{
	case(1):
		{
			//Vectors
			switch(m_SubDemoNum)
			{
			case(0):
				{
					//fall though
				}
			default:
				{
					//default display - nothing changes
					break;
				}
			case(1):
				{
					//vector addition
					Line* line1 = (Line*)m_DemoDrawables[1][0];
					Line* line2 = (Line*)m_DemoDrawables[1][1];
					Line* resultant = (Line*)m_DemoDrawables[1][2];
					resultant->SetVec(line1->GetAdd(*line2));
					break;
				}
			case(2):
				{
					//vector subtraction
					Line* line1 = (Line*)m_DemoDrawables[1][0];
					Line* line2 = (Line*)m_DemoDrawables[1][1];
					Line* resultant = (Line*)m_DemoDrawables[1][2];
					resultant->SetVec(line1->GetSubtract(*line2));
					break;
				}
			case(3):
				{
					//vector cross product
					Line* line1 = (Line*)m_DemoDrawables[1][0];
					Line* line2 = (Line*)m_DemoDrawables[1][1];
					Line* resultant = (Line*)m_DemoDrawables[1][2];
					resultant->SetVec(line1->GetCrossProduct(*line2));
					break;
				}
			case(4):
				{
					//angle between two vectors (radians)
					Line* line1 = (Line*)m_DemoDrawables[1][0];
					Line* line2 = (Line*)m_DemoDrawables[1][1];
					std::stringstream ss;
					ss << line1->GetAngleWith(*line2);
					m_DemoTitles[2]->first = ss.str();
					break;
				}
			}
			break;
		}
	case(2):
		{
			//Matrices
			switch(m_SubDemoNum)
			{
			default:
			case(0):
				{
					//default
					break;
				}
			case(1):
				{
					//scaling
					//multiply by scale matrix
					Cube* cube1 = (Cube*)m_DemoDrawables[2][0];
					Cube* cube2 = (Cube*)m_DemoDrawables[2][1];
					Matrix::Identity(&cube1->m_ModelToWorld);
					Matrix::TranslateX(&cube1->m_ModelToWorld,-2.0f);
					Matrix::Identity(&cube2->m_ModelToWorld);
					Matrix::TranslateX(&cube2->m_ModelToWorld,2.0f);
					D3DXMATRIX scale;
					Matrix::Identity(&scale);
					Matrix::ScaleX(&scale,1.1f);
					//scale cube
					Matrix::ScaleX(&cube2->m_ModelToWorld,1.1f);
					Matrix::ScaleY(&cube2->m_ModelToWorld,1.1f);
					Matrix::ScaleZ(&cube2->m_ModelToWorld,1.1f);
					//copy to output matrix
					delete m_Matrices.at(0);
					m_Matrices.at(0) = Matrix::Get2DVector(&cube1->m_ModelToWorld);
					delete m_Matrices.at(1);
					m_Matrices.at(1) = Matrix::Get2DVector(&scale);
					m_Matrices.at(2) = Matrix::Get2DVector(&cube1->m_ModelToWorld);
					//calculate inverse
					*m_Matrices.at(3) = Matrix::Inverse(*m_Matrices.at(2));
					//work out if resultant is orthogonal
					std::vector<std::vector<float>> matrix1 = Matrix::Transpose(*m_Matrices.at(2));
					std::vector<std::vector<float>> matrix2 = Matrix::Inverse(*m_Matrices.at(2));
					bool ortho = true;
					for(unsigned short y=0;y<matrix1.size();y++)
					{
						for(unsigned short x=0;x<matrix1.size();x++)
						{
							if(matrix1[y][x] != m_Matrices.at(3)->at(y)[x])
							{
								ortho = false;
								goto _break1;
							}
						}
					}
					_break1:

					//update output
					std::vector<std::vector<float>>* matrix = m_Matrices.at(0);
					//m_DemoTitles[1]->first = "Scaling";
					std::stringstream sd;
					sd << "Determinant: " << Matrix::Determinant(*m_Matrices.at(2));
					m_DemoTitles[2]->first = sd.str();
					//resource_manager.UpdateRect(m_DemoTitles[2]);
					if(ortho)
						m_DemoTitles[3]->first = "Is the resultant orthogonal: Yes";
					else
						m_DemoTitles[3]->first = "Is the resultant orthogonal: No";
					//resource_manager.UpdateRect(m_DemoTitles[3]);
					m_DemoTitles[4]->first = "Is the transformation linear: Yes";
					//resource_manager.UpdateRect(m_DemoTitles[4]);
					//m_DemoTitles[5]->first = "Matrix 1";
					std::stringstream s1;
					matrix = m_Matrices.at(0);
					s1 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s1 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s1 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s1 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[6]->first = s1.str();
					//resource_manager.UpdateRect(m_DemoTitles[6]);
					//m_DemoTitles[7]->first = "Scaling Matrix";
					std::stringstream s2;
					matrix = m_Matrices.at(1);
					s2 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s2 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s2 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s2 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[8]->first = s2.str();
					//resource_manager.UpdateRect(m_DemoTitles[8]);
					//m_DemoTitles[9]->first = "Resultant matrix";
					std::stringstream s3;
					matrix = m_Matrices.at(2);
					s3 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s3 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s3 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s3 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[10]->first = s3.str();
					//resource_manager.UpdateRect(m_DemoTitles[10]);
					//m_DemoTitles[11]->first = "Inverse matrix";
					std::stringstream s4;
					matrix = m_Matrices.at(3);
					s4 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s4 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s4 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s4 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[12]->first = s4.str();
					break;
				}
			case(2):
				{
					//void ProjectOrthogonal(D3DXMATRIX* a_pMat, float a_Width, float a_Height, float a_Near, float a_Far)
					Cube* cube1 = (Cube*)m_DemoDrawables[2][0];
					cube1->m_RotatingX = true;
					Cube* cube2 = (Cube*)m_DemoDrawables[2][1];
					cube2->m_RotatingX = true;
					//
					Matrix::Identity(&cube1->m_ModelToWorld);
					Matrix::TranslateX(&cube1->m_ModelToWorld,-2.0f);
					//
					Matrix::Identity(&cube2->m_ModelToWorld);
					Matrix::TranslateX(&cube2->m_ModelToWorld,2.0f);
					break;
				}
			case(4):
				{
					//reflection
					float xTrans = -2.0f;
					//apply basic matrices to cube 1, rotation then translation
					Cube* cube1 = (Cube*)m_DemoDrawables[2][0];
					Matrix::Identity(&cube1->m_ModelToWorld);
					//Matrix::ScaleY(&cube1->m_ModelToWorld,1.5f);
					Matrix::RotateX(&cube1->m_ModelToWorld, m_RotValX);
					Matrix::RotateY(&cube1->m_ModelToWorld, m_RotValY);
					Matrix::RotateZ(&cube1->m_ModelToWorld, m_RotValZ);
					Matrix::TranslateX(&cube1->m_ModelToWorld,xTrans);
					m_Matrices.at(0) = Matrix::Get2DVector(&cube1->m_ModelToWorld);
					//apply same matrices to cube 2, rotation then translation
					Cube* cube2 = (Cube*)m_DemoDrawables[2][1];
					Matrix::Identity(&cube2->m_ModelToWorld);
					//Matrix::ScaleY(&cube2->m_ModelToWorld,1.5f);
					Matrix::ReflectY(&cube2->m_ModelToWorld);
					Matrix::RotateX(&cube2->m_ModelToWorld, m_RotValX);
					Matrix::RotateY(&cube2->m_ModelToWorld, m_RotValY);
					Matrix::RotateZ(&cube2->m_ModelToWorld, m_RotValZ);
					Matrix::TranslateX(&cube2->m_ModelToWorld,-xTrans);
					//reflect across all axes
					//Matrix::ReflectY(&cube2->m_ModelToWorld);
					//Matrix::ReflectZ(&cube2->m_ModelToWorld);
					//copy reflection matrix to output matrix
					m_Matrices.at(2) = Matrix::Identity(m_Matrices.at(2));
					//copy world matrix to output matrix
					delete m_Matrices.at(2);
					m_Matrices.at(2) = Matrix::Get2DVector(&cube2->m_ModelToWorld);
					//copy inverse to output vector
					*m_Matrices.at(3) = Matrix::Inverse(*m_Matrices.at(2));
					//work out if resultant is orthogonal
					std::vector<std::vector<float>> matrix1 = Matrix::Transpose(*m_Matrices.at(2));
					std::vector<std::vector<float>> matrix2 = Matrix::Inverse(*m_Matrices.at(2));
					bool ortho = true;
					for(unsigned short y=0;y<matrix1.size();y++)
					{
						for(unsigned short x=0;x<matrix1.size();x++)
						{
							if(matrix1[y][x] != m_Matrices.at(3)->at(y)[x])
							{
								ortho = false;
								goto _break4;
							}
						}
					}
					_break4:

					//update output
					std::vector<std::vector<float>>* matrix = m_Matrices.at(0);
					//m_DemoTitles[1]->first = "Scaling";
					std::stringstream sd;
					sd << "Determinant: " << Matrix::Determinant(*m_Matrices.at(2));
					m_DemoTitles[2]->first = sd.str();
					if(ortho)
						m_DemoTitles[3]->first = "Is the resultant orthogonal: Yes";
					else
						m_DemoTitles[3]->first = "Is the resultant orthogonal: No";
					m_DemoTitles[4]->first = "Is the transformation linear: Yes";
					//m_DemoTitles[5]->first = "Matrix 1";
					std::stringstream s1;
					matrix = m_Matrices.at(0);
					s1 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s1 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s1 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s1 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[6]->first = s1.str();
					m_DemoTitles[7]->first = "Rotate values: ";
					std::stringstream s2;
					matrix = m_Matrices.at(1);
					s2 << " XVal: " << m_RotValX << std::endl << " YVal: " << m_RotValY << std::endl << " ZVal: " << m_RotValZ << std::endl;
					m_DemoTitles[8]->first = s2.str();
					//m_DemoTitles[9]->first = "Resultant matrix";
					std::stringstream s3;
					matrix = m_Matrices.at(2);
					s3 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s3 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s3 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s3 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[10]->first = s3.str();
					//m_DemoTitles[11]->first = "Inverse matrix";
					std::stringstream s4;
					matrix = m_Matrices.at(3);
					s4 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s4 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s4 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s4 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[12]->first = s4.str();

					/*resultant->m_ExtRotation._11 = m_Matrices.at(1)->at(0)[0];
					resultant->m_ExtRotation._12 = m_Matrices.at(1)->at(0)[1];
					resultant->m_ExtRotation._13 = m_Matrices.at(1)->at(0)[2];
					resultant->m_ExtRotation._14 = m_Matrices.at(1)->at(0)[3];
					resultant->m_ExtRotation._21 = m_Matrices.at(1)->at(1)[0];
					resultant->m_ExtRotation._22 = m_Matrices.at(1)->at(1)[1];
					resultant->m_ExtRotation._23 = m_Matrices.at(1)->at(1)[2];
					resultant->m_ExtRotation._24 = m_Matrices.at(1)->at(1)[3];
					resultant->m_ExtRotation._31 = m_Matrices.at(1)->at(2)[0];
					resultant->m_ExtRotation._32 = m_Matrices.at(1)->at(2)[1];
					resultant->m_ExtRotation._33 = m_Matrices.at(1)->at(2)[2];
					resultant->m_ExtRotation._34 = m_Matrices.at(1)->at(2)[3];
					resultant->m_ExtRotation._41 = m_Matrices.at(1)->at(3)[0];
					resultant->m_ExtRotation._42 = m_Matrices.at(1)->at(3)[1];
					resultant->m_ExtRotation._43 = m_Matrices.at(1)->at(3)[2];
					resultant->m_ExtRotation._44 = m_Matrices.at(2)->at(3)[3];*/

					break;
				}
			case(5):
				{
					//shearing
					/**/
					float xShear = 2.0f;
					//apply basic matrices to cube 1, rotation then translation
					Cube* cube1 = (Cube*)m_DemoDrawables[2][0];
					Matrix::Identity(&cube1->m_ModelToWorld);
					Matrix::TranslateX(&cube1->m_ModelToWorld,-2.0f);
					//apply same matrices to cube 2, rotation then translation
					Cube* cube2 = (Cube*)m_DemoDrawables[2][1];
					Matrix::Identity(&cube2->m_ModelToWorld);
					Matrix::ShearXY(&cube2->m_ModelToWorld,PI/4);
					Matrix::TranslateX(&cube2->m_ModelToWorld,2.0f);
					//setup output shear
					D3DXMATRIX shear;
					Matrix::Identity(&shear);
					Matrix::ShearXY(&shear,PI/4);
					//copy matrices over
					delete m_Matrices.at(0);
					m_Matrices.at(0) = Matrix::Get2DVector(&cube1->m_ModelToWorld);
					delete m_Matrices.at(1);
					m_Matrices.at(1) = Matrix::Get2DVector(&shear);
					delete m_Matrices.at(2);
					m_Matrices.at(2) = Matrix::Get2DVector(&cube2->m_ModelToWorld);
					delete m_Matrices.at(3);
					m_Matrices.at(3) = Matrix::Get2DVector(&cube2->m_ModelToWorld);
					Matrix::Inverse(*m_Matrices.at(3));
					//update output
					std::vector<std::vector<float>>* matrix = m_Matrices.at(0);
					//m_DemoTitles[1]->first = "Scaling";
					std::stringstream sd;
					sd << "Determinant: " << Matrix::Determinant(*m_Matrices.at(2));
					m_DemoTitles[2]->first = sd.str();
					//work out if resultant is orthogonal
					std::vector<std::vector<float>> matrix1 = Matrix::Transpose(*m_Matrices.at(2));
					std::vector<std::vector<float>> matrix2 = Matrix::Inverse(*m_Matrices.at(2));
					bool ortho = true;
					for(unsigned short y=0;y<matrix1.size();y++)
					{
						for(unsigned short x=0;x<matrix1.size();x++)
						{
							if(matrix1[y][x] != m_Matrices.at(3)->at(y)[x])
							{
								ortho = false;
								goto _break5;
							}
						}
					}
					_break5:
					if(ortho)
						m_DemoTitles[3]->first = "Is the resultant orthogonal: Yes";
					else
						m_DemoTitles[3]->first = "Is the resultant orthogonal: No";
					m_DemoTitles[4]->first = "Is the transformation linear: Yes";
					//m_DemoTitles[5]->first = "Matrix 1";
					std::stringstream s1;
					matrix = m_Matrices.at(0);
					s1 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s1 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s1 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s1 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[6]->first = s1.str();
					m_DemoTitles[7]->first = "Shear matrix XY";
					std::stringstream s2;
					matrix = m_Matrices.at(1);
					s2 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s2 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s2 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s2 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[8]->first = s2.str();
					//m_DemoTitles[9]->first = "Resultant matrix";
					std::stringstream s3;
					matrix = m_Matrices.at(2);
					s3 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s3 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s3 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s3 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[10]->first = s3.str();
					//m_DemoTitles[11]->first = "Inverse matrix";
					std::stringstream s4;
					matrix = m_Matrices.at(3);
					s4 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s4 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s4 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s4 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[12]->first = s4.str();
					break;
				}
			case(6):
				{
					//
					//translate
					Cube* cube1 = (Cube*)m_DemoDrawables[2][0];
					Matrix::Identity(&cube1->m_ModelToWorld);
					Matrix::TranslateX(&cube1->m_ModelToWorld,-1.0f);
					Matrix::TranslateY(&cube1->m_ModelToWorld,-1.0f);
					Cube* cube2 = (Cube*)m_DemoDrawables[2][1];
					Matrix::Identity(&cube2->m_ModelToWorld);
					Matrix::TranslateX(&cube2->m_ModelToWorld,1.0f);
					Matrix::TranslateY(&cube2->m_ModelToWorld,1.0f);
					//copy to output matrices
					delete m_Matrices.at(0);
					m_Matrices.at(0) = Matrix::Get2DVector(&cube1->m_ModelToWorld);
					//multiply by translate matrix
					*m_Matrices.at(2) = Matrix::Multiply(*m_Matrices.at(0),*m_Matrices.at(1));
					//calculate inverse
					*m_Matrices.at(3) = Matrix::Inverse(*m_Matrices.at(2));
					//work out if resultant is orthogonal
					std::vector<std::vector<float>> matrix1 = Matrix::Transpose(*m_Matrices.at(2));
					std::vector<std::vector<float>> matrix2 = Matrix::Inverse(*m_Matrices.at(2));
					bool ortho = true;
					for(unsigned short y=0;y<matrix1.size();y++)
					{
						for(unsigned short x=0;x<matrix1.size();x++)
						{
							if(matrix1[y][x] != m_Matrices.at(3)->at(y)[x])
							{
								ortho = false;
								goto _break6;
							}
						}
					}
					_break6:

					//update output
					std::vector<std::vector<float>>* matrix = m_Matrices.at(0);
					//m_DemoTitles[1]->first = "Scaling";
					std::stringstream sd;
					sd << "Determinant: " << Matrix::Determinant(*m_Matrices.at(2));
					m_DemoTitles[2]->first = sd.str();
					//resource_manager.UpdateRect(m_DemoTitles[2]);
					if(ortho)
						m_DemoTitles[3]->first = "Is the resultant orthogonal: Yes";
					else
						m_DemoTitles[3]->first = "Is the resultant orthogonal: No";
					//resource_manager.UpdateRect(m_DemoTitles[3]);
					m_DemoTitles[4]->first = "Is the transformation linear: No";
					//resource_manager.UpdateRect(m_DemoTitles[4]);
					//m_DemoTitles[5]->first = "Matrix 1";
					std::stringstream s1;
					matrix = m_Matrices.at(0);
					s1 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s1 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s1 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s1 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[6]->first = s1.str();
					//resource_manager.UpdateRect(m_DemoTitles[6]);
					//m_DemoTitles[7]->first = "Scaling Matrix";
					std::stringstream s2;
					matrix = m_Matrices.at(1);
					s2 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s2 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s2 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s2 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[8]->first = s2.str();
					//resource_manager.UpdateRect(m_DemoTitles[8]);
					//m_DemoTitles[9]->first = "Resultant matrix";
					std::stringstream s3;
					matrix = m_Matrices.at(2);
					s3 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s3 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s3 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s3 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[10]->first = s3.str();
					//resource_manager.UpdateRect(m_DemoTitles[10]);
					//m_DemoTitles[11]->first = "Inverse matrix";
					std::stringstream s4;
					matrix = m_Matrices.at(3);
					s4 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
					s4 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
					s4 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
					s4 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
					m_DemoTitles[12]->first = s4.str();
					break;
				}
			}
		}
	case(3):
		{
			m_QuatT += a_DeltaT*0.00001f*m_QuatTCoeff;
			if(m_QuatT > 1)
				m_QuatTCoeff = -1.0f;
			else if(m_QuatT < 0)
				m_QuatTCoeff = 1.0f;
			m_QuatT += a_DeltaT*0.1f*m_QuatTCoeff;
			//Orientation and Angular Displacement
			Cube* cube1 = (Cube*)m_DemoDrawables[2][0];
			D3DXMATRIX start;
			Matrix::Identity(&start);
			D3DXMATRIX current;
			Matrix::Identity(&current);
			D3DXMATRIX finish;
			Matrix::Identity(&finish);
			Matrix::RotateX(&finish,PI/2);
			Matrix::RotateY(&finish,PI/2);
			Matrix::RotateZ(&finish,PI/2);
			D3DXQUATERNION startQuat = Matrix::MatrixToQuaternion(&start);
			D3DXQUATERNION endQuat = Matrix::MatrixToQuaternion(&finish);
			D3DXQUATERNION curQuat = Matrix::QuaternionSlerp(&startQuat,&endQuat,m_QuatT);
			D3DXMATRIX transform = Matrix::QuaternionToMatrix(&curQuat);
			Matrix::Multiply(&cube1->m_ModelToWorld,&transform);
			std::stringstream s1;
			s1 << "Start Quat.: " << startQuat.w << "," << startQuat.x << "," << startQuat.y << "," << startQuat.z;
			m_DemoTitles[1]->first = s1.str();
			std::stringstream s2;
			s2 << "End Quat.: " << startQuat.w << "," << startQuat.x << "," << startQuat.y << "," << startQuat.z;
			m_DemoTitles[2]->first = s2.str();
			std::stringstream s3;
			s3 << "Current Quat.: " << startQuat.w << "," << startQuat.x << "," << startQuat.y << "," << startQuat.z;
			m_DemoTitles[3]->first = s3.str();
			std::stringstream s4;
			D3DXVECTOR3 euler = Matrix::MatrixToEuler(cube1->m_ModelToWorld);
			s4 << "Euler angle: (" << euler.x << "," << euler.y << "," << euler.z << ")";
			m_DemoTitles[4]->first = s4.str();
			std::stringstream s5;
			s5 << "t: ";
			m_DemoTitles[5]->first = s5.str();
			m_DemoTitles[6]->first = "Rotation matrix";
			std::vector<std::vector<float>>* matrix = Matrix::Get2DVector(&cube1->m_ModelToWorld);
			std::stringstream s6;
			s6 << matrix->at(0)[0] << "," << matrix->at(0)[1] << "," << matrix->at(0)[2] << "," << matrix->at(0)[3] << "," << std::endl;
			s6 << matrix->at(1)[0] << "," << matrix->at(1)[1] << "," << matrix->at(1)[2] << "," << matrix->at(1)[3] << "," << std::endl;
			s6 << matrix->at(2)[0] << "," << matrix->at(2)[1] << "," << matrix->at(2)[2] << "," << matrix->at(2)[3] << "," << std::endl;
			s6 << matrix->at(3)[0] << "," << matrix->at(3)[1] << "," << matrix->at(3)[2] << "," << matrix->at(3)[3] << "," << std::endl;
			m_DemoTitles[7]->first = s6.str();
			delete matrix;
			break;
		}
	}
}
