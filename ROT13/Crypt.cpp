#include "Crypt.h"
#include <algorithm>
#include <map>

std::string StringToUpper(std::string);
std::string ReplaceUmlauts(std::string);
std::string Rotate(std::string);

std::string EncryptROTXIII(std::string text)
{
    //auto replaced = ReplaceUmlauts(text);
    //auto capped = StringToUpper(replaced);
    //return Rotate(capped);

    auto capped = StringToUpper(text);
    auto replaced = ReplaceUmlauts(capped);
    return Rotate(replaced);
}

std::string StringToUpper(std::string str)
{
    auto toupper = [](char& c) 
    {
        c = std::toupper(c);
    };

    std::for_each(std::begin(str), std::end(str), toupper);
    return str;
}

std::string ReplaceUmlauts(std::string str)
{
    std::string res{};
    std::map<char, std::string> umlautMap{ {'Ä', "AE"}, {'Ü', "UE"}, {'Ö', "OE"}, {'ß', "SS"}, {'ä', "AE"}, {'ü', "UE"}, {'ö', "OE"} };
    for (size_t i = 0; i < str.size(); i++)
    {
        if (umlautMap.find(str[i]) != umlautMap.end())
            res.append(umlautMap.at(str[i]));
        else
            res += (str[i]);
    }
    return res;
}

std::string Rotate(std::string str)
{
    auto rotate = [](char& c)
    {
        if (c >= 65 && c <= 90)
        {
            int val = c + 13;
            if (val > 90)
                val -= 26;
            c = val;
        }
        else if (c == 32)
            c = ' ';
        else
            c = '*';
    };
    std::for_each(std::begin(str), std::end(str), rotate);
    //;
    str.erase(std::remove(std::begin(str), std::end(str), '*'), std::end(str));
    return str;
}
