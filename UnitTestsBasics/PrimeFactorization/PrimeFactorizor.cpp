#include "PrimeFactorizor.h"

bool isPrime(int);

std::string PrimeFactorizor::Factorize(int num)
{
    int divisor = 2;
    std::string res{ std::to_string(divisor) };
	if(isPrime(num))
	{
		return std::to_string(num);
	}
	else
	{
		while(!isPrime(num))
		{
			if (num % divisor == 0)
			{
				res += "*"; 
				num /= divisor;
				res += isPrime(num) ? std::to_string(num) : std::to_string(divisor); //
			}
			else
			{
				while (!isPrime(divisor)) 
				{ 
					++divisor;
				};
			}
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
