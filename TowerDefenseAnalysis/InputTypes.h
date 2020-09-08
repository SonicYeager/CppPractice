#pragma once
#include <vector>
#include <string>

using Battlefield = std::vector<std::string>;
struct TurretStats
{
	char name;
	int range;
	int shots;
};
using Turrets = std::vector<TurretStats>;
using AlienCount = int;
using IncomingWaves = std::vector<AlienCount>;
