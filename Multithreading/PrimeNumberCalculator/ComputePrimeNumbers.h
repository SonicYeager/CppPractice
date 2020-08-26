#pragma once
#include "Contracts.h"
#include <experimental/generator>
#include <future>

class ComputePrimeNumbers
{
public:
	PrimeNumbers ComputePrimes(Range);
	std::experimental::generator<int> ComputePrimesGenerated(Range);
	void ComputePrimesEventGenerated(Range);
	std::future<void> ComputePrimesEventAsyncGenerated(Range); //adpt type
	Event<PrimeNumber> onProgress;
	Event<> onFinish;
};
