#include "Utility.h"
#include <cmath>
#include <assert.h>


Utility::Vec4::Vec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Utility::Vec4::Vec4(Vec3 v, float in)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = in;
}

Utility::Vec4::Vec4(float in_x, float in_y, float in_z, float in_w)
{
	this->x = in_x;
	this->y = in_y;
	this->z = in_z;
	this->w = in_w;
}

Utility::Vec4 Utility::Vec4::Normalize(Vec4 v)
{
	Vec4 Return;
	float length = std::powf((v.x * v.x) + (v.y * v.y) + (v.z * v.z) + (v.w * v.w), 0.5f);
	Return.x /= length;
	Return.y /= length;
	Return.z /= length;
	Return.w /= length;
	return Vec4();
}

Utility::Vec4 Utility::Vec4::Cross(Vec4, Vec4)
{
	return Vec4();
}

float Utility::Vec4::Dot(Vec4, Vec4)
{
	return float();
}

Utility::Vec4 Utility::Vec4::operator+(Vec4 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
}

Utility::Vec4 Utility::Vec4::operator-(Vec4 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
}

Utility::Vec4 Utility::Vec4::operator*(Vec4 v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
	return *this;
}

Utility::Vec4 Utility::Vec4::operator/(Vec4 v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
	return *this;
}

Utility::Vec4 Utility::Vec4::operator+=(Vec4 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->w += v.w;
	return *this;
}

Utility::Vec4 Utility::Vec4::operator-=(Vec4 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	this->w -= v.w;
	return *this;
}

Utility::Vec4 Utility::Vec4::operator*=(Vec4 v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->w *= v.w;
	return *this;
}

Utility::Vec4 Utility::Vec4::operator/=(Vec4 v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	this->w /= v.w;
	return *this;
}
