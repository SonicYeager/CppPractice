#include "Rotate.h"
#include <cmath>

void Rotate(double& x, double& y, double& z, double cx, double cy, double cz, double d, int a)
{
	double temp1 = 0.0;
	double temp2 = 0.0;
	switch(a)
	{
	case 1:
	{
		d *= 0.01745329251994329576923690768489;
		temp1 = (y - cy) * std::cos(d) - (z - cz) * std::sin(d) + cy;
		temp2 = (y - cy) * std::sin(d) + (z - cz) * std::cos(d) + cz;
		y = temp1;
		z = temp2;
		break;
	}
	case 2:
	{
		d *= 0.01745329251994329576923690768489;
		temp1 = (z - cz) * std::cos(d) - (x - cx) * std::sin(d) + cx;
		temp2 = (z - cz) * std::sin(d) + (x - cx) * std::cos(d) + cz;
		x = temp1;
		z = temp2;
		break;
	}
	case 3:
	{
		d *= 0.01745329251994329576923690768489;
		temp1 = (x - cx) * std::cos(d) - (y - cy) * std::sin(d) + cx;
		temp2 = (x - cx) * std::sin(d) + (y - cy) * std::cos(d) + cy;
		x = temp1;
		y = temp2;
		break;
	}
	case 4:
	{
		x += 2 * (cx - x);
		y += 2 * (cy - y);
		z += 2 * (cz - z);
		break;
	}
	}
}
