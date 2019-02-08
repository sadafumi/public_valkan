//========================================================================
//	maked by sadafumi 
//	2019/2/7
//========================================================================
#pragma once
#include <cmath>

namespace Utility 
{
	class Vec2
	{
	public:
		Vec2();
		Vec2(float, float);
		float x;
		float y;
	};
	class Int_Vec2 
	{
	public:
		Int_Vec2();
		Int_Vec2(int,int);
		int x;
		int y;
		Int_Vec2 operator+(Int_Vec2 v);
		Int_Vec2 operator-(Int_Vec2 v);
		Int_Vec2 operator*(Int_Vec2 v);
		Int_Vec2 operator/(Int_Vec2 v);
		Int_Vec2 operator+(int v);
		Int_Vec2 operator-(int v);
		Int_Vec2 operator*(int v);
		Int_Vec2 operator/(int v);
		Int_Vec2 operator+=(Int_Vec2 v);
		Int_Vec2 operator-=(Int_Vec2 v);
		Int_Vec2 operator*=(Int_Vec2 v);
		Int_Vec2 operator/=(Int_Vec2 v);
	};
	class Vec3 
	{
	public:
		Vec3();
		Vec3(float, float,float);
		static Vec3 Normalize(Vec3 v);
		static Vec3 Cross(Vec3, Vec3);
		static float Dot(Vec3, Vec3);
		float x;
		float y;
		float z;
		Vec3 operator+(Vec3 v);
		Vec3 operator-(Vec3 v);
		Vec3 operator*(Vec3 v);
		Vec3 operator/(Vec3 v);
		Vec3 operator+=(Vec3 v);
		Vec3 operator-=(Vec3 v);
		Vec3 operator*=(Vec3 v);
		Vec3 operator/=(Vec3 v);
	};
	class Int_Vec3 
	{
	public:
		Int_Vec3();
		Int_Vec3(int, int,int);
		int x;
		int y;
		int z;
	};
	class Vec4
	{
	public:
		Vec4();
		Vec4(Vec3,float);
		Vec4(float, float, float,float);
		static Vec4 Normalize(Vec4 v);
		static Vec4 Cross(Vec4, Vec4);
		static float Dot(Vec4, Vec4);
		float x;
		float y;
		float z;
		float w;
		Vec4 operator+(Vec4 v);
		Vec4 operator-(Vec4 v);
		Vec4 operator*(Vec4 v);
		Vec4 operator/(Vec4 v);
		Vec4 operator+=(Vec4 v);
		Vec4 operator-=(Vec4 v);
		Vec4 operator*=(Vec4 v);
		Vec4 operator/=(Vec4 v);

	};
	class Int_Vec4
	{
	public:
		Int_Vec4();
		Int_Vec4(int, int, int,int );
		int x;
		int y;
		int z;
		int w;
	};
	class mtx4x4 
	{
	public:
		mtx4x4();
		mtx4x4(float);
		mtx4x4(Vec4, Vec4, Vec4, Vec4);
		mtx4x4(	float, float, float, float, 
				float, float, float, float, 
				float, float, float, float, 
				float, float, float, float);
		void Identity();
		static mtx4x4 Perspective(float, float, float, float );
		static mtx4x4 Perspective_Direct(float, float, float, float);
		static mtx4x4 Transform(float x, float y, float z);
		static mtx4x4 Transform(Vec3 v);
		static mtx4x4 Rotation(float x, float y, float z);
		static mtx4x4 Rotation(Vec3 v);
		static mtx4x4 RotationX(float v);
		static mtx4x4 RotationY(float v);
		static mtx4x4 RotationZ(float v);
		static mtx4x4 Scale(float x, float y, float z);
		static mtx4x4 Scale(Vec3 v);
		static mtx4x4 LookAt(Vec3, Vec3, Vec3);
		float mtx[16];
		//Vec4 mtx[4];
		mtx4x4 operator*(mtx4x4 v);
		mtx4x4 operator*=(mtx4x4 v);
		mtx4x4 operator=(mtx4x4 v);
	};
	class math
	{
	public:
		static float radians(float);
		static float degrees(float);
		static float sin(float);
		static float cos(float);
		static float tan(float);
		static const float rad_PI;
		static const float deg_PI;

		//static const float rad_PI = 0.01745329251994329576923690768489;
		//static const float deg_PI = 57.295779513082320876798154814105;
	};
}

