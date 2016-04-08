#pragma once
#include "BoundingSphere.h"
#include "AABoundingBox.h"
#include "Ray.h"
#include "Plane.h"

static class CollisionChecker
{
public:
	static bool SphereToSphereCollision(BoundingSphere& sphere1, BoundingSphere& sphere2);

	static bool SphereToAABoxCollision(const BoundingSphere& sphere, const AABoundingBox& box);

	static bool SphereToRayCollision(BoundingSphere& sphere, Ray& ray);

	static bool SphereToPlaneCollision(const BoundingSphere& sphere, const Plane& plane);

	static bool RayToPlaneCollision(Ray& ray, Plane& plane);

};

