#pragma once
#include "CImg.h"
#include <string>
#include <future>
#include <random>
#include <vector>

struct ImageGenerator
{
	void CreateHelloWorld();
	void WriteImgagesAsync();
	void GenerateImages();
private:
	std::vector<cimg_library::CImg<unsigned int>> imgs{};
	unsigned char textColor[3] = {50,50,50};
};