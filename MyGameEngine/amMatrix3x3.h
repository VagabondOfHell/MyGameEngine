#pragma once
#include "amVec3.h"
#include "amMatrix4x4.h"

class amMatrix3x3
{
private:
	float m[9];

public:
	

	inline amMatrix3x3(const float value = 0.0f)
	{
		m[0] = value; m[3] = value; m[6] = value;  
		m[1] = value; m[4] = value; m[7] = value;  
		m[2] = value; m[5] = value; m[8] = value; 						
	}

	inline amMatrix3x3(float xx, float xy, float xz,
			float yx, float yy, float yz,
			float zx, float zy, float zz)
	{
		m[0] = xx; m[3] = xy; m[6] = xz;
		m[1] = yx; m[4] = yy; m[7] = yz; 
		m[2] = zx; m[5] = zy; m[8] = zz; 
	}

	~amMatrix3x3()
	{}

	inline void LoadIdentity()
	{
		m[0] = 1.0f; m[3] = 0.0f; m[6] = 0.0f;  
		m[1] = 0.0f; m[4] = 1.0f; m[7] = 0.0f;  
		m[2] = 0.0f; m[5] = 0.0f; m[8] = 1.0f; 	
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

	#define M(row,col)  m[(col*3)+row] //Gets the value of this matrix  
	#define N(row,col)  n[(col*3)+row] //Gets the value of the passed matrix
	#define P(row,col)  product[(col*3)+row] //Gets the value of the product matrix
	inline amMatrix3x3 operator*(const amMatrix3x3& n) const 
	{	
		amMatrix3x3 product;
		for (int i = 0; i < 3; i++) {
			float ai0=M(i,0),  ai1=M(i,1),  ai2=M(i,2);
			P(i,0) = ai0 * N(0,0) + ai1 * N(1,0) + ai2 * N(2,0);
			P(i,1) = ai0 * N(0,1) + ai1 * N(1,1) + ai2 * N(2,1);
			P(i,2) = ai0 * N(0,2) + ai1 * N(1,2) + ai2 * N(2,2);
		}

		return product;
	}
			/// Remove defines
	#undef M
	#undef N
	#undef P

	inline amMatrix3x3& operator*=(const amMatrix3x3& n)
	{
		return *this = *this * n;
	}

	inline amMatrix3x3 operator+(const amMatrix3x3& n) const
	{
		amMatrix3x3 returnMat;
		returnMat.LoadIdentity();

		for(int i = 0; i < 9; i++)
		{
			returnMat[i] = m[i] + n[i];
		}

		return returnMat;
	}

	inline amVec3 operator * (const amVec3 v) const
	{
		return amVec3(v.x * m[0] + v.y * m[3] + v.z * m[6],
					v.x * m[1] + v.y * m[4] + v.z * m[7] ,
					v.x * m[2] + v.y * m[5] + v.z * m[8] );
	}

	 // Copy constructor
	inline amMatrix3x3(const amMatrix4x4 &m)
    {
		*this = ExtractFrom4x4(m);
    }

	inline amMatrix3x3& operator= (const amMatrix4x4 &m)
	{
		// do the copy
		*this = ExtractFrom4x4(m);
 
		// return the existing object
		return *this;
	}

	inline amMatrix3x3 ExtractFrom4x4 (const amMatrix4x4 m)const
	{
		return amMatrix3x3(m[0], m[4], m[8],
							m[1], m[5], m[9],
							m[2], m[6], m[10]);
	}

	inline amMatrix3x3 Transpose()const
	{
		return amMatrix3x3(m[0], m[1], m[2],
							m[3], m[4], m[5],
							m[6], m[7], m[8]);
	}

	inline void Print()
	{
		printf("%f, %f, %f,\n%f, %f, %f,\n%f, %f, %f\n",
			m[0], m[3], m[6],
			m[1], m[4], m[7], 
			m[2], m[5], m[8]);
	}

	/// These allow me convert from type Matrix to const float * without issues
	inline operator float* () 
	{
		return static_cast<float*>( &m[0] );
	}

	inline operator const float* () const 
	{
		return static_cast<const float*>( &m[0]); 
	}

};