#include "Matrix.h"

FTransfrom::FTransfrom()
{

}

Matrix4x4::Matrix4x4()
{
}

Matrix4x4::Matrix4x4(float* f)
{
	if (sizeof(f) / sizeof(float) >= 16)
	{
		m[0][0] = f[0]; m[0][0] = f[1]; m[0][0] = f[2]; m[0][0] = f[3];
		m[0][0] = f[0]; m[0][0] = f[0]; m[0][0] = f[0]; m[0][0] = f[0];
		m[0][0] = f[0]; m[0][0] = f[0]; m[0][0] = f[0]; m[0][0] = f[0];
		m[0][0] = f[0]; m[0][0] = f[0]; m[0][0] = f[0]; m[0][0] = f[0];
		cout<< "goujian Matritx4X4 chenggong" <<endl;
	}
	cout << "goujian Matritx4X4 shibai" << endl;
}

Vector3::Vector3()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3(float In_x, float In_y, float In_z)
{
	x = In_x;
	y = In_y;
	z = In_z;
}

Quaternions::Quaternions()
{
	x = 0;
	x = 0;
	x = 0;
	w = 1;
}

Quaternions::Quaternions(float In_x, float In_y, float In_z, float In_w)
{
	x = In_x;
	y = In_y;
	z = In_z;
	w = In_w;
}
