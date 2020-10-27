#include "gmock/gmock.h"
#include "TestGen.h"

TEST(TestTestGen, RandChars_TenRandCharsWithThreeBack_AtLeastThreeNBack)
{
	//setup
	NBACK::TestGen gen;
	//exe
	auto generated = gen.GenNBackChars(10, 3);
	//eval
	int actual{};
	int atLeast{ 3 };
	for (int i{ 3 }; i < 10; ++i)
	{
		auto res = generated[i - 3] == generated[i];
		if (res == true)
			++actual;
	}
	EXPECT_TRUE(actual >= atLeast);
}