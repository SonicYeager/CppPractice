#include "Reversi.h"
#include <ctime>
#include "ReversiKIAdvanced.h"

namespace Reversi
{
	bool EnemyMoveIsImportantPos(const int importantPos_x[],const int importantPos_y[], const Board board, const Player enemyPlayer) {

		for (int col = 0; col < DIMENSION; col++)
		{
			for (int row = 0; row < DIMENSION; row++)
			{
				//TODO ProConcept 2 step
				if (IsMoveValid(enemyPlayer, board, col, row))
				{
					for (int x = 0; x < 16; x++)
					{
						for (int y = 0; y < 16; y++)
						{
							if (col == importantPos_x[x] && row == importantPos_y[y])
							{
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool CheckAndDoBestMove(const int importantPos_x[],const  int importantPos_y[], const Player player, Board board) {
		for (int col = 0; col < DIMENSION; col++)
		{
			for (int row = 0; row < DIMENSION; row++)
			{
				//TODO ProConcept 1 step
				for (int x = 0; x < 16; x++)
				{
					for (int y = 0; y < 16; y++)
					{
						if (col == importantPos_x[x] && row == importantPos_y[y])
						{
							if (IsMoveValid(player, board, col, row))
							{
								MakeMove(player, board, col, row);
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool ChackAndDoBestAltMove(const Player player, Board board, const int pos_x, const int pos_y, const int importantPos_x[], const  int importantPos_y[] ) {

		if (IsMoveValid(player, board, pos_x, pos_y))
		{

			//set enemy value
			const Player enemyPlayer = Player(1 - player + 2);

			//check validity of move
			int coordinateModifier_x[] = { 0, 1, 1 ,1 ,0 ,-1 ,-1 ,-1 };
			int coordinateModifier_y[] = { -1, -1 ,0 ,1 ,1 ,1 ,0 ,-1 };

			for (int toCheckFields = 0; toCheckFields < 8; toCheckFields++)
			{
				if ((pos_x + coordinateModifier_x[toCheckFields] < 0 || pos_x + coordinateModifier_x[toCheckFields] > 7) || (pos_y + coordinateModifier_y[toCheckFields] < 0 || pos_y + coordinateModifier_y[toCheckFields] > 7))
				{
					continue;
				}
				if (board[pos_y + coordinateModifier_y[toCheckFields]][pos_x + coordinateModifier_x[toCheckFields]] == enemyPlayer) {
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
						if (board[newPos_y][newPos_x] == P_NONE)
						{
							break;
						}
						if (board[newPos_y][newPos_x] == player)
						{
							int iterativeIndex_x = newPos_x - pos_x;
							int iterativeIndex_y = newPos_y - pos_y;
							int iterateTimes_x = iterativeIndex_x < 0 ? iterativeIndex_x * -1 : iterativeIndex_x;
							int iterateTimes_y = iterativeIndex_y < 0 ? iterativeIndex_y * -1 : iterativeIndex_y;
							int iterateTimes = iterateTimes_x < iterateTimes_y ? iterateTimes_y : iterateTimes_x;
							int newCoordinates_x = pos_x;
							int newCoordinates_y = pos_y;

							for (int toChangeFields = 0; toChangeFields < iterateTimes; toChangeFields++)
							{

								if (iterativeIndex_x != 0)
									newCoordinates_x += iterativeIndex_x > 0 ? +1 : -1;
								if (iterativeIndex_y != 0)
									newCoordinates_y += iterativeIndex_y > 0 ? +1 : -1;

								for (int x = 0; x < 16; x++)
								{
									for (int y = 0; y < 16; y++)
									{
										if (newCoordinates_x == importantPos_x[x] && newCoordinates_y == importantPos_y[y])
										{

											MakeMove(player, board, pos_x, pos_y);
											return true;

										}
									}
								}

								if (iterativeIndex_x != 0)
									iterativeIndex_x = iterativeIndex_x > 0 ? --iterativeIndex_x : ++iterativeIndex_x;
								if (iterativeIndex_y != 0)
									iterativeIndex_y = iterativeIndex_y > 0 ? --iterativeIndex_y : ++iterativeIndex_y;

							}
							break;

						}
					}
				}
			}
			return false;
		}
		else
			return false;

	}

	bool MakeComputerMovePro(Player player, Board board)
	{
		const Player ENEMY = Player(1 - player + 2);
		Board lookAhead = {};
		int importantPos_x[] = { 0,0,7,7,2,5,0,7,0,7,2,5,2,5,2,5 };
		int importantPos_y[] = { 0,7,0,7,0,0,2,2,5,5,7,7,2,2,5,5 };

		// copy board
		for(int ci = 0; ci < DIMENSION; ci++)
			for(int cj = 0; cj < DIMENSION; cj++)
				lookAhead[ci][cj] = board[ci][cj];

		int optimalPos_x = 0;
		int optimalPos_y = 0;
		bool bOptimalWasFound = false;

		//check for best move
		if (CheckAndDoBestMove(importantPos_x, importantPos_y, player, board))
			return true;

		//check for second best move
		for (int col = 0; col < DIMENSION; col++)
		{
			for (int row = 0; row < DIMENSION; row++)
			{
				if (ChackAndDoBestAltMove(player, board, col, row, importantPos_x, importantPos_y))
					return true;
			}
		}


		//check for alternative move
		for (int col = 0; col < DIMENSION; col++)
		{
			for (int row = 0; row < DIMENSION; row++)
			{
				if (IsMoveValid(player, lookAhead, col, row))
				{

					//TODO ProConcept 2 step
					MakeMove(player, lookAhead, col, row); //Pro rekursive ?
					if (EnemyMoveIsImportantPos(importantPos_x, importantPos_y, lookAhead, ENEMY))
						continue;
					else {
						optimalPos_x = col;
						optimalPos_y = row;
						bOptimalWasFound = true;
					}
					for (int x = 0; x < DIMENSION; x++)
					{
						for (int y = 0; y < DIMENSION; y++)
						{
							if (IsMoveValid(ENEMY, lookAhead, x, y))
							{
								if (ChackAndDoBestAltMove(ENEMY, lookAhead, x, y, importantPos_x, importantPos_y))
									break;
								else {
									optimalPos_x = col;
									optimalPos_y = row;
									bOptimalWasFound = true;
								}
							}
						}
					}
				}
				// reset field
				for (int ci = 0; ci < DIMENSION; ci++)
					for (int cj = 0; cj < DIMENSION; cj++)
						lookAhead[ci][cj] = board[ci][cj];
			}
		}


		if (bOptimalWasFound) {
			MakeMove(player, board, optimalPos_x, optimalPos_y);
		}
		else
			return MakeComputerMoveAdvanced(player, board); //take the best option if step 1 and 2 failed

		/*clock_t goal = clock() + 2 * CLOCKS_PER_SEC;
		while (goal > clock());*/
		return true;
	}
}
