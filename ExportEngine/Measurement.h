#pragma once
#include <chrono>

struct Measurement
{
	std::chrono::steady_clock::time_point Now();

private:
};