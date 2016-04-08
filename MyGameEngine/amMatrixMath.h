#pragma once
#include "amVectorMath.h"
#include "amMatrix4x4.h"
#include "amVec3.h"
#include "Plane.h"

struct ProjectionFrustum
{
	Plane topPlane, leftPlane, rightPlane, bottomPlane, nearPlane, farPlane;

	ProjectionFrustum(){}

	ProjectionFrustum(Plane top, Plane bottom, Plane left, Plane right, Plane _nearPlane, Plane _farPlane)
	{
		topPlane = top;
		bottomPlane = bottom;
		leftPlane = left;
		rightPlane = right;
		nearPlane = _nearPlane;
		farPlane = _farPlane;
	}

	void NormalizeAllPlanes()
	{
		topPlane.normal.Normalize();
		bottomPlane.normal.Normalize();
		leftPlane.normal.Normalize();
		rightPlane.normal.Normalize();
		nearPlane.normal.Normalize();
		farPlane.normal.Normalize();
	}
};

namespace amMatrixMath
{
	static inline amMatrix4x4 Frustum(float left, float right, float bottom, float top, float n, float f)
	{
		amMatrix4x4 result(amMatrix4x4::LoadIdentity());

		if ((right == left) ||
			(top == bottom) ||
			(n == f) ||
			(n < 0.0) ||
			(f < 0.0))
			return amMatrix4x4::LoadIdentity();

		return amMatrix4x4((2.0f * n) / (right - left), 0.0f, 0.0f, 0.0f,
					0.0f, (2.0f * n) / (top - bottom), 0.0f, 0.0f,
					(right + left) / (right - left), (top + bottom) / (top - bottom), -(f + n) / (f - n), -1.0f,
					0.0f, 0.0f, -(2.0f * f * n) / (f - n), 0.0f);

	}

	static amMatrix4x4 Rotate(float angle, float x, float y, float z)
	{
		float cosang, sinang, cosm;
		amMatrix4x4 m;
		amVec3 rotAxis(x,y,z);
		rotAxis = amVectorMath::Normalize(rotAxis);
	
		angle *= DEGREES_TO_RADIANS;

		cosang = cos(angle);
		sinang = sin(angle);
		cosm = (1.0f - cosang);

		m[0] = (rotAxis.x * rotAxis.x * cosm) + cosang;
		m[1] = (rotAxis.x * rotAxis.y * cosm) + (rotAxis.z * sinang);
		m[2] = (rotAxis.x * rotAxis.z * cosm) - (rotAxis.y * sinang);
		m[3] = 0.0;
		m[4] = (rotAxis.x * rotAxis.y * cosm) - (rotAxis.z * sinang);
		m[5] = (rotAxis.y * rotAxis.y * cosm) + cosang;
		m[6] = (rotAxis.y * rotAxis.z * cosm) + (rotAxis.x * sinang);
		m[7] = 0.0;
		m[8] = (rotAxis.x * rotAxis.z * cosm) + (rotAxis.y * sinang);
		m[9] = (rotAxis.y * rotAxis.z * cosm) - (rotAxis.x * sinang);
		m[10] =(rotAxis.z * rotAxis.z * cosm) + cosang;
		m[11] = 0.0;
		m[12] = 0.0;	
		m[13] = 0.0;
		m[14] = 0.0;
		m[15] = 1.0;
		return m;
	}

	static amMatrix4x4 Translate(float x, float y, float z)
	{
		return amMatrix4x4(1.0f, 0.0f, 0.0f, x,
				  0.0f, 1.0f, 0.0f, y,
				  0.0f, 0.0f, 1.0f, z,
				  0.0f, 0.0f, 0.0f,	1.0f); 
	}

	static amMatrix4x4 Scale(float x, float y, float z)
	{
		return amMatrix4x4(x,	0.0f, 0.0f, 0.0f,
					 0.0f, y   , 0.0f, 0.0f,
					0.0f, 0.0f, z,    0.0f,
					0.0f, 0.0f, 0.0f,	1.0f); 
	}

	static amMatrix4x4 Perspective(float fFov, float fAspect, float zMin, float zMax)
	{
		amMatrix4x4 m;
		m.LoadIdentity();
		float yMax = zMin * tanf(fFov * 0.5f * DEGREES_TO_RADIANS);
		float yMin = -yMax;
		float xMin = yMin * fAspect;
		float xMax = -xMin; 
    
		m[0] = (2.0f * zMin) / (xMax - xMin);
		m[5] = (2.0f * zMin) / (yMax - yMin);
		m[8] = (xMax + xMin) / (xMax - xMin);
		m[9] = (yMax + yMin) / (yMax - yMin);
		m[10] = -((zMax + zMin) / (zMax - zMin));
		m[14] = -1.0f;
		m[11] = -((2.0f * (zMax*zMin))/(zMax - zMin));
		m[15] = 0.0f;
		return m;
	}

	static ProjectionFrustum ExtractPlanesFromPerspective(amMatrix4x4 perspectiveMatrix, bool normalize)
	{
		ProjectionFrustum frustum;
		frustum.leftPlane = Plane(amVec3(perspectiveMatrix[12] + perspectiveMatrix[0],
							perspectiveMatrix[13] + perspectiveMatrix[1],
							perspectiveMatrix[14] + perspectiveMatrix[2]),
							perspectiveMatrix[15] + perspectiveMatrix[3]);

		frustum.rightPlane = Plane(amVec3(perspectiveMatrix[12] - perspectiveMatrix[0],
							perspectiveMatrix[13] - perspectiveMatrix[1],
							perspectiveMatrix[14] - perspectiveMatrix[2]),
							perspectiveMatrix[15] - perspectiveMatrix[3]);

		frustum.topPlane = Plane(amVec3(perspectiveMatrix[12] - perspectiveMatrix[4],
							perspectiveMatrix[13] - perspectiveMatrix[5],
							perspectiveMatrix[14] - perspectiveMatrix[6]),
							perspectiveMatrix[15] - perspectiveMatrix[7]);

		frustum.bottomPlane = Plane(amVec3(perspectiveMatrix[12] + perspectiveMatrix[4],
							perspectiveMatrix[13] + perspectiveMatrix[5],
							perspectiveMatrix[14] + perspectiveMatrix[6]),
							perspectiveMatrix[15] + perspectiveMatrix[7]);

		frustum.nearPlane = Plane(amVec3(perspectiveMatrix[12] + perspectiveMatrix[8],
							perspectiveMatrix[13] + perspectiveMatrix[9],
							perspectiveMatrix[14] + perspectiveMatrix[10]),
							perspectiveMatrix[15] + perspectiveMatrix[11]);

		frustum.farPlane = Plane(amVec3(perspectiveMatrix[12] - perspectiveMatrix[8],
							perspectiveMatrix[13] - perspectiveMatrix[9],
							perspectiveMatrix[14] - perspectiveMatrix[10]),
							perspectiveMatrix[15] - perspectiveMatrix[11]);

		if(normalize)
			frustum.NormalizeAllPlanes();

		return frustum;
	}

	static amMatrix4x4 Orthographic(float xMin, float xMax,
								float yMin, float yMax,
								float zMin, float zMax)
	{
		amMatrix4x4 m;
		m[0] = 2.0f / (xMax - xMin);
		m[5] = 2.0f / (yMax - yMin);
		m[10] = -2.0f / (zMax - zMin);
		m[12] = -((xMax + xMin) / (xMax - xMin));
		m[13] = -((yMax + yMin) / (yMax - yMin));
		m[14] = -((zMax + zMin) / (zMax - zMin));
		m[15] = 1.0f;
		return m;
	}

	static amMatrix4x4 LookAt(float eyeX, float eyeY, float eyeZ,
							float atX,  float atY,  float atZ,
							float upX,  float upY,  float upZ)
	{
		/// These are the default vectors of the eye according to OpenGL
		///	origin(0.0f,0.0f,0.0f);
		/// up(0.0f,1.0f,0.0f);
		/// forward(0.0f,0.0f,-1.0f);

		amVec3 at(atX,atY,atZ);
		amVec3 up(upX,upY,upZ);
		amVec3 eye(eyeX,eyeY,eyeZ);

		amMatrix4x4 result;

		amVec3 forward = amVectorMath::Normalize(at - eye);
		up = amVectorMath::Normalize(up);
		amVec3 side = amVectorMath::Normalize( amVectorMath::CalcCrossProduct(forward,up));
		up = amVectorMath::CalcCrossProduct(side,forward);

		result[0] = side.x;
		result[1] = side.y;
		result[2] = side.z;
		result[3] = 0.0;

		result[4] = up.x;
		result[5] = up.y;
		result[6] = up.z;
		result[7] = 0.0;

		result[8]  = -forward.x;
		result[9]  = -forward.y;
		result[10] = -forward.z;
		result[11] = 0.0;
	
		result[12] = -amVectorMath::CalcDotProduct(side,eye);	
		result[13] = -amVectorMath::CalcDotProduct(up,eye);
		result[14] =  amVectorMath::CalcDotProduct(forward,eye);
		result[15] = 1.0;

		return result;
	}

};