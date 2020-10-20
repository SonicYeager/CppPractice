#include "ConflictSolver.h"

namespace ConflictSolver
{
	void ConflictSolver::SetConflict(const Lines& conflict)
	{
		Table res{};
		Lines::const_iterator iter = conflict.begin();
		while (iter != conflict.end())
		{
			Lines leftConflict{};
			Lines leftContent{};
			Lines rightConflict{};
			Lines rightContent{};

			while (iter != conflict.end() && iter->find("<<<<<<<", 0) == std::string::npos)
			{
				leftContent.push_back(*iter);
				rightContent.push_back(*iter);
				++iter;
			}
			if (iter != conflict.end())
			{
				res.left.header = iter->substr(8, iter->size() - 8);
				++iter;
			}

			while (iter != conflict.end() && iter->find("=======", 0) == std::string::npos)
			{
				leftConflict.push_back(*iter);
				++iter;
			}
			if (iter != conflict.end()) 
				++iter;
			while (iter != conflict.end() && iter->find(">>>>>>>", 0) == std::string::npos)
			{
				rightConflict.push_back(*iter);
				++iter;
			}
			if (iter != conflict.end())
			{
				res.right.header = iter->substr(8, iter->size() - 8);
				++iter;
			}

			if (leftConflict.size() != rightConflict.size())
				if (leftConflict.size() < rightConflict.size())
					for (size_t i{}; i < rightConflict.size() - leftConflict.size(); ++i)
						leftConflict.push_back("");
				else if (leftConflict.size() > rightConflict.size())
					for (size_t i{}; i < leftConflict.size() - rightConflict.size(); ++i)
						rightConflict.push_back("");

			if(leftConflict.size() > 0)
				res.left.conflicts.push_back(leftConflict);
			if (leftContent.size() > 0)
				res.left.contents.push_back(leftContent);
			if (rightConflict.size() > 0)
				res.right.conflicts.push_back(rightConflict);
			if (rightContent.size() > 0)
				res.right.contents.push_back(rightContent);
		}				
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
			solved = conflictContent.left;
		}
		else if (solveTo == SOLVE::RIGHT)
		{
			solved = conflictContent.right;
		}
		else if (solveTo == SOLVE::BOTH)
		{
			for (size_t i{}; i < conflictContent.left.conflicts.size(); ++i)
				conflictContent.right.conflicts[i].insert(conflictContent.right.conflicts[i].end(), conflictContent.left.conflicts[i].begin(), conflictContent.left.conflicts[i].end());
			solved = conflictContent.right;
		}

		if (solved.conflicts.size() == solved.contents.size())
		{
			for (size_t i{}; i < solved.conflicts.size(); ++i)
			{
				for (auto line : solved.contents[i])
					res.push_back(line);
				for (auto line : solved.conflicts[i])
					res.push_back(line);
			}
		}
		else
		{
			if (solved.conflicts.size() < solved.contents.size())
			{
				int diff = solved.contents.size() - solved.conflicts.size();
				for (size_t i{}; i < solved.conflicts.size(); ++i)
				{
					for (auto line : solved.contents[i])
						res.push_back(line);
					for (auto line : solved.conflicts[i])
						if (line != "")
							res.push_back(line);
				}
				for (size_t i{ solved.conflicts.size()}; i < diff + solved.conflicts.size(); ++i)
				{
					for (auto line : solved.contents[i])
						res.push_back(line);
				}
			}
			else
			{
				int diff = solved.conflicts.size() - solved.contents.size();
				for (size_t i{}; i < solved.contents.size(); ++i)
				{
					for (auto line : solved.contents[i])
							res.push_back(line);
					for (auto line : solved.conflicts[i])
						if (line != "")
							res.push_back(line);
				}
				for (size_t i{ solved.contents.size() }; i < diff + solved.contents.size(); ++i)
				{
					for (auto line : solved.conflicts[i])
						if (line != "")
							res.push_back(line);
				}
			}

		}
		return res;
	}
}
