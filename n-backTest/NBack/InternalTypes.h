#pragma once
#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <functional>

#ifdef NBACK_EXPORTS
#define NBACK_API __declspec(dllexport)
#else
#define NBACK_API __declspec(dllimport)
#endif

//std::time_t t = std::chrono::system_clock::to_time_t(startTime);
//char c[26]{};
//ctime_s(c, 26, &t);

namespace NBACK
{
	using Path = std::filesystem::path;
	using Lines = std::vector<std::string>;

	struct NBACK_API TestData
	{
		int n{};
		int countStimuli{};
		std::string subjectname{};
		std::vector<char> stimuli{};
		std::chrono::milliseconds stimuliIntervall{};
	};

	struct NBACK_API EvalData
	{
		TestData tdata{};
		std::chrono::system_clock::time_point startTime{};
		std::vector<bool> answers{};
		double percentCorrect{-1};
	};
}