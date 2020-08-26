#pragma once
class Vec4
{
public:
	union
	{
		struct
		{
			float x, y, z, w;
		};
		struct
		{
			float r, g, b, a;
		};
	};
	// all vals 0
	Vec4();
	// all vals s(n)
	Vec4(float s1, float s2, float s3, float s4);
	// all values will be ini with 'scalar'
	Vec4(float scalar);
	// copys the values from another vec4
	Vec4(const Vec4& cpy);
	~Vec4();

	// copys value from ...
	Vec4& operator=(float scalar);
	Vec4& operator=(const Vec4& cpy);
	bool operator==(const Vec4& vRight);
	bool operator!=(const Vec4& vRight);
};
