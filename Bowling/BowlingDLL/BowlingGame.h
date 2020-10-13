#pragma once
#include <string>
#include <vector>

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

		bool operator==(const Bowling::Frame& right) const
		{
			return this->pinsPerRoll == right.pinsPerRoll && this->score == right.score;
		}
	};

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