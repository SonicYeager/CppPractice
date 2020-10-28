#include "Matrix3x3.h"
#include <ostream>

Matrix3x3::Matrix3x3()
	: Matrix3x3(1)
{}

Matrix3x3::Matrix3x3(const Matrix3x3& mat)
	: matrix{mat[0], mat[1], mat[2]}
{}

Matrix3x3::Matrix3x3(float scalar)
	: matrix{{scalar, 0, 0}, {0, scalar, 0}, {0, 0, scalar}}
{}

Matrix3x3::Matrix3x3(float scalar11, float scalar12, float scalar13, float scalar21, float scalar22, float scalar23,
					 float scalar31, float scalar32, float scalar33)
	: matrix{{scalar11, scalar12, scalar13}, {scalar21, scalar22, scalar23}, {scalar31, scalar32, scalar33}}
{}

const Vec3f& Matrix3x3::operator[](int index) const
{
	return this->matrix[index];
}

Vec3f& Matrix3x3::operator[](int index)
{
	return this->matrix[index];
}

Matrix3x3& Matrix3x3::operator=(const Matrix3x3& mat)
{
	this->matrix[0] = mat[0];
	this->matrix[1] = mat[1];
	this->matrix[2] = mat[2];
	return *this;
}

Matrix3x3& Matrix3x3::operator*=(float scale)
{
	this->matrix[0] *= scale;
	this->matrix[1] *= scale;
	this->matrix[2] *= scale;
	return *this;
}

Matrix3x3 operator*(Matrix3x3 mat, float scale)
{
	mat *= scale;
	return mat;
}

Matrix3x3 operator*(float scale, Matrix3x3 mat)
{
	return mat * scale;
}

Matrix3x3 Transpose(Matrix3x3 mat)
{
	float temp = mat[1].x;
	mat[1].x = mat[0].y;
	mat[0].y = temp;
	temp = mat[2].x;
	mat[2].x = mat[0].z;
	mat[0].z = temp;
	temp = mat[1][2];
	mat[1].z = mat[2].y;
	mat[2].y = temp;
	return mat;
}

bool operator==(const Matrix3x3& left, const Matrix3x3& right)
{
	return left[0] == right[0] && left[1] == right[1] && left[2] == right[2];
}

bool operator!=(const Matrix3x3& left, const Matrix3x3& right)
{
	return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const Matrix3x3& mat)
{
	out << mat[0] << '\n' << mat[1] << '\n' << mat[2];
	return out;
}
