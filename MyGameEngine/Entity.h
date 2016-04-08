#pragma once
#include "BoundingSphere.h"

class Entity
{
public:
	virtual BoundingSphere GetBoundingSphere() = 0;
};