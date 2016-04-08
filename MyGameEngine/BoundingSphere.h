#pragma once
#include "amVec3.h"

class BoundingSphere
{
public:
	amVec3 position;
	float radius;

	BoundingSphere(amVec3 _position = amVec3(0.0f), float _radius = 1.0f)
	{
		position = _position;
		radius = _radius;
	}
};