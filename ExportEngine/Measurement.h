#pragma once
#include <chrono>

struct Measurement
{
	void Start();
	void Stop();
	int GetPassesTime();

private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
};