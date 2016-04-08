#include "CollisionChecker.h"
#include "amVectorMath.h"

bool CollisionChecker::SphereToSphereCollision(BoundingSphere& sphere1, BoundingSphere& sphere2)
{
	amVec3 posDiff = sphere1.position - sphere2.position;

	return amVectorMath::CalcSqrtMagnitude(posDiff) <= sphere1.radius + sphere2.radius;
}

bool CollisionChecker::SphereToAABoxCollision(const BoundingSphere& sphere, const AABoundingBox& box)
{
	return false;
}

bool CollisionChecker::SphereToRayCollision(BoundingSphere& sphere, Ray& ray)
{
	float det,projection;
	amVec3 posDiff = sphere.position - ray.position;

	projection = amVectorMath::CalcDotProduct(posDiff, ray.direction);
	det = projection * projection - amVectorMath::CalcDotProduct(posDiff, posDiff) + sphere.radius * sphere.radius;

	if(det < 0)
		return false;

	det = sqrtf(det);

	float intersect1 = projection - det;
	float intersect2 = projection + det;

	if(intersect2 < 0)
		return false;

	if(intersect1 < 0)
		intersect1 = 0;

	return true;
}

bool CollisionChecker::SphereToPlaneCollision(const BoundingSphere& sphere, const Plane& plane)
{
	return false;
}

bool CollisionChecker::RayToPlaneCollision(Ray& ray, Plane& plane)
{
	float normalAndRayDot = amVectorMath::CalcDotProduct(plane.normal, ray.direction);

	if(fabs(normalAndRayDot) < VERY_SMALL)
		return false;

	float timeOfCollision = -(amVectorMath::CalcDotProduct(ray.position, plane.normal) + plane.d) / normalAndRayDot;

	if(timeOfCollision < 0.0f)
		return false;

	amVec3 contactPoint = amVec3(ray.position + ray.direction * timeOfCollision);
	
	return true;
}