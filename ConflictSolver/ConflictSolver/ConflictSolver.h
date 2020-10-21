#pragma once
#include "Logic.h"

namespace ConflictSolver
{

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
			os << line.second << "; ";
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

	class CONFLICTSOLVER_API ConflictSolver : public Logic
	{
	public:
		void SetConflict(const Lines& conflict) override;
		Table GetConflict() const override;
		Lines Solve(const SOLVE, int) override;

	private:
		Table conflictContent{};
		std::vector<SOLVE> solveLog{};
	};
}