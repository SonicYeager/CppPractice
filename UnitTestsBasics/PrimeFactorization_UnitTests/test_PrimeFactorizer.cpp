#pragma once
#include "gtest/gtest.h"
#include "PrimeFactorizor.h"

TEST(TestPrimeFactorizor, Factorize_InputPrimes_ExpectPrimes)
{
	EXPECT_EQ(PrimeFactorizor::Factorize(5), "5");
	EXPECT_EQ(PrimeFactorizor::Factorize(7), "7");
	EXPECT_EQ(PrimeFactorizor::Factorize(13), "13");
}

TEST(TestPrimeFactorizor, Factorize_InputEvenSingleDigit_ExpectFactorized)
{
	EXPECT_EQ(PrimeFactorizor::Factorize(2), "2");
	EXPECT_EQ(PrimeFactorizor::Factorize(4), "2*2");
	EXPECT_EQ(PrimeFactorizor::Factorize(6), "2*3");
	EXPECT_EQ(PrimeFactorizor::Factorize(8), "2*2*2");
}

