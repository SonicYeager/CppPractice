#include "Measurement.h"

void Measurement::Start()
{
	start = std::chrono::high_resolution_clock::now();
}

void Measurement::Stop()
{
	stop = std::chrono::high_resolution_clock::now();
}

int Measurement::GetPassesTime() const
{
	auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	return dur.count();
}
