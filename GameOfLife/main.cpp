#include "GameOfLife.h"
#include "Tools.h"
#include <Windows.h>

int main()
{
	Test();

	auto testy = GenerateRandomGrid(25, 25);
	RunGoFFor(100, testy);
}