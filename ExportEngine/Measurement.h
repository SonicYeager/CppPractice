#pragma once
#include "ExportData.h"

struct Measurement
{
	void Start();
	void Stop();
	auto GetElapsedTime() -> long long;

private:
	std::chrono::steady_clock::time_point start{};
	std::chrono::steady_clock::time_point stop{};
};