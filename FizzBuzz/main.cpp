#include <assert.h>
#include "FizzBuzz.h"

int main()
{
	std::vector<int> arr{};
	for (size_t i = 1; i < 101; i++)
		arr.push_back(i);
	auto result = ReturnFizzBuzz(arr);

	std::vector<std::string> expected{
		"1", "2", "Fizz", "4", "Buzz","Fizz","Foo","8","Fizz","Buzz",
		"11", "Fizz", "Fizz", "Foo", "FizzBuzz","16","17","Fizz","19","Buzz",
		"Fizz", "22", "Fizz", "Fizz", "Buzz","Bar","Fizz","Foo","29","FizzBuzz",
		"Fizz", "Fizz", "Fizz", "Fizz", "Buzz","Fizz","Fizz","Fizz","Fizz","Buzz", 
		"41", "Fizz", "Fizz", "44", "FizzBuzz","46","47","Fizz","Foo","Buzz", 
		"Fizz", "Buzz", "Fizz", "Fizz", "Buzz","Buzz","Fizz","Buzz","Buzz","FizzBuzz", 
		"61", "62", "Fizz", "64", "Buzz","Fizz","67","68","Fizz","Buzz", 
		"71", "Fizz", "Fizz", "74", "FizzBuzz","76","Foo","Fizz","79","Buzz", 
		"Fizz", "82", "Fizz", "Fizz", "Buzz","86","Fizz","88","89","FizzBuzz", 
		"FooBar", "92", "Fizz", "94", "Buzz","Fizz","97","Foo","Fizz","Buzz", 
	};
	assert(result == expected);

	return 0;
}