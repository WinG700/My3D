#pragma once
#include "Actor.h"
class Camera :
    public Actor
{
public:
    Camera();
    ~Camera();
    Camera(const FTransfrom& trans);

    double FovX;
    Matrix4x4* PerspectiveMatrix;

	void SetFovX(const double& _FovX);
	Vector3 WorldToCamera(const Vector3& v3);
    Matrix4x4* GetPerspectiveMatrix();
    Matrix4x4* CreatePerPerspectiveMatrix(double N, double F);
};

