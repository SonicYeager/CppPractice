#pragma once
#include <exception>
#include <string>

struct DirectCircularDependencyException : public std::exception
{
	DirectCircularDependencyException(char a, char b) : joba(a), jobb(b)
	{
		msg =  joba + " and " + jobb;
		msg.append(" have a Circular Dependency");
	}

	std::string what()
	{
		return msg;
	}

	const char joba;
	const char jobb;
	std::string msg;
};

struct IndirectCircularDependencyException : public std::exception
{
	IndirectCircularDependencyException(char job_key, char job_val) : job_key(job_key), job_val(job_val)
	{
		msg = "Job: " + job_key + ',' + job_val;
		msg += " is causing Indirect Circular Dependency";
	}

	std::string what()
	{
		return msg;
	}

	const char job_key;
	const char job_val;
	std::string msg;
};