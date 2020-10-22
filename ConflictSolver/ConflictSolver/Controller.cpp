#include "Controller.h"

namespace ConflictSolver
{
	Controller::Controller(UI& ui, Logic& logic, Ressource& ress) : ui(&ui), logic(&logic), ress(&ress)
	{}

	void Controller::InputLoop()
	{
		auto fileContent = ress->ReadFromFile(INTERNALPATHREAD);
		logic->SetConflict(fileContent);
		auto parsed = logic->GetConflict();
		ui->Display(parsed);
		UserInput input = ui->GetUserInput();
		Lines lastSolve{};
		while (!input.quit)
		{
			lastSolve = logic->Solve(input.solve, input.index);
			parsed = logic->GetModifiedConflict();
			ui->Display(parsed);
			input = ui->GetUserInput();
		}
		ress->WriteToFile(INTERNALPATHWRITE, lastSolve);
	}

}