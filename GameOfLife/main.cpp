#include "GameOfLife.h"
#include "Tools.h"
#include <Windows.h>

int main()
{
	Test();

	auto testy = GenerateRandomGrid(50, 100);
	RunGoF(testy);
}