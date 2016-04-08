#pragma once
#include "amVec3.h"

class Ray
{
public:
	amVec3 position;
	amVec3 direction;

	Ray(amVec3 _position = amVec3(0.0f), amVec3 _direction = amVec3(0.0f))
	{
		position = _position;
		direction = _direction;
	}
};