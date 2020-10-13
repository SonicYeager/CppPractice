#include "BowlingGame.h"
namespace Bowling
{
	void Game::Roll(int kickedPins)
	{
		if (history.size() == 0)
		{
			history.push_back({ {kickedPins}, kickedPins });
		}
		else
		{
			if (history.size() != 10)
			{
				if (history[history.size() - 1].pinsPerRoll.size() < 2)
				{
					//assert max pins <= 10 (only a programmer can pass wrong val)
					history[history.size() - 1].pinsPerRoll.push_back(kickedPins);
					history[history.size() - 1].score += kickedPins;
				}
				else {} //create new pinsPerRoll
			}
			else {} //handle specialcase
		}
	}

	std::vector<Bowling::Frame> Game::History()
	{
		return history;
	}

	int Game::Score()
	{
		return history.size() == 0 ? 0 : history[history.size()-1].score;
	}
}