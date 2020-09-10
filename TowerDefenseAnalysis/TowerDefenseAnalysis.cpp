#include "TowerDefenseAnalysis.h"
#include "InternalTypes.h"
#include "InputTypes.h"
#include <cmath>
#include <algorithm>
#include <functional>

std::pair<Path, ExtTurrets> ConvertData(const Battlefield&, const Turrets&);
int PlayMoves(const Path&, const ExtTurrets&, const IncomingWaves&);

AlienCount TowerDefenseAnalysis(const Battlefield& field, const Turrets& turrets, const IncomingWaves& waves)
{
	auto converted = ConvertData(field, turrets);
	AlienCount count = PlayMoves(converted.first, converted.second, waves);
	return count;
}

#pragma region ConvertData

Path GetPathFromField(const Battlefield&);
ExtTurrets GetExtTurrets(const Battlefield&, const Turrets&, const Path&);

std::pair<Path, ExtTurrets> ConvertData(const Battlefield& field, const Turrets& turr)
{
	auto path = GetPathFromField(field);
	auto extTurr = GetExtTurrets(field, turr, path);
	return std::make_pair(path, extTurr);
}

#pragma region GetPathFromField

Pos GetSpawn(const Battlefield&);
Path GetPath(const Pos&, const Battlefield&);

Path GetPathFromField(const Battlefield& field)
{
	auto spawn = GetSpawn(field);
	auto path = GetPath(spawn, field);
	return path;
}

Pos GetSpawn(const Battlefield& field)
{
	for(size_t y = 0; y < field.size(); ++y)
		for(size_t x = 0; x < field[y].size(); ++x)
			if(field[y][x] == '0')
				return Pos(x,y);
}

Path GetPath(const Pos& pos, const Battlefield& field) 
{
	Path res{};
	res.push_back({pos, 0});
	Pos nextPos{pos};
	Pos lastPos(-1, -1);
	while(nextPos.x != -1 && nextPos.y != -1)
	{
		if (nextPos.y - 1 >= 0 && field[nextPos.y - 1i64][nextPos.x] == '1' && lastPos.y != nextPos.y - 1i64)
		{
			lastPos = nextPos;
			nextPos = Pos(nextPos.x, nextPos.y - 1);
		}
		else if (nextPos.y + 1 < signed int(field.size()) && field[nextPos.y + 1i64][nextPos.x] == '1' && lastPos.y != nextPos.y + 1i64)
		{
			lastPos = nextPos;
			nextPos = Pos(nextPos.x, nextPos.y + 1);
		}
		else if (nextPos.x - 1 >= 0 && field[nextPos.y][nextPos.x - 1i64] == '1' && lastPos.x != nextPos.x - 1i64)
		{
			lastPos = nextPos;
			nextPos = Pos(nextPos.x - 1, nextPos.y);
		}
		else if (nextPos.x + 1 < signed int(field[nextPos.y].size()) && field[nextPos.y][nextPos.x + 1i64] == '1' && lastPos.x != nextPos.x + 1i64)
		{
			lastPos = nextPos;
			nextPos = Pos(nextPos.x + 1, nextPos.y);
		}
		else
			nextPos = Pos(-1, -1);
		if(nextPos.x != -1 && nextPos.y != -1)
			res.push_back({nextPos, 0});
	}
	return res;
}

#pragma endregion

#pragma region GetExtTurrets

Pos GetTurretPos(const Battlefield&, const TurretStats&);
std::vector<Pos> GetFieldsInRange(const Pos&, const Path&, const TurretStats&);
ExtendedTurretStats AssembleExtendedTurretStats(const TurretStats&, const std::vector<Pos>&);

ExtTurrets GetExtTurrets(const Battlefield& field, const Turrets& turr, const Path& path)
{
	ExtTurrets res{};
	for(const auto& t : turr)
	{
		auto pos = GetTurretPos(field, t);
		auto inRangePos = GetFieldsInRange(pos, path, t);
		auto extStats = AssembleExtendedTurretStats(t, inRangePos);
		res.push_back(extStats);
	}
	return res;
}

Pos GetTurretPos(const Battlefield& field, const TurretStats& stats)
{
	for(size_t y = 0; y < field.size(); ++y)
		for(size_t x = 0; x < field[y].size(); ++x)
			if(stats.name == field[y][x])
				return Pos(x,y);
}

std::vector<Pos> GetFieldsInRange(const Pos& pos, const Path& path, const TurretStats& stats) 
{
	std::vector<Pos> res{};
	auto euclidean = [](const Pos& p, const Pos& q) -> double {return std::sqrt(std::pow(q.x - p.x, 2) + std::pow(q.y - p.y, 2));};

	for(const auto& pElem : path)
		if(euclidean(pos, pElem.pos) <= stats.range)
			res.push_back(pElem.pos);
	return res;
}

ExtendedTurretStats AssembleExtendedTurretStats(const TurretStats& stats, const std::vector<Pos>& positions) 
{
	return {stats, positions};
}

#pragma endregion

#pragma endregion

#pragma region PlayMoves

Path SpawnWave(const Path&, const AlienCount&);
Path TowerShoot(const Path&, const ExtTurrets&);
Path MoveAliens(const Path&, std::function<void(const AlienCount&)>);
constexpr AlienCount GetSurvivedAlienCount(const AlienCount&);

int PlayMoves(const Path& path, const ExtTurrets& extTurr, const IncomingWaves& waves)
{
	AlienCount res = 0;
	auto OnSurvived = [&res](const AlienCount& c) { res += GetSurvivedAlienCount(c); };
	auto moved{path};
	for(auto wave : waves) //does not iterate through whole process!!!
	{
		auto spawned = SpawnWave(moved, wave);
		auto shot = TowerShoot(spawned, extTurr);
		moved = MoveAliens(shot, OnSurvived);
	}
	for(size_t i = 0; i < path.size(); i++)
	{
		auto shot = TowerShoot(moved, extTurr);
		moved = MoveAliens(shot, OnSurvived);
	}
	return res;
}

Path SpawnWave(const Path& path, const AlienCount& count)
{
	Path res{path};
	res[0].alienCount = count;
	return res;
}

#pragma region TowerShoot

bool CanShoot(const Path&, const ExtTurrets&);
Pos GetMostAdvancedOnPath(const Path&, const ExtendedTurretStats&);
std::pair<Path, ExtendedTurretStats> Shoot(const Path&, const Pos& pos, const ExtendedTurretStats& extTStats);

Path TowerShoot(const Path& path, const ExtTurrets& extTurr)
{
	Path res(path);
	ExtTurrets temp(extTurr);
	while(CanShoot(res, temp))
	{
		for(auto& extTurrStats : temp) //can be optimzed !!
		{
			auto mainTarget = GetMostAdvancedOnPath(res, extTurrStats);
			auto shot = Shoot(res, mainTarget, extTurrStats);
			res = shot.first;
			extTurrStats = shot.second;
		}
	}
	return res;
}

bool CanShoot(const Path& path, const ExtTurrets& extTurr) 
{
	
	auto findElemInPath = [](const Path& path, const Pos& pos)->PathElement
	{
		for(auto elem : path)
			if(elem.pos.x == pos.x && elem.pos.y == pos.y)
				return elem;
		return PathElement({-1, -1}, -1);
	};

	for(auto turr : extTurr)
		if(turr.stats.shots > 0)
			for(auto pos : turr.positionsInRange)
				if(findElemInPath(path, pos).alienCount > 0)
					return true;

	return false;
}

Pos GetMostAdvancedOnPath(const Path& path, const ExtendedTurretStats& extTStats) 
{
	auto findElemInPath = [](const Path& path, const Pos& pos) -> PathElement {
		for(auto elem : path)
			if(elem.pos.x == pos.x && elem.pos.y == pos.y)
				return elem;
		return PathElement({-1,-1}, -1);
	};

	auto reversed(extTStats.positionsInRange);
	std::reverse(std::begin(reversed), std::end(reversed));

	for(auto pos : reversed)
		if(findElemInPath(path, pos).alienCount > 0)
			return pos;

	return Pos(-1,-1);
}

std::pair<Path, ExtendedTurretStats> Shoot(const Path& path, const Pos& pos, const ExtendedTurretStats& extTStats)
{
	auto findElemInPath = [](Path& path, const Pos& pos) -> PathElement& {
		for(auto& elem : path)
			if(elem.pos.x == pos.x && elem.pos.y == pos.y)
				return elem;
	};

	Path pRes(path);
	ExtendedTurretStats eRes(extTStats);

	if(pos.x != -1 && pos.y != -1)
	{
		if(eRes.stats.shots != 0)
		{
			auto& elem = findElemInPath(pRes, pos);
			elem.alienCount = elem.alienCount - 1;
			eRes.stats.shots = eRes.stats.shots - 1;
		}
	}
	return std::make_pair(pRes, eRes);
}

#pragma endregion

Path MoveAliens(const Path& path, std::function<void(const AlienCount&)> onSurvied)
{
	Path res(path);
	for(int i = res.size()-1; i >= 0; --i)
	{
		if(i + 1i64 < res.size())
		{
			res[i + 1].alienCount = res[i].alienCount;
			res[i].alienCount = 0;
		}
		else if(res[i].alienCount > 0)
			onSurvied(res[i].alienCount);
	}
	return res;
}

constexpr AlienCount GetSurvivedAlienCount(const AlienCount& count)
{
	return count;
}

#pragma endregion