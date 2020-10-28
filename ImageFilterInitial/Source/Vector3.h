#pragma once
#include <ostream>

template<typename T>
class Vector3
{
public:
#pragma warning(push)
// Not standard conform extension: struct/union without name
#pragma warning(disable : 4201)
	union
	{
		struct
		{
			T x, y, z;
		};
		struct
		{
			T r, g, b;
		};
	};
#pragma warning(pop)

	Vector3()
		: Vector3(0)
	{}
	Vector3(const Vector3& vec)
		: x(vec.x)
		, y(vec.y)
		, z(vec.z)
	{}
	explicit Vector3(T scalar)
		: x(scalar)
		, y(scalar)
		, z(scalar)
	{}
	Vector3(T scalar1, T scalar2, T scalar3)
		: x(scalar1)
		, y(scalar2)
		, z(scalar3)
	{}

	T operator[](int index) const
	{
		return (&this->x)[index];
	}
	T& operator[](int index)
	{
		return (&this->x)[index];
	}

	Vector3& operator=(T scalar)
	{
		this->x = scalar;
		this->y = scalar;
		this->z = scalar;
		return *this;
	}
	Vector3& operator=(const Vector3& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
		return *this;
	}

	Vector3& operator*=(T scale)
	{
		this->x *= scale;
		this->y *= scale;
		this->z *= scale;
		return *this;
	}
};

template<typename T>
bool operator==(const Vector3<T>& left, const Vector3<T>& right)
{
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}
template<typename T>
bool operator!=(const Vector3<T>& left, const Vector3<T>& right)
{
	return !(left == right);
}
template<typename T>
std::ostream& operator<<(std::ostream& out, const Vector3<T>& vec)
{
	out << '{' << vec.x << ", " << vec.y << ", " << vec.z << '}';
	return out;
}
