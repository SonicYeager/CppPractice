#include "ImageUtils.h"
#include <algorithm>

bool operator==(const ImageResolution& left, const ImageResolution& right)
{
	return left.width == right.width && left.height == right.height;
}

bool operator!=(const ImageResolution& left, const ImageResolution& right)
{
	return !(left == right);
}

std::ostream& operator<<(std::ostream& out, const ImageResolution& resol)
{
	out << '{' << resol.width << ", " << resol.height << '}';
	return out;
}

namespace Utils
{
	GrayscaleImage ToGrayscale(const RGBImage& img)
	{
		GrayscaleImage result(img.Resolution());
		int* gray = result.GetRaw();
		const int* end = gray + result.Resolution().width * result.Resolution().height;
		const Pixel* rgb = img.GetRaw();
		while(gray != end)
		{
			*gray++ = static_cast<int>(0.3f * rgb->r + 0.59f * rgb->g + 0.11f * rgb->b);
			++rgb;
		}
		return result;
	}

	void CopyFromTo(const GrayscaleImage& source, RGBImage& destination)
	{
		const int* gray = source.GetRaw();
		Pixel* rgb = destination.GetRaw();
		const Pixel* end = rgb + source.Resolution().width * source.Resolution().height;
		while(rgb != end)
		{
			*rgb++ = *gray++;
		}
	}

	GrayscaleImage Convolute(const GrayscaleImage& source, const Matrix3x3& kernel)
	{
		auto resolution = source.Resolution();
		GrayscaleImage result(resolution);
		// Beginne bei i=1 bzw. Ende bei height/width - 1, da es keine Nachbarpixel am Rand gibt
		for(int i = 1; i < resolution.height - 1; ++i)
		{
			auto pre = source[i - 1];
			auto current = source[i];
			auto succ = source[i + 1];
			for(int j = 1; j < resolution.width - 1; ++j)
			{
				// Filter
				float sum = 0.0f;
				for(int k = 0; k < 3; ++k)
				{
					sum += pre[j - 1 + k] * kernel[0][k];
					sum += current[j - 1 + k] * kernel[1][k];
					sum += succ[j - 1 + k] * kernel[2][k];
				}
				result[i][j] = std::abs(static_cast<int>(sum));
			}
		}
		return result;
	}

	void ClipTo255(GrayscaleImage& gray)
	{
		int* current = gray.GetRaw();
		const int* end = current + gray.Resolution().width * gray.Resolution().height;
		while(current != end)
		{
			*current = std::min(255, *current);
			++current;
		}
	}

	void Normalize(GrayscaleImage& gray)
	{
		auto current = gray.GetRaw();
		auto end = current + gray.Resolution().width * gray.Resolution().height;
		int greatest = *std::max_element(current, end);

		while(current != end)
		{
			*current *= 255;
			*current /= greatest;
			++current;
		}
	}

	GrayscaleImage Gradient(const GrayscaleImage& left, const GrayscaleImage& right)
	{
		GrayscaleImage result(left.Resolution());
		auto current = result.GetRaw();
		auto end = current + result.Resolution().width * result.Resolution().height;
		auto x = left.GetRaw();
		auto y = right.GetRaw();
		while(current != end)
		{
			*current++ = static_cast<int>(std::sqrt((*x) * (*x) + (*y) * (*y)));
			++x;
			++y;
		}
		return result;
	}

} // namespace Utils
