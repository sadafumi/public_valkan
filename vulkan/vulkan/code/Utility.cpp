#include "Utility.h"
#include <cmath>
#include <assert.h>

const float Utility::math::rad_PI = 0.01745329251994329576923690768489f;
const float Utility::math::deg_PI = 57.295779513082320876798154814105f;

Utility::Vec2::Vec2()
{
	this->x = 0;
	this->y = 0;
}

Utility::Vec2::Vec2(float in_x,  float in_y)
{
	this->x = in_x;
	this->y = in_y;
}


Utility::Int_Vec3::Int_Vec3()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Utility::Int_Vec3::Int_Vec3(int in_x, int in_y,int in_z)
{
	this->x = in_x;
	this->y = in_y;
	this->z = in_z;
}

Utility::Int_Vec4::Int_Vec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->w = 0;
}

Utility::Int_Vec4::Int_Vec4(int in_x, int in_y, int in_z,int in_w)
{
	this->x = in_x;
	this->y = in_y;
	this->z = in_z;
	this->w = in_w;
}

float Utility::math::radians(float in)
{
	return in * rad_PI;
}

float Utility::math::degrees(float in)
{
	return in * deg_PI;
}

float Utility::math::sin(float in)
{
	return std::sin(in);
}

float Utility::math::cos(float in)
{
	return std::cos(in);
}

float Utility::math::tan(float in)
{
	return std::tan(in);
}

