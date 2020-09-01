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
		, KI_PRO
	};
	
	// alias simplify usage
	using Board = Player[DIMENSION][DIMENSION];

	// add function declarations below // all functions added
	void ShowBoard(const Board board);
	Player DetermineWinner(const Board board);
	bool IsMoveValid(Player player, const Board board, int pos_x, int pos_y);
	bool MakeMove(Player player, Board board, int pos_x, int pos_y);
	int NumberPossibleMoves(Player player, const Board board);
	bool MakeHumanMove(Player player, Board board);
	void RunGame(PlayerKind players[2]);
	
	
}
