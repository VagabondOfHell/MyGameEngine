#include "Camera.h"


Camera::Camera(void)
{
}


Camera::~Camera(void)
{
}

void Camera::SetPerspectiveMatrix(float fovy, float aspectRatio, float near, float far )
{
	perspectiveMatrix = amMatrixMath::Perspective(fovy, aspectRatio, near, far);
}