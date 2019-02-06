#include "Utility.h"
#include <cmath>
#include <assert.h>

Utility::Vec3::Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Utility::Vec3::Vec3(float in_x, float in_y, float in_z)
{
	this->x = in_x;
	this->y = in_y;
	this->z = in_z;
}

Utility::Vec3 Utility::Vec3::Normalize(Vec3 v)
{
	Vec3 Return;
	Return = v;
	float length = std::powf((v.x * v.x) + (v.y * v.y) + (v.z * v.z), 0.5f);
	//length = std::abs(length);
	if (length > 0)
	{
		Return.x = v.x / length;
		Return.y = v.y / length;
		Return.z = v.z / length;
	}
	
	return Return;
}

Utility::Vec3 Utility::Vec3::Cross(Vec3 v1, Vec3 v2)
{
	Vec3 Return;
	Return.x = v1.y * v2.z - v1.z * v2.y;
	Return.y = v1.z * v2.x - v1.x * v2.z;
	Return.z = v1.x * v2.y - v1.y * v2.x;
	return Return;
}

float Utility::Vec3::Dot(Vec3 v1, Vec3 v2)
{
	float Return;
	Return = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return Return;
}

Utility::Vec3 Utility::Vec3::operator+(Vec3 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Utility::Vec3 Utility::Vec3::operator-(Vec3 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Utility::Vec3 Utility::Vec3::operator*(Vec3 v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

Utility::Vec3 Utility::Vec3::operator/(Vec3 v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}

Utility::Vec3 Utility::Vec3::operator+=(Vec3 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	return *this;
}

Utility::Vec3 Utility::Vec3::operator-=(Vec3 v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
	return *this;
}

Utility::Vec3 Utility::Vec3::operator*=(Vec3 v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	return *this;
}

Utility::Vec3 Utility::Vec3::operator/=(Vec3 v)
{
	this->x /= v.x;
	this->y /= v.y;
	this->z /= v.z;
	return *this;
}
