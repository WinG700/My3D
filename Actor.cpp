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

void Actor::AddVertex(const vector<Vertex*>& Vers)
{
	Vertexs.clear();
	for (Vertex* k : Vers)
	{
		Vertexs.push_back(k);
	}
}

void Actor::AddTringle(Vertex* Point1, Vertex* Point2, Vertex* Point3, bool bNormal)
{

	UTriangle* LocalVar = new UTriangle(Point1, Point2, Point3);
	//LocalVar->color3.R = rand() * 255 / 100;
	//LocalVar->color3.G = rand() * 255 / 100;
	//LocalVar->color3.B = rand() * 255 / 100;
	if(bNormal)LocalVar->Calculate_NormalVector();
	Triangles.push_back(LocalVar);
}

void Actor::AddTringle(const vector<vector<int>>& TringleArr)
{
	for (const vector<int>& k : TringleArr)
	{
		if (k.size() == 3)
		{
			if (k[0] < Vertexs.size() && k[1] < Vertexs.size() && k[2] < Vertexs.size())
			{
				AddTringle(Vertexs[k[0]], Vertexs[k[1]], Vertexs[k[2]]);
			}
			else
			{
				cout << " add tringle arr is error " <<endl;
			}
		}
	}
}

void Actor::Tick(double DeltaSecond)
{
	
}
