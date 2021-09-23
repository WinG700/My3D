#pragma once
#include "Actor.h"
//#include "Windows.h"
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
    virtual void Tick(double DeltaSecond) override;
    void CameraMove(const Vector3& v3);
    int* screen_keys;
    int* mouse_x;
    int* mouse_y;
    int lastMouse_x;
    int lastMouse_y;
    double Mouse_Rot_factor = 20.0;
    double Move_factor = 100.0;
    double Lookup = 0;
    double Turn = 0;
};

