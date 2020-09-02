#include "Crypt.h"
#include <algorithm>
#include <map>

std::string StringToUpper(std::string);
std::string ReplaceUmlauts(std::string);
std::string CleanString(std::string);
std::string Rotate(std::string);

std::string EncryptROTXIII(std::string text)
{
    //both works <- thats what fu's are intended to be

    //auto replaced = ReplaceUmlauts(text);
    //auto capped = StringToUpper(replaced);
    //auto cleaned = CleanString(capped);
    //return Rotate(cleaned);

    auto capped = StringToUpper(text);
    auto replaced = ReplaceUmlauts(capped);
    auto cleaned = CleanString(replaced);
    return Rotate(cleaned);
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

std::string CleanString(std::string str)
{
    auto clean = [](char& c)
    {
        if ((c < 65 || c > 90) && c != 32)
            c = '*';
    };

    std::for_each(std::begin(str), std::end(str), clean);
    str.erase(std::remove(std::begin(str), std::end(str), '*'), std::end(str));
    return str;
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
    };
    std::for_each(std::begin(str), std::end(str), rotate);
    str.erase(std::remove(std::begin(str), std::end(str), '*'), std::end(str));
    return str;
}
