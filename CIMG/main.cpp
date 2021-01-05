#include "CImg.h"
#include "ImageGenerator.h"
#include <string>
#include <future>

int main(int argc, char* argv[])
{
	//img.display("My first CImg code"); // Display the image in a display window.
	ImageGenerator imgg;
	imgg.GenerateImages();
	imgg.WriteImgagesAsync();
}