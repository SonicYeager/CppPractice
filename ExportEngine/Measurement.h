#pragma once
#include "ExportData.h"

struct Measurement
{
	auto Start() -> std::chrono::steady_clock::time_point;
	auto Stop() -> std::chrono::steady_clock::time_point;

private:
	std::chrono::steady_clock::time_point start{};
	std::chrono::steady_clock::time_point stop{};
};