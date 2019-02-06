#include "Utility.h"
#include <cmath>
#include <assert.h>

Utility::Int_Vec2::Int_Vec2()
{
	this->x = 0;
	this->y = 0;
}

Utility::Int_Vec2::Int_Vec2(int in_x, int in_y)
{
	this->x = in_x;
	this->y = in_y;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator+(Int_Vec2 v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator-(Int_Vec2 v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator*(Int_Vec2 v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator/(Int_Vec2 v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator+(int v)
{
	this->x += v;
	this->y += v;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator-(int v)
{
	this->x -= v;
	this->y -= v;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator*(int v)
{
	this->x *= v;
	this->y *= v;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator/(int v)
{
	this->x /= v;
	this->y /= v;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator+=(Int_Vec2 v)
{
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator-=(Int_Vec2 v)
{
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator*=(Int_Vec2 v)
{
	this->x *= v.x;
	this->y *= v.y;
	return *this;
}

Utility::Int_Vec2 Utility::Int_Vec2::operator/=(Int_Vec2 v)
{
	this->x /= v.x;
	this->y /= v.y;
	return *this;
}
