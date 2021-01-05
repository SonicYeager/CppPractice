#include "ImageGenerator.h"
#include <chrono>

void ImageGenerator::CreateHelloWorld()
{
#if true
	cimg_library::CImg<unsigned char> img(200, 200);
	img.fill(0);
	img.draw_text(50, 50, "Hello World", textColor);
	img.draw_text(100, 100, "Hello World2", textColor);
	img.draw_text(50, 50, "Hello World3", textColor);
	img.draw_text(10, 10, "Hello World4", textColor);
	img.draw_text(130, 130, "Hello World5", textColor);
	img.draw_text(20, 40, "Hello World6", textColor);
	imgs.push_back(img);
#else
	const unsigned char purple[] = { 255,0,255 };
	CImg<unsigned char>(640, 400, 1, 3, 0).draw_text(100, 100, "Hello World", purple).display("My first CImg code");
#endif
}

void WriteImage(std::vector<cimg_library::CImg<unsigned char>> imgs, int thread)
{
	for (size_t i{0}; i < imgs.size(); ++i)
	{
		imgs[i].save_bmp(("Images\\gen" + std::to_string(i) + std::to_string(thread) + ".bmp").c_str());
	}
}

void ImageGenerator::WriteImgagesAsync()
{
	std::vector<std::vector<cimg_library::CImg<unsigned char>>> splitted{};
	for (size_t i{ 0 }; i < 12; ++i)
	{
		auto beginv = ((imgs.size() / 12) * i);
		auto endv = (imgs.size() / 12) + beginv;
		std::vector<cimg_library::CImg<unsigned char>>::const_iterator begin = imgs.begin() + beginv;
		std::vector<cimg_library::CImg<unsigned char>>::const_iterator end = imgs.begin() + endv;
		splitted.emplace_back(begin, end );
	}
	std::vector<std::future<void>> asyncs{};
	int thread{0};
	for (auto& split : splitted)
	{
		asyncs.emplace_back(std::async(std::launch::async, std::bind(WriteImage, split, thread)));
		++thread;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(2000));
	for (auto& as : asyncs)
		as.get();
}

void ImageGenerator::GenerateImages()
{
	imgs.reserve(6000);
	for (int i{}; i < 6000; ++i)
		CreateHelloWorld();
}
