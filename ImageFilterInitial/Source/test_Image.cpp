#include <gmock/gmock.h>
#include "ImageUtils.h"

TEST(TestImage, Access_NonConstantLine_ModifyImage)
{
	RGBImage actual(ImageResolution{2, 3});

	actual[0][1] = Pixel{1, 2, 3};
	actual[1][1] = Pixel{4, 5, 6};
	actual[2][0] = Pixel{7, 8, 9};

	const RGBImage expected({{}, {1, 2, 3}, {}, {4, 5, 6}, {7, 8, 9}, {}}, actual.Resolution());
	EXPECT_EQ(actual, expected);
}

TEST(TestImage, Resize_FilledImage_ResetImage)
{
	RGBImage actual({Pixel(1), Pixel(2), Pixel(3), Pixel(4), Pixel(5), Pixel(6)}, ImageResolution{2, 3});

	actual.Resize(ImageResolution{2, 3});

	const RGBImage expected({{}, {}, {}, {}, {}, {}}, actual.Resolution());
	EXPECT_EQ(actual, expected);
}
