#pragma once
#include <string>

#ifdef PRIMEFACTORIZATION_EXPORTS
#define PARSESUM_API __declspec(dllexport)
#else
#define PARSESUM_API __declspec(dllimport)
#endif

class PARSESUM_API ParseSum
{
public:
	static int ParseAndSum(const std::string&);
};