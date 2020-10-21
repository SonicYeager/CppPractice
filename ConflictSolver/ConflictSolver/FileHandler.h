#pragma once
#include "InternalTypes.h"
#include "Ressource.h"

namespace ConflictSolver
{
	class CONFLICTSOLVER_API FileHandler : public Ressource
	{
	public:
		Lines ReadFromFile(const Path& filename) override;
		void WriteToFile(const Path& filename, const Lines& table) override;
	};
}