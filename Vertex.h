#pragma once
#include "Matrix.h"
class Vertex
{
public:
	Vector3 Location;
	Color3 Color;
	Vector2 Texcoord;

	Vertex() = default;
	~Vertex() = default;

	Vertex(const Vector3& InLocation, const Color3& InColor, const Vector2& InTexcoord);
};

