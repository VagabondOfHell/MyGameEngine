#pragma once
#include "amVec3.h"

///Axis aligned bounding box
class AABoundingBox
{
public:
	amVec3 origin;
	float halfWidth;
	float halfHeight;
	float halfDepth;

	AABoundingBox(amVec3 _origin = amVec3(0.0f), float hw = 1.0f, float hh = 1.0f, float hd = 1.0f)
	{
		origin = _origin;
		halfWidth = hw;
		halfHeight = hh;
		halfDepth = hd;
	}

	AABoundingBox(amVec3 _min, amVec3 _max)
	{
		halfWidth = (_max.x - _min.x) * 0.5f;
		halfHeight = (_max.y - _min.y) * 0.5f;
		halfDepth = (_max.z - _min.z) * 0.5f;

		origin = amVec3(_max.x - halfWidth,
						_max.y - halfHeight,
						_max.z - halfDepth);
	}

	inline float GetWidth()
	{
		return halfWidth * 2;
	}

	inline float GetHeight()
	{
		return halfHeight * 2;
	}

	inline float GetDepth()
	{
		return halfDepth * 2;
	}

	void GetVertices(amVec3* vertexArray)
	{
		//Back face
		vertexArray[0] = amVec3(origin.x - halfWidth, origin.y + halfHeight, origin.z - halfDepth);
		vertexArray[1] = amVec3(origin.x + halfWidth, origin.y + halfHeight, origin.z - halfDepth);
		vertexArray[2] = amVec3(origin.x + halfWidth, origin.y - halfHeight, origin.z - halfDepth);
		vertexArray[3] = amVec3(origin.x - halfWidth, origin.y - halfHeight, origin.z - halfDepth);
		
		//Front Face
		vertexArray[4] = amVec3(origin.x - halfWidth, origin.y + halfHeight, origin.z + halfDepth);
		vertexArray[5] = amVec3(origin.x + halfWidth, origin.y + halfHeight, origin.z + halfDepth);
		vertexArray[6] = amVec3(origin.x + halfWidth, origin.y - halfHeight, origin.z + halfDepth);
		vertexArray[7] = amVec3(origin.x - halfWidth, origin.y - halfHeight, origin.z + halfDepth);
	}
};