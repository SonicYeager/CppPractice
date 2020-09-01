#include "pch.h"
#include <iostream>
#include "Reversi.h"
#include <cstdlib>

Reversi::PlayerKind players[2] = {};

bool AdvancedMenue() {
	bool bCorrectInput = false;
	char usersChoice = 0;
	std::cout << "Welcome to Reversi!" << std::endl;

	for (int i = 0; i < 2; i++)
	{
		std::cout << "Choose Player " << i + 1 << ": " << "\n [0] Human" << "\n [1] KI" << "\n [2] KI Pro" << std::endl;
		std::cin >> usersChoice;

		while (!bCorrectInput) {
			switch (usersChoice)
			{
			case '0': players[i] = Reversi::HUMAN;
				bCorrectInput = true;
				break;
			case '1': players[i] = Reversi::KI;
				bCorrectInput = true;
				break;
			case '2': players[i] = Reversi::KI_PRO;
				bCorrectInput = true;
				break;
			default: std::cout << "Your input was not correct, please try again: " << std::endl;
				std::cin >> usersChoice;
				bCorrectInput = false;
			}
		}
		bCorrectInput = false;
		system("cls");
	}

	std::cout << "Who should start? : " << "\n [0] Player 1" << "\n [1] Player 2" << std::endl;
	std::cin >> usersChoice;

	if (usersChoice == 1)
	{
		Reversi::PlayerKind temp = players[0];
		players[0] = players[1];
		players[1] = temp;
	}

	return true;
}

int main()
{
	//system("cls"); // clearing the screen if desired
	char usersChoice = 0;
	bool bCorrectInput = false;

	std::cout << "Welcome to Reversi!" << std::endl;
	std::cout << "Choose your Mode:" << "\n [0] 2 Players" << "\n [1] 1 Player" << "\n [2] Fun Mode"<< "\n [3] Advanced Menu" << std::endl;
	std::cin >> usersChoice;

	while (!bCorrectInput) {
		switch (usersChoice)
		{
		case '0': players[0] = Reversi::HUMAN;
				players[1] = Reversi::HUMAN;
				bCorrectInput = true;
			break;
		case '1': players[0] = Reversi::KI;
				players[1] = Reversi::HUMAN;
				bCorrectInput = true;
			break;
		case '2': players[0] = Reversi::KI;
				players[1] = Reversi::KI;
				bCorrectInput = true;
			break;
		case '3': system("cls"); 
				bCorrectInput = AdvancedMenue();
			break;
		default: std::cout << "Your input was not correct, please try again: " << std::endl;
				 std::cin >> usersChoice;
				 bCorrectInput = false;
		}
	}

	system("cls");
	RunGame(players);
}
