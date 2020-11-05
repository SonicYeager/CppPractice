#pragma once
#include "3DPoint.h"

const int XAXIS = 1;
const int YAXIS = 2;
const int ZAXIS = 3;
const int ALLAXIS = 4;

void RotateVectorByDegreeOnAxisAroundOrigin(ThreeDPoint& point, ThreeDPoint origin, double degree, int axis);
