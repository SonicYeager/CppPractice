#include "Console.h"

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

	void Console::DisplayStimuli(char stimuli, int count, const std::chrono::milliseconds& ms)
	{
		::system("cls");
		std::ostringstream ostr;
		ostr << stimuli << "\n\n" << count << "\t" << ms.count() << " ms";
		std::cout << ostr.str();
	}

	void Console::GetReaction(Event onSpacebar, Event onNokey, Event onEscape) const
	{
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
