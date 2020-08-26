#include "Tools.h"
#include <iostream>
#include <random>
//include here

double Random()
{
	//Generate random uniform number
	static std::mt19937 generator; //random
	std::uniform_real_distribution<> distribution(0.0, 1.0); //uniform number
	return distribution(generator);
}

Measurment::Measurment(int numSteps)
	: out("PerfMeasurements.txt", std::ios_base::app)
{
	out << "Start measurement with " << numSteps << " steps\n";
}

void Measurment::Start(std::string_view testName)
{
	name = testName;
	//start = ;
	start = std::chrono::high_resolution_clock::now();
}

void Measurment::Stop(double pi, int numThreads)
{
	//auto duration = ;
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count();
	out << name << ": computes PI=" << pi << " with " << numThreads << " Thread(s) in "
		<< duration
		<< " ms" << std::endl;
}
