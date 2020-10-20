#include "Vec4.h"


Vec4::Vec4()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

Vec4::Vec4(float s1, float s2, float s3, float s4)
{
	this->x = s1;
	this->y = s1;
	this->z = s1;
	this->w = s1;
}

Vec4::Vec4(float scalar)
{
	this->x = scalar;
	this->y = scalar;
	this->z = scalar;
	this->w = scalar;
}


Vec4::Vec4(const Vec4& cpy)
{
	this->x = cpy.x;
	this->y = cpy.y;
	this->z = cpy.z;
	this->w = cpy.w;
}

Vec4::~Vec4()
{
}

Vec4& Vec4::operator=(float scalar)
{
	this->x = scalar;
	this->y = scalar;
	this->z = scalar;
	this->w = scalar;
}

Vec4& Vec4::operator=(const Vec4& cpy)
{
	this->x = cpy.x;
	this->y = cpy.y;
	this->z = cpy.z;
	this->w = cpy.w;
	return *this;
}

bool Vec4::operator==(const Vec4& vRight)
{
	if(this->x == vRight.x && this->y == vRight.y && this->z == vRight.z && this->w == vRight.w)
		return true;
	else
		return false;
}

bool Vec4::operator!=(const Vec4& vRight)
{
	if(this->x != vRight.x || this->y != vRight.y || this->z != vRight.z || this->w != vRight.w)
		return true;
	else
		return false;
}
