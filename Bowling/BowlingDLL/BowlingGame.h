#pragma once
#include <string>
#include <vector>
#include <iostream>

#ifdef BOWLINGDLL_EXPORTS
#define BOWLING_API __declspec(dllexport)
#else
#define BOWLING_API __declspec(dllimport)
#endif

namespace Bowling
{


	struct BOWLING_API Frame
	{
		std::vector<int> pinsPerRoll{};
		int score{};
	};

	bool operator==(const Bowling::Frame& left, const Bowling::Frame& right)
	{
		return left.pinsPerRoll == right.pinsPerRoll && left.score == right.score;
	}

	std::ostream& operator<<(std::ostream& os, const Frame& fr)
	{
		os << "{{";
		for (auto entry : fr.pinsPerRoll)
			os << " " << entry;
		os << " } ";
		return os << fr.score << " }";
	}

	class BOWLING_API Game
	{
	public:
		void Roll(int);							//Spereate Tests
		std::vector<Bowling::Frame> History();	//Seperate Tests
		int Score();							//Seperate Tests
	protected:
		std::vector<Bowling::Frame> history{};
	};
}