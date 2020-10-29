#include <gmock/gmock.h>
#include "FilterImage.h"
#include "LoadSaveImage.h"

#pragma region Prepare
class TestFilterImage : public testing::Test
{
public:
	RGBImage GenerateImageWithVerticalLine()
	{
		RGBImage img(
			{
				Pixel{10}, Pixel{87},  Pixel{12}, Pixel{2},  //
				Pixel{17}, Pixel{91},  Pixel{11}, Pixel{12}, //
				Pixel{15}, Pixel{88},  Pixel{5},  Pixel{5},  //
				Pixel{5},  Pixel{107}, Pixel{8},  Pixel{18}, //
				Pixel{18}, Pixel{92},  Pixel{15}, Pixel{30} //
			},
			{4, 5});
		return img;
	}
	RGBImage GenerateImageWithHorizontalLine()
	{
		RGBImage img(
			{
				Pixel{10}, Pixel{17}, Pixel{15}, Pixel{5},   Pixel{18}, //
				Pixel{87}, Pixel{91}, Pixel{88}, Pixel{107}, Pixel{92}, //
				Pixel{10}, Pixel{11}, Pixel{5},  Pixel{8},   Pixel{15}, //
				Pixel{2},  Pixel{12}, Pixel{5},  Pixel{18},  Pixel{30}  //
			},
			{5, 4});
		return img;
	}
};
#pragma endregion


TEST_F(TestFilterImage, ApplyOneDirection_VerticalLinePrewittNoOptions_ImproveEdge)
{
	const RGBImage original = GenerateImageWithVerticalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = FilterKernel::PREWITT;
	filter.ApplyOneDirection(original, actual);

	const RGBImage expected(
		{
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
			Pixel{0}, Pixel{13}, Pixel{247}, Pixel{0}, //
			Pixel{0}, Pixel{12}, Pixel{250}, Pixel{0}, //
			Pixel{0}, Pixel{10}, Pixel{234}, Pixel{0}, //
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST_F(TestFilterImage, ApplyOneDirection_HorizontalLinePrewittNoOptions_NoEdge)
{
	const RGBImage original = GenerateImageWithHorizontalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = FilterKernel::PREWITT;
	filter.ApplyOneDirection(original, actual);

	const RGBImage expected(
		{
			Pixel{0}, Pixel{0}, Pixel{0},  Pixel{0},  Pixel{0}, //
			Pixel{0}, Pixel{0}, Pixel{0},  Pixel{17}, Pixel{0}, //
			Pixel{0}, Pixel{1}, Pixel{18}, Pixel{37}, Pixel{0}, //
			Pixel{0}, Pixel{0}, Pixel{0},  Pixel{0},  Pixel{0}  //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST_F(TestFilterImage, ApplyOneDirection_HorizontalLinePrewittHorizontal_ImproveEdge)
{
	const RGBImage original = GenerateImageWithHorizontalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = Transpose(FilterKernel::PREWITT);
	filter.ApplyOneDirection(original, actual);

	const RGBImage expected(
		{
			Pixel{0}, Pixel{0},   Pixel{0},   Pixel{0},   Pixel{0}, //
			Pixel{0}, Pixel{15},  Pixel{12},  Pixel{10},  Pixel{0}, //
			Pixel{0}, Pixel{247}, Pixel{250}, Pixel{234}, Pixel{0}, //
			Pixel{0}, Pixel{0},   Pixel{0},   Pixel{0},   Pixel{0}  //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST_F(TestFilterImage, ApplyOneDirection_VerticalLinePrewittWithScaleSmallerOne_ImproveEdgeAndReduceBrightness)
{
	const RGBImage original = GenerateImageWithVerticalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = FilterKernel::PREWITT * 0.5;
	filter.ApplyOneDirection(original, actual);

	const RGBImage expected(
		{
			Pixel{0}, Pixel{0}, Pixel{0},   Pixel{0}, //
			Pixel{0}, Pixel{6}, Pixel{123}, Pixel{0}, //
			Pixel{0}, Pixel{6}, Pixel{125}, Pixel{0}, //
			Pixel{0}, Pixel{5}, Pixel{117}, Pixel{0}, //
			Pixel{0}, Pixel{0}, Pixel{0},   Pixel{0}, //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}


TEST_F(TestFilterImage, ApplyOneDirection_OverflowOfElementValues_ClipTo255)
{
	const RGBImage original = GenerateImageWithVerticalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = FilterKernel::PREWITT * 1.5;
	filter.rectifyValues = Utils::ClipTo255;
	filter.ApplyOneDirection(original, actual);

	const RGBImage expected(
		{
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
			Pixel{0}, Pixel{19}, Pixel{255}, Pixel{0}, //
			Pixel{0}, Pixel{18}, Pixel{255}, Pixel{0}, //
			Pixel{0}, Pixel{15}, Pixel{255}, Pixel{0}, //
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST_F(TestFilterImage, ApplyOneDirection_VerticalLineSobelWithScale_ImproveEdge)
{
	const RGBImage original = GenerateImageWithVerticalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = FilterKernel::SOBEL * 0.5;
	filter.ApplyOneDirection(original, actual);

	const RGBImage expected(
		{
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
			Pixel{0}, Pixel{9},  Pixel{163}, Pixel{0}, //
			Pixel{0}, Pixel{10}, Pixel{166}, Pixel{0}, //
			Pixel{0}, Pixel{3},  Pixel{161}, Pixel{0}, //
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST_F(TestFilterImage, ApplyBothDirection_CrossLineSobelWithScale_ImproveEdge)
{
	const RGBImage original = GenerateImageWithVerticalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = FilterKernel::SOBEL * 0.5;
	filter.rectifyValues = Utils::ClipTo255;
	filter.ApplyBothDirection(original, actual);


	const RGBImage expected(
		{
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
			Pixel{0}, Pixel{9},  Pixel{163}, Pixel{0}, //
			Pixel{0}, Pixel{12}, Pixel{166}, Pixel{0}, //
			Pixel{0}, Pixel{10},  Pixel{162}, Pixel{0}, //
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0} //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST_F(TestFilterImage, ApplyBothDirection_VerticalLinePrewittNoOptions_ImproveEdge)
{
	const RGBImage original = GenerateImageWithVerticalLine();
	RGBImage actual(original.Resolution());

	FilterImage filter;
	filter.kernel = FilterKernel::PREWITT;
	filter.rectifyValues = Utils::ClipTo255;
	filter.ApplyBothDirection(original, actual);

	const RGBImage expected(
		{
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}, //
			Pixel{0}, Pixel{13}, Pixel{247}, Pixel{0}, //
			Pixel{0}, Pixel{12}, Pixel{250}, Pixel{0}, //
			Pixel{0}, Pixel{19}, Pixel{236}, Pixel{0}, //
			Pixel{0}, Pixel{0},  Pixel{0},   Pixel{0}  //
		},
		original.Resolution());
	EXPECT_EQ(expected, actual);
}


//	{
//	const GrayscaleImage grayscale = Utils::ToGrayscale(original);
//	GrayscaleImage resultVert = Utils::Convolute(grayscale, filter.kernel);
//	auto kernelHori = Transpose(filter.kernel);
//	GrayscaleImage resultHori = Utils::Convolute(grayscale, kernelHori);
//	auto result = Utils::Gradient(resultVert, resultHori);
//	auto resss = Utils::Gradient(resultVert, resultHori);
//	;
//}