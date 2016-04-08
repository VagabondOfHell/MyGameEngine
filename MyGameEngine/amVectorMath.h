#pragma once
#include "amVec3.h"
#include <math.h>

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

#ifndef Degree_To_Radians
#define Degree_To_Radians (PI/180.0)
#endif

namespace amVectorMath
{
	//Calculates Vec3 Dot Product
	static inline float CalcDotProduct(const amVec3& v1, const amVec3& v2)
	{
		return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
	}
	
	//Calculates the Vec3 magnitude
	static inline float CalcSqrtMagnitude(const amVec3& v1)
	{
		return (sqrt((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z)));
	}
	
	//Calcualtes Vec3 magnitude without square root
	static inline float CalcMagnitude(const amVec3& v1)
	{
		return ((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
	}

	//Calculates the perpendicular of a Vec3
	static inline amVec3 CalcCrossProduct(const amVec3& v1, const amVec3& v2)
	{
		float newX, newY, newZ;
		newX = (v1.y * v2.z) - (v1.z * v2.y);
		newY = (v1.z * v2.x) - (v1.x * v2.z);
		newZ = (v1.x * v2.y) - (v1.y * v2.x);

		return amVec3(newX, newY, newZ);
	}

	//Normalize Vec3 with the passed magnitude
	static inline amVec3 Normalize(const amVec3& v1, const float magnitude)
	{
		if(magnitude == 0)
			return amVec3();
		else
			return v1 / magnitude;
	}

	//Normalize and get magnitude of Vec3
	static inline amVec3 Normalize(const amVec3& v1)
	{
		float magnitude = CalcSqrtMagnitude(v1);

		return Normalize(v1, magnitude);
	}
	
	static inline float CalcAngleBetween(const amVec3& v1, const amVec3& v2)
	{
		float dotProd = CalcDotProduct(v1, v2);

		return ::acos(dotProd);
	}

	static inline float CalcNormdAngleBetween(const amVec3& v1, const amVec3& v2)
	{
		float dotProd = CalcDotProduct(v1, v2);
		float v1Mag = CalcSqrtMagnitude(v1);
		float v2Mag = CalcSqrtMagnitude(v2);

		float result = dotProd / (v1Mag * v2Mag);
		return ::acos(result);
	}

	static inline float ConvertRadiansToDegrees(float radians)
	{
		return radians * (180 / PI);
	}

	static inline float ConvertDegreesToRadians(float degrees)
	{
		return degrees * (PI / 180);
	}

};