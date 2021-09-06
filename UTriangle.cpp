#include "UTriangle.h"

UTriangle::UTriangle()
{

}

UTriangle::UTriangle(Vector3 In_Point1,
					Vector3 In_Point2, 
					Vector3 In_Point3) : 
					Point1(In_Point1), 
					Point2(In_Point2), 
					Point3(In_Point3)
{
	//Calculate_NormalVector();
}

UTriangle::UTriangle(Vector3 In_Point1,
					 Vector3 In_Point2, 
					 Vector3 In_Point3, 
	                 Color3 In_color) :
	                 Point1(In_Point1),
	                 Point2(In_Point2),
	                 Point3(In_Point3),
					 color3(In_color)
{
	//Calculate_NormalVector();
}

UTriangle::~UTriangle()
{
}

void UTriangle::Calculate_NormalVector()
{
	NormalVector = (Point2 - Point1)^(Point3 - Point1);
	NormalVector.Normalize();
}

