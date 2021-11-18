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

	/** ���ص���ɫ���� */
	PixelColor Pixel[screen_h][screen_w];
	
	BufferPoint Buffer[screen_h][screen_w];
	/** ��Ȼ��� */
	double ZBuffer[screen_h][screen_w];

	/** ��Ҫ���Ƶ����������� */
	vector<UTriangle*> Triangles;

	/** ����ͼƬ��BMP�������� */
	char* BackGround_BMP;

	/** ���Ʊ�����ɫ */
	void DrawBackground();

	/** ���һ�������ε���դ������ */
	void AddTringle(Vector3 Point1, Vector3 Point2, Vector3 Point3, Color3 In_Color, bool bNormal = true);

	/** ���������ϵת������դ����������ϵ */
	Vector3 ToScreenPoint(Vector3 InPoint);

	/** ���������� */
	void DrawTringle(UTriangle* In_Triangles);

	/** ������y���С��������õ���������������� */
	void DrawTringleThreePoint(const Vector3& top, const Vector3& mid, const Vector3& down, const Color3& color3);

	/** ���ƶ��������� */
	void DrawTopTringle(const Vector3& TopPoint, double BaseEdge, double leftDx, double leftC, double rightDx, double rightC, double leftZ, double rightZ, const Color3& color3);

	/** ���Ƶײ������� */
	void DrawDownTringle(const Vector3& DownPoint, double BaseEdge, double leftDx, double leftC, double rightDx, double rightC, double leftZ, double rightZ, const Color3& color3);

	/** �������е��� */
	void DrawYLine(double leftX, double rightX, int thisY, double leftZ, double rightZ, const Color3& color3);

	/** �����ɫ����ɫ����(������Ȼ����ж�) */
	void setColor(int x, int y, double Z, const Color3& color3);
};

