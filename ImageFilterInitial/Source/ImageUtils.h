#pragma once
#include "Image.h"
#include "Matrix3x3.h"
#include <ostream>

using RGBImage = Image<Pixel>;
using GrayscaleImage = Image<int>;

namespace Utils
{
	GrayscaleImage ToGrayscale(const RGBImage& img);
	void CopyFromTo(const GrayscaleImage& source, RGBImage& destination);
	GrayscaleImage Convolute(const GrayscaleImage& img, const Matrix3x3& kernel);
	void ClipTo255(GrayscaleImage& gray);
	void Normalize(GrayscaleImage& img);
	GrayscaleImage Gradient(const GrayscaleImage& left, const GrayscaleImage& right);
} // namespace Utils

// Comparison
bool operator==(const ImageResolution& left, const ImageResolution& right);
bool operator!=(const ImageResolution& left, const ImageResolution& right);
template<typename T>
bool operator==(const Image<T>& left, const Image<T>& right)
{
	if(left.Resolution() != right.Resolution())
		return false;

	return std::equal(left.GetRaw(), left.GetRaw() + left.Resolution().height * left.Resolution().width,
					  right.GetRaw());
}
template<typename T>
bool operator!=(const Image<T>& left, const Image<T>& right)
{
	return !(left == right);
}

// Output the content of the image to a stream
std::ostream& operator<<(std::ostream& out, const ImageResolution& resol);
template<typename T>
std::ostream& operator<<(std::ostream& out, const Image<T>& img)
{
	out << img.Resolution() << '\n';
	auto start = img.GetRaw();
	for(int row = 0; row < std::min(20, img.Resolution().height); ++row)
	{
		out << '[';
		auto current = start + row * img.Resolution().width;
		for(int col = 0; col < std::min(20, img.Resolution().width); ++col)
			out << *current++ << ", ";
		out << "]\n";
	}
	return out;
}
