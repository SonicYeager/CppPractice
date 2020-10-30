#pragma once
#include <experimental/generator>
#include "Contracts.h"
#include <mutex>
#include <thread>

namespace std
{
	using namespace experimental;
}


class Ui
{
public:
	void Run();
	void RunStandalone(const Range& range);
	void ShowResult(Range, PrimeNumbers);

	size_t AddProgress();
	void UpdateProgress(size_t, PrimeNumber);
	void Finished(size_t, Range);

	Event<Range> onRange;

private:
	Range GetInput();
	void Display();
	auto GetStartEnd(std::string input);

	std::vector<std::string> progess;
	std::string input;
	std::mutex mtx;
};
