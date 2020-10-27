#include "Console.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <experimental/coroutine>
#include <sstream>

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

	void AsyncDisplayStimuli(char c, int count, const std::chrono::milliseconds& ms)
	{
		for (std::chrono::milliseconds i{ms}; i > 0ms; i -= 100ms)
		{
			std::this_thread::sleep_for(100ms);
			::system("cls");
			std::ostringstream ostr;
			ostr << c << "\n\n" << count << "\t" << i.count();
			std::cout << ostr.str();
		}
	}

	std::future<void> Console::DisplayStimuli(char c, int count, const std::chrono::milliseconds& ms)
	{
		co_await std::async(std::launch::async, AsyncDisplayStimuli, c, count, ms);
	}

	void Console::GetReaction(const std::chrono::milliseconds& ms, Event onSpacebar, Event onNokey, Event onEscape) const
	{
		std::this_thread::sleep_for(ms + 300ms);
		if (_kbhit() == true)
		{
			char c = _getch();
			if (c == VK_SPACE)
				onSpacebar();
			else if (c == VK_ESCAPE)
				onEscape();
		}
		else
			onNokey();
		::system("cls");
	}

	void Console::Countdown(int c) const
	{
		for (int i{c}; i > 0; --i)
		{
			::system("cls");
			std::cout << i;
			std::this_thread::sleep_for(1s);
		}
	}

	void Console::DisplayResults(const EvalData& edata) const
	{
		std::cout << "Percentage of Correct Reactions: " << edata.percentCorrect;
		//table format etc would be nice
	}
}
