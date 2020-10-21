#pragma once
#include "UI.h"

namespace ConflictSolver
{
	class CONFLICTSOLVER_API Console : public UI
	{
	public:
		UserInput GetUserInput() override;
		void Display(const Table&) override;
	};
}