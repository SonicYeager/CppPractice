#include "gmock/gmock.h"
#include "ProcessImage.h"
#include "ImageUtils.h"
#include "LoadSaveImage.h"
#include <filesystem>


TEST(TestProcessImages, Run_PrewittBothDirections_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{ 
		{"-src" }, 
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(PrewittBothDirections).bmp"},
		{"-orient"},
		{"both"}
	};


	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Prewitt,beide Richtungen).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(PrewittBothDirections).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_PrewittHorizontal_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(PrewittHorizontal).bmp"},
		{"-orient"},
		{"horizontal"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Prewitt,horizontal).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(PrewittHorizontal).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_PrewittNormalizedBoth_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(PrewittNormalizedBoth).bmp"},
		{"-orient"},
		{"both"},
		{"-norm"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Prewitt,normiert,beide Richtungen).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(PrewittNormalizedBoth).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_PrewittNormalizedVertical_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(PrewittNormalizedVertical).bmp"},
		{"-orient"},
		{"vertical"},
		{"-norm"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Prewitt,normiert,vertikal).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(PrewittNormalizedVertical).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_PrewittScaledTwoPointFiveNormalizedVertical_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(PrewittScaledTwoPointFiveNormalizedVertical).bmp"},
		{"-scale"},
		{"2.5"},
		{"-orient"},
		{"vertical"},
		{"-norm"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Prewitt,skaliert2.5,normiert,vertikal).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(PrewittScaledTwoPointFiveNormalizedVertical).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_PrewittScaledTwoPointFiveVertical_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(PrewittScaledTwoPointFiveVertical).bmp"},
		{"-scale"},
		{"2.5"},
		{"-orient"},
		{"vertical"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Prewitt,skaliert2.5,vertikal).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(PrewittScaledTwoPointFiveVertical).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_PrewittVertical_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(PrewittVertical).bmp"},
		{"-orient"},
		{"vertical"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Prewitt,vertikal).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(PrewittVertical).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_SobelBoth_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(SobelBoth).bmp"},
		{"-kernel"},
		{"sobel"},
		{"-orient"},
		{"both"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Sobel,beide Richtungen).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(SobelBoth).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_SobelBothNormalized_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(SobelBothNormalized).bmp"},
		{"-kernel"},
		{"sobel"},
		{"-orient"},
		{"both"},
		{"-norm"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Sobel,normiert,beide Richtungen).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(SobelBothNormalized).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_SobelScaledTwoPointFiveVertical_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(SobelScaledTwoPointFiveVertical).bmp"},
		{"-kernel"},
		{"sobel"},
		{"-scale"},
		{"2.5"},
		{"-orient"},
		{"vertical"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Sobel,skaliert2.5,vertikal).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(SobelScaledTwoPointFiveVertical).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

TEST(TestProcessImages, Run_SobelVertical_ExcactCongruentWithReference)
{
	//setup
	LoadImage imgloader{};
	ProcessImage pimg{};
	std::vector<std::string> args
	{
		{"-src" },
		{"Haus.bmp"},
		{"-dest"},
		{"Haus(SobelVertical).bmp"},
		{"-kernel"},
		{"sobel"},
		{"-orient"},
		{"vertical"}
	};

	//execution
	pimg.Run(args);

	//validate
	auto expectedIMG = imgloader.FromBMP(std::filesystem::path("Haus(Sobel,vertikal).bmp"));
	auto actualIMG = imgloader.FromBMP(std::filesystem::path("Haus(SobelVertical).bmp"));
	EXPECT_EQ(expectedIMG, actualIMG);
}

//TEST(TestProcessImages, Run_Help_ShowHelpOnConsole)
//{
//	//setup
//	LoadImage imgloader{};
//	ProcessImage pimg{};
//	std::vector<std::string> args
//	{};
//
//	//execution
//	pimg.Run(args);
//
//	//validate
//}