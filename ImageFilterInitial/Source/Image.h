#pragma once
#include "Vector3.h"
#include <vector>

// A pixel is a single point in the image plane mostly RGB (red, green, blue)
using Pixel = Vector3<int>;

// A line of an image contains 'width' number pixels
template<typename T>
class ImageLine
{
public:
	explicit ImageLine(T* s)
		: start(s)
	{}

	const T& operator[](int index) const
	{
		return start[index];
	}
	T& operator[](int index)
	{
		return start[index];
	}

private:
	T* start = nullptr;
};


// The resolution pinpoints the limits of an image
class ImageResolution
{
public:
	int width = 0;
	int height = 0;
};


// Image contains pixel data as interleaved RGB
template<typename T>
class Image
{
public:
	explicit Image(const ImageResolution& resol)
		: data(resol.width * resol.height)
		, resolution(resol)
	{}
	Image(Image&& img)
		: Image(std::move(img.data), img.resolution)
	{}
	Image(std::vector<T>&& d, const ImageResolution& resol)
		: data(std::move(d))
		, resolution(resol)
	{}

	const ImageLine<T> operator[](int index) const
	{
		return ImageLine<T>(const_cast<T*>(this->data.data()) + this->resolution.width * index);
	}
	ImageLine<T> operator[](int index)
	{
		return ImageLine<T>(this->data.data() + this->resolution.width * index);
	}
	const T* GetRaw() const
	{
		return this->data.data();
	}
	T* GetRaw()
	{
		return this->data.data();
	}

	void Resize(const ImageResolution& newSize)
	{
		this->resolution = newSize;
		this->data.clear();
		this->data.resize(newSize.width * newSize.height);
	}
	const ImageResolution& Resolution() const
	{
		return this->resolution;
	}

private:
	std::vector<T> data;
	ImageResolution resolution;
};
