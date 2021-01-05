#include "Measurement.h"

void Measurement::Start()
{
	start =  std::chrono::high_resolution_clock::now();
}

void Measurement::Stop()
{
	stop = std::chrono::high_resolution_clock::now();
}

auto Measurement::GetElapsedTime() -> long long
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}
