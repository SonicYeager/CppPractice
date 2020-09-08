#include "CSV.h"
#include <unordered_map>
#include <algorithm>

using Table = std::vector<std::vector<std::string>>;

Table ParseCSV(const  Lines&);
Lines FormatToTable(const Table&);

Lines TabulateCSV(const Lines& lines)
{
    auto col = ParseCSV(lines);
    auto res = FormatToTable(col);
    return res;
}

std::vector<std::vector<std::string>> DecomposeLines(const Lines&);
std::vector<std::string> DecomposeLine(const std::string&);

Table ParseCSV(const Lines& lines)
{
    auto res = DecomposeLines(lines);
    return res;
}

Table DecomposeLines(const Lines& lines)
{
    Table res{};
    for (auto line : lines)
        res.push_back(DecomposeLine(line));
    return res;
}

std::vector<std::string> DecomposeLine(const std::string& line)
{
    size_t last = 0;
    size_t next = 0; 
    std::vector<std::string> res;
    while ((next = line.find(';', last)) != std::string::npos)
    { 
        res.push_back(line.substr(last, next - last)); 
        last = next + 1; 
    } 
    res.push_back(line.substr(last));
    return res;
}

std::vector<int> GetMaxColumnLengths(const Table&);
Lines FormatTable(std::vector<int>, const Table&);

Lines FormatToTable(const Table& table)
{
    auto maxLengths = GetMaxColumnLengths(table);
    auto res = FormatTable(maxLengths, table);
    return res;
}

std::vector<int> GetMaxColumnLengths(const Table& table)
{
    std::vector<int> res{};
    for (size_t i = 0; i < table[0].size(); i++)
    {
        int last = 0;
        for (auto line : table)
        {
            if(line[i].size() > last)
                last = line[i].size();
        }
        res.push_back(last);
    }
    return res;
}

Lines FormatLines(std::vector<int>, const Table&, std::string);

Lines FormatTable(std::vector<int> maxColumnLeghth, const Table& table)
{
    return FormatLines(maxColumnLeghth, table, "|");
}

std::string FormatLine(std::vector<int>, const std::vector<std::string>&, std::string, std::string);

Lines FormatLines(std::vector<int> maxColumnWidth, const Table& table, std::string seperator)
{
    Lines res{};

    auto cpy = table;
    std::vector<std::string> insert{};
    for (size_t i = 0; i < table[0].size(); i++)
        insert.push_back("");
    cpy.insert(++std::begin(cpy), insert);

    size_t index = 0;
    for (auto line : cpy)
    {
        res.push_back(FormatLine(maxColumnWidth,line, index == 1 ? "-" : " ", index == 1 ? "+" : seperator));
        ++index;
    }
    return res;
}

std::string FormatLine(std::vector<int> maxColumnWidth, const std::vector<std::string>& line, std::string spaceFill,std::string seperator)
{
    std::string res{};
    size_t index = 0;
    for (auto word : line) {
        std::string fill{};
        for (size_t i = 0; i < maxColumnWidth[index] - word.size(); i++)
        {
            fill += spaceFill;
        }
        res += word + fill + seperator;
        ++index;
    }
    return res;
}
