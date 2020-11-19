#include "Measurement.h"

auto Measurement::Start() -> std::chrono::steady_clock::time_point
{
	return std::chrono::high_resolution_clock::now();
}

inline auto Measurement::Stop() -> std::chrono::steady_clock::time_point
{
	return std::chrono::high_resolution_clock::now();
}
