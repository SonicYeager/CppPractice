#include "Controller.h"
#include "Console.h"
#include "FileHandler.h"
#include "NBackLogic.h"
#include "TestGen.h"

int main()
{
	NBACK::Console cnsl{};
	NBACK::FileHandler fh{};
	NBACK::NBackLogic nbackl{};
	NBACK::TestGen tgen{};
	NBACK::Controller cntr{ nbackl, fh, tgen, cnsl };
	cntr.Run();
}