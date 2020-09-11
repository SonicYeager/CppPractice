#pragma once
#include <vector>
#include <iostream>

enum struct STATE : char
{
	DEAD = '.',
	ALIVE = '*'
};
using Cell = STATE;

std::ostream& operator<<(std::ostream& os, const Cell& dt);

using Grid = std::vector<std::vector<Cell>>;

Grid TheNextGeneration(const Grid&); //Star Trek ^^