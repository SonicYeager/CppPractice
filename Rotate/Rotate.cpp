#include "Rotate.h"
#include <cmath>

void RotateVectorByDegreeOnAxisAroundOrigin(double& x, double& y, double& z, double originx, double originy, double originz, double degree, int axis)
{
	const double DEGTORADCONSTANT = 0.01745329251994329576923690768489;
	double radiants = degree * DEGTORADCONSTANT;
	auto cos = std::cos(radiants);
	auto sin = std::sin(radiants);

	switch(axis)
	{
	case 1:	//x
	{
		auto combinedy = y - originy;
		auto combinedz = z - originz;
		y = combinedy * cos - combinedz * sin + originy;
		z = combinedy * sin + combinedz * cos + originz;
		break;
	}
	case 2:	//y
	{
		auto vectorx = x - originx;
		auto vectorz = z - originz;
		x = vectorz * cos - vectorx * sin + originx;
		z = vectorz * sin + vectorx * cos + originz;
		break;
	}
	case 3:	//z
	{
		auto vectorx = x - originx;
		auto vectory = y - originy;
		x = vectorx * cos - vectory * sin + originx;
		y = vectorx * sin + vectory * cos + originy;
		break;
	}
	case 4: //clear out the magic number!!
	{
		x += 2 * (originx - x);
		y += 2 * (originy - y);
		z += 2 * (originz - z);
		break;
	}
	}
}
