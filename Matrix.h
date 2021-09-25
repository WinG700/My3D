#pragma once
#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <cmath>
using namespace std;
struct Matrix4x4;
struct Matrix3x3;
struct Vector3;
struct Vector4;
struct Quaternions;

#define PI 3.14159265359
#define Radian(x)  PI * x / 180.0
#define NearZero(x) x <= 0.00000001 && x>=-0.00000001
#define NearPlane 1.0
#define FarPlane 3000.0
#define MaxMin(ma, mi, val) max(min(val, ma), mi)
#define DoubleLerp(x,y,z) x+MaxMin(1.0, 0.0, z)*(y-x) 

constexpr int screen_w = 800;
constexpr int screen_h = 450;

Vector3 operator*(const double& k, const Vector3& v3);
//char* LoadTe

struct Matrix4x4
{
	Matrix4x4();
	Matrix4x4(double* f);
	double m[4][4];
	Vector3 operator*(const Vector3 &v3);
	Vector3 operator&(const Vector3& v3);
	Vector4 operator^(const Vector3 &v3);
	Matrix4x4 operator*(const Matrix4x4 &M4);
	void CoutThis(string head);
};

struct Matrix3x3
{
	double m[3][3];
};

struct Vector2
{
	Vector2();
	Vector2(double In_x, double In_y);
	double x;
	double y;
	double operator*(const Vector2& v2);
	Vector2 operator-(const Vector2& v2);
	static bool InTriangle(Vector2 A, Vector2 B, Vector2 C, Vector2 P);
	void CoutThis(string head);
};

struct Vector3
{
	Vector3();
	Vector3(double all_value);
	Vector3(double In_x, double In_y, double In_z);
	double x;
	double y;
	double z;
	Vector3 operator+(const Vector3 &v3);
	Vector3 operator-(const Vector3& v3);
	//点积
	double operator*(const Vector3 &v3);
	//叉积
	Vector3 operator^(const Vector3 &v3);

	Vector3 operator*(const double& k);
	//归一化
	void Normalize();
	void CoutThis(string head);
	void CheckZero();
};

struct Vector4
{
	Vector4();
	//Vector4(double all_value);
	Vector4(double In_x, double In_y, double In_z, double In_w);
	double x;
	double y;
	double z;
	double w;
	void CoutThis(string head);
};

struct Quaternions
{
	Quaternions();
	Quaternions(Vector3 Axi, double Angle);
	Quaternions(double In_x, double In_y, double In_z, double In_w);
	double x;
	double y;
	double z;
	double w;
	Quaternions operator*(const Quaternions& Quat);
	void Normalize();
	Matrix4x4 ToMatrix4x4();
	void CoutThis(string head);
	Vector3 GetForward();
	Vector3 GetRight();
	Vector3 GetUp();
	Quaternions Inversed();

};

struct Color3
{
	Color3();
	Color3(int In_R, int In_G, int In_B);
	int R;
	int G;
	int B;
	int S;

};

struct FTransfrom
{
	FTransfrom();
	FTransfrom(const Vector3 &loc, const Quaternions &qua);
	FTransfrom(const Vector3 &loc, const Quaternions &qua, const Vector3 &sca);
	Vector3 Location;
	Quaternions Quat;
	Vector3 Scale;
	Matrix4x4 ToAffineMatrix(bool WorldToRel = false);
	void CoutThis(string head);
};
