#include "Rasterization.h"

Rasterization::Rasterization(unsigned char* P)
{
	for (int i = 0; i < screen_h; i++)
	{
		for (int j = 0; j < screen_w; j++)
		{
			Pixel[i][j].B = P + (i * screen_w + j) * 4;
			//*Pixel[i][j].R = (unsigned char)(((float)i / screen_h) * 255.f);
			Pixel[i][j].G = P + (i * screen_w + j) * 4 + 1;
			Pixel[i][j].R = P + (i * screen_w + j) * 4 + 2;
			Pixel[i][j].S = P + (i * screen_w + j) * 4 + 3;
		}
	}

	BackGround_BMP = FunctionLibrary::LoadBMP("Sky.bmp");

}

Rasterization::~Rasterization()
{
	delete[] BackGround_BMP;
}

void Rasterization::DrawBackground()
{
	/*memset(Pixel[0][0], 0, w * h * 4);*/
	for (int i = 0; i < screen_h; i++)
	{
		for (int j = 0; j < screen_w; j++)
		{
			//*Pixel[i][j].R = 102;
			//*Pixel[i][j].G = 204;
			//*Pixel[i][j].B = 255;
			*Pixel[i][j].R = BackGround_BMP[((screen_h - i - 1) * screen_w + j) * 3 + 2];
			*Pixel[i][j].G = BackGround_BMP[((screen_h - i - 1) * screen_w + j) * 3 + 1];
			*Pixel[i][j].B = BackGround_BMP[((screen_h - i - 1) * screen_w + j) * 3];
		}
	}

	memset(ZBuffer, 100, sizeof(ZBuffer));
}

void Rasterization::AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3, Color3 In_Color, bool bNormal)
{
	UTriangle* LocalVar = new UTriangle(ToScreenPoint(Point1), ToScreenPoint(Point2), ToScreenPoint(Point3), In_Color);
	if (bNormal)LocalVar->Calculate_NormalVector();
	//Triangles.push_back(LocalVar);
	DrawTringle(LocalVar);
}

Vector3 Rasterization::ToScreenPoint(Vector3 InPoint)
{
	return Vector3((InPoint.x + 1)* (screen_w/2.0), (1-InPoint.y)*(screen_h/2.0), InPoint.z);
}

void Rasterization::DrawTringle(UTriangle* In_Triangles)
{
	//cout << In_Triangles->Point1.x << " " << In_Triangles->Point1.y<< endl;
	//cout << In_Triangles->Point2.x << " " << In_Triangles->Point2.y << endl;
	//cout << In_Triangles->Point3.x << " " << In_Triangles->Point3.y << endl;
	//cout << Vector2::InTriangle(Vector2(0, 1), Vector2(0, 0), Vector2(1, 0), Vector2(0.2, 0.2));

	/************************************************************************/
	/*遍历判断像素是否在三角形内的绘制                                        */
	/************************************************************************/

	//for (int i = 0; i < screen_h; i++)
	//{
	//	for (int j = 0; j < screen_w; j++)
	//	{
	//		if (Vector2::InTriangle(Vector2(In_Triangles->Point1.x, In_Triangles->Point1.y), 
	//								Vector2(In_Triangles->Point2.x, In_Triangles->Point2.y), 
	//								Vector2(In_Triangles->Point3.x, In_Triangles->Point3.y), 
	//								Vector2((double)j + 0.5f, (double)i + 0.5f)))
	//		{
	//			*Pixel[i][j].R = In_Triangles->color3.R;
	//			*Pixel[i][j].G = In_Triangles->color3.G;
	//			*Pixel[i][j].B = In_Triangles->color3.B;
	//			//cout << "yes" <<endl;
	//		}
	//	}
	//}

	/************************************************************************/
	/*逐行求两边交点的绘制法                                                 */
	/************************************************************************/

	if (In_Triangles->Point1.y >= In_Triangles->Point2.y && In_Triangles->Point2.y >= In_Triangles->Point3.y)
	{
		DrawTringleThreePoint(In_Triangles->Point1, In_Triangles->Point2, In_Triangles->Point3, In_Triangles->color3);
	}
	else if (In_Triangles->Point2.y >= In_Triangles->Point1.y && In_Triangles->Point1.y >= In_Triangles->Point3.y)
	{
		DrawTringleThreePoint(In_Triangles->Point2, In_Triangles->Point1, In_Triangles->Point3, In_Triangles->color3);
	}
	else if (In_Triangles->Point1.y >= In_Triangles->Point3.y && In_Triangles->Point3.y >= In_Triangles->Point2.y)
	{
		DrawTringleThreePoint(In_Triangles->Point1, In_Triangles->Point3, In_Triangles->Point2, In_Triangles->color3);
	}
	else if (In_Triangles->Point3.y >= In_Triangles->Point1.y && In_Triangles->Point1.y >= In_Triangles->Point2.y)
	{
		DrawTringleThreePoint(In_Triangles->Point3, In_Triangles->Point1, In_Triangles->Point2, In_Triangles->color3);
	}
	else if (In_Triangles->Point3.y >= In_Triangles->Point2.y && In_Triangles->Point2.y >= In_Triangles->Point1.y)
	{
		DrawTringleThreePoint(In_Triangles->Point3, In_Triangles->Point2, In_Triangles->Point1, In_Triangles->color3);
	}
	else if (In_Triangles->Point2.y >= In_Triangles->Point3.y && In_Triangles->Point3.y >= In_Triangles->Point1.y)
	{
		DrawTringleThreePoint(In_Triangles->Point2, In_Triangles->Point3, In_Triangles->Point1, In_Triangles->color3);
	}

}


void Rasterization::DrawTringleThreePoint(const Vector3& top, const Vector3& mid, const Vector3& down, const Color3& color3)
{
	if (down.y > (double)screen_h + 1.0 || top.y < 0)
		return;
	/** 计算斜线一次函数的斜率 */
	double top_mid_dx = (top.y - mid.y) / (top.x - mid.x);
	double top_down_dx = (top.y - down.y) / (top.x - down.x);
	double mid_down_dx = (down.y - mid.y) / (down.x - mid.x);

	/** 计算斜线一次函数的常数 */
	double top_mid_C = top.y - top.x * top_mid_dx;
	double top_down_C = top.y - top.x * top_down_dx;
	double mid_down_C = down.y - down.x * mid_down_dx;

	/** 计算三个点的深度 */
	double depth_top =  abs(top.z);
	double depth_down = abs(down.z);
	double depth_mid = abs(mid.z);
	double depth_other = DoubleLerp(depth_down, depth_top, (mid.y-down.y)/(top.y-down.y));

	/** 如果两条线的斜率基本都为0的话, 不进行绘制，直接返回 */
	if (NearZero(top_mid_dx) && NearZero(mid_down_dx))
	{
		return;
	}
	else if (NearZero(top_mid_dx))
	{
		if (top.x > mid.x)
		{
			DrawDownTringle(down, mid.y, mid_down_dx, mid_down_C, top_down_dx, top_down_C, depth_mid, depth_top, color3);
		}
		else
		{
			DrawDownTringle(down, mid.y, top_down_dx, top_down_C, mid_down_dx, mid_down_C, depth_top, depth_mid, color3);
		}
		return;
	}
	else if (NearZero(mid_down_dx))
	{
		if (down.x > mid.x)
		{
			DrawTopTringle(top, mid.y, top_mid_dx, top_mid_C, top_down_dx, top_down_C, depth_mid, depth_down, color3);
		}
		else
		{
			DrawTopTringle(top, mid.y, top_down_dx, top_down_C, top_mid_dx, top_mid_C, depth_down, depth_mid, color3);
		}
		return;
	}

	double midOtherX = (mid.y - top_down_C)/ top_down_dx;

	if (midOtherX > mid.x)
	{
		DrawTopTringle(top, mid.y, top_mid_dx, top_mid_C, top_down_dx, top_down_C, depth_mid, depth_other, color3);
		DrawDownTringle(down, mid.y, mid_down_dx, mid_down_C, top_down_dx, top_down_C, depth_mid, depth_other, color3);
	}
	else
	{
		DrawTopTringle(top, mid.y, top_down_dx, top_down_C, top_mid_dx, top_mid_C, depth_other, depth_mid, color3);
		DrawDownTringle(down, mid.y, top_down_dx, top_down_C, mid_down_dx, mid_down_C, depth_other, depth_mid, color3);
	}
}
//绘制上三角形
void Rasterization::DrawTopTringle(const Vector3& topPoint, double BaseEdge, double leftDx, double leftC, double rightDx, double rightC, double leftZ, double rightZ, const Color3& color3)
{	
	
	if(BaseEdge > screen_h)
	{
		return;
	}
	double chushi = topPoint.y > (double)(screen_h-1) ? (double)(screen_h - 1) : topPoint.y;
	
	for (int i = (int)chushi; i >= (int)(BaseEdge+0.5) && i >= 0; --i)
	{
		double thisY = i * 1.0 + 0.5;
		double leftX = 0;
		double rightX = 0;
		if (isinf(leftDx))
		{
			leftX = topPoint.x;
		}
		else
		{
			leftX = (thisY - leftC) / leftDx;
			leftX = max(min(leftX, (double)screen_w), 0.0);
		}
		if (isinf(rightDx))
		{
			rightX = topPoint.x;
		}
		else
		{
			rightX = (thisY - rightC) / rightDx;
			rightX = max(min(rightX, (double)screen_w), 0.0);
		}
		DrawYLine(leftX, rightX, i, DoubleLerp(topPoint.z, leftZ, (((double)i + 0.5) - topPoint.y) / (BaseEdge - topPoint.y)),
									DoubleLerp(topPoint.z, rightZ, (((double)i + 0.5) - topPoint.y) / (BaseEdge - topPoint.y)), color3);
		//cout << (((double)i + 0.5) - chushi) / (BaseEdge - chushi) << " ";
	}
	//cout << endl;
	
}
//绘制下三角形
void Rasterization::DrawDownTringle(const Vector3& DownPoint, double BaseEdge, double leftDx, double leftC, double rightDx, double rightC, double leftZ, double rightZ, const Color3& color3)
{
	if (BaseEdge < 0.0)
	{
		return;
	}
	double chushi = DownPoint.y > 0 ? (int)DownPoint.y : 0;
	for (int i = (int)chushi; i <= (int)(BaseEdge-0.5) && i < screen_h; ++i)
	{
		double thisY = i * 1.0 + 0.5;
		double leftX = 0;
		double rightX = 0;
		if (isinf(leftDx))
		{
			leftX = DownPoint.x;
		}
		else
		{
			leftX = (thisY - leftC) / leftDx;
			leftX = max(min(leftX, (double)screen_w), 0.0);
		}
		if (isinf(rightDx))
		{
			rightX = DownPoint.x;
		}
		else
		{
			rightX = (thisY - rightC) / rightDx;
			rightX = max(min(rightX, (double)screen_w), 0.0);
		}

		DrawYLine(leftX, rightX, i, DoubleLerp(DownPoint.z, leftZ, (((double)i + 0.5) - DownPoint.y) / (BaseEdge - DownPoint.y)),
									DoubleLerp(DownPoint.z, rightZ, (((double)i + 0.5) - DownPoint.y) / (BaseEdge - DownPoint.y)), color3);
	}
}


//根据左右两个边界点绘制一行像素
void Rasterization::DrawYLine(double leftX, double rightX, int thisY, double leftZ, double rightZ, const Color3& color3)
{
	//if ((int)leftX == (int)rightX)
	//{
	//	if (leftX - rightX < 0)
	//	{
	//		setColor(thisY, (int)leftX,  color3);
	//	}
	//}
	//else
	//{
		//cout << rightX - leftX <<endl;
		for (int j = (int)(leftX + 0.5); j <= (int)(rightX - 0.5); j++)
		{
			setColor(thisY, j, DoubleLerp(leftZ, rightZ, (((double)j+0.5)- leftX) / (rightX - leftX)), color3);
			
		}
	//}
}

void Rasterization::setColor(int x, int y, double Z, const Color3& color3)
{
	//cout << Z;
	if (ZBuffer[x][y] > Z)
	{
		*Pixel[x][y].R = color3.R;
		*Pixel[x][y].G = color3.G;
		*Pixel[x][y].B = color3.B;
		ZBuffer[x][y] = Z;
	}

}
