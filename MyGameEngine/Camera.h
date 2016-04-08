#pragma once
#include "Entity.h"
#include "amMatrixMath.h"

class Camera : public Entity
{
private:

public:
	amVec3 position;
	amVec3 direction;
	amVec3 up;

	amMatrix4x4 perspectiveMatrix;

	Camera(void);
	~Camera(void);

	void SetPerspectiveMatrix(float fovy, float aspectRatio, float near, float far );

	inline amMatrix4x4 GetPerspectiveMatrix()
	{
		return perspectiveMatrix;
	}

	///<summary>Gets the World Matrix as interpreted by the Camera</summary>
	///<returns>The matrix representing the world</returns>
	inline amMatrix4x4 GetWorldMatrix()
	{
		return amMatrixMath::LookAt(position.x, position.y, position.z, 
									direction.x, direction.y, direction.z,
									up.x, up.y, up.z);
	}

	BoundingSphere GetBoundingSphere()
	{
		return BoundingSphere();
	}
};

