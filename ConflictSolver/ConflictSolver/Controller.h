#pragma once
#include "Logic.h"
#include "Ressource.h"
#include "UI.h"

namespace ConflictSolver 
{
	class CONFLICTSOLVER_API Controller
	{
	public:
		Controller(UI&, Logic&, Ressource&);
		void InputLoop();
	private:
		UI* ui;
		Logic* logic;
		Ressource* ress;
	};
}