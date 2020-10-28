#pragma once

#include "Vector3.h"
using Vec3f = Vector3<float>;

class Matrix3x3
{
public:
	Matrix3x3();
	Matrix3x3(const Matrix3x3& mat);
	explicit Matrix3x3(float scalar);
	Matrix3x3(float scalar11, float scalar12, float scalar13, float scalar21, float scalar22, float scalar23,
			  float scalar31, float scalar32, float scalar33);

	const Vec3f& operator[](int index) const;
	Vec3f& operator[](int index);

	Matrix3x3& operator=(const Matrix3x3& mat);
	Matrix3x3& operator*=(float scale);

private:
	Vec3f matrix[3];
};

Matrix3x3 operator*(Matrix3x3 mat, float scale);
Matrix3x3 operator*(float scale, Matrix3x3 mat);

Matrix3x3 Transpose(Matrix3x3 mat);
bool operator==(const Matrix3x3& left, const Matrix3x3& right);
bool operator!=(const Matrix3x3& mat, const Matrix3x3& right);
std::ostream& operator<<(std::ostream& out, const Matrix3x3& mat);
