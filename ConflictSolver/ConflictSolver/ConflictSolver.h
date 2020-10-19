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
		BOTH
	};

	class CONFLICTSOLVER_API ConflictSolver
	{
	public:
		void SetConflict(const Lines& conflict);
		Table GetConflict() const;
		Lines Solve(const SOLVE);

	private:
		Table conflictContent{};
	};
}