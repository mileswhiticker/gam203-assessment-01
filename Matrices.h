#ifndef MATRICES_H
#define MATRICES_H

#include <vector>

#define PI 3.141592653589793f

struct D3DXMATRIX;
struct Matrix9;

namespace Matrix
{
	D3DXVECTOR3 MatrixToEuler(D3DXMATRIX a_Mat);
	//
	D3DXQUATERNION QuaternionSlerp(D3DXQUATERNION* a_Q1, D3DXQUATERNION* a_Q2, float a_T);
	D3DXQUATERNION MatrixToQuaternion(D3DXMATRIX* a_Mat);
	float QuaternionDotProduct(D3DXQUATERNION* a_Q1, D3DXQUATERNION* a_Q2);
	float QuaternionMagnitude(D3DXQUATERNION* a_Quat);
	float QuaternionAngle(D3DXQUATERNION* a_Q1, D3DXQUATERNION* a_Q2);
	D3DXQUATERNION QuaternionNormalise(D3DXQUATERNION* a_Quat);
	D3DXMATRIX QuaternionToMatrix(D3DXQUATERNION* a_Quat);
	//
	float Round(float a_Val, int a_Radix);
	std::vector< std::vector<float> >* Get2DVector(D3DXMATRIX* a_Mat);
	D3DXMATRIX* GetD3DXMATRIX(std::vector< std::vector<float> > a_Mat);
	//
	D3DXMATRIX* Identity(D3DXMATRIX* a_Mat);
	std::vector< std::vector<float> >* Identity(std::vector< std::vector<float> >* a_Mat);
	void Identity9(Matrix9* a_Mat);
	void Multiply(D3DXMATRIX* a_M1, D3DXMATRIX* a_M2);
	float Determinant9(Matrix9* a_Mat);
	float Determinant4(float a,float b,float c,float d);
	void Cofactors(D3DXMATRIX* a_Mat);
	void Cofactors9(Matrix9* a_Mat);
	void Minor9(Matrix9* a_Mat);
	//tbd
	void Inverse(D3DXMATRIX* a_Mat);
	//
	void ProjectOrthographic(D3DXMATRIX* a_pMat, float a_Width, float a_Height, float a_Near, float a_Far);
	void ProjectPerspective(D3DXMATRIX* a_Mat);
	//
	void RotateX(D3DXMATRIX* a_Mat, float a_Val);
	void RotateY(D3DXMATRIX* a_Mat, float a_Val);
	void RotateZ(D3DXMATRIX* a_Mat, float a_Val);
	void ShearXY(D3DXMATRIX* a_Mat, float a_Val);
	void ShearYZ(D3DXMATRIX* a_Mat, float a_Val);
	void ShearZX(D3DXMATRIX* a_Mat, float a_Val);
	void ScaleX(D3DXMATRIX* a_Mat, float a_Val);
	void ScaleY(D3DXMATRIX* a_Mat, float a_Val);
	void ScaleZ(D3DXMATRIX* a_Mat, float a_Val);
	void ReflectX(D3DXMATRIX* a_Mat);
	void ReflectY(D3DXMATRIX* a_Mat);
	void ReflectZ(D3DXMATRIX* a_Mat);
	void TranslateX(D3DXMATRIX* a_Mat, float a_Val);
	void TranslateY(D3DXMATRIX* a_Mat, float a_Val);
	void TranslateZ(D3DXMATRIX* a_Mat, float a_Val);
	//2d vector functions - use these because they're easier + faster to code
	std::vector< std::vector<float> > Multiply(std::vector< std::vector<float> > a_M1, std::vector< std::vector<float> > a_M2);
	float Determinant(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > Transpose(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > Inverse(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> >ofactors(std::vector< std::vector<float> > a_Mat);
	std::vector< std::vector<float> > Minor(std::vector< std::vector<float> > a_Mat);
	float DotProduct(std::vector<float> a_Vec1, std::vector<float> a_Vec2);
}

#endif