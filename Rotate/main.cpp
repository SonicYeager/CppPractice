#include "Rotate.h"
#include <cassert>
#include <cstdlib>

bool AreEqualToFourDecimals(double left, double right)
{
	auto abs = std::abs(left - right);
	return abs < 0.0001;
}

int main()
{
	double originx = 1.0;
	double originy = 2.0;
	double originz = -1.0;
	double x = 2.0;
	double y = -2.0;
	double z = 1.0;

	RotateVectorByDegreeOnAxisAroundOrigin(x, y, z, originx, originy, originz, 45.0, 1); // !x

	assert(AreEqualToFourDecimals(x, 2.0));
	assert(AreEqualToFourDecimals(y, -2.24264));
	assert(AreEqualToFourDecimals(z, -2.4142));

	x = 2.0;
	y = -2.0;
	z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(x, y, z, originx, originy, originz, 45.0, 2); // !y

	assert(AreEqualToFourDecimals(x, 1.7071));
	assert(AreEqualToFourDecimals(y, -2.0));
	assert(AreEqualToFourDecimals(z, 1.1213));

	x = 2.0;
	y = -2.0;
	z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(x, y, z, originx, originy, originz, 45.0, 3); // !z

	assert(AreEqualToFourDecimals(x, 4.5355));
	assert(AreEqualToFourDecimals(y, -0.1213));
	assert(AreEqualToFourDecimals(z, 1.0));

	x = 2.0;
	y = -2.0;
	z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(x, y, z, originx, originy, originz, 45.0, 4); //all

	assert(AreEqualToFourDecimals(x, 0.0));
	assert(AreEqualToFourDecimals(y, 6.0));
	assert(AreEqualToFourDecimals(z, -3.0));

	x = 2.0;
	y = -2.0;
	z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(x, y, z, originx, originy, originz, 45.0, 0); //not existing case

	assert(AreEqualToFourDecimals(x, 2.0));
	assert(AreEqualToFourDecimals(y, -2.0));
	assert(AreEqualToFourDecimals(z, 1.0));
}
