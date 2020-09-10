#pragma once
#include <vector>
#include <functional>

//Pos for coordinates
struct Pos
{
	Pos(int x, int y) :
		x(x), y(y)
	{}
	int x;
	int y;

	constexpr bool operator==(const Pos& pos) const
	{
		return x == pos.x && y == pos.y;
	}

	constexpr bool operator!=(const Pos& pos) const
	{
		return x != pos.x && y != pos.y;
	}
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

	bool operator==(const ExtendedTurretStats& otherStats) const
	{
		return otherStats.positionsInRange == positionsInRange &&
			otherStats.stats.name == stats.name &&
			otherStats.stats.shots == stats.shots &&
			otherStats.stats.range == stats.range;
	}
};

using ExtTurrets = std::vector<ExtendedTurretStats>;
using ActionAlienCount = std::function<void(const AlienCount&)>;
using ActionReturnsDouble = std::function<double(const Pos&, const Pos&)>;