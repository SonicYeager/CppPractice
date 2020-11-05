#include "Rotate.h"
#include <cmath>

void RotateVectorByDegreeOnAxisAroundOrigin(double& x, double& y, double& z, double originx, double originy, double originz, double degree, int axis)
{
	const double DEGTORADCONSTANT = 0.01745329251994329576923690768489;
	double radiants = degree * DEGTORADCONSTANT;

	switch(axis)
	{
	case 1:	//x
	{


		auto tempy = (y - originy) * std::cos(radiants) - (z - originz) * std::sin(radiants) + originy;
		auto tempz = (y - originy) * std::sin(radiants) + (z - originz) * std::cos(radiants) + originz;
		y = tempy;
		z = tempz;
		break;
	}
	case 2:	//y
	{
		auto tempx = (z - originz) * std::cos(radiants) - (x - originx) * std::sin(radiants) + originx;
		auto tempz = (z - originz) * std::sin(radiants) + (x - originx) * std::cos(radiants) + originz;
		x = tempx;
		z = tempz;
		break;
	}
	case 3:	//z
	{
		auto tempx = (x - originx) * std::cos(radiants) - (y - originy) * std::sin(radiants) + originx;
		auto tempy = (x - originx) * std::sin(radiants) + (y - originy) * std::cos(radiants) + originy;
		x = tempx;
		y = tempy;
		break;
	}
	case 4:
	{
		x += 2 * (originx - x);
		y += 2 * (originy - y);
		z += 2 * (originz - z);
		break;
	}
	}
}
