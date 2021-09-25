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

Matrix4x4 FTransfrom::ToAffineMatrix(bool WorldToRel)
{
	Matrix4x4 M_Scale;
	if (WorldToRel)
	{
		M_Scale.m[0][0] =1 / Scale.x; M_Scale.m[1][1] = 1 / Scale.y; M_Scale.m[2][2] = 1 / Scale.z;
	}
	else
	{
		M_Scale.m[0][0] = Scale.x; M_Scale.m[1][1] = Scale.y; M_Scale.m[2][2] = Scale.z;
	}
	
	//M_Scale.CoutThis();
	Matrix4x4 M_Rotation;
	Quaternions LocalQuat;
	if (WorldToRel)
	{
		LocalQuat = Quaternions(-1.f *Quat.x, -1.f * Quat.y, -1.f * Quat.z, Quat.w);
	}
	else
	{
		LocalQuat = Quat;
	}
	M_Rotation = LocalQuat.ToMatrix4x4();
	//M_Rotation.CoutThis();
	Matrix4x4 M_Translation;
	Vector3 Loc_Location;
	if (WorldToRel)
	{
		Loc_Location.x = Location.x * -1.f;
		Loc_Location.y = Location.y * -1.f;
		Loc_Location.z = Location.z * -1.f;
	}
	else
	{
		Loc_Location = Location;
	}
	M_Translation.m[0][0] = 1;  M_Translation.m[0][3] = Loc_Location.x;
	M_Translation.m[1][1] = 1;  M_Translation.m[1][3] = Loc_Location.y;
	M_Translation.m[2][2] = 1;  M_Translation.m[2][3] = Loc_Location.z;
	//M_Translation.CoutThis();
	if (WorldToRel)
	{
		return M_Scale* M_Rotation* M_Translation ;
	}
	return  M_Translation * M_Rotation * M_Scale;
}

void FTransfrom::CoutThis(string head)
{
	Location.CoutThis(head);
	Quat.CoutThis(head);
	Scale.CoutThis(head);
	ToAffineMatrix().CoutThis(head);
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

Matrix4x4::Matrix4x4(double* f)
{
	if (sizeof(f) / sizeof(double) >= 11.9f)
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
	double x[4];
	for (int i=0; i<4; i++)
	{
		x[i] = m[i][0] * v3.x + m[i][1] * v3.y + m[i][2]*v3.z + m[i][3]*1.f;
	}
	x[0] /= x[3];
	x[1] /= x[3];
	x[2] /= x[3];
	return Vector3(x[0], x[1], x[2]
			);
}

Vector3 Matrix4x4::operator&(const Vector3& v3)
{
	double x[4];
	for (int i = 0; i < 4; i++)
	{
		x[i] = m[i][0] * v3.x + m[i][1] * v3.y + m[i][2] * v3.z + m[i][3] * 1.f;
	}
	x[0] /= abs(x[3]);
	x[1] /= abs(x[3]);
	x[2] /= abs(x[3]);
	return Vector3(x[0], x[1], x[2]
	);
}

Vector4 Matrix4x4::operator^(const Vector3& v3)
{
	double x[4];
	for (int i = 0; i < 4; i++)
	{
		x[i] = m[i][0] * v3.x + m[i][1] * v3.y + m[i][2] * v3.z + m[i][3] * 1.f;
	}
	//x[0] /= x[3];
	//x[1] /= x[3];
	//x[2] /= x[3];
	return Vector4(x[0], x[1], x[2], x[3]
	);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &M4)
{
	Matrix4x4 M;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4 ; j++)
		{
			M.m[i][j] = m[i][0] * M4.m[0][j] + m[i][1] * M4.m[1][j] + m[i][2] * M4.m[2][j] + m[i][3]*M4.m[3][j];
			//cout << i << " " << j <<" "<< M.m[i][j] << endl;
		}
	}
	return M;
}



void Matrix4x4::CoutThis(string head)
{
	cout << head << " Matrix4x4 : " << endl;
	for (int i = 0; i < 4 ; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
}

Vector3::Vector3()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3(double In_x, double In_y, double In_z)
{
	x = In_x;
	y = In_y;
	z = In_z;
}

Vector3::Vector3(double all_value)
{
	x = all_value;
	y = all_value;
	z = all_value;
}

Vector3 Vector3::operator+(const Vector3 &v3)
{
	return Vector3(x+v3.x, y+v3.y, z+v3.z);
}

Vector3 Vector3::operator-(const Vector3& v3)
{
	return Vector3(x-v3.x, y-v3.y, z-v3.z);
}

double Vector3::operator*(const Vector3& v3)
{
	return x*v3.x + y*v3.y + z*v3.z;
}

Vector3 Vector3::operator^(const Vector3& v3)
{
	return Vector3(y*v3.z - z*v3.y, z*v3.x - x*v3.z, x*v3.y - y*v3.x);
}

Vector3 Vector3::operator*(const double& k)
{
	return Vector3(k * x, k * y, k * z);
}

void Vector3::Normalize()
{
	double k = sqrt(x*x + y*y + z*z);
	x/=k;
	y/=k;
	z/=k;

	CheckZero();
}

void Vector3::CoutThis(string head)
{
	cout << head << " Vec3 x : " << x << " y : " << y << " z : " << z << endl;
}

void Vector3::CheckZero()
{
	if (NearZero(x))
	{
		x = 0;
	}
	if (NearZero(y))
	{
		y = 0;
	}
	if (NearZero(z))
	{
		z = 0;
	}
}

Vector3 operator*(const Vector3& v3, const double& k)
{
	return Vector3(v3.x*k, v3.y*k, v3.z*k);
}

Vector3 operator*(const double& k, const Vector3& v3)
{
	return Vector3(v3.x * k, v3.y * k, v3.z * k);
}

Quaternions::Quaternions()
{
	x = 0;
	x = 0;
	x = 0;
	w = 1;
}

Quaternions::Quaternions(Vector3 Axi, double Angle)
{
	x = Axi.x * sin(Radian(Angle/2.0));
	y = Axi.y * sin(Radian(Angle/2.0));
	z = Axi.z * sin(Radian(Angle/2.0));
	w = cos(Radian(Angle/2.0));
	Normalize();
}

Quaternions::Quaternions(double In_x, double In_y, double In_z, double In_w)
{
	x = In_x;
	y = In_y;
	z = In_z;
	w = In_w;
	Normalize();
}

void Quaternions::Normalize()
{
	double k = x * x + y * y + z * z + w * w;
	x /= k;
	y /= k;
	z /= k;
	w /= k;
}

Matrix4x4 Quaternions::ToMatrix4x4()
{
	Matrix4x4 Rot_Matrix4x4;
	Rot_Matrix4x4.m[0][0] = 1.f - 2.f * y * y - 2.f * z * z; Rot_Matrix4x4.m[0][1] = 2.f * x * y - 2.f * z * w; Rot_Matrix4x4.m[0][2] = 2.f * x * z + 2.f * y * w; Rot_Matrix4x4.m[0][3] = 0;
	Rot_Matrix4x4.m[1][0] = 2.f * x * y + 2 * z * w;       Rot_Matrix4x4.m[1][1] = 1.f - 2.f * x * x - 2.f * z * z; Rot_Matrix4x4.m[1][2] = 2.f * y * z - 2.f * x * w; Rot_Matrix4x4.m[1][3] = 0;
	Rot_Matrix4x4.m[2][0] = 2.f * x * z - 2.f * y * w; Rot_Matrix4x4.m[2][1] = 2.f * y * z + 2.f * x * w; Rot_Matrix4x4.m[2][2] = 1.f - 2.f * x * x - 2.f * y * y ; Rot_Matrix4x4.m[2][3] = 0;
	Rot_Matrix4x4.m[3][0] = 0; Rot_Matrix4x4.m[3][1] = 0; Rot_Matrix4x4.m[3][2] = 0; Rot_Matrix4x4.m[3][3] = 1.f;
	return Rot_Matrix4x4;
}

void Quaternions::CoutThis(string head)
{
	cout << head << " Quat x : " << x << " y : " << y << " z : " << z << " w : " << w << endl;
}

Vector3 Quaternions::GetForward()
{
	Vector3 a = ToMatrix4x4()* Vector3(1, 0, 0);
	a.Normalize();
	//a.CoutThis("GetForward");
	return a;
}

Vector3 Quaternions::GetRight()
{
	Vector3 a = ToMatrix4x4() * Vector3(0, 1, 0);
	a.Normalize();
	//a.CoutThis("GetForward");
	return a;
}

Vector3 Quaternions::GetUp()
{
	Vector3 a = ToMatrix4x4() * Vector3(0, 0, 1);
	a.Normalize();
	//a.CoutThis("GetForward");
	return a;
}

Quaternions Quaternions::Inversed()
{
	return Quaternions(-1.0*x, -1.0*y, -1.0*z, w);
}

Quaternions Quaternions::operator*(const Quaternions& Quat)
{
	double New_x = (y * Quat.z - z * Quat.y + x * Quat.w + w * Quat.x);
	double New_y = (z * Quat.x - x * Quat.z + y * Quat.w + w * Quat.y);
	double New_z = (x * Quat.y - y * Quat.x + z * Quat.w + w * Quat.z);
	double New_w = (w * Quat.w - x * Quat.x - y * Quat.y - z * Quat.z);
	Quaternions k = Quaternions(New_x, New_y, New_z, New_w);
	k.Normalize();
	return k;
}

Vector2::Vector2()
{

}

Vector2::Vector2(double In_x, double In_y)
{
	x = In_x;
	y = In_y;
}



double Vector2::operator*(const Vector2& v2)
{
	return x * v2.x + y * v2.y;
}

Vector2 Vector2::operator-(const Vector2& v2)
{
	return Vector2(x - v2.x, y - v2.y);
}

bool Vector2::InTriangle(Vector2 A, Vector2 B, Vector2 C, Vector2 P)
{
	Vector2 v0 = C - A;
	Vector2 v1 = B - A;
	Vector2 v2 = P - A;

	double dot00 = v0 * v0;
	double dot01 = v0 * v1;
	double dot02 = v0 * v2;
	double dot11 = v1 * v1;
	double dot12 = v1 * v2;

	double inverDeno = 1 / (dot00 * dot11 - dot01 * dot01);

	double u = (dot11 * dot02 - dot01 * dot12) * inverDeno;
	if (u < 0 || u > 1) // if u out of range, return directly
	{
		return false;
	}

	double v = (dot00 * dot12 - dot01 * dot02) * inverDeno;
	if (v < 0 || v > 1) // if v out of range, return directly
	{
		return false;
	}

	return u + v <= 1;
}

void Vector2::CoutThis(string head)
{
	cout << head << " Vec2 x : " << x << " y : " << y << endl;
}

Color3::Color3()
{
	
}

Color3::Color3(int In_R, int In_G, int In_B)
{
	R = In_R;
	G = In_G;
	B = In_B;
	S = 1;
}

Vector4::Vector4()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
	w = 1.0;
}

Vector4::Vector4(double In_x, double In_y, double In_z, double In_w)
{
	x = In_x;
	y = In_y;
	z = In_z;
	w = In_w;
}

void Vector4::CoutThis(string head)
{
	cout << head << " Vec3 x : " << x << " y : " << y << " z : " << z << " w : " << w << endl;
}