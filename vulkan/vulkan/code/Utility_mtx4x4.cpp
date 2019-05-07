#include "Utility.h"
#include <cmath>
#include <assert.h>

Utility::mtx4x4::mtx4x4()
{
	for (int i = 0; i < 16; i++)
	{
		this->mtx[i] = 0;
	}
}
Utility::mtx4x4::mtx4x4(float in)
{
	for (int i = 0; i < 16; i++)
	{
		this->mtx[i] = in;
	}
}
Utility::mtx4x4::mtx4x4(Vec4 v0, Vec4 v1, Vec4 v2, Vec4 v3)
{
	this->mtx[0] = v0.x;
	this->mtx[1] = v0.y;
	this->mtx[2] = v0.z;
	this->mtx[3] = v0.w;

	this->mtx[4] = v1.x;
	this->mtx[5] = v1.y;
	this->mtx[6] = v1.z;
	this->mtx[7] = v1.w;

	this->mtx[8] = v2.x;
	this->mtx[9] = v2.y;
	this->mtx[10] = v2.z;
	this->mtx[11] = v2.w;

	this->mtx[12] = v3.x;
	this->mtx[13] = v3.y;
	this->mtx[14] = v3.z;
	this->mtx[15] = v3.w;
}
Utility::mtx4x4::mtx4x4(
	float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
{
	this->mtx[0] = _11;
	this->mtx[1] = _12;
	this->mtx[2] = _13;
	this->mtx[3] = _14;

	this->mtx[4] = _21;
	this->mtx[5] = _22;
	this->mtx[6] = _23;
	this->mtx[7] = _24;

	this->mtx[8] = _31;
	this->mtx[9] = _32;
	this->mtx[10] = _33;
	this->mtx[11] = _34;

	this->mtx[12] = _41;
	this->mtx[13] = _42;
	this->mtx[14] = _43;
	this->mtx[15] = _44;
}
void Utility::mtx4x4::Identity()
{
	this->mtx[0] = 1;
	this->mtx[1] = 0;
	this->mtx[2] = 0;
	this->mtx[3] = 0;

	this->mtx[4] = 0;
	this->mtx[5] = 1;
	this->mtx[6] = 0;
	this->mtx[7] = 0;

	this->mtx[8] =  0;
	this->mtx[9] =  0;
	this->mtx[10] = 1;
	this->mtx[11] = 0;

	this->mtx[12] = 0;
	this->mtx[13] = 0;
	this->mtx[14] = 0;
	this->mtx[15] = 1;
}
Utility::mtx4x4 Utility::mtx4x4::Perspective(float fovy, float aspect, float zNear, float zFar)
{
	float tanHalfFovy = tan(fovy / 2 );

	mtx4x4 Return;
	Return = mtx4x4(
		(1) / (aspect * tanHalfFovy), 0, 0, 0,
		0, (1) / (tanHalfFovy), 0, 0,
		0, 0, -(zFar + zNear) / (zFar - zNear), -1,
		0, 0, -((2) * zFar * zNear) / (zFar - zNear), 0);
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::Perspective_Direct(float fovy, float aspect, float zNear, float zFar)
{
	assert(aspect != 0);
	assert(zFar != zNear);
	float h = (cos(fovy / 2)/ sin(fovy / 2));
	float w = h / aspect;

	mtx4x4 Return;

	Return = mtx4x4(
		w, 0, 0, 0,
		0, h, 0, 0,
		0, 0, zFar / (zFar - zNear),1,
		0, 0, -zNear * zFar / (zFar - zNear), 0);

	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::Transform(float x, float y, float z)
{
	mtx4x4 Return;
	Return.Identity();
	Return.mtx[12] = x;
	Return.mtx[13] = y;
	Return.mtx[14] = z;
	//Return.mtx[3].x = x;
	//Return.mtx[3].y = y;
	//Return.mtx[3].z = z;
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::Transform(Vec3 v)
{
	mtx4x4 Return;
	Return.Identity();
	Return.mtx[12] = v.x;
	Return.mtx[13] = v.y;
	Return.mtx[14] = v.z;
	//Return.mtx[3].x = x;
	//Return.mtx[3].y = y;
	//Return.mtx[3].z = z;
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::Transverse(mtx4x4 mtx)
{
	mtx4x4 Return;
	Return = mtx;
	Return.mtx[1] = mtx.mtx[4];
	Return.mtx[2] = mtx.mtx[8];
	Return.mtx[6] = mtx.mtx[9];
	Return.mtx[3] = mtx.mtx[12];
	Return.mtx[7] = mtx.mtx[13];
	Return.mtx[11] = mtx.mtx[14];
	Return.mtx[4] = mtx.mtx[1];
	Return.mtx[8] = mtx.mtx[2];
	Return.mtx[9] = mtx.mtx[6];
	Return.mtx[12] = mtx.mtx[3];
	Return.mtx[13] = mtx.mtx[7];
	Return.mtx[14] = mtx.mtx[11];
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::Rotation(float x, float y, float z)
{
	x = x;
	x = y;
	x = z;
	return mtx4x4();
}
Utility::mtx4x4 Utility::mtx4x4::Rotation(Vec3 v)
{
	v = v;
	return mtx4x4();
}
Utility::mtx4x4 Utility::mtx4x4::RotationX(float v)
{
	mtx4x4 Return(
		1.0f,  0.0f, 0.0f, 0.0f, 
		0.0f, cos(v),sin(v), 0.0f, 
		0.0f,-sin(v), cos(v), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::RotationY(float v)
{
	mtx4x4 Return(
	  cos(v), 0.0f,sin(v), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
	  -sin(v), 0.0f, cos(v), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::RotationZ(float v)
{
	mtx4x4 Return(
		cos(v),-sin(v), 0.0f, 0.0f,
	    sin(v), cos(v), 0.0f, 0.0f,
	 	 0.0f, 0.0f, 1.0f, 0.0f,
	 	 0.0f, 0.0f, 0.0f, 1.0f);
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::Scale(float x, float y, float z)
{
	mtx4x4 Return;
	Return.Identity();
	Return.mtx[0] = x;
	Return.mtx[5] = y;
	Return.mtx[10] = z;
	//Return.mtx[0].x = x;
	//Return.mtx[1].y = y;
	//Return.mtx[2].z = z;
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::Scale(Vec3 v)
{
	mtx4x4 Return;
	Return.Identity();
	Return.mtx[0] = v.x;
	Return.mtx[5] = v.y;
	Return.mtx[10] = v.z;
	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::LookAt(Vec3 eye, Vec3 centor, Vec3 up)
{
	Vec3 f(Vec3::Normalize(centor - eye));
	Vec3 s(Vec3::Normalize(Vec3::Cross(f, up)));
	Vec3 u(Vec3::Cross(s, f));
	mtx4x4 Return;

	Return = mtx4x4(
		s.x, u.x, -f.x, 0,
		s.y, u.y, -f.y, 0,
		s.z, u.z, -f.z, 0,
		-Vec3::Dot(u, eye), -Vec3::Dot(s, eye), Vec3::Dot(f, eye), 1.0f);

	return Return;
}
Utility::mtx4x4 Utility::mtx4x4::operator*(mtx4x4 v)
{
	this->mtx[0] = this->mtx[0] * v.mtx[0] + this->mtx[1] * v.mtx[4] + this->mtx[2] * v.mtx[8] + this->mtx[3] * v.mtx[12];
	this->mtx[1] = this->mtx[0] * v.mtx[1] + this->mtx[1] * v.mtx[5] + this->mtx[2] * v.mtx[9] + this->mtx[3] * v.mtx[13];
	this->mtx[2] = this->mtx[0] * v.mtx[2] + this->mtx[1] * v.mtx[6] + this->mtx[2] * v.mtx[10] + this->mtx[3] * v.mtx[14];
	this->mtx[3] = this->mtx[0] * v.mtx[3] + this->mtx[1] * v.mtx[7] + this->mtx[2] * v.mtx[11] + this->mtx[3] * v.mtx[15];

	this->mtx[4] = this->mtx[4] * v.mtx[0] + this->mtx[5] * v.mtx[4] + this->mtx[6] * v.mtx[8] + this->mtx[7] * v.mtx[12];
	this->mtx[5] = this->mtx[4] * v.mtx[1] + this->mtx[5] * v.mtx[5] + this->mtx[6] * v.mtx[9] + this->mtx[7] * v.mtx[13];
	this->mtx[6] = this->mtx[4] * v.mtx[2] + this->mtx[5] * v.mtx[6] + this->mtx[6] * v.mtx[10] + this->mtx[7] * v.mtx[14];
	this->mtx[7] = this->mtx[4] * v.mtx[3] + this->mtx[5] * v.mtx[7] + this->mtx[6] * v.mtx[11] + this->mtx[7] * v.mtx[15];

	this->mtx[8] = this->mtx[8] * v.mtx[0] + this->mtx[9] * v.mtx[4] + this->mtx[10] * v.mtx[8] + this->mtx[11] * v.mtx[12];
	this->mtx[9] = this->mtx[8] * v.mtx[1] + this->mtx[9] * v.mtx[5] + this->mtx[10] * v.mtx[9] + this->mtx[11] * v.mtx[13];
	this->mtx[10] = this->mtx[8] * v.mtx[2] + this->mtx[9] * v.mtx[6] + this->mtx[10] * v.mtx[10] + this->mtx[11] * v.mtx[14];
	this->mtx[11] = this->mtx[8] * v.mtx[3] + this->mtx[9] * v.mtx[7] + this->mtx[10] * v.mtx[11] + this->mtx[11] * v.mtx[15];

	this->mtx[12] = this->mtx[12] * v.mtx[0] + this->mtx[13] * v.mtx[4] + this->mtx[14] * v.mtx[8] + this->mtx[15] * v.mtx[12];
	this->mtx[13] = this->mtx[12] * v.mtx[1] + this->mtx[13] * v.mtx[5] + this->mtx[14] * v.mtx[9] + this->mtx[15] * v.mtx[13];
	this->mtx[14] = this->mtx[12] * v.mtx[2] + this->mtx[13] * v.mtx[6] + this->mtx[14] * v.mtx[10] + this->mtx[15] * v.mtx[14];
	this->mtx[15] = this->mtx[12] * v.mtx[3] + this->mtx[13] * v.mtx[7] + this->mtx[14] * v.mtx[11] + this->mtx[15] * v.mtx[15];
	return *this;
}
Utility::mtx4x4 Utility::mtx4x4::operator*=(mtx4x4 v)
{
	this->mtx[0] = this->mtx[0] * v.mtx[0] + this->mtx[1] * v.mtx[4] + this->mtx[2] * v.mtx[8] + this->mtx[3] * v.mtx[12];
	this->mtx[1] = this->mtx[0] * v.mtx[1] + this->mtx[1] * v.mtx[5] + this->mtx[2] * v.mtx[9] + this->mtx[3] * v.mtx[13];
	this->mtx[2] = this->mtx[0] * v.mtx[2] + this->mtx[1] * v.mtx[6] + this->mtx[2] * v.mtx[10] + this->mtx[3] * v.mtx[14];
	this->mtx[3] = this->mtx[0] * v.mtx[3] + this->mtx[1] * v.mtx[7] + this->mtx[2] * v.mtx[11] + this->mtx[3] * v.mtx[15];

	this->mtx[4] = this->mtx[4] * v.mtx[0] + this->mtx[5] * v.mtx[4] + this->mtx[6] * v.mtx[8] + this->mtx[7] * v.mtx[12];
	this->mtx[5] = this->mtx[4] * v.mtx[1] + this->mtx[5] * v.mtx[5] + this->mtx[6] * v.mtx[9] + this->mtx[7] * v.mtx[13];
	this->mtx[6] = this->mtx[4] * v.mtx[2] + this->mtx[5] * v.mtx[6] + this->mtx[6] * v.mtx[10] + this->mtx[7] * v.mtx[14];
	this->mtx[7] = this->mtx[4] * v.mtx[3] + this->mtx[5] * v.mtx[7] + this->mtx[6] * v.mtx[11] + this->mtx[7] * v.mtx[15];

	this->mtx[8] = this->mtx[8] * v.mtx[0] + this->mtx[9] * v.mtx[4] + this->mtx[10] * v.mtx[8] + this->mtx[11] * v.mtx[12];
	this->mtx[9] = this->mtx[8] * v.mtx[1] + this->mtx[9] * v.mtx[5] + this->mtx[10] * v.mtx[9] + this->mtx[11] * v.mtx[13];
	this->mtx[10] = this->mtx[8] * v.mtx[2] + this->mtx[9] * v.mtx[6] + this->mtx[10] * v.mtx[10] + this->mtx[11] * v.mtx[14];
	this->mtx[11] = this->mtx[8] * v.mtx[3] + this->mtx[9] * v.mtx[7] + this->mtx[10] * v.mtx[11] + this->mtx[11] * v.mtx[15];

	this->mtx[12] = this->mtx[12] * v.mtx[0] + this->mtx[13] * v.mtx[4] + this->mtx[14] * v.mtx[8] + this->mtx[15] * v.mtx[12];
	this->mtx[13] = this->mtx[12] * v.mtx[1] + this->mtx[13] * v.mtx[5] + this->mtx[14] * v.mtx[9] + this->mtx[15] * v.mtx[13];
	this->mtx[14] = this->mtx[12] * v.mtx[2] + this->mtx[13] * v.mtx[6] + this->mtx[14] * v.mtx[10] + this->mtx[15] * v.mtx[14];
	this->mtx[15] = this->mtx[12] * v.mtx[3] + this->mtx[13] * v.mtx[7] + this->mtx[14] * v.mtx[11] + this->mtx[15] * v.mtx[15];
	return *this;
}
Utility::mtx4x4 Utility::mtx4x4::operator=(mtx4x4 v)
{
	for (int i = 0; i < 16; i++)
	{
		this->mtx[i] = v.mtx[i];
	}
	return *this;
}
