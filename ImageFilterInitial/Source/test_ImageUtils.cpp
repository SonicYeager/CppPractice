#include <gmock/gmock.h>
#include "ImageUtils.h"

TEST(TestImageUtils, ToGrayscale_AttendEyeConstraint_ReturnSmoothGray)
{
	const RGBImage original({Pixel{10, 20, 30}, Pixel{20, 30, 40}, Pixel{50, 60, 70},      //
							 Pixel{80, 90, 100}, Pixel{110, 200, 50}, Pixel{255, 40, 100}, //
							 Pixel{255}, Pixel{0}, Pixel{20, 50, 215}},
							ImageResolution{3, 3});

	const GrayscaleImage actual = Utils::ToGrayscale(original);

	const GrayscaleImage expected({18, 28, 58, 88, 156, 111, 255, 0, 59}, actual.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST(TestImageUtils, Clip_OutOfRange_ReturnClamped)
{
	GrayscaleImage actual({0, 5, 58, 88, 256, 256, 123, 12, 255}, ImageResolution{3, 3});

	Utils::ClipTo255(actual);

	const GrayscaleImage expected({0, 5, 58, 88, 255, 255, 123, 12, 255}, actual.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST(TestImageUtils, Convolute_KernelAllOne_ReturnSum)
{
	const GrayscaleImage source({1, 5, -58, 12,      //
								 88, -256, 256, 25,  //
								 -123, 12, 255, -33, //
								 18, 9, -2, 95},     //
								ImageResolution{4, 4});

	auto actual = Utils::Convolute(source, Matrix3x3{1, 1, 1, 1, 1, 1, 1, 1, 1});

	const GrayscaleImage expected({0, 0, 0, 0,     //
								   0, 180, 218, 0, //
								   0, 257, 361, 0, //
								   0, 0, 0, 0},    //
								  actual.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST(TestImageUtils, Normalize_MaxAboveLimit_DecreaseAll)
{
	GrayscaleImage actual({1, 5, 58, 12,     //
						   88, 300, 156, 25, //
						   123, 12, 255, 33, //
						   18, 9, 2, 95},    //
						  ImageResolution{4, 4});

	Utils::Normalize(actual);

	const GrayscaleImage expected({0, 4, 49, 10,     //
								   74, 255, 132, 21, //
								   104, 10, 216, 28, //
								   15, 7, 1, 80},    //
								  actual.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST(TestImageUtils, Normalize_MaxBelowLimit_IncreaseAll)
{
	GrayscaleImage actual({1, 5, 58, 12,     //
						   88, 73, 156, 25,  //
						   123, 12, 200, 33, //
						   18, 9, 2, 95},    //
						  ImageResolution{4, 4});

	Utils::Normalize(actual);

	const GrayscaleImage expected({1, 6, 73, 15,     //
								   112, 93, 198, 31, //
								   156, 15, 255, 42, //
								   22, 11, 2, 121},  //
								  actual.Resolution());
	EXPECT_EQ(expected, actual);
}

TEST(TestImageUtils, Gradient_WithLine_)
{
	const GrayscaleImage left({0, 95, 128, 0,  //
							   0, 180, 218, 0, //
							   0, 257, 361, 0, //
							   0, 95, 128, 0}, //
							  ImageResolution{4, 4});
	const GrayscaleImage right({0, 0, 0, 0,         //
								180, 257, 361, 180, //
								218, 95, 128, 218,  //
								0, 0, 0, 0},        //
							   ImageResolution{4, 4});

	auto actual = Utils::Gradient(left, right);

	const GrayscaleImage expected({0, 95, 128, 0,      //
								   180, 313, 421, 180, //
								   218, 273, 383, 218, //
								   0, 95, 128, 0},     //
								  actual.Resolution());
	EXPECT_EQ(expected, actual);
}
