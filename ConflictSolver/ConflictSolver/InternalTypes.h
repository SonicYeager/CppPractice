#pragma once
#include <vector>
#include <map>
#include <string>

namespace ConflictSolver
{
	using Lines = std::vector<std::string>;

	struct Column
	{
		std::string header{};
		std::multimap<int, std::string> contents{};
		std::multimap<int, std::string> conflicts{};
		int lasKey{};

		bool operator==(const Column& other) const
		{
			if (header != other.header)
				return false;
			if (contents != other.contents)
				return false;
			if (conflicts != other.conflicts)
				return false;
			if (lasKey != other.lasKey)
				return false;
			return true;
		}
	};

	using Table = std::vector<Column>;

	bool operator==(const Table& left, const Table& right)
	{
		if (left.size() != right.size())
			return false;
		for (size_t i = 0; i < left.size(); ++i)
		{
			if (left[i] == right[i])
				continue;
			else
				return false;
		}
		return true;
	}
}