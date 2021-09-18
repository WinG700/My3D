#pragma once

#include "Matrix.h"
#include "UTriangle.h"

struct PixelColor
{
	unsigned char* R;
	unsigned char* G;
	unsigned char* B;
	unsigned char* S;
};

struct BufferPoint
{
	float Z = 1.1f;

};

class Rasterization
{
public:
	Rasterization(unsigned char* P);

	PixelColor Pixel[screen_h][screen_w];
	BufferPoint Buffer[screen_h][screen_w];
	double ZBuffer[screen_h][screen_w];

	vector<UTriangle*> Triangles;

	void DrawBackground();

	void AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3, Color3 In_Color, bool bNormal = true);

	Vector3 ToScreenPoint(Vector3 InPoint);

	void DrawTringle(UTriangle* In_Triangles);
};

