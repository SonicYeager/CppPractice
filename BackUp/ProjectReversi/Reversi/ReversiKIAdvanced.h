#include "Reversi.h"
#include <ctime>

namespace Reversi
{


	int NumberPossibleCountChips(const Player player, const Player enemyPlayer, const Board board, const int pos_x, const int pos_y) {

		int validPos_x = 0;
		int validPos_y = 0;

		int possibleChipsCounter = 0;

		//check validity of move
		int coordinateModifier_x[] = { 0, 1, 1 ,1 ,0 ,-1 ,-1 ,-1 };
		int coordinateModifier_y[] = { -1, -1 ,0 ,1 ,1 ,1 ,0 ,-1 };

		for (int toCheckFields = 0; toCheckFields < 8; toCheckFields++)
		{
			if ((pos_x + coordinateModifier_x[toCheckFields] < 0 || pos_x + coordinateModifier_x[toCheckFields] > 7) || (pos_y + coordinateModifier_y[toCheckFields] < 0 || pos_y + coordinateModifier_y[toCheckFields] > 7))
			{
				continue;
			}
			if (board[pos_y + coordinateModifier_y[toCheckFields]][pos_x + coordinateModifier_x[toCheckFields]] == player) {
				int newPos_x = pos_x;
				int newPos_y = pos_y;
				for (int index = 0; index < 8; index++)
				{
					newPos_x += coordinateModifier_x[toCheckFields];
					newPos_y += coordinateModifier_y[toCheckFields];
					if ((newPos_x < 0 || newPos_x > 7) || (newPos_y < 0 || newPos_y > 7))
					{
						break;
					}
					if (board[newPos_y][newPos_x] == enemyPlayer)
					{

						validPos_x = newPos_x - pos_x < 0 ? (newPos_x - pos_x) * -1 : newPos_x - pos_x;
						validPos_y = newPos_y - pos_y < 0 ? (newPos_y - pos_y) * -1 : newPos_y - pos_y;

						possibleChipsCounter += (validPos_x != 0 ? validPos_x : validPos_y) - 1;

					}
				}
			}
		}

		return possibleChipsCounter;
	}

	bool MakeComputerMoveAdvanced(Player player, Board board)
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
		int minChips = 16;
		for(int col = 0; col < DIMENSION; col++)
		{
			for(int row = 0; row < DIMENSION; row++)
			{
				if(IsMoveValid(player, lookAhead, col, row))
				{
					MakeMove(player, lookAhead, col, row);
					const int numMoves = NumberPossibleMoves(ENEMY, lookAhead);
					const int numChips = NumberPossibleCountChips(ENEMY, player, board, col, row);
					if(numMoves < min || numChips < minChips)
					{
						min = numMoves;
						minChips = numChips;
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

		//clock_t goal = clock() + 2 * CLOCKS_PER_SEC;
		//while (goal > clock());
		return true;
	}
}
