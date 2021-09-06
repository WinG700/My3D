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

void Actor::AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3, bool bNormal)
{

	UTriangle* LocalVar = new UTriangle(Point1, Point2, Point3);
	LocalVar->color3.R = rand() * 255 / 100;
	LocalVar->color3.G = rand() * 255 / 100;
	LocalVar->color3.B = rand() * 255 / 100;
	if(bNormal)LocalVar->Calculate_NormalVector();
	Triangles.push_back(LocalVar);
}

void Actor::Tick(double DeltaSecond)
{

}
