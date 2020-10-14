#include "OrderJobs.h"
#include <algorithm>

namespace OrderJobs
{

	bool operator==(const const std::pair<const char, char>& left, const std::pair<const char, char>& right)
	{
		return left.first == right.first;
	}
	bool operator<(const std::pair<const char, char>& left, const std::pair<const char, char>& right)
	{
		return left.first == right.second;
	};

	void OrderedJobs::Register(char dependentJob, char independentJob)
	{
		registeredJobs[dependentJob] = independentJob;
		if (registeredJobs.find(independentJob) == std::end(registeredJobs))
			Register(independentJob);
	}

	void OrderedJobs::Register(char independentJob)
	{
		registeredJobs[independentJob] = '0';
	}

	RegisteredJobs GetIndependentJobs(const RegisteredJobs&);
	RegisteredJobs GetDependentJobs(const RegisteredJobs&);
	RegisteredJobs OrderDependentJobsByDependency(const RegisteredJobs&);
	std::string MergeIndependentAndDependentJobs(const RegisteredJobs&, const RegisteredJobs&);

	std::string OrderedJobs::Sort()
	{
		std::string res{};
		auto independent = GetIndependentJobs(registeredJobs);
		auto dependent = GetDependentJobs(registeredJobs);
		res = MergeIndependentAndDependentJobs(independent, dependent);
		return res;
	}

	RegisteredJobs GetIndependentJobs(const RegisteredJobs& reg)
	{
		RegisteredJobs res{};
		for (auto& entry : reg)
			if(entry.second == '0')
				res.emplace(entry);
		return res;
	}

	RegisteredJobs GetDependentJobs(const RegisteredJobs& reg)
	{
		RegisteredJobs res{};
		for (auto& entry : reg)
			if (entry.second != '0')
				res.emplace(entry);
		return res;
	}

	RegisteredJobs OrderDependentJobsByDependency(const RegisteredJobs& depReg)
	{
		RegisteredJobs res{};

		for (auto& regEntry : depReg)
		{
			for (auto& resEntry : res)
			{
				if (res.find(regEntry.second) != std::end(res))
					res.insert(res.find(resEntry.first), regEntry);
				else
					res.insert(std::begin(res), regEntry);
			}
		}

		return res;
	}

	std::string MergeIndependentAndDependentJobs(const RegisteredJobs& independentJobs, const RegisteredJobs& dependentJobs)
	{
		std::string res{};
		for (auto& entry : independentJobs)
			res += entry.first;
		for (auto& entry : dependentJobs)
			res += entry.first;
		return res;
	}
}


