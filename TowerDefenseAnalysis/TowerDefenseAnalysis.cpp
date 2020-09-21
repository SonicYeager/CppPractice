#include "TowerDefenseAnalysis.h"
#include "InternalTypes.h"
#include "InputTypes.h"
#include "Tools.h"
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>

auto CalcEuclidean2D(const Pos& p, const Pos& q) -> double
{
	return std::sqrt(std::pow(q.x - p.x, 2) + std::pow(q.y - p.y, 2));
}

std::pair<Path, ExtTurrets> ConvertData(const Battlefield&, const Turrets&);
int PlayMoves(const Path&, const ExtTurrets&, const IncomingWaves&);

AlienCount TowerDefenseAnalysis(const Battlefield& field, const Turrets& turrets, const IncomingWaves& waves)
{
	auto converted = ConvertData(field, turrets);
	AlienCount count = PlayMoves(std::move(converted.first), std::move(converted.second), waves);
	return count;
}

#pragma region ConvertData

Path GetPathFromField(const Battlefield&);
ExtTurrets GetExtTurrets(const Battlefield&, const Turrets&, const Path&);

std::pair<Path, ExtTurrets> ConvertData(const Battlefield& field, const Turrets& turr)
{
	auto path = GetPathFromField(field);
	auto extTurr = GetExtTurrets(field, turr, path); //mp here eventually
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
	return Pos(-1,-1);
}

Path GetPath(const Pos& pos, const Battlefield& field) 
{
	Path res{};
	res.push_back({pos, 0});
	Pos nextPos{pos};
	Pos lastPos(-1, -1);
	while(nextPos != Pos(-1,-1))
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
		if(nextPos != Pos(-1, -1))
			res.push_back({nextPos, 0});
	}
	return res;
}

#pragma endregion //DONE

#pragma region GetExtTurrets

Pos GetTurretPos(const Battlefield&, const TurretStats&);
std::vector<Pos> GetFieldsInRange(const Pos&, const Path&, const TurretStats&, ActionReturnsDouble);
ExtendedTurretStats AssembleExtendedTurretStats(const TurretStats&, const std::vector<Pos>&);

ExtTurrets GetExtTurrets(const Battlefield& field, const Turrets& turr, const Path& path)
{
	ExtTurrets res{};
	for(const auto& t : turr)
	{
		auto pos = GetTurretPos(field, t);
		auto inRangePos = GetFieldsInRange(pos, path, t, CalcEuclidean2D);
		auto extStats = AssembleExtendedTurretStats(t, inRangePos);
		res.push_back(extStats);
	}
	return res;
}

Pos GetTurretPos(const Battlefield& field, const TurretStats& stats) // eventually MP (least concern here)
{
	for(size_t y = 0; y < field.size(); ++y)
		for(size_t x = 0; x < field[y].size(); ++x)
			if(stats.name == field[y][x])
				return Pos(x,y);
	return Pos(-1,-1);
}

std::vector<Pos> GetFieldsInRange(const Pos& pos, const Path& path, const TurretStats& stats, ActionReturnsDouble euclideanCalc)
{
	std::vector<Pos> res{};

	for(const auto& pElem : path)
		if(euclideanCalc(pos, pElem.pos) <= stats.range)
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
Path MoveAliens(const Path&);
AlienCount GetSurvivedAlienCount(const Path&);

int PlayMoves(const Path& path, const ExtTurrets& extTurr, const IncomingWaves& waves)
{
	AlienCount res = 0;
	auto moved{path};
	for(auto wave : waves)
	{
		auto spawned = SpawnWave(moved, wave);
		auto shot = TowerShoot(spawned, extTurr);
		res += GetSurvivedAlienCount(shot);
		moved = MoveAliens(shot);
	}
	for(size_t i = 0; i < path.size(); i++)
	{
		auto shot = TowerShoot(moved, extTurr);
		res += GetSurvivedAlienCount(shot);
		moved = MoveAliens(shot);
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

Path TowerShoot(const Path& path, const ExtTurrets& extTurr) //make mp possible at least here
{
	Path res(path);
	ExtTurrets temp(extTurr);
	while(CanShoot(res, temp))
	{
		for(auto& extTurrStats : temp)
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
	for(const auto& turr : extTurr)
		if(turr.stats.shots > 0)
			for(const auto& pos : turr.positionsInRange)
			{
				auto findPos = [pos](const PathElement& elem) -> bool { return elem.pos == pos; };
				if(std::find_if(std::begin(path), std::end(path), findPos)->alienCount > 0)
					return true;
			}
	return false;
}

Pos GetMostAdvancedOnPath(const Path& path, const ExtendedTurretStats& extTStats) 
{
	auto reversed(extTStats.positionsInRange);
	std::reverse(std::begin(reversed), std::end(reversed));

	for(const auto& pos : reversed)
	{
		auto findPos = [pos](const PathElement& elem) -> bool { return elem.pos == pos; };
		auto it = std::find_if(std::begin(path), std::end(path), findPos);
		if(it != std::end(path) and it->alienCount > 0) // just for safety
			return pos;
	}

	return Pos(-1,-1);
}

std::pair<Path, ExtendedTurretStats> Shoot(const Path& path, const Pos& pos, const ExtendedTurretStats& extTStats)
{
	Path pRes(path);
	ExtendedTurretStats eRes(extTStats);

	if(pos != Pos(-1, -1))
	{
		if(eRes.stats.shots != 0)
		{
			auto findPos = [pos](const PathElement& elem) -> bool { return elem.pos == pos; };
			auto elem = std::find_if(std::begin(pRes), std::end(pRes), findPos);
			elem->alienCount = elem->alienCount - 1;
			eRes.stats.shots = eRes.stats.shots - 1;
		}
	}
	return std::make_pair(pRes, eRes);
}

#pragma endregion

Path MoveAliens(const Path& path/*, ActionAlienCount onSurvied*/)
{
	Path res(path);
	for(int i = res.size()-2; i >= 0; --i)
	{
			res[i + 1].alienCount = res[i].alienCount;
	}
	res.front().alienCount = 0;
	return res;
}

AlienCount GetSurvivedAlienCount(const Path& path)
{
	return path.back().alienCount;
}

#pragma endregion

#pragma region DISPLAY

void PlayMovesWithDisplay(const Path&, const ExtTurrets&, const IncomingWaves&, const Battlefield&);

void RunTD(const Battlefield& field, const Turrets& turr, const IncomingWaves& waves)
{
	auto converted = ConvertData(field, turr);
	const auto& path = converted.first;
	const auto& extTurr = converted.second;
	PlayMovesWithDisplay(path, extTurr, waves, field);
}

void PlayMovesWithDisplay(const Path& path, const ExtTurrets& extTurr, const IncomingWaves& waves, const Battlefield& field) //has not yet bin specialized
{
	auto moved{path};
	for(auto wave : waves)
	{
		auto spawned = SpawnWave(moved, wave);
		auto shot = TowerShoot(spawned, extTurr);
		moved = MoveAliens(shot);
		auto displayable = ConvertGameData(moved, field);
		PrintBattlefieldToConsole(displayable);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
	for(size_t i = 0; i < path.size(); i++) // replace evtl. by While loop with IsAlienOnField() to minimize loop iterations
	{
		auto shot = TowerShoot(moved, extTurr);
		moved = MoveAliens(shot);
		auto displayable = ConvertGameData(moved, field);
		PrintBattlefieldToConsole(displayable);
		std::this_thread::sleep_for(std::chrono::milliseconds(150));
	}
}

#pragma endregion