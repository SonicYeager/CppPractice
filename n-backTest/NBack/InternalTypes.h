#pragma once
#include <string>
#include <chrono>
#include <vector>
#include <filesystem>
#include <functional>
#include <future>

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
	using Event = std::function<void()>;

	using namespace std::chrono_literals;
	
	const Path INTERNALPATH{"testresults.txt"};

	enum class NBACK_API REACTION
	{
		NOKEY = 0,
		SPACEBAR,
		ESC
	};

	struct NBACK_API TestConfig
	{
		int n{};
		int countStimuli{};
		std::string subjectname{};
		std::vector<char> stimuli{};
		std::chrono::milliseconds stimuliIntervall{};
	};

	struct NBACK_API EvalData
	{
		TestConfig tdata{};
		std::chrono::system_clock::time_point startTime{};
		std::vector<bool> answers{};
		double percentCorrect{-1};
	};
}