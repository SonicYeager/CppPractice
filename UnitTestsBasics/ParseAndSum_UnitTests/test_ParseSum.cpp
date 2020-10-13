#include "gtest/gtest.h"
#include "ParseSum.h"

TEST(TestParseSum, ParseAndSum_SingleDigit_ReturnParsedDigit)
{
	auto actual = ParseSum::ParseAndSum("3");
	EXPECT_EQ(actual, 3);
}

TEST(TestParseSum, ParseAndSum_TwoSemicolonSeperatedDigit_ReturnParsedDigitSummed)
{
	EXPECT_EQ(ParseSum::ParseAndSum("3;4"), 7);
}

TEST(TestParseSum, ParseAndSum_MultipleSemicolonSeperatedDigit_ReturnParsedDigitSummed)
{
	EXPECT_EQ(ParseSum::ParseAndSum("3;4;8"), 15);
}