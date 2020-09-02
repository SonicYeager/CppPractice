#include "FizzBuzz.h"
#include <functional>

std::string ToFizz();
std::string ToBuzz();
std::string ToFizzBuzz();
std::string ToString(int);
std::string ApplyRules(int, std::function<std::string()>, std::function<std::string()>, std::function<std::string()>, std::function<std::string(int)>);

std::vector<std::string> ReturnFizzBuzz(std::vector<int> arr)
{
   std::vector<std::string> res{};
   for(auto num : arr)
       res.push_back(ApplyRules(num, ToFizz, ToBuzz, ToFizzBuzz, ToString));
   return res;
}

std::string ApplyRules(int num, std::function<std::string()> onFizz, std::function<std::string()> onBuzz, std::function<std::string()> onFizzBuzz, std::function<std::string(int)> onNum)
{
    if (num % 3 == 0 && num % 5 == 0)
        return onFizzBuzz();
    else if (num % 3 == 0)
        return onFizz();
    else if (num % 5 == 0)
        return onBuzz();
    else
        return onNum(num);
}

std::string ToFizz()
{
    return "Fizz";
}

std::string ToBuzz()
{
    return "Buzz";
}

std::string ToFizzBuzz()
{
    return "FizzBuzz";
}

std::string ToString(int num)
{
    return std::to_string(num);
}