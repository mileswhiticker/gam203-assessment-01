#ifndef MATHLOGIC_H
#define MATHLOGIC_H

#include "Renderer.h"
#include <vector>

class Line;
class Cube;
typedef std::pair<std::string, RECT*> Title;

class MathLogic
{
public:
	static MathLogic& GetInstance()
	{
		static MathLogic* instance = NULL;
		if(!instance)
			instance = new MathLogic();
		return *instance;
	}
	/*
	std::vector< std::vector<float> > MatrixMultiply(std::vector< std::vector<float> > a_M1, std::vector< std::vector<float> > a_M2);
	float MatrixDeterminant(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > MatrixTranspose(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > MatrixInverse(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > MatrixCofactors(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > MatrixMinor(std::vector< std::vector<float> > a_Mat);
	float DotProduct(std::vector<float> a_Vec1, std::vector<float> a_Vec2);
	//
	std::vector< std::vector<float> > MatrixRotateByAll(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > MatrixRotateX(std::vector< std::vector<float> > a_Mat, float a_Val);
	std::vector< std::vector<float> > MatrixRotateY(std::vector< std::vector<float> > a_Mat, float a_Val);
	std::vector< std::vector<float> > MatrixRotateZ(std::vector< std::vector<float> > a_Mat, float a_Val);
	//
	std::vector< std::vector<float> > EmptyMatrix(std::vector< std::vector<float> > a_Mat);
	*/
	bool Init();
	void Update(float a_DeltaT);
	bool ShowDemo(short a_DemoNum);
	bool ShowSubDemo(short a_SubDemoNum);
	void ShowNextDemo();
	void ShowNextSubDemo();
	void RandomisePrimaryMatrix();
	void RandomiseSecondaryMatrix();
	//
	std::vector< std::vector<Drawable*> > m_DemoDrawables;
	std::vector<Title*> m_DemoTitles;
	std::vector< std::vector< std::vector<float> >* > m_Matrices;
	//
	void RandomiseRotVal(short a_Axis);
	float m_RotValX;
	float m_RotValY;
	float m_RotValZ;
	float m_QuatT;
	float m_QuatTCoeff;
	//
	void ToggleDebugLine();
	Line* debugLine;
	//
	Renderer* m_Scene; 
private:
	MathLogic();
	//
	short m_CurDemoNum;			//4: default,vectors,matrices,quaternions
	short m_SubDemoNum;			//varies: operations, manipulations etc
};

#endif