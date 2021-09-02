#pragma once
#include "Matrix.h"
class UTriangle
{
public:
	Vector3 Point1;
	Vector3 Point2;
	Vector3 Point3;
	//面的法线
	Vector3 NormalVector;
	UTriangle();
	UTriangle(Vector3 In_Point1, Vector3 In_Point2, Vector3 In_Point3);
	~UTriangle();
	void Calculate_NormalVector();
};

