#pragma once
#include <string>
#include <cstdio>

#ifndef VERY_SMALL

#define VERY_SMALL 1.0e-9

#endif

#ifndef M_PI

#define M_PI 3.14159265358979323846f

#endif

#ifndef DEGREES_TO_RADIANS

#define DEGREES_TO_RADIANS (M_PI / 180.0f)

#endif 

struct amVec3
{
	float x,y,z;

	///Sets the values of the Vector
	inline void Set(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	inline amVec3(float _x = float(0.0f), float _y = float(0.0f), float _z = float (0.0f))
	{
		Set(_x, _y, _z);
	}

	inline amVec3(const amVec3& otherVec)
	{
		Set(otherVec.x, otherVec.y, otherVec.z);
	}

	//Overload array operator to access vector as an array (Reading)
	inline const float operator [] ( int index) const 
	{
		return *(&x + index);
	}

	//Overload array operator to access vector as an array (Writing)
	inline float& operator [] ( int index) 
	{
		return *(&x + index);
	} 

	//Overloads assignment operator
	inline amVec3& operator = (const amVec3& v)
	{
		Set(v.x, v.y, v.z);
		
		// return the existing object
		return *this;
	}

	//Overloads addition operator
	inline const amVec3 operator + (const amVec3& v) const
	{
		return amVec3(x + v.x, y + v.y, z + v.z);
	}

	//Overloads assigning addition operator
	inline const amVec3& operator += (const amVec3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	//Overloads negate operator
	inline const amVec3 operator - ()const
	{
		return amVec3(-x, -y, -z);
	}

	//Overloads subtraction operator
	inline amVec3 operator - (const amVec3& v)
	{
		return amVec3(x - v.x, y - v.y, z - v.z);
	}

	//Overloads assigning subtraction operator
	inline amVec3& operator -= (const amVec3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	//Overloads multiplication operator
	inline const amVec3 operator * (const float s) const
	{
		return amVec3(x * s, y * s, z * s);
	}

	//Overloads assigning multiplication operator
	inline amVec3& operator *= (const float s)
	{
		x *= s;
		y *= s;
		z *= s;

		return *this;
	}

	//Overloads multiplication operator to have scalar first
	inline friend amVec3 operator * (const float s, const amVec3& v)
	{
		return v * s;
	}

	//Overloads division operator
	inline const amVec3 operator / (const float s) const
	{
		#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
			if ( fabs(s) < VERY_SMALL ) {
				std::string errorMsg("Divide by nearly zero! ");
				throw errorMsg;
			}
		#endif

		return amVec3(x / s, y / s, z / s);		
	}

	//Overloads assignment division operator
	inline amVec3& operator /= (const float s)
	{
		#ifdef _DEBUG  /// If in debug mode let's worry about divide by zero or nearly zero!!! 
		if ( fabs(s) < VERY_SMALL ) {
			std::string errorMsg("Divide by nearly zero! ");
			throw errorMsg;
		}
		#endif

		x /= s;
		y /= s;
		z /= s;

		return *this;
	}

	inline void Normalize()
	{
		float mag = GetMagnitude();

		if(mag > 0.0f)
			*this = amVec3(x / mag, y / mag, z / mag);
	}

	inline float GetMagnitude()
	{
		return sqrtf(x * x + y * y + z * z);
	}

	//Print the vector to the console
	inline void PrintToConsole()
	{
		printf("x: %f, y: %f, z: %f\n", x, y, z);
	}
};