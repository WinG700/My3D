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

	/** ��Ҫ���Ƶ������� */
	vector<UTriangle*> Triangles;
	/** ��Ҫ���Ƶ������ζ��� */
	vector<Vertex*> Vertexs;
	string ActorName;
	void AddVertex(const vector<Vertex*>& Vers);
	void AddTringle(const vector<vector<int>>& TringleArr);
	void AddTringle(Vertex* Point1, Vertex* Point2, Vertex* Point3, bool bNormal = true);
	virtual void Tick(double DeltaSecond);
};

