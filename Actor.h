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
	vector<Vector3> Vertexs;
	string ActorName;
	void AddVertex(const vector<Vector3>& Vers);
	void AddTringle(const vector<vector<int>>& TringleArr);
	void AddTringle(const Vector3& Point1, const Vector3& Point2, const Vector3& Point3, bool bNormal = true);
	virtual void Tick(double DeltaSecond);
};

