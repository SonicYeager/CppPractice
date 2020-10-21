#pragma once
#include "InternalTypes.h"

namespace ConflictSolver
{
	class CONFLICTSOLVER_API Logic
	{
	public:
		virtual void SetConflict(const Lines& conflict) = 0;
		virtual Table GetConflict() const = 0;
		virtual Lines Solve(const SOLVE, int) = 0;
	};
}