#pragma once
#include "Matrix.h"
#include "Vertex.h"
class UTriangle
{
public:	
	Vertex* Point1;
	Vertex* Point2;
	Vertex* Point3;
	//面的法线
	Vector3 NormalVector;
	//Color3 color3;
	UTriangle();
	UTriangle(Vertex* In_Point1, Vertex* In_Point2, Vertex* In_Point3);
	//UTriangle(const Vertex& In_Point1, const Vertex& In_Point2, const Vertex& In_Point3);
	~UTriangle();
	void Calculate_NormalVector();
};

