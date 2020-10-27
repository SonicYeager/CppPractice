#include "gmock/gmock.h"
#include "TestGen.h"

TEST(TestTestGen, RandChars_TenRandCharsWithThreeBack_AtLeastThreeNBack)
{
	//setup
	const int N{3};
	NBACK::TestGen gen;
	//exe
	auto generated = gen.GenNBackChars(10, N);
	//eval
	int actual{};
	int atLeast{ 3 };
	for (int i{ N }; i < 10; ++i)
	{
		auto res = generated[i - N] == generated[i];
		if (res == true)
			++actual;
	}
	EXPECT_TRUE(actual >= atLeast);
}