#include "RomanConvert.h"
#include <algorithm>
#include <iterator>
#include <vector>

std::vector<char> DecomposeRoman(std::string);
std::vector<int> MapRomanToDecimal(std::vector<char>);
int FuseDecimal(std::vector<int>);

std::vector<int> DecomposeDecimal(int);
std::vector<std::string> MapDecimalToRoman(std::vector<int>);
std::string FuseRoman(std::vector<std::string>);

std::string DecimalToRoman(int dec)
{
    auto decomposed = DecomposeDecimal(dec);
    auto mapped = MapDecimalToRoman(decomposed);
    return FuseRoman(mapped);
}

int RomanToDecimal(std::string rom)
{
    auto decomposed = DecomposeRoman(rom);
    auto mapped = MapRomanToDecimal(decomposed);
    return FuseDecimal(mapped);
}



std::vector<char> DecomposeRoman(std::string rom)
{
    std::vector<char> decomposedRoman{};
    for (auto roman : rom) 
    {
        decomposedRoman.push_back(roman);
    }
    return decomposedRoman;
}

std::vector<int> MapRomanToDecimal(std::vector<char> chars)
{
    std::vector<int> mappedDecimal{};
    for (auto cha : chars) 
    {
        switch (cha)
        {
            case('I'):
                mappedDecimal.push_back(1);
                break;
            case('V'):
                mappedDecimal.push_back(5);
                break;
            case('X'):
                mappedDecimal.push_back(10);
                break;
            case('L'):
                mappedDecimal.push_back(50);
                break;
            case('C'):
                mappedDecimal.push_back(100);
                break;
            case('D'):
                mappedDecimal.push_back(500);
                break;
            case('M'):
                mappedDecimal.push_back(1000);
                break;
            default:
                break;
        }
    }
    return mappedDecimal;
}

int FuseDecimal(std::vector<int> decimals)
{
    int sum{};
    int lastVal = 0;
    for (auto dec : decimals) 
    {
        if (sum != 0 && lastVal < dec)
            sum -= (lastVal * 2) - dec;
        else
            sum += dec;
        lastVal = dec;
    }
    return sum;
}

std::vector<int> DecomposeDecimal(int dec)
{
    std::vector<int> decomposedDecimal{};

    int fac = 1;
    while (dec != 0)
    {
        decomposedDecimal.push_back((dec % 10)*fac);
        dec /= 10;
        fac *= 10;
    }
    std::reverse(std::begin(decomposedDecimal), std::end(decomposedDecimal));
    return decomposedDecimal;
}

std::vector<std::string> MapDecimalToRoman(std::vector<int> decimals)
{
    std::vector<std::string> mappedRoman{};
    for (auto dec : decimals)
    {
        switch (dec)
        {
        case(1):
            mappedRoman.push_back("I");
            break;
        case(4):
            mappedRoman.push_back("IV");
            break;
        case(5):
            mappedRoman.push_back("V");
            break;
        case(9):
            mappedRoman.push_back("IX");
            break;
        case(10):
            mappedRoman.push_back("X");
            break;
        case(40):
            mappedRoman.push_back("XL");
            break;
        case(50):
            mappedRoman.push_back("L");
            break;
        case(90):
            mappedRoman.push_back("XC");
            break;
        case(100):
            mappedRoman.push_back("C");
            break;
        case(400):
            mappedRoman.push_back("CD");
            break;
        case(500):
            mappedRoman.push_back("D");
            break;
        case(900):
            mappedRoman.push_back("DM");
            break;
        case(1000):
            mappedRoman.push_back("M");
            break;
        default:
            int fac = 1;
            while (dec % 10 == 0)
            {
                fac *= 10;
                dec /= 10;
            }
            int val = dec % 10;
            if (val > 5)
            {
                std::vector<int> tempVal{};
                tempVal.push_back(5 * fac);
                mappedRoman.push_back(MapDecimalToRoman(tempVal).at(0));
                val -= 5;
            }
            for (size_t i = 0; i < val; i++)
            {
                std::vector<int> tempVal{};
                tempVal.push_back(fac);
                mappedRoman.push_back(MapDecimalToRoman(tempVal).at(0));
            }
            break;
        }
    }
    return mappedRoman;
}

std::string FuseRoman(std::vector<std::string> chars)
{
    std::string sum{};
    for (auto cha : chars)
    {
        sum += cha;
    }
    return sum;
}
