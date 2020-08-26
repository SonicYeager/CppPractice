#pragma once
#include <string>
#include <fstream>
#include <chrono>
//include here

// Returns random number between [0,1]
double Random();

class Measurment
{
public:
	explicit Measurment(int numSteps);
	void Start(std::string_view testName);
	void Stop(double pi, int numThreads);
	
private:
	std::ofstream out;
	std::string name;
	//... start;
	std::chrono::steady_clock::time_point start;
};

//how about a thread guard -> exceptions