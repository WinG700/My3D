#pragma once

#include "Matrix.h"

constexpr int screen_w = 1280;
constexpr int screen_h = 720;

struct PixelColor
{
	unsigned char* R;
	unsigned char* G;
	unsigned char* B;
	unsigned char* S;
};

class Rasterization
{
public:
	Rasterization(unsigned char* P);

	PixelColor Pixel[screen_h][screen_w];
};

