#pragma once
#include <string>

#ifdef PRIMEFACTORIZATION_EXPORTS
#define PRIMEFACTORIZATION_API __declspec(dllexport)
#else
#define PRIMEFACTORIZATION_API __declspec(dllimport)
#endif

static class PRIMEFACTORIZATION_API PrimeFactorizor
{
public:
	static std::string Factorize(int);
};