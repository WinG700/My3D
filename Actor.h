#pragma once
#include <string>
#include "Matrix.h"
#include "UTriangle.h"
class Actor
{
public:
	Actor();
	~Actor();
	Actor(const FTransfrom &Trans);

	FTransfrom ActorTransform;
	vector<UTriangle*> Triangles;
	string ActorName;

	void AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3, bool bNormal = true);
	void Tick(double DeltaSecond);
};

