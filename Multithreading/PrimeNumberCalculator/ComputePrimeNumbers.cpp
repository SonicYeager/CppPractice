#include "ComputePrimeNumbers.h"
#include <thread>
#include <algorithm>
#include <experimental/coroutine>

PrimeNumbers ComputePrimeNumbers::ComputePrimes(Range range)
{
	PrimeNumbers result;
	int last = range.end;
	int candidate = std::max(2, range.begin);
	while(candidate < last)
	{
		bool isPrime = true;
		for(int trialDivisor = 2; trialDivisor * trialDivisor <= candidate; ++trialDivisor)
		{
			if(candidate % trialDivisor == 0)
			{
				isPrime = false;
				break;
			}
		}
		if(isPrime)
		{
			result.push_back(candidate);
			//Slowdown computation ;)
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
		candidate++;
	}
	return result;
}

std::experimental::generator<int> ComputePrimeNumbers::ComputePrimesGenerated(Range range)
{
	//PrimeNumbers result; 
	int last = range.end;
	int candidate = std::max(2, range.begin);
	while(candidate < last)
	{
		bool isPrime = true;
		for(int trialDivisor = 2; trialDivisor * trialDivisor <= candidate; ++trialDivisor)
		{
			if(candidate % trialDivisor == 0)
			{
				isPrime = false;
				break;
			}
		}
		if(isPrime)
		{
			//result.push_back(candidate);
			co_yield candidate;
			//onProgress(candidate);
			//Slowdown computation ;)
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
		}
		candidate++;
	}
}

void ComputePrimeNumbers::ComputePrimesEventGenerated(Range range)
{
	//PrimeNumbers result;
	int last = range.end;
	int candidate = std::max(2, range.begin);
	while(candidate < last)
	{
		bool isPrime = true;
		for(int trialDivisor = 2; trialDivisor * trialDivisor <= candidate; ++trialDivisor)
		{
			if(candidate % trialDivisor == 0)
			{
				isPrime = false;
				break;
			}
		}
		if(isPrime)
		{
			//result.push_back(candidate);
			onProgress(candidate);
			//onProgress(candidate);
			//Slowdown computation ;)
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
		}
		candidate++;
	}
}

std::future<void> ComputePrimeNumbers::ComputePrimesEventAsyncGenerated(Range range) //adpt type
{
	co_await std::async(std::launch::async, &ComputePrimeNumbers::ComputePrimesEventGenerated, this, range);
	onFinish();
}