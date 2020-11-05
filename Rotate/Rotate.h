#pragma once

const int XAXIS = 1;
const int YAXIS = 2;
const int ZAXIS = 3;
const int ALLAXIS = 4;

void RotateVectorByDegreeOnAxisAroundOrigin(double& x, double& y, double& z, double originx, double originy, double originz, double degree, int axis);
