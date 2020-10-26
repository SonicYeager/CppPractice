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

	bool Console::GetReaction(const std::chrono::milliseconds& ms, const char& c)
	{
		bool reaction = false;
		std::cout << c;
		auto current = std::chrono::system_clock::now();
		do {
			if (GetAsyncKeyState(VK_SPACE) & 0x80000000)
			{
				reaction = true;
				break;
			}
		} while (current.time_since_epoch().count() < ms.count());
		return reaction;
	}

	void Console::DisplayResults(const EvalData& edata)
	{
	}
}
