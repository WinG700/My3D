#include "Camera.h"
#include "Rasterization.h"

Camera::Camera()
{
	FovX = 90.0;
}

Camera::~Camera()
{
	delete PerspectiveMatrix;
}

Camera::Camera(const FTransfrom& trans) : Actor(trans)
{
	FovX = 90.0;
}

void Camera::SetFovX(const double& _FovX)
{
	FovX = _FovX;
}

Vector3 Camera::WorldToCamera(const Vector3& v3)
{
	return Vector3(v3.y, v3.z, v3.x);
}

Matrix4x4* Camera::GetPerspectiveMatrix()
{
	return PerspectiveMatrix;
}

Matrix4x4* Camera::CreatePerPerspectiveMatrix(double N, double F)
{
	PerspectiveMatrix = new Matrix4x4;
	PerspectiveMatrix->m[0][0] = 1.0f / tan(Radian(FovX/2.0)); PerspectiveMatrix->m[0][1] = 0.0f; PerspectiveMatrix->m[0][2] = 0.0f; PerspectiveMatrix->m[0][3] = 0.0f;
	PerspectiveMatrix->m[1][0] = 0; PerspectiveMatrix->m[1][1] = ((double)screen_w) / tan(Radian(FovX/2.0)) / ((double)screen_h); PerspectiveMatrix->m[1][2] = 0.0f; PerspectiveMatrix->m[1][2] = 0.0f;
	PerspectiveMatrix->m[2][0] = 0; PerspectiveMatrix->m[2][1] = 0.0f; PerspectiveMatrix->m[2][2] = F / (F - N); PerspectiveMatrix->m[2][3] = -1.0 * N * F / (F - N);
	PerspectiveMatrix->m[3][0] = 0; PerspectiveMatrix->m[3][1] = 0.0f; PerspectiveMatrix->m[3][2] = 1.0f; PerspectiveMatrix->m[3][3] = 0;
	return PerspectiveMatrix;
}


