#include "OrderJobs.h"
#include "Exceptions.h"
#include <algorithm>

namespace OrderJobs
{

	RegisteredJobs::iterator FindKey(const RegisteredJobs& reg, char jkey) //only a helper
	{
		RegisteredJobs::iterator it{ reg.begin() };

		for (auto& key : reg)
		{
			if (key.job_key == jkey)
				return it;
			++it;
		}
		return reg.end();
	}

	Job ValidateDependency(const RegisteredJobs& reg, char jkey, char jval)
	{
		for (auto& key : reg)
		{
			if (key.jobDependency_value == jkey && jval == key.job_key) //corner case self dependent
				throw DirectCircularDependencyException(key.job_key, jkey);
		}

		RegisteredJobs::iterator next{ --reg.end() };

		for (size_t i{}; i < reg.size(); ++i)
		{
			if (next == reg.end() && i == reg.size() - 1)
				break;
			else if (next == reg.end())
			{
				next = --reg.end();
				for (size_t k{}; k < i; ++k)
					--next;
			}

			if(next->job_key == jkey)
				next = FindKey(reg, jval);
			else
				next = FindKey(reg, next->jobDependency_value);

		}
		if(reg.end() == next)
			return { jkey, jval };

		throw IndirectCircularDependencyException(next->job_key, next->jobDependency_value);
		
	}

	void OrderedJobs::Register(char dependentJob, char independentJob)
	{
		if (FindKey( registeredJobs, independentJob) == registeredJobs.end())
			Register(independentJob);
		auto found = FindKey(registeredJobs, dependentJob);
		if (found != registeredJobs.end())
		{
			Job temp{ ValidateDependency(registeredJobs, found->job_key, independentJob) };
			registeredJobs.erase(found);
			registeredJobs.insert(temp);
		}
		else
		{
			auto validated = ValidateDependency(registeredJobs, dependentJob, independentJob);
			registeredJobs.insert({ validated.job_key, validated.jobDependency_value });
		}
	}

	void OrderedJobs::Register(char independentJob)
	{
		auto found = FindKey(registeredJobs, independentJob);
		if (found != registeredJobs.end())
		{
			Job temp{ ValidateDependency(registeredJobs, found->job_key, EMPTYDEPENDENCY) };
			registeredJobs.erase(found);
			registeredJobs.insert(temp);
		}
		else
			registeredJobs.insert({ independentJob, EMPTYDEPENDENCY });
	}

	std::string OrderedJobs::Sort()
	{
		std::string res{};
		for (auto& job : registeredJobs)
			res += job.job_key;
		return res;
	}
}


