#include "Reversi.h"
#include <iostream>
#include "ReversiKI.h"
#include "ReversiKIPro.h"

namespace Reversi
{
	char row[] = { 'A', 'B', 'C' ,'D' ,'E' ,'F' ,'G' ,'H' };
	char column[] = { '1', '2', '3' ,'4' ,'5' ,'6' ,'7' ,'8' };

	void ShowBoard(const Board board) {

		char representative[] = { '.', 'O', 'X' };

		std::cout << "  | " ;
		for (int index = 0; index < 8; index++)
		{
			std::cout << column[index] << " | ";
		}
		std::cout << std::endl;

		for (int index_x = 0; index_x < 8; index_x++)
		{
			std::cout << row[index_x] << " | ";
			for (int index_y = 0; index_y < 8; index_y++)
			{
				std::cout << representative[board[index_x][index_y]] << " | ";
			}
			std::cout << std::endl;
		}

	}

	Player DetermineWinner(const Board board) {

		//count each players owned space, the player with the most is returned
		int counterWhite = 0;
		int counterBlack = 0;

		for (int index_y = 0; index_y < 8; index_y++)
		{
			for (int index_x = 0; index_x < 8; index_x++)
			{
				if (board[index_y][index_x] == 0)
				{
					continue;
				}
				else if (board[index_y][index_x] == 1)
				{
					counterWhite += 1;
				}
				else
				{
					counterBlack += 1;
				}
			}
		}

		if (counterBlack > counterWhite)
		{
			return Reversi::P_BLACK;
		}
		else if (counterBlack == counterWhite)
		{
			return Reversi::P_NONE;
		}
		else
			return Reversi::P_WHITE;;

	}

	bool IsMoveValid(const Player player, const Board board, int pos_x, int pos_y) {

		if (board[pos_y][pos_x] != P_NONE)
		{
			return false;
		}
		else
		{
			//set enemy value
			const Player enemyPlayer = Player(1 - player + 2);

			//check validity of move
			int coordinateModifier_x[] = { 0 , 1 , 1 ,1 ,0,-1,-1 ,-1 };
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
							return true;
						}
					}
				}
			}
			return false;
		}
	}

	bool MakeMove(const Player player, Board board, const int pos_x, const int pos_y) {

		if (IsMoveValid(player, board, pos_x, pos_y))
		{

			//Set the field which is desired and valid to player
			board[pos_y][pos_x] = player;

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

								board[newCoordinates_y ][newCoordinates_x] = player;

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
			//Only true if rly done something -> else report error
			return true;
		}
		else
			return false;

	}

	int NumberPossibleMoves(Player player, const Board board) {
		int countPosibleMoves = 0;
		for (int index_y = 0; index_y < 8; index_y++){
			for (int index_x = 0; index_x < 8; index_x++){
				if (IsMoveValid(player, board, index_x, index_y))
				{
					countPosibleMoves++;
				}
			}
		}

		return countPosibleMoves;
	}

	bool MakeHumanMove(Player player, Board board) {

		char userInput[10] = {};
		std::cin >> userInput;

		int pos_y = 0;
		switch (userInput[0]) {
		case 'A': pos_y = 0;
			break;
		case 'B': pos_y = 1;
			break;
		case 'C': pos_y = 2;
			break;
		case 'D': pos_y = 3;
			break;
		case 'E': pos_y = 4;
			break;
		case 'F': pos_y = 5;
			break;
		case 'G': pos_y = 6;
			break;
		case 'H': pos_y = 7;
			break;
		default: return false;
		}
		int pos_x = 0;
		switch (userInput[1]) {
		case '1': pos_x = 0;
			break;
		case '2': pos_x = 1;
			break;
		case '3': pos_x = 2;
			break;
		case '4': pos_x = 3;
			break;
		case '5': pos_x = 4;
			break;
		case '6': pos_x = 5;
			break;
		case '7': pos_x = 6;
			break;
		case '8': pos_x = 7;
			break;
		default: return false;
		}

		return MakeMove(player, board, pos_x, pos_y);
	}

	void RunGame(PlayerKind players[2]) {
		//test for possible moves and take actions
		//handle valid and invalid input and or possible moves
		//keep the battlefield up to date

		Player p = P_WHITE;
		Player p2 = P_BLACK;
		Player p0 = P_NONE;
		Board board = { {p0,p0,p0,p0,p0,p0,p0,p0},
								{p0,p0,p0,p0,p0,p0,p0,p0} ,
								{p0,p0,p0,p0,p0,p0,p0,p0} ,
								{p0,p0,p0,p2,p,p0,p0,p0} ,
								{p0,p0,p0,p,p2,p0,p0,p0} ,
								{p0,p0,p0,p0,p0,p0,p0,p0} ,
								{p0,p0,p0,p0,p0,p0,p0,p0} ,
								{p0,p0,p0,p0,p0,p0,p0,p0} };

		int noMoveTaken = 0;
		int index = 0;

		std::string playerKind[] = {"Human","KI", "KI Pro"};

		//The Loop for the game
		while (noMoveTaken < 2)
		{

			const PlayerKind actualPlayer = players[index];
			const PlayerKind player = actualPlayer;

			if (NumberPossibleMoves(index == 0 ? P_WHITE : P_BLACK, board) == 0) {
				index = 1 - index;
				noMoveTaken++;
				continue;
			}
			else {
				noMoveTaken = 0;
				system("cls");
				if (index == 1) {
					std::cout << " Player White [O] : " << playerKind[players[0]] << "\t | \t" << " > Player Black [X] : " << playerKind[players[1]] << std::endl;
				}
				else
					std::cout << " > Player White [O] : " << playerKind[players[0]] << "\t | \t" << " Player Black [X] : " << playerKind[players[1]] << std::endl;
				ShowBoard(board);
			}

			if (index == 1) {
				std::cout << "Player Black, its your turn!: You have " << NumberPossibleMoves(P_BLACK, board) << " possible moves!" << std::endl;
			}
			else
				std::cout << "Player White, its your turn!: You have " << NumberPossibleMoves(P_WHITE, board) << " possible moves!" << std::endl;

			if (player == KI_PRO)
				MakeComputerMovePro(index == 0 ? P_WHITE : P_BLACK , board);
			else if (player == KI)
				MakeComputerMove(index == 0 ? P_WHITE : P_BLACK, board);
			else {
				while (!MakeHumanMove(index == 0 ? P_WHITE : P_BLACK, board)) {
					std::cout << "Your input was nor possible neither correct! Please retry!: " << std::endl;
				}
			}
			index = 1 - index;
		}

		const Player player = DetermineWinner(board);
		if (player == P_WHITE)
			std::cout << "You have won player WHITE!";
		else
			std::cout << "You have won player BLACK!";
	}
}
