#include "Camera.h"
#include "Rasterization.h"
//#include "windows.h"

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

void Camera::Tick(double DeltaSecond)
{
	//0x02ÊÇVK_RBUTTON
	if (screen_keys['W'] || screen_keys['w'])
	{
		CameraMove(ActorTransform.Quat.GetForward() * Move_factor * DeltaSecond);
	}
	if (screen_keys['A'] || screen_keys['a'])
	{
		CameraMove(ActorTransform.Quat.GetRight() * Move_factor * DeltaSecond * -1.0);
	}
	if (screen_keys['D'] || screen_keys['d'])
	{
		CameraMove(ActorTransform.Quat.GetRight() * Move_factor * DeltaSecond);
	}
	if (screen_keys['S'] || screen_keys['s'])
	{
		CameraMove(ActorTransform.Quat.GetForward() * Move_factor * DeltaSecond * -1.0);
	}
	if (screen_keys[0x02] && !(* mouse_x == lastMouse_x && *mouse_y == lastMouse_y))
	{
		double x = *mouse_x - lastMouse_x;
		double y = *mouse_y - lastMouse_y;
		Turn += x * Mouse_Rot_factor * DeltaSecond;
		Lookup += y * Mouse_Rot_factor * DeltaSecond;
		//v3 = ActorTransform.Quat.GetRight();
		//v3.z = 0;
		//v3.Normalize();
		//ActorTransform.Quat = ActorTransform.Quat * Quaternions(v3, y* Mouse_Rot_factor * DeltaSecond);
		ActorTransform.Quat = Quaternions(Vector3(0, 0, 1), Turn) * Quaternions(Vector3(0, 1, 0), Lookup);
		//v3.Normalize();
		//Quaternions Q = Quaternions(v3, Mouse_Rot_factor * sqrt(x * x + y * y));
	}
	lastMouse_x = *mouse_x;
	lastMouse_y = *mouse_y;
	//cout << *mouse_x << " " << *mouse_y << endl;
}

void Camera::CameraMove(const Vector3& v3)
{
	ActorTransform.Location = ActorTransform.Location + v3;
}

