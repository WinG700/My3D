#pragma once
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;
struct Matrix4x4;
struct Matrix3x3;
struct Vector3;
struct Quaternions;

#define PI 3.14159265359
#define Radian(x)  PI * x / 360.f

constexpr int screen_w = 800;
constexpr int screen_h = 450;



struct Matrix4x4
{
	Matrix4x4();
	Matrix4x4(float * f);
	float m[4][4];
	Vector3 operator*(const Vector3 &v3);
	Matrix4x4 operator*(const Matrix4x4 &M4);
	void CoutThis();
};

struct Matrix3x3
{
	float m[3][3];
};

struct Vector2
{
	Vector2();
	Vector2(float In_x, float In_y);
	float x;
	float y;
	float operator*(const Vector2& v2);
	Vector2 operator-(const Vector2& v2);
	static bool InTriangle(Vector2 A, Vector2 B, Vector2 C, Vector2 P);
	void CoutThis();
};

struct Vector3
{
	Vector3();
	Vector3(float all_value);
	Vector3(float In_x, float In_y, float In_z);
	float x;
	float y;
	float z;
	Vector3 operator+(const Vector3 &v3);
	Vector3 operator-(const Vector3& v3);
	//点积
	float operator*(const Vector3 &v3);
	//叉积
	Vector3 operator^(const Vector3 &v3);
	//归一化
	void Normalize();
	void CoutThis();

	
};

struct Quaternions
{
	Quaternions();
	Quaternions(Vector3 Axi, float Angle);
	Quaternions(float In_x, float In_y, float In_z, float In_w);
	float x;
	float y;
	float z;
	float w;
	Quaternions operator*(const Quaternions& Quat);
	void Normalize();
	Matrix4x4 ToMatrix4x4();
	void CoutThis();
	Vector3 GetForward();
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
	FTransfrom(const Vector3& loc, const Quaternions& qua, const Vector3& sca);
	Vector3 Location;
	Quaternions Quat;
	Vector3 Scale;
	Matrix4x4 ToAffineMatrix(bool WorldToRel = false);
	void CoutThis();
};
