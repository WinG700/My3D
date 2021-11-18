#pragma once

#include "Matrix.h"
#include "UTriangle.h"
#include "FunctionLibrary.h"

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
	Rasterization() = default;
	~Rasterization();
	Rasterization(unsigned char* P);

	/** 像素点颜色缓冲 */
	PixelColor Pixel[screen_h][screen_w];
	
	BufferPoint Buffer[screen_h][screen_w];
	/** 深度缓冲 */
	double ZBuffer[screen_h][screen_w];

	/** 需要绘制的所有三角形 */
	vector<UTriangle*> Triangles;

	/** 背景图片的BMP缓冲数组 */
	char* BackGround_BMP;

	/** 绘制背景颜色 */
	void DrawBackground();

	/** 添加一个三角形到光栅化器中 */
	void AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3, Color3 In_Color, bool bNormal = true);

	/** 从相机坐标系转换到光栅化器的坐标系 */
	Vector3 ToScreenPoint(Vector3 InPoint);

	/** 绘制三角形 */
	void DrawTringle(UTriangle* In_Triangles);

	/** 根据以y轴从小到大排序好的三个点绘制三角形 */
	void DrawTringleThreePoint(const Vector3& top, const Vector3& mid, const Vector3& down, const Color3& color3);

	/** 绘制顶部三角形 */
	void DrawTopTringle(const Vector3& TopPoint, double BaseEdge, double leftDx, double leftC, double rightDx, double rightC, double leftZ, double rightZ, const Color3& color3);

	/** 绘制底部三角形 */
	void DrawDownTringle(const Vector3& DownPoint, double BaseEdge, double leftDx, double leftC, double rightDx, double rightC, double leftZ, double rightZ, const Color3& color3);

	/** 绘制逐行的线 */
	void DrawYLine(double leftX, double rightX, int thisY, double leftZ, double rightZ, const Color3& color3);

	/** 填充颜色到颜色缓冲(根据深度缓冲判断) */
	void setColor(int x, int y, double Z, const Color3& color3);
};

