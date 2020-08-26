#include "Reversi.h"
#include <ctime>

namespace Reversi
{
	bool MakeComputerMove(Player player, Board board)
	{
		const Player ENEMY = Player(1 - player + 2);
		Board lookAhead = {};
		// copy board
		for(int ci = 0; ci < DIMENSION; ci++)
			for(int cj = 0; cj < DIMENSION; cj++)
				lookAhead[ci][cj] = board[ci][cj];

		int min_x = 0;
		int min_y = 0;
		int min = 64;
		for(int col = 0; col < DIMENSION; col++)
		{
			for(int row = 0; row < DIMENSION; row++)
			{
				if(IsMoveValid(player, lookAhead, col, row))
				{
					MakeMove(player, lookAhead, col, row);
					const int numMoves = NumberPossibleMoves(ENEMY, lookAhead);
					if(numMoves < min)
					{
						min = numMoves;
						min_x = col;
						min_y = row;
					}
				}
				// reset field
				//lookAhead[row][col] = board[row][col]; <- wrong solution!!!
				for (int ci = 0; ci < DIMENSION; ci++)
					for (int cj = 0; cj < DIMENSION; cj++)
						lookAhead[ci][cj] = board[ci][cj];
			}
		}
		MakeMove(player, board, min_x, min_y);
		//// wait a little bit
	 //   clock_t goal = clock() + 2 * CLOCKS_PER_SEC;
		//while(goal > clock());
		return true;
	}
}
