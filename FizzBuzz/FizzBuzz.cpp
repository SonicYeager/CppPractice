#include "FizzBuzz.h"
#include <functional>


std::string ToFizz();
std::string ToBuzz();
std::string ToFizzBuzz();
std::string ToFoo();
std::string ToBar();
std::string ToFooBar();
std::string ToString(int);

class Rules
{
public:
    Rules(std::function<void()> tofizz, std::function<void()> tobuzz, std::function<void()> tofizzbuzz,
        std::function<void()> tofoo, std::function<void()> tobar, std::function<void()> tofoobar, std::function<void(int)> tostring) :
        onFizz(tofizz), onBuzz(tobuzz), onFizzBuzz(tofizzbuzz), onFoo(tofoo), onBar(tobar), onFooBar(tofoobar), onNum(tostring)
    {}
    void ApplyRules(int);
private:
    bool ContainsNum(int, int);
    std::function<void()> onFizz;
    std::function<void()> onBuzz;
    std::function<void()> onFizzBuzz;
    std::function<void()> onFoo;
    std::function<void()> onBar;
    std::function<void()> onFooBar;
    std::function<void(int)> onNum;
};

std::vector<std::string> ReturnFizzBuzz(std::vector<int> arr)
{
    std::vector<std::string> res{};
    auto onToFizz = [&res] {res.push_back(ToFizz()); };
    auto onToBuzz = [&res] {res.push_back(ToBuzz()); };
    auto onToFizzBuzz = [&res] {res.push_back(ToFizzBuzz()); };
    auto onToFoo = [&res] {res.push_back(ToFoo()); };
    auto onToBar = [&res] {res.push_back(ToBar()); };
    auto onToFooBar = [&res] {res.push_back(ToFooBar()); };
    auto onToString = [&res] (int num){res.push_back(ToString(num)); };

    Rules rl = Rules(onToFizz, onToBuzz, onToFizzBuzz, onToFoo, onToBar, onToFooBar, onToString);
    for (auto num : arr) 
    {
        rl.ApplyRules(num);
    }
   return res;
}

auto Rules::ContainsNum (int num, int con) -> bool
{
    std::string checkStr = std::to_string(num);
    auto res = checkStr.find(std::to_string(con));
    return res != std::string::npos;
};

void Rules::ApplyRules(int num)
{
    if (num % 3 == 0 && num % 5 == 0)
        onFizzBuzz();
    else if (num % 3 == 0)
        onFizz();
    else if (num % 5 == 0)
        onBuzz();
    else if (ContainsNum(num, 3))
        onFizz();
    else if (ContainsNum(num, 5))
        onBuzz();
    else if (num % 7 == 0 && num % 13 == 0)
        onFooBar();
    else if (num % 7 == 0)
        onFoo();
    else if (num % 13 == 0)
        onBar();
    else
        onNum(num);
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

std::string ToFoo()
{
    return "Foo";
}

std::string ToBar()
{
    return "Bar";
}

std::string ToFooBar()
{
    return "FooBar";
}

std::string ToString(int num)
{
    return std::to_string(num);
}