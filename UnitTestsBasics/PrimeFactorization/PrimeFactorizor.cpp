#include "PrimeFactorizor.h"

bool isPrime(int);

std::string PrimeFactorizor::Factorize(int num)
{
    int primdivisor = 2;
    std::string res{};
	while(!isPrime(num) && num > 2)
	{
		if (num % primdivisor == 0)
		{
			res += res == "" ? "" : "*";
			res += std::to_string(primdivisor);
			num /= primdivisor;
		}
		else 
		{
			++primdivisor;
			while (!isPrime(primdivisor))
				++primdivisor;
		}
	}
	if (isPrime(num))
	{
		if(res == "")
			res += std::to_string(num);
		else if (num >= 2) 
		{
			res += "*";
			res += std::to_string(num);
		}
	}
	return res;
}

bool isPrime(int candidate)
{
	if (candidate <= 1)
		return false;

	for (int i = 2; i < candidate; i++)
		if (candidate % i == 0)
			return false;

	return true;
}
