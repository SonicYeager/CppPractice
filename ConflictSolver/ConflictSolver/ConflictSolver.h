#pragma once
#include "InternalTypes.h"

#ifdef CONFLICTSOLVER_EXPORTS
#define CONFLICTSOLVER_API __declspec(dllexport)
#else
#define CONFLICTSOLVER_API __declspec(dllimport)
#endif

namespace ConflictSolver
{

	enum class CONFLICTSOLVER_API SOLVE
	{
		RIGHT,
		LEFT,
		BOTH,
		UNSOLVED
	};

	class CONFLICTSOLVER_API ConflictSolver
	{
	public:
		void SetConflict(const Lines& conflict);
		Table GetConflict() const;
		Lines Solve(const SOLVE, int);

	private:
		Table conflictContent{};
		std::vector<SOLVE> solveLog{};
	};
}