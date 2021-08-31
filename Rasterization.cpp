#include "Rasterization.h"

Rasterization::Rasterization(unsigned char* P)
{
	for (int i = 0; i < screen_h; i++)
	{
		for (int j = 0; j < screen_w; j++)
		{
			Pixel[i][j].R = P + (i * screen_w + j) * 4;
			*Pixel[i][j].R = (unsigned char)(((float)i / screen_h) * 255.f);
			Pixel[i][j].G = P + (i * screen_w + j) * 4 + 1;
			Pixel[i][j].B = P + (i * screen_w + j) * 4 + 2;
			Pixel[i][j].S = P + (i * screen_w + j) * 4 + 3;
		}
	}
}
