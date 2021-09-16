#include "Actor.h"

Actor::Actor()
{

}

Actor::~Actor()
{
}

Actor::Actor(const FTransfrom& Trans)
{
	ActorTransform = Trans;
}

void Actor::AddVertex(const vector<Vector3>& Vers)
{
	Vertexs.clear();
	for (const Vector3& k : Vers)
	{
		Vertexs.push_back(k);
	}
}

void Actor::AddTringle(const Vector3& Point1, const Vector3& Point2, const Vector3& Point3, bool bNormal)
{

	UTriangle* LocalVar = new UTriangle(Point1, Point2, Point3);
	LocalVar->color3.R = rand() * 255 / 100;
	LocalVar->color3.G = rand() * 255 / 100;
	LocalVar->color3.B = rand() * 255 / 100;
	if(bNormal)LocalVar->Calculate_NormalVector();
	Triangles.push_back(LocalVar);
}

void Actor::AddTringle(const vector<vector<int>>& TringleArr)
{
	for (const vector<int>& k : TringleArr)
	{
		if (k.size() == 3)
		{
			AddTringle(Vector3(Vertexs[k[0]]), Vector3(Vertexs[k[1]]), Vector3(Vertexs[k[2]]));
		}
	}
}

void Actor::Tick(double DeltaSecond)
{
	
}
