#include "ConflictSolver.h"

namespace ConflictSolver
{

#pragma region SetConflict

	Contents ExtractContent(const Lines&);
	std::pair<Conflicts, Conflicts> ExtractConflicts(const Lines&);
	std::pair<std::string, std::string> ExtractHeads(const Lines&);
	Table Merge(const Contents&, const std::pair<Conflicts, Conflicts>&, const std::pair<std::string, std::string>&);
	std::vector<SOLVE> GetSolveLog(const Table&);

	void ConflictSolver::SetConflict(const Lines& conflict)
	{
		auto content = ExtractContent(conflict);
		auto conflicts = ExtractConflicts(conflict);
		auto heads = ExtractHeads(conflict);
		conflictContent = Merge(content, conflicts, heads);
		solveLog = GetSolveLog(conflictContent);
	}

	std::vector<SOLVE> GetSolveLog(const Table& conflicts)
	{
		std::vector<SOLVE> res;
		for (size_t i{}; i < conflicts.left.conflicts.size(); ++i)
		{
			res.push_back(SOLVE::UNSOLVED);
		}
		return res;
	}

	Contents ExtractContent(const Lines& lines)
	{
		Contents res{};
		Lines::const_iterator iter = lines.begin();
		int index{};
		while (iter != lines.end())
		{
			Lines contentBlock{};

			//ceck if another conflict is immediate
			if (iter != lines.end() && iter->find("<<<<<<<", 0) != std::string::npos)
				++index;

			//Retrieve Content until conflict
			while (iter != lines.end() && iter->find("<<<<<<<", 0) == std::string::npos)
			{
				contentBlock.push_back(*iter);
				++iter;
			}

			//surpass conflict
			while (iter != lines.end() && iter->find(">>>>>>>", 0) == std::string::npos)
				++iter;
			if (iter != lines.end())
				++iter;

			if (contentBlock.size() > 0)
			{
				res[index] = contentBlock;
				++index;
			}
		}
		return res;
	}

	std::pair<Lines, Lines> EqualizeWithEmptyStrings(const Lines&, const Lines&);

	std::pair<Conflicts, Conflicts> ExtractConflicts(const Lines& lines)
	{
		std::vector<Lines> resLeft{};
		std::vector<Lines> resRight{};

		Lines::const_iterator iter = lines.begin();
		while (iter != lines.end())
		{
			Lines conflictBlockLeft{};
			Lines conflictBlockRight{};
			while (iter != lines.end() && iter->find("<<<<<<<", 0) == std::string::npos)
				++iter;
			if (iter != lines.end())
				++iter;
			while (iter != lines.end() && iter->find("=======", 0) == std::string::npos)
			{
				conflictBlockLeft.push_back(*iter);
				++iter;
			}
			if (iter != lines.end())
				++iter;
			while (iter != lines.end() && iter->find(">>>>>>>", 0) == std::string::npos)
			{
				conflictBlockRight.push_back(*iter);
				++iter;
			}

			auto equalized = EqualizeWithEmptyStrings(conflictBlockLeft, conflictBlockRight);

			if (equalized.first.size() > 0)
				resLeft.push_back(equalized.first);
			if (equalized.second.size() > 0)
				resRight.push_back(equalized.second);
		}


		return std::make_pair(resLeft, resRight);
	}

	std::pair<Lines, Lines> EqualizeWithEmptyStrings(const Lines& left, const Lines& right)
	{
		Lines conflictBlockLeft{left};
		Lines conflictBlockRight{right};

		if (left.size() != right.size())
			if (left.size() < right.size())
				for (size_t i{}; i < right.size() - left.size(); ++i)
					conflictBlockLeft.push_back("");
			else if (left.size() > right.size())
				for (size_t i{}; i < left.size() - right.size(); ++i)
					conflictBlockRight.push_back("");

		return std::make_pair(conflictBlockLeft, conflictBlockRight);
	}

	std::pair<std::string, std::string> ExtractHeads(const Lines& lines)
	{
		std::string leftHead{""};
		std::string rightHead{""};

		Lines::const_iterator iter = lines.begin();
		while (iter != lines.end() && (leftHead == "" || rightHead == ""))
		{
			if (iter != lines.end() && leftHead == "" && iter->find("<<<<<<<", 0) != std::string::npos)
			{
				leftHead = iter->substr(8, iter->size() - 8);
				++iter;
			}
			if (iter != lines.end() && rightHead == "" && iter->find(">>>>>>>", 0) != std::string::npos)
			{
				rightHead = iter->substr(8, iter->size() - 8);
				++iter;
			}
			if (iter != lines.end())
				++iter;
		}

		return std::make_pair(leftHead, rightHead);;
	}

	Table Merge(const Contents& content, const std::pair<Conflicts, Conflicts>& conflicts, const std::pair<std::string, std::string>& heads)
	{
		Table res{};

		res.left.header = heads.first;
		res.right.header = heads.second;

		res.left.contents = content;
		res.right.contents = content;

		res.left.conflicts = conflicts.first;
		res.right.conflicts = conflicts.second;

		return res;
	}

#pragma endregion

	Table ConflictSolver::GetConflict() const
	{
		return conflictContent;
	}

#pragma region Solve

	std::vector<SOLVE> LogSolve(const std::vector<SOLVE>&, const SOLVE&, const int&);
	Lines SolveByLog(const std::vector<SOLVE>&, const Table&);

	Lines ConflictSolver::Solve(const SOLVE solveTo, int index)
	{
		solveLog = LogSolve(solveLog, solveTo, index);
		auto res = SolveByLog(solveLog, conflictContent);
		return res;
	}

	std::vector<SOLVE> LogSolve(const std::vector<SOLVE>& log, const SOLVE& solveTo, const int& index)
	{
		std::vector<SOLVE> res{log};
		res[index] = solveTo;
		return res;
	}

	Lines SolveByLog(const std::vector<SOLVE>& solveLog, const Table& conflicts)
	{
		Lines res{};
		for (size_t i{}; i < solveLog.size(); ++i)
		{
			if(conflicts.left.contents.size() > i && conflicts.left.contents.find(i) != conflicts.left.contents.end())
				for (auto line : conflicts.left.contents.at(i))
					res.push_back(line);
			if(solveLog[i] == SOLVE::LEFT)
			{
				for (auto line : conflicts.left.conflicts[i])
					if(line != "")
						res.push_back(line);
			}
			if (solveLog[i] == SOLVE::RIGHT)
			{
				for (auto line : conflicts.right.conflicts[i])
					if (line != "")
						res.push_back(line);
			}
			if (solveLog[i] == SOLVE::BOTH)
			{
				for (auto line : conflicts.left.conflicts[i])
					if (line != "")
						res.push_back(line);
				for (auto line : conflicts.right.conflicts[i])
					if (line != "")
						res.push_back(line);
			}
			if (solveLog[i] == SOLVE::UNSOLVED)
			{
				res.push_back("<<<<<<< " + conflicts.left.header);
				for (auto line : conflicts.left.conflicts[i])
					if (line != "")
						res.push_back(line);
				res.push_back("=======");
				for (auto line : conflicts.right.conflicts[i])
					if (line != "")
						res.push_back(line);
				res.push_back(">>>>>>> " + conflicts.right.header);
			}
		}
		auto it = --conflicts.left.contents.end();
		if(solveLog.size() <= it->first)
			for (auto line : conflicts.left.contents.at(it->first))
				res.push_back(line);
		return res;
	}

#pragma endregion
}
