#include "Tools.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <random>
#include <assert.h>

Grid SetGrid(size_t, size_t);

void PrintToConsole(const Grid& grid)
{
	for (auto row : grid)
	{
		for (auto col : row)
			std::cout << col << " ";
		std::cout << "\n";
	}
}

Cell GenerateRandomCell(const Cell& dead, const Cell& alive)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);
	int val = distrib(gen);
	if (val == 0)
		return dead;
	else
		return alive;
}

Grid GenerateRandomGrid(size_t height, size_t width)
{
	Grid grid = SetGrid(height, width);
	for (size_t i = 1; i < height - 1; i++)
	{
		for (size_t ii = 1; ii < width - 1; ii++)
			grid[i][ii] = (GenerateRandomCell(Cell('.'), Cell('*')));
	}
	return grid;
}

void RunGoFFor(size_t times, const Grid& grid)
{
	auto workingGrid(grid);
	for (size_t i = 0; i < times; i++)
	{
		system("CLS");
		PrintToConsole(workingGrid);
		//std::this_thread::sleep_for(std::chrono::milliseconds(50));
		workingGrid = TheNextGeneration(workingGrid);
		std::cout << "\n\n";
	}
}

void Test()
{
	//1
	auto prep = Grid{
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.'),Cell('.'),Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('*'),Cell('.'),Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('*'),Cell('*'),Cell('.'),Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.'),Cell('.'),Cell('.'),Cell('.')}
	};

	auto expected = Grid{
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.'),Cell('.'),Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('*'),Cell('*'),Cell('.'),Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('*'),Cell('*'),Cell('.'),Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.'),Cell('.'),Cell('.'),Cell('.')}
	};

	auto res = TheNextGeneration(prep);

	assert(res == expected);

	//2
	prep = Grid{
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('*'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('*'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('*'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')}
	};

	expected = Grid{
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('*'), Cell('*'), Cell('*'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')}
	};

	res = TheNextGeneration(prep);

	assert(res == expected);

	//3
	prep = Grid{
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('*'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('*'),Cell('.')},
		{Cell('.'),Cell('*'), Cell('*'), Cell('*'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')}
	};

	expected = Grid{
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('*'), Cell('.'), Cell('*'),Cell('.') },
		{Cell('.'),Cell('.'), Cell('*'), Cell('*'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('*'), Cell('.'),Cell('.')},
		{Cell('.'),Cell('.'), Cell('.'), Cell('.'),Cell('.')}
	};

	res = TheNextGeneration(prep);

	assert(res == expected);
}

Grid SetGrid(size_t height, size_t width)
{
	Grid grid{};
	for (size_t i = 0; i < height; i++)
	{
		grid.push_back(std::vector<Cell>());
		for (size_t ii = 0; ii < width; ii++)
			grid[i].push_back(Cell('.'));
	}
	return grid;
}