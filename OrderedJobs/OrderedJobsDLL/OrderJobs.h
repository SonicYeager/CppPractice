#pragma once
#include <string>
#include <set>
#include <iostream>

#ifdef ORDEREDJOBSDLL_EXPORTS
#define ORDEREDJOBS_API __declspec(dllexport)
#else
#define ORDEREDJOBS_API __declspec(dllimport)
#endif

namespace OrderJobs
{
	const char EMPTYDEPENDENCY = '0';

	struct Job
	{
		Job(char job, char dependency) 
			: job_key(job), jobDependency_value(dependency)
		{}

		const char job_key{};
		char jobDependency_value{ EMPTYDEPENDENCY };
	};

	bool operator<(const Job& left, const Job& right)
	{
		if (left.job_key == right.job_key)
			return false;
		if (left.jobDependency_value == EMPTYDEPENDENCY && right.jobDependency_value == EMPTYDEPENDENCY)
			return left.job_key < right.job_key;
		if (left.jobDependency_value == right.jobDependency_value)
			return left.job_key < right.job_key;
		return left.job_key == right.jobDependency_value || left.jobDependency_value == EMPTYDEPENDENCY;
	};

	using RegisteredJobs = std::set<Job, std::less<>>;

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