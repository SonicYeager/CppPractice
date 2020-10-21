#pragma once
#include "InternalTypes.h"

namespace ConflictSolver
{
	class CONFLICTSOLVER_API UI
	{
	public:
		virtual UserInput GetUserInput() = 0;
		virtual void Display(const Table&) = 0;
	};
}
