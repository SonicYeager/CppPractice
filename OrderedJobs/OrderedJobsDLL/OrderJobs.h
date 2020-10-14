#pragma once
#include <string>
#include <unordered_map>
#include <iostream>

#ifdef ORDEREDJOBSDLL_EXPORTS
#define ORDEREDJOBS_API __declspec(dllexport)
#else
#define ORDEREDJOBS_API __declspec(dllimport)
#endif

namespace OrderJobs
{

	using RegisteredJobs = std::unordered_map<char, char>;

	class ORDEREDJOBS_API OrderedJobs
	{
	public:
		void Register(char, char);
		void Register(char);
		std::string Sort();

	private:
		RegisteredJobs registeredJobs{};
	};
}