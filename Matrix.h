#pragma once
#include <vector>
#include <iostream>
using namespace std;
struct Matrix4x4;
struct Matrix3x3;
struct Vector3;
struct Quaternions;

struct Matrix4x4
{
	Matrix4x4();
	Matrix4x4(float * f);
	float m[4][4];
	Vector3 operator*(const Vector3 &v3);
	Matrix4x4 operator*(const Matrix4x4 &M4);
};

struct Matrix3x3
{
	float m[3][3];
};

struct Vector3
{
	Vector3();
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
};

struct Quaternions
{
	Quaternions();
	void Normalize();
	Quaternions(float In_x, float In_y, float In_z, float In_w);
	float x;
	float y;
	float z;
	float w;
	Quaternions operator*(const Quaternions& Quat);
};

struct FTransfrom
{
	FTransfrom();
	FTransfrom(const Vector3 &loc, const Quaternions &qua);
	FTransfrom(const Vector3& loc, const Quaternions& qua, const Vector3& sca);
	Vector3 Location;
	Quaternions Quat;
	Vector3 Scale;
};
