#pragma once
#include <vector>
#include <map>
#include <string>
#include <ostream>

namespace ConflictSolver
{
	using Lines = std::vector<std::string>;

	struct Column
	{
		std::string header{};
		std::vector<Lines> contents{};
		std::vector<Lines> conflicts{};

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

	std::ostream& operator<<(std::ostream& os, const Lines& lines)
	{
		for (auto line : lines)
			os << line << " ";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Column& col)
	{
		os << "{ ";
		os << col.header << " ";
		os << "{ ";
		for (auto line : col.contents)
			os << line << "; ";
		os << " }";
		os << "{ ";
		for (auto line : col.conflicts)
			os << line << "; ";
		os << " }";
		os << " }";
		return os;
	}

	std::ostream& operator<<(std::ostream& os, const Table& tabl)
	{
			os << tabl.left << tabl.right;
		return os;
	}

	bool operator==(const Table& left, const Table& right)
	{
		if (left.left == right.left && left.right == right.right)
			return true;
		else
			return false;
	}
}