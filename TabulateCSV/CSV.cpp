#include "CSV.h"
#include <unordered_map>
#include <algorithm>

using Columns = std::unordered_map<std::string, std::vector<std::string>>;

Columns ParseCSV(const  Lines&);
Lines FormatToTable(const Columns&);

Lines TabulateCSV(const Lines& lines)
{
    auto col = ParseCSV(lines);
    auto res = FormatToTable(col);
    return res;
}

std::vector<std::vector<std::string>> DecomposeLines(const Lines&);
std::vector<std::string> DecomposeLine(const std::string&);
Columns ConvertToColumns(const std::vector<std::vector<std::string>>&);

Columns ParseCSV(const Lines& lines)
{
    auto decomp = DecomposeLines(lines);
    auto res = ConvertToColumns(decomp);
    return res;
}

std::vector<std::vector<std::string>> DecomposeLines(const Lines& lines)
{
    std::vector<std::vector<std::string>> res{};
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

Columns ConvertToColumns(const std::vector<std::vector<std::string>>& columns)
{
    Columns res{};
    for (size_t i = 0; i < columns[0].size(); i++)
    {
        res.emplace(columns[0][i], std::vector<std::string>());
        for (size_t ii = 1; ii < columns.size(); ii++)
            res[columns[0][i]].push_back(columns[ii][i]);
    }
    return res;
}

std::vector<int> GetMaxColumnLengths(const Columns&);
int GetMaxColumnLength(const std::pair<std::string, std::vector<std::string>>& col);
Lines FormatColumnsToLines(std::vector<int>, const Columns&);

Lines FormatToTable(const Columns& col)
{
    auto maxLengths = GetMaxColumnLengths(col);
    auto res = FormatColumnsToLines(maxLengths, col);
    return res;
}

std::vector<int> GetMaxColumnLengths(const Columns& cols)
{
    std::vector<int> res{};
    for (auto col : cols)
    {
        int count = GetMaxColumnLength(col);
        res.push_back(count > col.first.size() ? count : col.first.size());
    }
    return res;
}

int GetMaxColumnLength(const std::pair<std::string, std::vector<std::string>>& col)
{
    int res = 0;
    auto greaterThan = [](const std::string& a, const std::string b) -> bool { return a.size() < b.size(); };
    auto maxElement = std::max_element(std::begin(col.second), std::end(col.second), greaterThan);
    res = maxElement._Unwrapped()->size();
    return res;
}

std::string CreateTableHead(std::vector<int>, const Columns&);
std::string FillWhiteSpaces(int);
std::string CreateSeparationLine(std::vector<int>);
std::vector<std::vector<std::string>> ConvertToTable(const Columns& col);
std::vector<std::string> CreateContentLines(std::vector<int>, const std::vector<std::vector<std::string>>&);
std::vector<std::string> AddContentLines(const std::vector<std::string>&, const std::vector<std::string>&);

Lines FormatColumnsToLines(std::vector<int> max, const Columns& col)
{
    Lines res{};
    res.push_back(CreateTableHead(max, col));
    res.push_back(CreateSeparationLine(max));
    auto table = ConvertToTable(col);
    auto contentLines = (CreateContentLines(max, table));
    res = AddContentLines(contentLines, res);
    return res;
}

std::vector<std::string> AddContentLines(const std::vector<std::string>& content, const std::vector<std::string>& res)
{
    auto cpy = res;
    for (auto con : content)
        cpy.push_back(con);
    return cpy;
}

std::string CreateTableHead(std::vector<int> max, const Columns& col)
{
    std::string res{};
    size_t index = 0;
    for (auto head : col)
    {
        res += head.first + FillWhiteSpaces(max[index] - head.first.size()) + "|";
        ++index;
    }
    return res;
}

std::string FillWhiteSpaces(int num) 
{
    std::string res{};
    for (size_t i = 0; i < num; i++)
    {
        res += ' ';
    }
    return res;
}

std::string CreateSeparationLine(std::vector<int> max)
{
    std::string res{};
    for (size_t i = 0; i < max.size(); i++)
    {
        for (size_t ii = 0; ii < max[i]; ii++)
        {
            res += '-';
        }
        res += "+";
    }
    return res;
}

std::string CreateContentLine(std::vector<int>, const std::vector<std::string>&);
std::vector<std::vector<std::string>> ConvertToTable(const Columns&);

std::vector<std::string> CreateContentLines(std::vector<int> max, const std::vector<std::vector<std::string>>& lines)
{
    std::vector<std::string> res{};
    for (auto line : lines) 
        res.push_back(CreateContentLine(max, line));
    return res;
}

std::string CreateContentLine(std::vector<int> max, const std::vector<std::string>& line)
{
    std::string res{};
    size_t index = 0;
    for (auto word : line)
    {
        res += word + FillWhiteSpaces(max[index] - word.size()) + "|";
        ++index;
    }
    return res;
}

std::vector<std::vector<std::string>> ConvertToTable(const Columns& col)
{
    std::vector<std::vector<std::string>> res{};
    std::vector<std::vector<std::string>> tempRes{};
    for (auto c : col)
        tempRes.push_back(c.second);
    for (size_t i = 0; i < tempRes[0].size(); i++)
    {
        res.push_back(std::vector<std::string>());
        for (size_t ii = 0; ii < tempRes.size(); ii++)
            res[i].push_back(tempRes[ii][i]);
    }

    return res;
}
