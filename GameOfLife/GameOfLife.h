#pragma once
#include <vector>

//enum class State
//{
//	DEAD = 0,
//	ALIVE = 1
//};
//using Cell = State;
//using DeadCell = State::DEAD;
//using AliveCell = State::ALIVE;

using Cell = char;
using Grid = std::vector<std::vector<Cell>>;

Grid TheNextGeneration(const Grid&); //Star Trek ^^