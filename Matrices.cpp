#include <d3dx9math.h>
#include "Matrices.h"

struct Matrix9
{
	float a;
	float b;
	float c;
	float d;
	float e;
	float f;
	float g;
	float h;
	float i;
};

namespace Matrix
{
	D3DXVECTOR3 MatrixToEuler(D3DXMATRIX a_Mat)
	{
		D3DXVECTOR3 vector;
		vector.x = asin(a_Mat._21);
		vector.y = atan2(-a_Mat._31,a_Mat._11);
		vector.z = atan2(-a_Mat._23,a_Mat._22);
		return vector;
	}
	//
	D3DXQUATERNION QuaternionSlerp(D3DXQUATERNION* a_Q1, D3DXQUATERNION* a_Q2, float a_T)
	{
		float angle = QuaternionAngle(a_Q1,a_Q2);
		float coeff1 = sin(1-a_T)*angle / sin(angle);
		float coeff2 = sin(a_T*angle) / sin(angle);
		return coeff1*(*a_Q1)+ coeff2*(*a_Q2);
	}

	D3DXQUATERNION MatrixToQuaternion(D3DXMATRIX* a_Mat)
	{
		D3DXQUATERNION quat;
		float D = sqrt(a_Mat->_11 + a_Mat->_22 + a_Mat->_33 + a_Mat->_44);
		quat.w = D / 2;
		quat.x = (a_Mat->_32 - a_Mat->_23) / (2*D);
		quat.y = (a_Mat->_31 - a_Mat->_13) / (2*D);
		quat.z = (a_Mat->_21 - a_Mat->_12) / (2*D);
		return quat;
	}

	float QuaternionDotProduct(D3DXQUATERNION* a_Q1, D3DXQUATERNION* a_Q2)
	{
		//dot product of the two quats
		return a_Q1->w*a_Q2->w + a_Q1->x*a_Q2->x + a_Q1->y*a_Q2->y + a_Q1->z*a_Q2->z;
	}

	float QuaternionMagnitude(D3DXQUATERNION* a_Quat)
	{
		return sqrt(a_Quat->w*a_Quat->w + a_Quat->x*a_Quat->x + a_Quat->y*a_Quat->y + a_Quat->z*a_Quat->z);
	}

	float QuaternionAngle(D3DXQUATERNION* a_Q1, D3DXQUATERNION* a_Q2)
	{
		//find the angle between them
		float dotProduct = QuaternionDotProduct(a_Q1,a_Q2);
		float mag1 = QuaternionMagnitude(a_Q1);
		float mag2 = QuaternionMagnitude(a_Q2);
		float angle = acos(dotProduct / (mag1*mag2));
		return angle;
	}

	D3DXQUATERNION QuaternionNormalise(D3DXQUATERNION* a_Quat)
	{
		float mag = sqrt(a_Quat->w*a_Quat->w + a_Quat->x*a_Quat->x + a_Quat->y*a_Quat->y + a_Quat->z*a_Quat->z);
		a_Quat->w /= mag;
		a_Quat->x /= mag;
		a_Quat->y /= mag;
		a_Quat->z /= mag;
		return *a_Quat;
	}

	D3DXMATRIX QuaternionToMatrix(D3DXQUATERNION* a_Quat)
	{
		D3DXMATRIX mat;
		mat._11 = 1 - 2*pow(a_Quat->y,2) - 2*pow(a_Quat->z,2);
		mat._12 = 2*a_Quat->x*a_Quat->y - 2*a_Quat->z*a_Quat->w;
		mat._13 = 2*a_Quat->x*a_Quat->z + 2*a_Quat->y*a_Quat->w;
		mat._14 = 0.0f;
		mat._21 = 2*a_Quat->x*a_Quat->y + 2*a_Quat->z*a_Quat->w;
		mat._22 = 1 - 2*pow(a_Quat->x,2) - 2*pow(a_Quat->z,2);
		mat._23 = 2*a_Quat->z*a_Quat->y - 2*a_Quat->x*a_Quat->w;
		mat._24 = 0.0f;
		mat._31 = 2*a_Quat->z*a_Quat->x - 2*a_Quat->y*a_Quat->w;
		mat._32 = 2*a_Quat->z*a_Quat->y + 2*a_Quat->x*a_Quat->w;
		mat._33 = 1 - 2*pow(a_Quat->x,2) - 2*pow(a_Quat->y,2);
		mat._34 = 0.0f;
		mat._41 = 0.0f;
		mat._42 = 0.0f;
		mat._43 = 0.0f;
		mat._44 = 1.0f;
		return mat;
	}

	void ProjectOrthographic(D3DXMATRIX* a_pMat, float a_Width, float a_Height, float a_Near, float a_Far)
	{
		D3DXMATRIX multiply;
		Inverse(&multiply);
		multiply._11 = 1 / (a_Width/2);
		multiply._22 = 1 / (a_Height/2);
		multiply._33 = -2 / (a_Far - a_Near);
		multiply._34 = -(a_Far + a_Near)/(a_Far - a_Near);
		multiply._44 = 1.0f;
		Multiply(a_pMat,&multiply);
	}

	void ProjectPerspective(D3DXMATRIX* a_pMat)
	{
		//tbd
		D3DXMATRIX multiply;
		Inverse(&multiply);
		multiply._33 = 0.0f;
		Multiply(a_pMat,&multiply);
	}

	void ShearXY(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._12 = cos(a_Val);
		Multiply(a_Mat,&multiply);
	}

	void ShearYZ(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._23 = cos(a_Val);
		Multiply(a_Mat,&multiply);
	}

	void ShearZX(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._13 = cos(a_Val);
		Multiply(a_Mat,&multiply);
	}

	void ScaleX(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._11 *= a_Val;
		Multiply(a_Mat,&multiply);
	}

	void ScaleY(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._22 *= a_Val;
		Multiply(a_Mat,&multiply);
	}

	void ScaleZ(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._33 *= a_Val;
		Multiply(a_Mat,&multiply);
	}

	std::vector< std::vector<float> >* Identity(std::vector< std::vector<float> >* a_Mat)
	{
		for(unsigned short y=0;y<a_Mat->size();y++)
		{
			for(unsigned short x=0;x<a_Mat->size();x++)
			{
				a_Mat->at(y)[x];
			}
		}
		for(short n=0;n<4;n++)
			a_Mat->at(n)[n] = 1.0f;
		return a_Mat;
	}

	void ReflectX(D3DXMATRIX* a_Mat)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._11 *= -1;
		Multiply(a_Mat,&multiply);
	}
	void ReflectY(D3DXMATRIX* a_Mat)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._22 *= -1;
		Multiply(a_Mat,&multiply);
	}
	void ReflectZ(D3DXMATRIX* a_Mat)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._33 *= -1;
		Multiply(a_Mat,&multiply);
	}

	float Round(float a_Val, int a_Radix)
	{
		//radix is the degree if accuracy (number of decimal places)
		float degree = pow(10.0f,a_Radix);
		int mid = (int)(a_Val * degree);
		return ((float)mid) / degree;
	}

	std::vector< std::vector<float> >* Get2DVector(D3DXMATRIX* a_Mat)
	{
		std::vector< std::vector<float> >* out = new std::vector< std::vector<float> >();
		out->push_back(std::vector<float>());
		out->back().push_back(Round(a_Mat->_11,2));
		out->back().push_back(Round(a_Mat->_12,2));
		out->back().push_back(Round(a_Mat->_13,2));
		out->back().push_back(Round(a_Mat->_14,2));
		out->push_back(std::vector<float>());
		out->back().push_back(Round(a_Mat->_21,2));
		out->back().push_back(Round(a_Mat->_22,2));
		out->back().push_back(Round(a_Mat->_23,2));
		out->back().push_back(Round(a_Mat->_24,2));
		out->push_back(std::vector<float>());
		out->back().push_back(Round(a_Mat->_31,2));
		out->back().push_back(Round(a_Mat->_32,2));
		out->back().push_back(Round(a_Mat->_33,2));
		out->back().push_back(Round(a_Mat->_34,2));
		out->push_back(std::vector<float>());
		out->back().push_back(Round(a_Mat->_41,2));
		out->back().push_back(Round(a_Mat->_42,2));
		out->back().push_back(Round(a_Mat->_43,2));
		out->back().push_back(Round(a_Mat->_44,2));
		return out;
	}

	D3DXMATRIX* GetD3DXMATRIX(std::vector< std::vector<float> > a_Mat)
	{
		D3DXMATRIX* out = new D3DXMATRIX();
		out->_11 = a_Mat[0][0];
		out->_12 = a_Mat[0][1];
		out->_13 = a_Mat[0][2];
		out->_14 = a_Mat[0][3];
		out->_21 = a_Mat[1][0];
		out->_22 = a_Mat[1][1];
		out->_23 = a_Mat[1][2];
		out->_24 = a_Mat[1][3];
		out->_31 = a_Mat[2][0];
		out->_32 = a_Mat[2][1];
		out->_33 = a_Mat[2][2];
		out->_34 = a_Mat[2][3];
		out->_41 = a_Mat[3][0];
		out->_42 = a_Mat[3][1];
		out->_43 = a_Mat[3][2];
		out->_44 = a_Mat[3][3];
		return out;
	}

	//low level matrix functions
	void Inverse(D3DXMATRIX* a_Mat)
	{
		//
	}

	D3DXMATRIX* Identity(D3DXMATRIX* a_Mat)
	{
		a_Mat->_11 = 1.0f;
		a_Mat->_12 = 0.0f;
		a_Mat->_13 = 0.0f;
		a_Mat->_14 = 0.0f;
		a_Mat->_21 = 0.0f;
		a_Mat->_22 = 1.0f;
		a_Mat->_23 = 0.0f;
		a_Mat->_24 = 0.0f;
		a_Mat->_31 = 0.0f;
		a_Mat->_32 = 0.0f;
		a_Mat->_33 = 1.0f;
		a_Mat->_34 = 0.0f;
		a_Mat->_41 = 0.0f;
		a_Mat->_42 = 0.0f;
		a_Mat->_43 = 0.0f;
		a_Mat->_44 = 1.0f;
		return a_Mat;
	}

	void Identity9(Matrix9* a_Mat)
	{
		a_Mat->a = 1.0f;
		a_Mat->b = 0.0f;
		a_Mat->c = 0.0f;
		a_Mat->d = 0.0f;
		a_Mat->e = 1.0f;
		a_Mat->f = 0.0f;
		a_Mat->g = 0.0f;
		a_Mat->h = 0.0f;
		a_Mat->i = 1.0f;
	}
	void Multiply(D3DXMATRIX* a_M1, D3DXMATRIX* a_M2)
	{
		D3DXMATRIX resultant = *a_M1;
		resultant._11 = a_M1->_11*a_M2->_11 + a_M1->_12*a_M2->_21 + a_M1->_13*a_M2->_31 + a_M1->_14*a_M2->_41;
		resultant._12 = a_M1->_11*a_M2->_12 + a_M1->_12*a_M2->_22 + a_M1->_13*a_M2->_32 + a_M1->_14*a_M2->_42;
		resultant._13 = a_M1->_11*a_M2->_13 + a_M1->_12*a_M2->_23 + a_M1->_13*a_M2->_33 + a_M1->_14*a_M2->_43;
		resultant._14 = a_M1->_11*a_M2->_14 + a_M1->_12*a_M2->_24 + a_M1->_13*a_M2->_34 + a_M1->_14*a_M2->_44;
		resultant._21 = a_M1->_21*a_M2->_11 + a_M1->_22*a_M2->_21 + a_M1->_23*a_M2->_31 + a_M1->_24*a_M2->_41;
		resultant._22 = a_M1->_21*a_M2->_12 + a_M1->_22*a_M2->_22 + a_M1->_23*a_M2->_32 + a_M1->_24*a_M2->_42;
		resultant._23 = a_M1->_21*a_M2->_13 + a_M1->_22*a_M2->_23 + a_M1->_23*a_M2->_33 + a_M1->_24*a_M2->_43;
		resultant._24 = a_M1->_21*a_M2->_14 + a_M1->_22*a_M2->_24 + a_M1->_23*a_M2->_34 + a_M1->_24*a_M2->_44;
		resultant._31 = a_M1->_31*a_M2->_11 + a_M1->_32*a_M2->_21 + a_M1->_33*a_M2->_31 + a_M1->_34*a_M2->_41;
		resultant._32 = a_M1->_31*a_M2->_12 + a_M1->_32*a_M2->_22 + a_M1->_33*a_M2->_32 + a_M1->_34*a_M2->_42;
		resultant._33 = a_M1->_31*a_M2->_13 + a_M1->_32*a_M2->_23 + a_M1->_33*a_M2->_33 + a_M1->_34*a_M2->_43;
		resultant._34 = a_M1->_31*a_M2->_14 + a_M1->_32*a_M2->_24 + a_M1->_33*a_M2->_34 + a_M1->_34*a_M2->_44;
		resultant._41 = a_M1->_41*a_M2->_11 + a_M1->_42*a_M2->_21 + a_M1->_43*a_M2->_31 + a_M1->_44*a_M2->_41;
		resultant._42 = a_M1->_41*a_M2->_12 + a_M1->_42*a_M2->_22 + a_M1->_43*a_M2->_32 + a_M1->_44*a_M2->_42;
		resultant._43 = a_M1->_41*a_M2->_13 + a_M1->_42*a_M2->_23 + a_M1->_43*a_M2->_33 + a_M1->_44*a_M2->_43;
		resultant._44 = a_M1->_41*a_M2->_14 + a_M1->_42*a_M2->_24 + a_M1->_43*a_M2->_34 + a_M1->_44*a_M2->_44;
		*a_M1 = resultant;
	}

	float Determinant9(Matrix9* a_Mat)
	{
		float out = 0.0f;
		//multiply each element in any row or column by it's cofactor
		Matrix9 cofactorMat = *a_Mat;
		Cofactors9(&cofactorMat);
		out += a_Mat->a*cofactorMat.a;
		out += a_Mat->b*cofactorMat.b;
		out += a_Mat->c*cofactorMat.c;
		return out;
	}
	float Determinant4(float a,float b,float c,float d)
	{
		return a*d - b*c;
	}
	void Cofactors(D3DXMATRIX* a_Mat)
	{
		//make minor
		a_Mat = GetD3DXMATRIX(Minor(*Get2DVector(a_Mat)));
		//apply signs
		a_Mat->_12 *= -1;
		a_Mat->_14 *= -1;
		a_Mat->_21 *= -1;
		a_Mat->_23 *= -1;
		a_Mat->_32 *= -1;
		a_Mat->_34 *= -1;
		a_Mat->_41 *= -1;
		a_Mat->_43 *= -1;
	}
	void Cofactors9(Matrix9* a_Mat)
	{
		//make minor
		Minor9(a_Mat);
		//apply signs
		a_Mat->b *= -1;
		a_Mat->d *= -1;
		a_Mat->f *= -1;
		a_Mat->h *= -1;
	}
	void Minor9(Matrix9* a_Mat)
	{
		a_Mat->a = Determinant4(a_Mat->e,a_Mat->f,a_Mat->h,a_Mat->i);
		a_Mat->b = Determinant4(a_Mat->d,a_Mat->f,a_Mat->g,a_Mat->i);
		a_Mat->c = Determinant4(a_Mat->d,a_Mat->e,a_Mat->g,a_Mat->i);
		a_Mat->d = Determinant4(a_Mat->b,a_Mat->c,a_Mat->h,a_Mat->i);
		a_Mat->e = Determinant4(a_Mat->a,a_Mat->b,a_Mat->g,a_Mat->i);
		a_Mat->f = Determinant4(a_Mat->a,a_Mat->b,a_Mat->g,a_Mat->h);
		a_Mat->g = Determinant4(a_Mat->b,a_Mat->c,a_Mat->e,a_Mat->f);
		a_Mat->h = Determinant4(a_Mat->a,a_Mat->c,a_Mat->d,a_Mat->f);
		a_Mat->i = Determinant4(a_Mat->a,a_Mat->b,a_Mat->d,a_Mat->e);
	}
	//high level matrix functions
	void RotateX(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._22 = Round(cos(a_Val),5);
		multiply._23 = Round(-sin(a_Val),5);
		multiply._32 = Round(sin(a_Val),5);
		multiply._33 = Round(cos(a_Val),5);
		Multiply(a_Mat,&multiply);
	}

	void RotateY(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._11 = Round(cos(a_Val),5);
		multiply._13 = Round(sin(a_Val),5);
		multiply._31 = Round(-sin(a_Val),5);
		multiply._33 = Round(cos(a_Val),5);
		Multiply(a_Mat,&multiply);
	}

	void RotateZ(D3DXMATRIX* a_Mat, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._11 = Round(cos(a_Val),5);
		multiply._12 = Round(sin(a_Val),5);
		multiply._21 = Round(-sin(a_Val),5);
		multiply._22 = Round(cos(a_Val),5);
		Multiply(a_Mat,&multiply);
	}
	void TranslateX(D3DXMATRIX* a_M1, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._41 = a_Val;
		Multiply(a_M1,&multiply);
	}
	void TranslateY(D3DXMATRIX* a_M1, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._42 = a_Val;
		Multiply(a_M1,&multiply);
	}
	void TranslateZ(D3DXMATRIX* a_M1, float a_Val)
	{
		D3DXMATRIX multiply;
		Identity(&multiply);
		multiply._43 = a_Val;
		Multiply(a_M1,&multiply);
	}
	//2d vector functions
	std::vector< std::vector<float> > Empty(std::vector< std::vector<float> > a_Mat)
	{
		for(unsigned short y=0;y<a_Mat.size();y++)
		{
			for(unsigned short x=0;x<a_Mat.size();x++)
			{
				a_Mat[y][x] = 0.0f;
			}
		}
		return a_Mat;
	}

	float DotProduct(std::vector<float> a_Vec1, std::vector<float> a_Vec2)
	{
		if(a_Vec1.size() != a_Vec2.size())
			return -1.0f;
		float out = 0.0f;
		for(unsigned short n=0;n<a_Vec1.size();n++)
		{
			out += a_Vec1[n] * a_Vec2[n];
		}
		return out;
	}

	std::vector< std::vector<float> > Multiply(std::vector< std::vector<float> > a_M1, std::vector< std::vector<float> > a_M2)
	{
		//this is probably working (pretty sure)
		std::vector< std::vector<float> > resultant = a_M1;
		for(short y=0;y<4;y++)
		{
			for(short x=0;x<4;x++)
			{
				//a_M1[y][x] = a_M2[y][x];
				std::vector<float> row = a_M1[y];
				std::vector<float> column;
				for(short n=0;n<4;n++)
					column.push_back(a_M2[n][x]);
				resultant[y][x] = DotProduct(row,column);
				//do some hacky rounding to get rid of extraneous decimals
				//2 decimal places will do for now
				int whole = (int)(resultant[y][x]*100.0f);
				resultant[y][x] = ((float)whole) / 100.0f;
			}
		}
		return resultant;
	}

	std::vector< std::vector<float> > Cofactors(std::vector< std::vector<float> > a_Mat)
	{
		//this should work nao plz~
		//first, grab the minor matrix
		std::vector< std::vector<float> > cofactorOut = Minor(a_Mat);
		//now loop through it working out the cofactors of each elemement
		for(unsigned short y=0;y<cofactorOut.size();y++)
		{
			for(unsigned short x=0;x<cofactorOut.size();x++)
			{
				//then multiply it by it's respective sign to make it a cofactor
				if((x+y)%2)
					cofactorOut[y][x] *= -1;
			}
		}
		return cofactorOut;
	}

	//to find the determinant of any size matrix:
	//pick an element of the matrix 
	//multiply each element in a corresponding row or colum by their cofactors and sum them all (can be either)
	//sum all modified elements

	//to find the cofactor of an element, find the minor of the element then multiply the cofactor sign to it (alternating + and -, starting with + in the top left corner)
	//to find an element minor, remove the corresponding row and column from the matrix then find the determinant
	//repeat until you get down to a 2x2 or a 3x3 matrix, they have other formulae you can use
	float Determinant(std::vector< std::vector<float> > a_Mat)
	{
		//this is not working for 4x4~lol
		float out = 0.0f;
		//~`
		switch(a_Mat.size())
		{
		case(1):
			{
				out = a_Mat[0][0];
				break;
			}
		case(2):
			{
				//2x2
				out = a_Mat[0][0]*a_Mat[1][1] - a_Mat[1][0]*a_Mat[0][1];
				break;
			}
		case(3):
			{
				//3x3
				/*
				out += a_Mat[0][0]*a_Mat[1][1]*a_Mat[2][2];
				out += a_Mat[0][1]*a_Mat[1][2]*a_Mat[2][0];
				out += a_Mat[0][2]*a_Mat[1][0]*a_Mat[2][1];
				//
				out -= a_Mat[0][2]*a_Mat[1][1]*a_Mat[2][0];
				out -= a_Mat[0][1]*a_Mat[1][0]*a_Mat[2][2];
				out -= a_Mat[0][0]*a_Mat[1][2]*a_Mat[2][1];
				*/
				std::vector< std::vector<float> > cofactor9 = Cofactors(a_Mat);
				for(short x=0;x<3;x++)
				{
					out += a_Mat[0][x]*cofactor9[0][x];
				}
				break;
			}
		case(4):
			{
				//could optimise here - don't have to work out the cofactor of every element!
				std::vector< std::vector<float> > cofactor16 = Cofactors(a_Mat);
				//now multiply the elements of row or column by their cofactors and add the original element back on
				//pick central element 0,0 for simplicity's sake
				for(short y=0;y<4;y++)
				{
					out += a_Mat[y][0]*cofactor16[y][0] + a_Mat[y][0];
				}
				break;
			}
		}
		return out;
	}

	std::vector< std::vector<float> > Transpose(std::vector< std::vector<float> > a_Mat)
	{
		//this is working~
		std::vector< std::vector<float> > out = a_Mat;
		for(unsigned short y1=0;y1<a_Mat.size();y1++)
		{
			std::vector<float> column;
			//loop through y grabbing the values
			for(unsigned short y2=0;y2<a_Mat.size();y2++)
			{
				column.push_back(a_Mat[y2][y1]);
			}
			//replace the row with our new column
			out[y1] = column;
		}
		return out;
	}

	std::vector< std::vector<float> > Minor(std::vector< std::vector<float> > a_Mat)
	{
		//4x4 mats only for now~
		//fairlysurethisworks.jpg
		std::vector< std::vector<float> > minorOut = a_Mat;
		if(a_Mat.size() > 4 || a_Mat.size() < 2)
			return minorOut;
		for(unsigned short y1=0;y1<a_Mat.size();y1++)
		{
			for(unsigned short x=0;x<a_Mat[0].size();x++)
			{
				//loop through to remove the corresponding row and column
				std::vector< std::vector<float> > minorIn = a_Mat;
				minorIn.erase(minorIn.begin()+y1);
				for(unsigned short y2=0;y2<minorIn.size();y2++)
				{
					minorIn[y2].erase(minorIn[y2].begin()+x);
				}
				minorOut[y1][x] = Determinant(minorIn);
			}
		}
		return minorOut;
	}

	std::vector< std::vector<float> > Inverse(std::vector< std::vector<float> > a_Mat)
	{
		//miaow <^.^>
		//i am not a furry, but today is inverse day
		//uhh, what?
		std::vector< std::vector<float> > inverse16 = a_Mat;
		//first, grab the cofactor 
		inverse16 = Cofactors(inverse16);
		//next make it an adjoint (adjugate?) by transposing it
		inverse16 = Transpose(inverse16);
		//now divide all elements by the determinant of the original matrix
		float det = Determinant(a_Mat);
		//inverse only exists if determinant is non-zero
		if(!det)
			return a_Mat;
		for(unsigned short y=0;y<a_Mat.size();y++)
		{
			for(unsigned short x=0;x<a_Mat.size();x++)
			{
				inverse16[y][x] /= det;
			}
		}
		return inverse16;
	}
}

