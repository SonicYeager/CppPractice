#include "Console.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>

namespace NBACK
{
	TestData Console::GetUserInput()
	{
		TestData res{};

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

	REACTION Console::GetReaction(const std::chrono::milliseconds& ms, const char& c) //maybe be externally controlled (based on time)
	{
		REACTION reaction = REACTION::NOKEY;
		std::cout << c;
		auto current = std::chrono::system_clock::now();
		do {
			if (GetAsyncKeyState(VK_SPACE)) //maybe there is a better solution??
			{
				reaction = REACTION::SPACEBAR;
				break;
			}
			if (GetAsyncKeyState(VK_ESCAPE))
			{
				reaction = REACTION::ESC;
				break;
			}
		} while (current.time_since_epoch().count() < ms.count());
		return reaction;
	}

	bool Console::DisplayYesNoQuestion(const std::string& question)
	{
		std::cout << question << " [y/n]";
		std::string res{};
		std::cin >> res;
		return res == "y";
	}

	void Console::DisplayResults(const EvalData& edata)
	{
		std::cout << "Percentage of Correct Reactions: " << edata.percentCorrect;
		//table format etc would be nice
	}
}
