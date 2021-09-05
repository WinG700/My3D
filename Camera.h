#pragma once
#include "Actor.h"
class Camera :
    public Actor
{
public:
    Camera();
    ~Camera();
    Camera(const FTransfrom& trans);

    float FovX;
    Matrix4x4* PerspectiveMatrix;

	void SetFovX(const float& _FovX);
	Vector3 WorldToCamera(const Vector3& v3);
    Matrix4x4* GetPerspectiveMatrix();
    Matrix4x4* CreatePerPerspectiveMatrix(float N);
};

