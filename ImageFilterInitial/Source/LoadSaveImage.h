#pragma once
#include "ImageUtils.h"
#include <filesystem>

class SaveImage
{
public:
	static void ToBMP(const std::filesystem::path& path, const RGBImage& img);
	static void ToBMP(const std::filesystem::path& path, const GrayscaleImage& img);
};

class LoadImage
{
public:
	static RGBImage FromBMP(const std::filesystem::path& fileName);
};
