#include "Matrix.h"

FTransfrom::FTransfrom()
{
	Location = Vector3(0.f, 0.f, 0.f);
	Quat = Quaternions(0.f, 0.f, 0.f, 1.f);
	Scale = Vector3(1.f, 1.f, 1.f);
}

FTransfrom::FTransfrom(const Vector3& loc, const Quaternions& qua)
{
	Location = loc;
	Quat = qua;
	Scale = Vector3(1.f, 1.f, 1.f);
}

FTransfrom::FTransfrom(const Vector3& loc, const Quaternions& qua, const Vector3& sca)
{
	Location = loc;
	Quat = qua;
	Scale = sca;
}

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m[i][j] = 0;
		}
	}
	m[3][3] = 1;
}

Matrix4x4::Matrix4x4(float* f)
{
	if (sizeof(f) / sizeof(float) >= 11.9f)
	{
		m[0][0] = f[0]; m[0][0] = f[1]; m[0][0] = f[2];  m[0][0] = f[3];
		m[0][0] = f[4]; m[0][0] = f[5]; m[0][0] = f[6];  m[0][0] = f[7];
		m[0][0] = f[8]; m[0][0] = f[9]; m[0][0] = f[10]; m[0][0] = f[11];
		m[0][0] = 0;    m[0][0] = 0;    m[0][0] = 0;     m[0][0] = 1;
		cout<< "goujian Matritx4X4 chenggong" <<endl;
	}
	else
	{
		cout << "goujian Matritx4X4 shibai" << endl;
		Matrix4x4();
	}
}

Vector3 Matrix4x4::operator*(const Vector3 &v3)
{
	return Vector3();
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &M4)
{
	return Matrix4x4();
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

Vector3 Vector3::operator+(const Vector3 &v3)
{
	return Vector3(x+v3.x, y+v3.y, z+v3.z);
}

Vector3 Vector3::operator-(const Vector3& v3)
{
	return Vector3(x-v3.x, y-v3.y, z-v3.z);
}

float Vector3::operator*(const Vector3& v3) 
{
	return x*v3.x + y*v3.y + z*v3.z;
}

Vector3 Vector3::operator^(const Vector3& v3)
{
	return Vector3(y*v3.z - z*v3.y, z*v3.x - x*v3.z, x*v3.y - y*v3.x);
}

void Vector3::Normalize()
{
	float k = x*x + y*y + z*z;
	x/=k;
	y/=k;
	z/=k;
}

Quaternions::Quaternions()
{
	x = 0;
	x = 0;
	x = 0;
	w = 1;
}

Quaternions::Quaternions(Vector3 Axi, float Angle)
{
	x = Axi.x * sin(Radian(Angle));
	y = Axi.y * sin(Radian(Angle));
	z = Axi.z * sin(Radian(Angle));
	w = cos(Radian(Angle));
	Normalize();
}

Quaternions::Quaternions(float In_x, float In_y, float In_z, float In_w)
{
	x = In_x;
	y = In_y;
	z = In_z;
	w = In_w;
	Normalize();
}

void Quaternions::Normalize()
{
	float k = x * x + y * y + z * z + w * w;
	x /= k;
	y /= k;
	z /= k;
	w /= k;
}

Matrix4x4 Quaternions::ToMatrix4x4()
{

}

Quaternions Quaternions::operator*(const Quaternions& Quat)
{
	float New_x = (y * Quat.z - z * Quat.y + x * Quat.w + w * Quat.x);
	float New_y = (z * Quat.x - x * Quat.z + y * Quat.w + w * Quat.y);
	float New_z = (x * Quat.y - y * Quat.x + z * Quat.w + w * Quat.z);
	float New_w = (w * Quat.w - x * Quat.x - y * Quat.y - z * Quat.z);
	return Quaternions(New_x, New_y, New_z, New_w);
}
