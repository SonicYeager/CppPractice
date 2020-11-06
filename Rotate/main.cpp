#include "Rotate.h"
#include "3DPoint.h"
#include <cassert>
#include <cstdlib>

bool AreEqualToFourDecimals(double left, double right)
{
	auto abs = std::abs(left - right);
	return abs < 0.0001;
}

const double FOURTYFIVEDEG = 45.0;

int main()
{
	ThreeDPoint origin{1.0, 2.0, -1.0};
	ThreeDPoint point{2.0, -2.0, 1.0};

	RotateVectorByDegreeOnAxisAroundOrigin(point, origin, FOURTYFIVEDEG, XAXIS); // !x

	assert(AreEqualToFourDecimals(point.x, 2.0));
	assert(AreEqualToFourDecimals(point.y, -2.24264));
	assert(AreEqualToFourDecimals(point.z, -2.4142));

	point.x = 2.0;
	point.y = -2.0;
	point.z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(point, origin, FOURTYFIVEDEG, YAXIS); // !y

	assert(AreEqualToFourDecimals(point.x, 1.7071));
	assert(AreEqualToFourDecimals(point.y, -2.0));
	assert(AreEqualToFourDecimals(point.z, 1.1213));

	point.x = 2.0;
	point.y = -2.0;
	point.z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(point, origin, FOURTYFIVEDEG, ZAXIS); // !z

	assert(AreEqualToFourDecimals(point.x, 4.5355));
	assert(AreEqualToFourDecimals(point.y, -0.1213));
	assert(AreEqualToFourDecimals(point.z, 1.0));

	point.x = 2.0;
	point.y = -2.0;
	point.z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(point, origin, FOURTYFIVEDEG, INVERTPOINT); //all

	assert(AreEqualToFourDecimals(point.x, 0.0));
	assert(AreEqualToFourDecimals(point.y, 6.0));
	assert(AreEqualToFourDecimals(point.z, -3.0));

	point.x = 2.0;
	point.y = -2.0;
	point.z = 1.0;
	RotateVectorByDegreeOnAxisAroundOrigin(point, origin, FOURTYFIVEDEG, 0); //not existing case

	assert(AreEqualToFourDecimals(point.x, 2.0));
	assert(AreEqualToFourDecimals(point.y, -2.0));
	assert(AreEqualToFourDecimals(point.z, 1.0));
}
