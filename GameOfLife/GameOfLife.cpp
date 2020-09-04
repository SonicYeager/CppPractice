#include "GameOfLife.h"
#include <functional>

struct Pos
{
	Pos(int x, int y) :
		x(x), y(y)
	{}

	signed int x;
	signed int y;
};

using Action = std::function<void()>;

int CountNeighbours(const Grid&, const Pos&);
Cell CurrentState(const Grid&, const Pos&);
int IsBorderZero(int, const Grid&, const Pos&);
class Rules
{
public:
	Rules(Action ondead, Action onalive) :
		onDead(ondead), onAlive(onalive)
	{}
	void NextState(int, const Cell&);
private:
	Action onDead;
	Action onAlive;
};
Cell SetDead();
Cell SetAlive();

Grid TheNextGeneration(const Grid& grid)
{
	Grid res(grid);

	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t ii = 0; ii < grid[i].size(); ii++)
		{
			Pos pos(ii, i);

			auto onSetDead = [&res, &pos]() {res[pos.y][pos.x] = SetDead(); };
			auto onSetAlive = [&res, &pos]() {res[pos.y][pos.x] = SetAlive(); };
			Rules r(onSetDead, onSetAlive);

			int count = CountNeighbours(grid, pos);
			Cell cell = CurrentState(grid, pos);
			count = IsBorderZero(count, grid, pos);
			r.NextState(count, cell);
		}
	}

	return res;
}

int CountNeighbours(const Grid& grid, const Pos& pos)
{
	int count = 0;
	if (pos.y - 1 >= 0 && grid[pos.y - 1][pos.x] == State::ALIVE)
		++count;
	if (pos.y + 1 < signed int(grid.size()) && grid[pos.y + 1][pos.x] == State::ALIVE)
		++count;
	if (pos.x - 1 >= 0 && grid[pos.y][pos.x - 1] == State::ALIVE)
		++count;
	if (pos.x + 1 < signed int(grid[pos.y].size()) && grid[pos.y][pos.x + 1] == State::ALIVE)
		++count;
	if ((pos.y - 1 >= 0 && pos.x - 1 >= 0) && grid[pos.y - 1][pos.x - 1] == State::ALIVE)
		++count;
	if ((pos.y + 1 < signed int(grid.size()) && pos.x + 1 < signed int(grid[pos.y + 1].size())) && grid[pos.y + 1][pos.x + 1] == State::ALIVE)
		++count;
	if ((pos.y + 1 < signed int(grid.size()) && pos.x - 1 >= 0) && grid[pos.y + 1][pos.x - 1] == State::ALIVE)
		++count;
	if ((pos.y - 1 >= 0 && pos.x + 1 < signed int(grid[pos.y].size())) && grid[pos.y - 1][pos.x + 1] == State::ALIVE)
		++count;
	return count;
}

Cell CurrentState(const Grid& grid, const Pos& pos)
{
	return grid[pos.y][pos.x];
}

int IsBorderZero(int count, const Grid& grid, const Pos& pos)
{
	if (pos.x == grid[pos.y].size() - 1 or pos.x == 0 or pos.y == grid.size() - 1 or pos.y == 0)
		count = 0;
	return count;
}

void Rules::NextState(int count, const Cell& cell)
{
	if (count < 2 && cell == State::ALIVE)
		onDead();
	if (count > 3 && cell == State::ALIVE)
		onDead();
	if (count == 3 || count == 2 && cell == State::ALIVE)
		onAlive();
	if (count == 3 && cell == State::ALIVE)
		onAlive();
}

Cell SetDead()
{
	return Cell::DEAD;
}

Cell SetAlive()
{
	return Cell::ALIVE;
}

std::ostream& operator<<(std::ostream& os, const Cell& dt)
{
	return os << char(dt);
}