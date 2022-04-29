#include "UTriangle.h"

UTriangle::UTriangle()
{

}

UTriangle::UTriangle(Vertex* In_Point1, 
					 Vertex* In_Point2, 
					 Vertex* In_Point3):
					Point1(In_Point1), 
					Point2(In_Point2), 
					Point3(In_Point3)
{
	//Calculate_NormalVector();
}

UTriangle::~UTriangle()
{
}

void UTriangle::Calculate_NormalVector()
{
	NormalVector = (Point2->Location - Point1->Location)^(Point3->Location - Point1->Location);
	NormalVector.Normalize();
	//NormalVector.CoutThis();
}

