#pragma once
#include "ImageUtils.h"
#include "Matrix3x3.h"
#include "Event.h"

using FilterAlgorithm = std::function<void(const RGBImage&, RGBImage&)>;

class FilterImage
{
public:
	void ApplyOneDirection(const RGBImage& source, RGBImage& destination);
	void ApplyBothDirection(const RGBImage& source, RGBImage& destination);

	Event<GrayscaleImage&> rectifyValues = [](GrayscaleImage&) {};
	Matrix3x3 kernel = {};
};

struct FilterKernel
{
	static const Matrix3x3 SOBEL;
	static const Matrix3x3 PREWITT;
};
