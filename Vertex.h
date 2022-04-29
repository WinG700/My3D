#pragma once
#include "Matrix.h"
class Vertex
{
public:
	Vector3 Location;
	Color3 Color;
	Vector2 Texcoord;
	Vector3 Normal;

	Vertex() = default;
	~Vertex() = default;

	Vertex(const Vector3& InLocation, const Color3& InColor = Color3(0, 0, 0), const Vector2& InTexcoord = Vector2(0.f, 0.f));
};

