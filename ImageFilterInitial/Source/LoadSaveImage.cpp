#include "LoadSaveImage.h"
#include <fstream>
#include <Windows.h>
#undef LoadImage

/// Save RGB/Grayscale image as BMP
#pragma region save
std::ofstream OpenFileForWrite(const std::filesystem::path& path)
{
	std::ofstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	file.open(path, std::ios::binary);
	return file;
}

void WriteBitmapContent(std::ofstream& file, const std::vector<unsigned char>& data)
{
	file.write(reinterpret_cast<const char*>(data.data()), data.size());
}

void WriteBitmapHeader(std::ofstream& file, const ImageResolution& resol)
{
	BITMAPFILEHEADER bmFile{};
	BITMAPINFOHEADER bmInfo{};
	bmInfo.biBitCount = 24;
	bmInfo.biSize = sizeof bmInfo;
	bmInfo.biWidth = resol.width;
	bmInfo.biHeight = resol.height;
	bmInfo.biSizeImage = 3 * resol.width * resol.height;
	bmInfo.biPlanes = 1;
	bmFile.bfOffBits = sizeof bmFile + sizeof bmInfo;
	bmFile.bfSize = bmFile.bfOffBits + bmInfo.biSizeImage;
	bmFile.bfType = 'MB';
	file.write(reinterpret_cast<const char*>(&bmFile), sizeof bmFile);
	file.write(reinterpret_cast<const char*>(&bmInfo), sizeof bmInfo);
}

std::vector<unsigned char> Convert(const RGBImage& img)
{
	std::vector<unsigned char> result(3 * img.Resolution().width * img.Resolution().height);
	const int factor = 1; //0x7fff;
	auto destination = result.data();
	auto source = img.GetRaw();

	for(size_t i = 0; i < result.size() / 3; ++i, ++source)
	{
		(*destination++) = static_cast<unsigned char>(source->b / factor);
		(*destination++) = static_cast<unsigned char>(source->g / factor);
		(*destination++) = static_cast<unsigned char>(source->r / factor);
	}
	return result;
}

std::vector<unsigned char> Convert(const GrayscaleImage& img)
{
	std::vector<unsigned char> result(3 * img.Resolution().width * img.Resolution().height);
	const int factor = 1; //0x7fff;
	auto destination = result.data();
	auto source = img.GetRaw();

	for(size_t i = 0; i < result.size() / 3; ++i, ++source)
	{
		(*destination++) = static_cast<unsigned char>(*source / factor);
		(*destination++) = static_cast<unsigned char>(*source / factor);
		(*destination++) = static_cast<unsigned char>(*source / factor);
	}
	return result;
}

void SaveImage::ToBMP(const std::filesystem::path& path, const RGBImage& source)
{
	auto file = OpenFileForWrite(path);
	WriteBitmapHeader(file, source.Resolution());
	auto content = Convert(source);
	WriteBitmapContent(file, content);
}

void SaveImage::ToBMP(const std::filesystem::path& path, const GrayscaleImage& source)
{
	auto file = OpenFileForWrite(path);
	WriteBitmapHeader(file, source.Resolution());
	auto content = Convert(source);
	WriteBitmapContent(file, content);
}
#pragma endregion


/// Load RGB image file
#pragma region Load
std::ifstream OpenFileForRead(const std::filesystem::path& path)
{
	std::ifstream file;
	auto absPath = std::filesystem::absolute(path);
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	file.open(path, std::ios::binary);
	return file;
}

std::uint32_t GetOffsetToData(std::ifstream& file)
{
	BITMAPFILEHEADER header{};
	file.read(reinterpret_cast<char*>(&header), sizeof header);
	return header.bfOffBits;
}

ImageResolution GetResolution(std::ifstream& file)
{
	BITMAPINFOHEADER header{};
	file.read(reinterpret_cast<char*>(&header), sizeof header);
	return ImageResolution{header.biWidth, header.biHeight};
}

void GoToFilePos(std::ifstream& file, std::uint32_t offset)
{
	file.seekg(offset, std::ios::beg);
}

std::vector<unsigned char> ReadData(std::ifstream& file, const ImageResolution& resol)
{
	std::vector<unsigned char> result(3 * resol.width * resol.height);
	file.read(reinterpret_cast<char*>(result.data()), result.size());
	return result;
}

std::vector<Pixel> Convert(const std::vector<unsigned char>& rawData)
{
	std::vector<Pixel> result(rawData.size() / 3);
	auto source = rawData.data();

	for(Pixel& px : result)
	{
		px.b = static_cast<int>(*source++);
		px.g = static_cast<int>(*source++);
		px.r = static_cast<int>(*source++);
	}
	return result;
}

RGBImage LoadImage::FromBMP(const std::filesystem::path& path)
{
	auto file = OpenFileForRead(path);
	auto offsetToData = GetOffsetToData(file);
	auto resolution = GetResolution(file);
	GoToFilePos(file, offsetToData);
	auto source = ReadData(file, resolution);
	auto dest = Convert(source);
	return RGBImage(std::move(dest), resolution);
}
#pragma endregion
