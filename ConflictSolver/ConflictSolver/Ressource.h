#pragma once
#include "InternalTypes.h"

namespace ConflictSolver
{
	class CONFLICTSOLVER_API Ressource
	{
	public:
		virtual Lines ReadFromFile(const Path&) = 0;
		virtual void WriteToFile(const Path&, const Lines&) = 0;
	};
}