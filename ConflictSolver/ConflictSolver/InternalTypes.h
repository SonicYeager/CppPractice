#pragma once
#include <vector>
#include <map>
#include <string>
#include <filesystem>
#include <functional>
#include <iostream>

#ifdef CONFLICTSOLVER_EXPORTS
#define CONFLICTSOLVER_API __declspec(dllexport)
#else
#define CONFLICTSOLVER_API __declspec(dllimport)
#endif

namespace ConflictSolver
{
	using Lines = std::vector<std::string>;
	using ConsoleLines = std::vector<std::pair<bool, std::string>>;
	using Contents = std::map<size_t, Lines>;
	using Conflicts = std::vector<Lines>;
	using Path = std::filesystem::path;

	const Path INTERNALPATHREAD{"conflict.txt"};
	const Path INTERNALPATHWRITE{"resolved.txt"};

	enum class SOLVE
	{
		RIGHT,
		LEFT,
		BOTH,
		UNSOLVED
	};

	struct UserInput 
	{
		int index{};
		SOLVE solve{};
		bool quit = false;
	};

	struct Column
	{
		std::string header{};
		Contents contents{};
		Conflicts conflicts{};

		bool operator==(const Column& other) const
		{
			if (header != other.header)
				return false;
			if (contents != other.contents)
				return false;
			if (conflicts != other.conflicts)
				return false;
			return true;
		}
	};

	struct Table
	{
		Column left{};
		Column right{};
	};
}