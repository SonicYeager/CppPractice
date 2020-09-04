#pragma once
#include <vector>
#include <iostream>

enum struct State : char
{
	DEAD = '.',
	ALIVE = '*'
};
using Cell = State;

std::ostream& operator<<(std::ostream& os, const Cell& dt);

using Grid = std::vector<std::vector<Cell>>;

Grid TheNextGeneration(const Grid&); //Star Trek ^^