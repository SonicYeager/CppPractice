#include "ConflictSolver.h"

namespace ConflictSolver
{
	void ConflictSolver::SetConflict(const Lines& conflict)
	{
		Table res{ 2 };
		Lines::const_iterator iter = conflict.begin();
		int index{};
		while (iter != conflict.end())
		{
			while (iter != conflict.end() && iter->find("<<<<<<<", 0) == std::string::npos)
			{
				res[0].contents.emplace(index, *iter);
				res[1].contents.emplace(index, *iter);
				++iter;
			}
			if (iter != conflict.end())
			{
				res[0].header = iter->substr(8, iter->size() - 8);
				++iter;
			}
			while (iter != conflict.end() && iter->find("=======", 0) == std::string::npos)
			{
				res[0].conflicts.emplace(index, *iter);
				++iter;
			}
			if (iter != conflict.end()) 
				++iter;
			while (iter != conflict.end() && iter->find(">>>>>>>", 0) == std::string::npos)
			{
				res[1].conflicts.emplace(index, *iter);
				++iter;
			}
			if (iter != conflict.end())
			{
				res[1].header = iter->substr(8, iter->size() - 8);
				++iter;
			}
			++index;
		}
		res[0].lasKey = index;
		res[1].lasKey = index;
		conflictContent = res;
	}

	Table ConflictSolver::GetConflict() const
	{
		return conflictContent;
	}

	Lines ConflictSolver::Solve(const SOLVE solveTo)
	{
		Lines res{};
		Column solved{};
		if (solveTo == SOLVE::LEFT)
		{
			solved = conflictContent[0];
		}
		else if (solveTo == SOLVE::RIGHT)
		{
			solved = conflictContent[1];
		}
		else if (solveTo == SOLVE::BOTH)
		{
			for (auto& line : conflictContent[0].conflicts)
				conflictContent[1].conflicts.insert(line);
			solved = conflictContent[1];
		}
		res.push_back(solved.header);
		for (size_t i = 0; i < solved.lasKey; i++)
		{
			for (auto& line : solved.contents)
				if (line.first == i)
					res.push_back(line.second);
			for (auto& line : solved.conflicts)
				if (line.first == i)
					res.push_back(line.second);
		}
		return res;
	}
}
