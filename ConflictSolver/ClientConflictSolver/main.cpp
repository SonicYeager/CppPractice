#include "Controller.h"
#include "Console.h"
#include "ConflictSolver.h"
#include "FileHandler.h"

int main()
{
    ConflictSolver::ConflictSolver cn{};
    ConflictSolver::Console cnsl{};
    ConflictSolver::FileHandler fh{};
    ConflictSolver::Controller ctrl{cnsl, cn, fh};
    ctrl.InputLoop();
}
