#include "Measurement.h"

std::chrono::steady_clock::time_point Measurement::Now()
{
	return std::chrono::high_resolution_clock::now();
}
