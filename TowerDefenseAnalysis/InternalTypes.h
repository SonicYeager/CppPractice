#pragma once
#include <vector>

//Pos for coordinates
struct Pos
{
	Pos(int x, int y) :
		x(x), y(y)
	{}
	int x;
	int y;
};

struct PathElement
{
	PathElement(const Pos& pos, int count) : 
		pos(pos), alienCount(count)
	{}
	Pos pos;
	int alienCount{};
};

//Path
using Path = std::vector<PathElement>;

//ExtendedTowerStruct (Keeps the fields in range already on hand ordered as well as their position -> so its simple to get the alien)
struct ExtendedTurretStats
{
	ExtendedTurretStats(const TurretStats& stats, const std::vector<Pos>& positions) : stats(stats), positionsInRange(positions)
	{}
	TurretStats stats;
	std::vector<Pos> positionsInRange;
};

using ExtTurrets = std::vector<ExtendedTurretStats>;