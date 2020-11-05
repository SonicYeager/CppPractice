#include "Rotate.h"
#include <cmath>

void RotateVectorByDegreeOnAxisAroundOrigin(ThreeDPoint& point, ThreeDPoint origin, double degree, int axis)
{
	const double DEGTORADCONSTANT = 0.01745329251994329576923690768489;
	const int MOVEFAC = 2;
	double radiants = degree * DEGTORADCONSTANT;
	auto cos = std::cos(radiants);
	auto sin = std::sin(radiants);

	switch(axis)
	{
	case 1:	//x
	{
		auto combinedy = point.y - origin.y;
		auto combinedz = point.z - origin.z;
		point.y = combinedy * cos - combinedz * sin + origin.y;
		point.z = combinedy * sin + combinedz * cos + origin.z;
		break;
	}
	case 2:	//y
	{
		auto vectorx = point.x - origin.x;
		auto vectorz = point.z - origin.z;
		point.x = vectorz * cos - vectorx * sin + origin.x;
		point.z = vectorz * sin + vectorx * cos + origin.z;
		break;
	}
	case 3:	//z
	{
		auto vectorx = point.x - origin.x;
		auto vectory = point.y - origin.y;
		point.x = vectorx * cos - vectory * sin + origin.x;
		point.y = vectorx * sin + vectory * cos + origin.y;
		break;
	}
	case 4: //clear out the magic number!!
	{
		point.x += MOVEFAC * (origin.x - point.x);
		point.y += MOVEFAC * (origin.y - point.y);
		point.z += MOVEFAC * (origin.z - point.z);
		break;
	}
	}
}
