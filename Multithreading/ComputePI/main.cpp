#include "Tools.h"
#include <thread>
#include <vector>
#include <mutex>
#include <future>

// Algorithmus:
// Zur Bestimmung von PI werden zufällig Koordinaten in einem 2x2 Rechteck (Mittelpunkt (0,0), Seitelänge 2) bestimmt
// Anschließend wird geprüft, ob die Koordinate innerhalb des Kreises (Mittelpunkt (0,0) und Radius von 1.0) ist
// Ist das der Fall ist es ein Treffer
// Die Fläche des Einheitskreise beträgt Pi*r^2 = Pi*1^2 = Pi
// Die Fläche des Rechtecks beträgt a*b = 2*2 = 4
// Durch das Verhältnis Treffer/Würfe = Pi / 4, lässt sich Pi bestimmen, Pi = 4 * Treffer/Würfe
double ComputePISequential(int numSteps)
{
	// Anzahl von Treffern die im Kreis landen
	int numHitsInCircle = 0;
	for(int k = 0; k < numSteps; ++k)
	{
		// Zufällige Koordinate in dem Rechteck [-1,1]x[-1,1] bestimmen
		double x_coord = 2.0 * Random() - 1.0;
		double y_coord = 2.0 * Random() - 1.0;
		// Liegt die Koordinate im Kreis?
		if(x_coord*x_coord + y_coord*y_coord <= 1.0)
			++numHitsInCircle;
	}
	// Pi berechnen
	return 4.0 * static_cast<double>(numHitsInCircle) / numSteps;
}

struct ThreadParam
{
	int start;
	int end;
};

int numHitsInCircle_global = 0; //es würde auch thread_local funktionieren ^^
std::mutex mx;

void ThreadFuncGlobal(ThreadParam thparam) 
{
	for (int k = thparam.start; k < thparam.end; ++k)
	{
		double x_coord = 2.0 * Random() - 1.0;
		double y_coord = 2.0 * Random() - 1.0;
		if (x_coord * x_coord + y_coord * y_coord <= 1.0) 
		{
			std::lock_guard<std::mutex> guard{ mx };
			++numHitsInCircle_global;
		}
	}
}

double ComputePIParalellGlobal(int numSteps, int numth = std::thread::hardware_concurrency())
{
	//call threads here
	std::vector<std::thread> threads;
	if (numth == 0) 
		numth = 4;
	for (size_t i = 0; i < numth; i++)
	{
		int numiteration = numSteps / numth; //ectl round() für aufgerundete werte (is ja splicing momentan)
		threads.emplace_back(std::thread{ ThreadFuncGlobal, ThreadParam{ 0 , numiteration }});
	}
	for (auto &thread : threads)
		thread.join();
	return 4.0 * static_cast<double>(numHitsInCircle_global) / numSteps;
}

struct ThreadParamWithHits : ThreadParam
{
	int localNumHitsInCircle;
};

void ThreadFuncLocal(ThreadParamWithHits& thparam)
{
	for (int k = thparam.start; k < thparam.end; ++k)
	{
		double x_coord = 2.0 * Random() - 1.0;
		double y_coord = 2.0 * Random() - 1.0;
		if (x_coord * x_coord + y_coord * y_coord <= 1.0)
		{
			++thparam.localNumHitsInCircle;
		}
	}
}

double ComputePIParalellLocal(int numSteps, int numth = std::thread::hardware_concurrency())
{
	//call threads here
	std::vector<std::thread> threads;
	std::vector<ThreadParamWithHits> localvars(numth);
	if (numth == 0)
		numth = 4;
	for (size_t i = 0; i < numth; i++)
	{
		int numiteration = numSteps / numth; //ectl round() für aufgerundete werte (is ja splicing momentan)
		localvars.at(i) = (ThreadParamWithHits{0, numiteration, 0});
		threads.push_back(std::thread(ThreadFuncLocal, std::ref(localvars.at(i))));
	}
	for (auto& thread : threads)
		thread.join();
	int sumNumHitsInCircle = 0;
	for (const auto& var : localvars)
		sumNumHitsInCircle += var.localNumHitsInCircle;
	return 4.0 * static_cast<double>(sumNumHitsInCircle) / numSteps;
}

int AsyncThreadFunc(int start, int end)
{
	int localNumHitsInCircle = 0;
	for (int k = start; k < end; ++k)
	{
		double x_coord = 2.0 * Random() - 1.0;
		double y_coord = 2.0 * Random() - 1.0;
		if (x_coord * x_coord + y_coord * y_coord <= 1.0)
		{
			++localNumHitsInCircle;
		}
	}
	return localNumHitsInCircle;
}

double ComputePIParalellAsync(int numSteps, int numth = std::thread::hardware_concurrency())
{
	//call threads here
	int sumNumHitsInCircle = 0;
	std::vector<std::future<int>> threads;
	if (numth == 0)
		numth = 4;
	for (size_t i = 0; i < numth; i++)
	{
		int numiteration = numSteps / numth; //ectl round() für aufgerundete werte (is ja splicing momentan)
		threads.push_back(std::async(std::launch::async, AsyncThreadFunc, 0, numiteration));
	}
	for (auto& thread : threads)
		sumNumHitsInCircle += thread.get();
	return 4.0 * static_cast<double>(sumNumHitsInCircle) / numSteps;
}

double ComputeAlgorithmSequential(int numSteps)
{
	double sum = 0;
	double step = 1.0 / numSteps;
	for (size_t k = 0; k < numSteps; ++k)
	{
		double x = (k + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}
	return sum / numSteps;
}

void ThreadFuncLocalForAlgorithm(ThreadParamWithHits& thparams)
{
	double sum = 0;
	int numSteps = thparams.end - thparams.start;
	double step = 1.0 / numSteps;
	for (size_t k = 0; k < numSteps; ++k)
	{
		double x = (k + 0.5) * step;
		sum += 4.0 / (1.0 + x * x);
	}
	thparams.localNumHitsInCircle = sum;
}

double ComputeAlgorithmParallelLocal(int numSteps, int numth = std::thread::hardware_concurrency())
{
	//call threads here
	std::vector<std::thread> threads;
	std::vector<ThreadParamWithHits> localvars(numth);
	int sum = 0;

	if (numth == 0)
		numth = 4;
	for (size_t i = 0; i < numth; ++i)
	{
		int numiteration = numSteps / numth; //ectl round() für aufgerundete werte (is ja splicing momentan)
		localvars.at(i) = (ThreadParamWithHits{ 0, numiteration, 0 });
		threads.push_back(std::thread(ThreadFuncLocalForAlgorithm, std::ref(localvars.at(i))));
	}
	for (auto& thread : threads)
		thread.join();
	for (const auto& var : localvars)
		sum += var.localNumHitsInCircle;
	return static_cast<double>(sum) / numSteps;
}

int main()
{
	int numSteps = 1000000;
	int numThreads = 1;
#if 0
	Measurment measure(numSteps);
	measure.Start("Sequ");
	double pi = ComputePISequential(numSteps);
	measure.Stop(pi, numThreads);

	// Deine Lösung folgt hier
	for (size_t i = 2; i < 16; i += 2)
	{
		numHitsInCircle_global = 0;
		numThreads = i;
		measure.Start("Paralell Thg");
		pi = ComputePIParalellGlobal(numSteps, numThreads);
		measure.Stop(pi, numThreads);

		measure.Start("Paralell Thl");
		pi = ComputePIParalellLocal(numSteps, numThreads);
		measure.Stop(pi, numThreads);

		measure.Start("Paralell Asy");
		pi = ComputePIParalellAsync(numSteps, numThreads);
		measure.Stop(pi, numThreads);
	}
#endif

	//algo
	numSteps = 1000000000;
	Measurment measureii(numSteps);
	measureii.Start("Sequ Alg");
	double pi = ComputeAlgorithmSequential(numSteps);
	measureii.Stop(pi, 1);

	for (size_t i = 2; i < 16; i += 2)
	{
		numThreads = i;
		measureii.Start("Paralell Alg");
		pi = ComputeAlgorithmParallelLocal(numSteps, numThreads);
		measureii.Stop(pi, numThreads);
	}

	return 0;
}
