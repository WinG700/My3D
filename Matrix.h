#pragma once
#include <vector>
#include <iostream>
using namespace std;
class Matrix4x4;
class Matrix3x3;
class Vector3;
class Quaternions;

struct FTransfrom
{
	FTransfrom();
	Vector3 Location;
	Quaternions Quat;
	Vector3 Scale;
};

struct Matrix4x4
{
	Matrix4x4();
	Matrix4x4(float * f);
	float m[4][4];
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
};

struct Quaternions
{
	Quaternions();
	Quaternions(float In_x, float In_y, float In_z, float In_w);
	float x;
	float y;
	float z;
	float w;
};
