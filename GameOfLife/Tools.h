#pragma once
#include "GameOfLife.h"

void PrintToConsole(const Grid&);
Grid GenerateRandomGrid(size_t, size_t);
void RunGoFFor(size_t, const Grid&);
void RunGoF(const Grid&);
void Test();