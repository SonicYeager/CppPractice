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
			if (key.jobDependency_value == jkey && jval == key.job_key)
				throw DirectCircularDependencyException(key.job_key, jkey);
		}

		Job j{'.','.'};
		for (auto& key : reg)
		{
			if (key.job_key == jkey)
				if (jval == EMPTYDEPENDENCY)
					return { jkey, jval };
				else
					continue;
			if (key.jobDependency_value == EMPTYDEPENDENCY)
				return { jkey, jval };
		}
		throw IndirectCircularDependencyException();
		
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
			registeredJobs.insert({ dependentJob, independentJob });
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


