#pragma once
#include "amVectorMath.h"
#include "BoundingSphere.h"

class Plane
{
public:
	amVec3 normal;
	float d;

	Plane(amVec3 _normal = amVec3(0.0f), float _d = (0.0f))
	{
		normal = _normal;
		d = _d;
	}

	bool IsBehind(BoundingSphere sphere)
	{
		return amVectorMath::CalcDotProduct(sphere.position, normal) < -sphere.radius;
	}
};