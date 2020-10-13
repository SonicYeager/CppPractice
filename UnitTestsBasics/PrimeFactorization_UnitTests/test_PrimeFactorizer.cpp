#pragma once
#include "gtest/gtest.h"
#include "PrimeFactorizor.h"

TEST(TestPrimeFactorizor, Factorize_InputPrimes_ReturnPrimes)
{
	EXPECT_EQ(PrimeFactorizor::Factorize(2), "2");
	EXPECT_EQ(PrimeFactorizor::Factorize(3), "3");
	EXPECT_EQ(PrimeFactorizor::Factorize(5), "5");
	EXPECT_EQ(PrimeFactorizor::Factorize(7), "7");
	EXPECT_EQ(PrimeFactorizor::Factorize(13), "13");
	EXPECT_EQ(PrimeFactorizor::Factorize(31), "31");
}

TEST(TestPrimeFactorizor, Factorize_InputEvenSingleDigit_ReturnFactors)
{
	EXPECT_EQ(PrimeFactorizor::Factorize(4), "2*2");
	EXPECT_EQ(PrimeFactorizor::Factorize(6), "2*3");
	EXPECT_EQ(PrimeFactorizor::Factorize(8), "2*2*2");
}


TEST(TestPrimeFactorizor, Factorize_InputUnevenMultipleDigit_ReturnFactors)
{
	EXPECT_EQ(PrimeFactorizor::Factorize(15), "3*5");
	EXPECT_EQ(PrimeFactorizor::Factorize(21), "3*7"); 
}

TEST(TestPrimeFactorizor, Factorize_InputMultipleDigit_ReturnFactorized)
{
	EXPECT_EQ(PrimeFactorizor::Factorize(44), "2*2*11");
	EXPECT_EQ(PrimeFactorizor::Factorize(56), "2*2*2*7");
	EXPECT_EQ(PrimeFactorizor::Factorize(70), "2*5*7");
	EXPECT_EQ(PrimeFactorizor::Factorize(1345), "5*269");
	EXPECT_EQ(PrimeFactorizor::Factorize(3 * 3 * 2 * 5 * 7 * 7 * 13 * 31 * 31 * 31), "2*3*3*5*7*7*13*31*31*31");
}

TEST(TestPrimeFactorizor, Factorize_InputOne_ReturnEmpty)
{
	//Aufbau
	const int input = 1;

	//Ausführen
	auto actual = PrimeFactorizor::Factorize(input);

	//Abprüfen
	const std::string expected;
	EXPECT_EQ(expected, actual);
}
