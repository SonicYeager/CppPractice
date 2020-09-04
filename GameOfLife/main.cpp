#include "GameOfLife.h"
#include "Tools.h"
#include <Windows.h>

int main()
{
	Test();

	auto testy = GenerateRandomGrid(100, 100);
	RunGoFFor(100, testy);
}