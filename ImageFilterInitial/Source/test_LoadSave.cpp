#include <gmock/gmock.h>
#include "LoadSaveImage.h"

TEST(TestLoadSave, Acceptance_LoadedIsSameAsSaved)
{
	const RGBImage expected(
		{
			Pixel{1},   Pixel{2},   Pixel{3},   Pixel{4},   Pixel{5},   //
			Pixel{6},   Pixel{7},   Pixel{8},   Pixel{9},   Pixel{10},  //
			Pixel{20},  Pixel{22},  Pixel{57},  Pixel{62},  Pixel{123}, //
			Pixel{251}, Pixel{252}, Pixel{253}, Pixel{254}, Pixel{255}, //
			Pixel{160}, Pixel{170}, Pixel{180}, Pixel{0},   Pixel{190}, //
			Pixel{57},  Pixel{187}, Pixel{29},  Pixel{15},  Pixel{211}, //
			Pixel{234}, Pixel{122}, Pixel{255}, Pixel{12},  Pixel{111}, //
		},
		{5, 7});

	SaveImage::ToBMP("test.bmp", expected);
	const RGBImage actual = LoadImage::FromBMP("test.bmp");

	EXPECT_EQ(expected, actual);

	std::remove("test.bmp");
}
