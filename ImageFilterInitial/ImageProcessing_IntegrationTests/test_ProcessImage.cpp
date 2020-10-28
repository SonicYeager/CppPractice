#include "gmock/gmock.h"
#include "ProcessImage.h"
#include "ImageUtils.h"
#include "LoadSaveImage.h"
#include <filesystem>

//del dump cont (if not overwritten)
//fetch files for comp then comp


TEST(TestProcessImages, Run_PrewittBothDirections_ExcactCongruent)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{ 
		{"-src" }, 
		{"C:/Uebungsprojekte/ImageFilterInitial/Images/Haus.bmp"}, 
		{"-dest" }, 
		{"C:/Uebungsprojekte/ImageFilterInitial/dump/Haus(Prewitt,beideRichtungen).bmp"},
		{"-orient"},
		{"both"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("C:/Uebungsprojekte/ImageFilterInitial/References/Haus(Prewitt, beide Richtungen).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("C:/Uebungsprojekte/ImageFilterInitial/dump/Haus(Prewitt,beideRichtungen).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);

}