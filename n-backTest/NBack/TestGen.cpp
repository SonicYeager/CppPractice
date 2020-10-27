#include "TestGen.h"
#include <random>

namespace NBACK
{
	int GenerateRandomInt(const int& min, const int& max)
	{
		std::random_device rd;
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<int> distrib(min, max);
		return distrib(gen);
	}

	std::vector<char> GenerateRandomMask(const int& count, const int& n)
	{
		std::vector<char> res{ '0' };
		res.reserve(count - 1);
		for (size_t i{}; i < count - 1; ++i)
		{
			res.push_back('0');
		}
		for (size_t i{}; i < count; ++i)
		{
			if (res[i] == '0' && GenerateRandomInt(0, 100) < 50)
			{
				res[i] = GenerateRandomInt(65, 90);
				if (res.size() > i + 3)
					res[i + 3] = res[i];
			}
			//three or more in a row is a additional feature
		}
		return res;
	}

	std::vector<char> FillGapsWithRandom(const std::vector<char>& mask)
	{
		std::vector<char> res{ mask };

		for (auto& ch : res)
			if (ch == '0')
				ch = GenerateRandomInt(65, 90);
		return res;
	}

	bool HasAtLeastThreeNBack(const std::vector<char>& mask)
	{
		int actual{};
		int atLeast{ 3 };
		for (int i{ 3 }; i < mask.size(); ++i)
		{
			if (mask[i] != '0')
			{
				auto res = mask[i - 3] == mask[i];
				if (res == true)
					++actual;
			}
		}
		return actual >= atLeast;
	}

	std::vector<char> TestGen::GenNBackChars(const int& count, const int& n)
	{
		auto mask = GenerateRandomMask(count, n);
		while(!HasAtLeastThreeNBack(mask))
			mask = GenerateRandomMask(count, n);
		auto res = FillGapsWithRandom(mask);
		return res;
	}
}