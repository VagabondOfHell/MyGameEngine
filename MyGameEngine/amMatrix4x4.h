#pragma once
#include<stdio.h>
#include "amVec3.h"

class amMatrix4x4
{

private:
	float m[16];

public:
	inline amMatrix4x4(const float value = 0.0f)
	{
		m[0] = value; m[4] = value; m[8] = value;  m[12] = value;
		m[1] = value; m[5] = value; m[9] = value;  m[13] = value;
		m[2] = value; m[6] = value; m[10] = value; m[14] = value;
		m[3] = value; m[7] = value; m[11] = value; m[15] = value;
	}

	inline amMatrix4x4(float xx, float xy, float xz, float xw,
			float yx, float yy, float yz, float yw,
			float zx, float zy, float zz, float zw, 
			float wx, float wy, float wz, float ww)
	{
		m[0] = xx; m[4] = xy; m[8] = xz;  m[12] = xw;
		m[1] = yx; m[5] = yy; m[9] = yz;  m[13] = yw;
		m[2] = zx; m[6] = zy; m[10] = zz; m[14] = zw;
		m[3] = wx; m[7] = wy; m[11] = wz; m[15] = ww;
	}

	~amMatrix4x4()
	{}

	inline static amMatrix4x4 LoadIdentity()
	{
		return amMatrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f, 
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f);
	}

	//Operator Overloads
		
	//Access class as an array [read from]
	inline const float operator[](const int index)const
	{
		return *(m+index);
	}
		
	//Access class as an array [write to]
	inline float& operator[](const int index)
	{
		return *(m + index);
	}

	#define M(row,col)  m[(col*4)+row] //Gets the value of this matrix  
	#define N(row,col)  n[(col*4)+row] //Gets the value of the passed matrix
	#define P(row,col)  product[(col*4)+row] //Gets the value of the product matrix
	inline amMatrix4x4 operator*(const amMatrix4x4& n) const 
	{	
		amMatrix4x4 product;
		for (int i = 0; i < 4; i++) {
			float ai0=M(i,0),  ai1=M(i,1),  ai2=M(i,2),  ai3=M(i,3);
			P(i,0) = ai0 * N(0,0) + ai1 * N(1,0) + ai2 * N(2,0) + ai3 * N(3,0);
			P(i,1) = ai0 * N(0,1) + ai1 * N(1,1) + ai2 * N(2,1) + ai3 * N(3,1);
			P(i,2) = ai0 * N(0,2) + ai1 * N(1,2) + ai2 * N(2,2) + ai3 * N(3,2);
			P(i,3) = ai0 * N(0,3) + ai1 * N(1,3) + ai2 * N(2,3) + ai3 * N(3,3);
		}

		return product;
	}
			/// Remove defines
	#undef M
	#undef N
	#undef P

	inline amMatrix4x4& operator*=(const amMatrix4x4& n)
	{
		return *this = *this * n;
	}

	inline amMatrix4x4 operator+(const amMatrix4x4& n) const
	{
		amMatrix4x4 returnMat;
		returnMat.LoadIdentity();

		for(int i = 0; i < 16; i++)
		{
			returnMat[i] = m[i] + n[i];
		}

		return returnMat;
	}

	//Vec4 operator * (const Vec4 v)const;
	inline amVec3 operator * (const amVec3 v) const
	{
		return amVec3(v.x * m[0] + v.y * m[4] + v.z * m[8] + m[12],
					v.x * m[1] + v.y * m[5] + v.z * m[9] + m[13],
					v.x * m[2] + v.y * m[6] + v.z * m[10] + m[14]);
	}

	inline amMatrix4x4 Inverse() {
		amMatrix4x4 m = *this;
		amMatrix4x4 inverseM;
		float det;

		inverseM[0] =  m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15] + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
		inverseM[1] = -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15] - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
		inverseM[2] =  m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15] + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
		inverseM[3] = -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11] - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
		inverseM[4] = -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15] - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
		inverseM[5] =  m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15] + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
		inverseM[6] = -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15] - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
		inverseM[7] =  m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11] + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
		inverseM[8] =  m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15] + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
		inverseM[9] = -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15] - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
		inverseM[10] = m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15] + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
		inverseM[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11] - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
		inverseM[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14] - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
		inverseM[13] =  m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14] + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
		inverseM[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14] - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
		inverseM[15] =  m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10] + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];

		det = m[0] * inverseM[0] + m[1] * inverseM[4] + m[2] * inverseM[8] + m[3] * inverseM[12];
		
#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if ( fabs(det) < VERY_SMALL ) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
#endif
		det = 1.0f / det;
		for (int i = 0; i < 16; i++){
			inverseM[i] *= det;
		}
		return inverseM;
}

	inline amMatrix4x4 Transpose() const
	{
		return amMatrix4x4(m[0], m[1], m[2], m[3],
							m[4], m[5], m[6], m[7],
							m[8], m[9], m[10], m[11],
							m[12], m[13], m[14], m[15]);
	}

	inline void Print()
	{
		printf("%f, %f, %f, %f,\n%f, %f, %f, %f,\n%f, %f, %f, %f,\n%f, %f, %f, %f\n\n",
			m[0], m[4], m[8], m[12],
			m[1], m[5], m[9], m[13],
			m[2], m[6], m[10], m[14],
			m[3], m[7], m[11], m[15]);
	}
};
