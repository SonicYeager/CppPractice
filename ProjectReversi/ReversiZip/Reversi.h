#pragma once

namespace Reversi
{
	// constants for better readability
	const int DIMENSION = 8;
	enum Player
	{
		P_NONE = 0
		, P_WHITE
		, P_BLACK
	};
	enum PlayerKind
	{
		HUMAN = 0
		, KI
	};
	
	// alias simplify usage
	using Board = Player[DIMENSION][DIMENSION];

	// add function declarations below
	void RunGame(PlayerKind players[2]);
	void ShowBoard(const Board board);
	Player DetermineWinner(const Board board);
}
