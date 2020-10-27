#include "Console.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

namespace NBACK
{
	TestConfig Console::GetUserInput() const
	{
		TestConfig res{};

		std::string name{};
		std::cout << "Please enter your name: ";
		std::cin >> name;

		std::string n{};
		std::cout << "Please enter n: ";
		std::cin >> n;

		std::string ms{};
		std::cout << "Please enter duration of stimuli (in ms): ";
		std::cin >> ms;

		std::string count{};
		std::cout << "Please enter count of stimuli: ";
		std::cin >> count;

		res.subjectname = name;
		res.n = std::stoi(n);
		res.stimuliIntervall = std::chrono::milliseconds(std::stoi(ms));
		res.countStimuli = std::stoi(count);

		return res;
	}

	void Console::DisplayStimuli(char c) const
	{
		::system("cls");
		std::cout << c;
	}

	void Console::GetReaction(const std::chrono::milliseconds& ms, Event onSpacebar, Event onNokey, Event onEscape) const
	{
		std::this_thread::sleep_for(ms);
		if (_kbhit() == true)
		{
			char c = _getch();
			if (c == VK_SPACE)
				onSpacebar();
			if (c == VK_ESCAPE)
				onEscape();
		}
		::system("cls");
		onNokey();
	}

	void Console::Countdown(int c) const
	{
		for (int i{c}; i > 0; --i)
		{
			::system("cls");
			std::cout << i;
		}
	}

	void Console::DisplayResults(const EvalData& edata) const
	{
		std::cout << "Percentage of Correct Reactions: " << edata.percentCorrect;
		//table format etc would be nice
	}
}
