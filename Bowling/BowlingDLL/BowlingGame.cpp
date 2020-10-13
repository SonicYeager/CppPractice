#include "BowlingGame.h"
namespace Bowling
{

	std::vector<Bowling::Frame> AddPinsToHistory(const std::vector<Bowling::Frame>&,int);
	std::vector<Bowling::Frame> UpdateHistoryScore(const std::vector<Bowling::Frame>&);

	void Game::Roll(int kickedPins)
	{
		history = AddPinsToHistory(history, kickedPins);
		history = UpdateHistoryScore(history);
	}

	std::vector<Bowling::Frame> AddPinsToHistory(const std::vector<Bowling::Frame>& his, int kickedPins)
	{
		std::vector<Bowling::Frame> res{his};

		if (res.size() != 10)
		{
			if (res.size() > 0 && res[res.size() - 1].pinsPerRoll.size() < 2)
			{
				res[res.size() - 1].pinsPerRoll.push_back(kickedPins);
				res[res.size() - 1].score += kickedPins;
			}
			else
			{
				res.push_back({ {kickedPins}, kickedPins });
			}
		}
		else {} //handle specialcase

		return res;
	}

	std::vector<Bowling::Frame> UpdateHistoryScore(const std::vector<Bowling::Frame>& his)
	{
		std::vector<Bowling::Frame> res{ his };

		for (size_t i{}; i < res.size(); ++i)
		{
			if (res[i].pinsPerRoll.size() == 2 && res[i].score == 10) //spare
			{
				if (res.size() - 1 > i + 1)
				{
					res[i].score += res[i+1].pinsPerRoll[0];
				}
			}
			else if (res.size() - 1 > i + 1 && res[i].pinsPerRoll[0] == 10 && res[i+ 1].pinsPerRoll[0] < 10) //strike
			{
				if (res[i+1].pinsPerRoll.size() == 2)
				{
					res[i].score = res[i+1].pinsPerRoll[0] + res[i+1].pinsPerRoll[1];
				}
				else
				{
					res[i].score = res[i + 1].pinsPerRoll[0];
				}
			}
			else if (res.size() - 1 > i + 1 && res[i].pinsPerRoll[0] == 10 && res[i + 1].pinsPerRoll[0] == 10)
			{
				if (res.size() - 1 > i + 2)
				{
					res[i].score = res[i + 1].pinsPerRoll[0] + res[i + 2].pinsPerRoll[0];
				}
				else
				{
					res[i].score = res[i + 1].pinsPerRoll[0];
				}
			}
		}

		return res;
	}

	std::vector<Bowling::Frame> Game::History()
	{
		return history;
	}

	int Game::Score()
	{
		int res{};
		for (auto entry : history)
		{
			res += entry.score;
		}
		return res;
	}
}