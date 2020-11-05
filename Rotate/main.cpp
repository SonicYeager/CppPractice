#include "Rotate.h"
#include <cassert>
#include <cstdlib>

bool DoubleEqual(double left, double right)
{
	return std::abs(left - right) < 0.0001;
}

int main()
{
	double cx = 1.0;
	double cy = 2.0;
	double cz = -1.0;
	double x = 2.0;
	double y = -2.0;
	double z = 1.0;

	Rotate(x, y, z, cx, cy, cz, 45.0, 1);

	assert(DoubleEqual(x, 2.0));
	assert(DoubleEqual(y, -2.24264));
	assert(DoubleEqual(z, -2.4142));

	x = 2.0;
	y = -2.0;
	z = 1.0;
	Rotate(x, y, z, cx, cy, cz, 45.0, 2);

	assert(DoubleEqual(x, 1.7071));
	assert(DoubleEqual(y, -2.0));
	assert(DoubleEqual(z, 1.1213));

	x = 2.0;
	y = -2.0;
	z = 1.0;
	Rotate(x, y, z, cx, cy, cz, 45.0, 3);

	assert(DoubleEqual(x, 4.5355));
	assert(DoubleEqual(y, -0.1213));
	assert(DoubleEqual(z, 1.0));


	x = 2.0;
	y = -2.0;
	z = 1.0;
	Rotate(x, y, z, cx, cy, cz, 45.0, 4);

	assert(DoubleEqual(x, 0.0));
	assert(DoubleEqual(y, 6.0));
	assert(DoubleEqual(z, -3.0));

	x = 2.0;
	y = -2.0;
	z = 1.0;
	Rotate(x, y, z, cx, cy, cz, 45.0, 0);

	assert(DoubleEqual(x, 2.0));
	assert(DoubleEqual(y, -2.0));
	assert(DoubleEqual(z, 1.0));
}
