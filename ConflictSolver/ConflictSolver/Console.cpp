#include "Console.h"
#include <sstream>
#include <Windows.h>

namespace ConflictSolver 
{

	constexpr const size_t MinVal(const size_t&, const size_t&);

	UserInput Console::GetUserInput()
	{
		UserInput res{};
		std::string temp;
		std::getline(std::cin, temp);
		std::vector<std::string> splitted;
		size_t pos = temp.find(" ");
		size_t initialPos = 0;
		while (pos != std::string::npos) {
			splitted.push_back(temp.substr(initialPos, pos - initialPos));
			initialPos = pos + 1;

			pos = temp.find(" ", initialPos);
		}
		splitted.push_back(temp.substr(initialPos, MinVal(pos, temp.size()) - initialPos + 1));

		if (splitted.size() > 0 && splitted[0] != "quit")
		{
			res.index = std::stoi(splitted[0])-1;
			res.quit = false;
		}
		else if (splitted.size() > 0 && splitted[0] == "quit")
		{
			res.quit = true;
			return res;
		}
		if (splitted.size() > 1 && splitted[1] != "")
		{
			if (splitted[1] == "unsolved")
				res.solve = SOLVE::UNSOLVED;
			else if (splitted[1] == "left")
				res.solve = SOLVE::LEFT;
			else if (splitted[1] == "right")
				res.solve = SOLVE::RIGHT;
			else if (splitted[1] == "both")
				res.solve = SOLVE::BOTH;
		}

		return res;
	}

	constexpr const size_t MinVal(const size_t& left, const size_t& right)
	{
		return left < right ? left : right;
	}

	ConsoleLines AddMenu(const ConsoleLines&);
	ConsoleLines Format(const Table&);

	void Console::Display(const Table& table)
	{
		auto formatted = Format(table);
		formatted = AddMenu(formatted);
		std::system("cls");

		for (auto line : formatted)
		{
			if (line.first == true)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
			std::cout << line.second + "\n";
			if (line.first == true)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		}
	}

	ConsoleLines AddMenu(const ConsoleLines& lines)
	{
		ConsoleLines res{lines};
		res.push_back(std::make_pair(false , "\n\nTo solve a conflict type following separated by a whitespace:"));
		res.push_back(std::make_pair(false, "Type the Number of the Conflict (starting by 1 (from top to bottom)) e.g.:\t2"));
		res.push_back(std::make_pair(false, "Type the State of the Conflict (unsolved, left, right, both) e.g.:\tleft"));
		res.push_back(std::make_pair(false, "For leaving just Type the word >>quit<< e.g.:\tquit\n"));
		return res;
	}

#pragma region Format

	size_t GetMaxColumnLength(const Column&);
	ConsoleLines FormatLines(size_t, size_t, const Table&);

	ConsoleLines Format(const Table& table)
	{
		auto maxLeft = GetMaxColumnLength(table.left);
		auto maxRight = GetMaxColumnLength(table.right);
		auto res = FormatLines(maxLeft, maxRight, table);
		return res;
	}

	size_t GetMaxColumnLength(const Column& col)
	{
		size_t res{ col.header.size()};
		for (auto blocks : col.contents)
			for (auto line : blocks.second)
				if (line.size() > res)
					res = line.size();
		for (auto blocks : col.conflicts)
			for (auto line : blocks)
				if (line.size() > res)
					res = line.size();
		return res;
	}

	std::string FormatLine(size_t, size_t, const std::string&, const std::string&, const std::string&, const std::string&);

	ConsoleLines FormatLines(size_t leftMaxWidth, size_t rightMaxWidth, const Table& table)
	{
		ConsoleLines res{};
		res.push_back(std::make_pair(false, FormatLine(leftMaxWidth, rightMaxWidth, "", "", "-", "+")));
		res.push_back(std::make_pair(false, FormatLine(leftMaxWidth, rightMaxWidth, table.left.header, table.right.header, " ", "|")));
		res.push_back(std::make_pair(false, FormatLine(leftMaxWidth, rightMaxWidth, "", "", "-", "+")));
		for (size_t i{}; i < table.left.conflicts.size(); ++i)
		{
			if (table.left.contents.size() > i && table.left.contents.find(i) != table.left.contents.end())
				for (auto line : table.left.contents.at(i))
					res.push_back(std::make_pair(false, FormatLine(leftMaxWidth, rightMaxWidth, line, line, " ", "|")));

			for (size_t ii = 0; ii < table.left.conflicts[i].size(); ++ii)
			{
				res.push_back(std::make_pair(true, FormatLine(leftMaxWidth, rightMaxWidth, table.left.conflicts[i][ii], table.right.conflicts[i][ii], " ", "|")));
			}
			res.push_back(std::make_pair(false, FormatLine(leftMaxWidth, rightMaxWidth, "", "", "-", "+")));
		}
		auto it = --table.left.contents.end();
		if (table.left.conflicts.size() <= it->first)
			for (auto line : table.left.contents.at(it->first))
				res.push_back(std::make_pair(false, FormatLine(leftMaxWidth, rightMaxWidth, line, line, " ", "|")));
		res.push_back(std::make_pair(false, FormatLine(leftMaxWidth, rightMaxWidth, "", "", "-", "+")));
		return res;
	}

	std::string FormatLine(size_t leftMaxWidth, size_t rightMaxWidth, const std::string& left, const std::string& right, const std::string& spaceFill, const std::string& seperator)
	{
		std::string res{};
		std::string fillLeft{};
		std::string fillRight{};
		for (size_t i{}; i < leftMaxWidth - left.size(); ++i)
		{
			fillLeft += spaceFill;
		}
		for (size_t i{}; i < rightMaxWidth - right.size(); ++i)
		{
			fillRight += spaceFill;
		}
		res += seperator + left + fillLeft + seperator + right + fillRight + seperator;
		return res;
	}

#pragma endregion

}