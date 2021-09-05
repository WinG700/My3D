#include "Rasterization.h"

Rasterization::Rasterization(unsigned char* P)
{
	for (int i = 0; i < screen_h; i++)
	{
		for (int j = 0; j < screen_w; j++)
		{
			Pixel[i][j].R = P + (i * screen_w + j) * 4;
			//*Pixel[i][j].R = (unsigned char)(((float)i / screen_h) * 255.f);
			Pixel[i][j].G = P + (i * screen_w + j) * 4 + 1;
			Pixel[i][j].B = P + (i * screen_w + j) * 4 + 2;
			Pixel[i][j].S = P + (i * screen_w + j) * 4 + 3;
		}
	}
}

void Rasterization::DrawBackground()
{
	for (int i = 0; i < screen_h; i++)
	{
		for (int j = 0; j < screen_w; j++)
		{
			*Pixel[i][j].R = (unsigned char)(i * 255.f / screen_h) ;
			*Pixel[i][j].G = 0;
			*Pixel[i][j].B = 0;
		}
	}
}

void Rasterization::AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3, Color3 In_Color, bool bNormal)
{
	UTriangle* LocalVar = new UTriangle(ToScreenPoint(Point1), ToScreenPoint(Point2), ToScreenPoint(Point3), In_Color);
	if (bNormal)LocalVar->Calculate_NormalVector();
	Triangles.push_back(LocalVar);
	DrawTringle(LocalVar);
}

Vector3 Rasterization::ToScreenPoint(Vector3 InPoint)
{
	return Vector3((InPoint.x + 1)* (screen_w/2.f), (1-InPoint.y)*(screen_h/2.f), InPoint.z);
}

void Rasterization::DrawTringle(UTriangle* In_Triangles)
{
	cout << In_Triangles->Point1.x << " " << In_Triangles->Point1.y<< endl;
	cout << In_Triangles->Point2.x << " " << In_Triangles->Point2.y << endl;
	cout << In_Triangles->Point3.x << " " << In_Triangles->Point3.y << endl;
	cout << Vector2::InTriangle(Vector2(0, 1), Vector2(0, 0), Vector2(1, 0), Vector2(0.2, 0.2));
	for (int i = 0; i < screen_h; i++)
	{
		for (int j = 0; j < screen_w; j++)
		{
			if (Vector2::InTriangle(Vector2(In_Triangles->Point1.x, In_Triangles->Point1.y), 
									Vector2(In_Triangles->Point2.x, In_Triangles->Point2.y), 
									Vector2(In_Triangles->Point3.x, In_Triangles->Point3.y), 
									Vector2((float)j + 0.5f, (float)i + 0.5f)))
			{
				*Pixel[i][j].R = In_Triangles->color3.R;
				*Pixel[i][j].G = In_Triangles->color3.G;
				*Pixel[i][j].B = In_Triangles->color3.B;
				//cout << "yes" <<endl;
			}
			
		}
	}
}
