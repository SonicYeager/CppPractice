#pragma once
#include <chrono>

struct Measurement
{
	void Start();
	void Stop();
	int GetPassesTime() const;

private:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point stop;
};