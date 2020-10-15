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
	IndirectCircularDependencyException()
	{
		msg = "No Independent Job was Registered -> causing Indirect Circular Dependency";
	}

	std::string what()
	{
		return msg;
	}

	std::string msg;
};