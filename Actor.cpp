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

void Actor::AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3)
{
	Triangles.push_back(new UTriangle(Point1, Point2, Point3));
}
