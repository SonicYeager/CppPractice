#include "Reversi.h"
#include <functional>
#include <algorithm>
#include <vector>

struct Pos
{
	Pos(int x, int y)
		: x(x), y(y) {}
	size_t x{};
	size_t y{};
};

using PossibleMoveAction = std::function<void(const Pos&)>;
using NeighbourAction = std::function<void(const Board&, char, const Pos&)>;

class CheckNeighbourFunctions 
{
public:
	CheckNeighbourFunctions(NeighbourAction onleft, NeighbourAction onright, NeighbourAction ontop, NeighbourAction onbottom)
		: onLeft(onleft), onRight(onright), onTop(ontop), onBottom(onbottom)
	{}

	void CheckEnemyNeighbours(const Board&, char, const std::vector<Pos>&);
private:
	NeighbourAction onLeft;
	NeighbourAction onRight;
	NeighbourAction onTop;
	NeighbourAction onBottom;
};

std::vector<Pos> GetPlayerPos(const Board&, char);
void CheckLineLeft(const Board&, char, const Pos&, PossibleMoveAction);
void CheckLineRight(const Board&, char, const Pos&, PossibleMoveAction);
void CheckLineTop(const Board&, char, const Pos&, PossibleMoveAction);
void CheckLineBottom(const Board&, char, const Pos&, PossibleMoveAction);
Board MarkPossibleMove(const Board&, const Pos&);

Board ShowNextMoves(const Board& board , char player)
{
	Board res(board);
	auto onMarkPossibleMove = [&res](const Pos& pos) { res = MarkPossibleMove(res, pos); };

	auto onCheckLineLeft = [onMarkPossibleMove](const Board& board, char player, Pos pos) { CheckLineLeft(board, player, pos, onMarkPossibleMove); };
	auto onCheckLineRight = [onMarkPossibleMove](const Board& board, char player, Pos pos) { CheckLineRight(board, player, pos, onMarkPossibleMove); };
	auto onCheckLineTop = [onMarkPossibleMove](const Board& board, char player, Pos pos) { CheckLineTop(board, player, pos, onMarkPossibleMove); };
	auto onCheckLineBottom = [onMarkPossibleMove](const Board& board, char player, Pos pos) { CheckLineBottom(board, player, pos, onMarkPossibleMove); };

	auto cnf = CheckNeighbourFunctions(onCheckLineLeft, onCheckLineRight, onCheckLineTop, onCheckLineBottom);

	std::vector<Pos> pos = GetPlayerPos(board, player);
	cnf.CheckEnemyNeighbours(board, player, pos);

	return res;
}

std::vector<Pos> GetPlayerPos(const Board& board, char player)
{
	std::vector<Pos> res{};
	for (size_t i = 0; i < board.size(); i++)
		for (size_t ii = 0; ii < board[i].size(); ii++)
			if (board[i][ii] == player)
				res.push_back(Pos(ii, i));
	return res;
}

void CheckNeighbourFunctions::CheckEnemyNeighbours(const Board& board, char player, const std::vector<Pos>& positions)
{
	char enemyPlayer = player == 'W' ? 'B' : 'W';
	for (const auto& pos :positions) {
		if (board[pos.y - 1][pos.x] == enemyPlayer)
			onTop(board, player, pos);
		if (pos.y + 1 < board.size() && board[pos.y + 1][pos.x] == enemyPlayer)
			onBottom(board, player, pos);
		if (board[pos.y][pos.x - 1] == enemyPlayer)
			onLeft(board, player, pos);
		if (pos.x + 1 < board[pos.y].size() && board[pos.y][pos.x + 1] == enemyPlayer)
			onRight(board, player, pos);
	}
}

void CheckLineLeft(const Board& board, char player, const Pos& pos, PossibleMoveAction onPossibleMove)
{
	char enemyPlayer = player == 'W' ? 'B' : 'W'; //enum or something like this
	signed int x = pos.x - 1;
	while(x >= 0 )
	{
		if (board[pos.y][x] != enemyPlayer) {
			if (board[pos.y][x + 1] == enemyPlayer && board[pos.y][x] == '.')
				onPossibleMove(Pos(x, pos.y));
			else
				break;
		}
		--x;
	}
}

void CheckLineRight(const Board& board, char player, const Pos& pos, PossibleMoveAction onPossibleMove)
{
	char enemyPlayer = player == 'W' ? 'B' : 'W'; 
	size_t x = pos.x + 1;
	while (x < board[pos.y].size())
	{
		if (board[pos.y][x] != enemyPlayer) {
			if (board[pos.y][x - 1] == enemyPlayer && board[pos.y][x] == '.')
				onPossibleMove(Pos(x, pos.y));
			else
				break;
		}
		++x;
	}
}

void CheckLineTop(const Board& board, char player, const Pos& pos, PossibleMoveAction onPossibleMove)
{
	char enemyPlayer = player == 'W' ? 'B' : 'W';
	signed int y = pos.y - 1;
	while (y >= 0)
	{
		if (board[y][pos.x] != enemyPlayer) {
			if (board[y + 1][pos.x] == enemyPlayer && board[y][pos.x] == '.')
				onPossibleMove(Pos(pos.x, y));
			else
				break;
		}
		--y;
	}
}

void CheckLineBottom(const Board& board, char player, const Pos& pos, PossibleMoveAction onPossibleMove)
{
	char enemyPlayer = player == 'W' ? 'B' : 'W';
	size_t y = pos.y + 1;
	while (y < board.size())
	{
		if (board[y][pos.x] != enemyPlayer) {
			if (board[y - 1][pos.x] == enemyPlayer && board[y][pos.x] == '.')
				onPossibleMove(Pos(pos.x, y));
			else
				break;
		}
		++y;
	}
}

Board MarkPossibleMove(const Board& board, const Pos& pos)
{
	Board res(board);
	res[pos.y][pos.x] = '0';
	return res;
}
