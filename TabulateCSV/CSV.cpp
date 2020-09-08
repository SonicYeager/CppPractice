#include "CSV.h"
#include <unordered_map>
#include <algorithm>

//using Columns = std::unordered_map<std::string, std::vector<std::string>>;
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
//Columns ConvertToColumns(const std::vector<std::vector<std::string>>&);

Table ParseCSV(const Lines& lines)
{
    auto res = DecomposeLines(lines);
    //auto res = ConvertToColumns(decomp);
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

//Columns ConvertToColumns(const std::vector<std::vector<std::string>>& columns)
//{
//    Columns res{};
//    for (size_t i = 0; i < columns[0].size(); i++)
//    {
//        res.emplace(columns[0][i], std::vector<std::string>());
//        for (size_t ii = 1; ii < columns.size(); ii++)
//            res[columns[0][i]].push_back(columns[ii][i]);
//    }
//    return res;
//}

std::vector<int> GetMaxColumnLengths(const Table&);
//int GetMaxColumnLength(const std::pair<std::string, std::vector<std::string>>&);
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

//int GetMaxColumnLength(const std::pair<std::string, std::vector<std::string>>& col)
//{
//    int res = 0;
//    auto greaterThan = [](const std::string& a, const std::string b) -> bool { return a.size() < b.size(); };
//    auto maxElement = std::max_element(std::begin(col.second), std::end(col.second), greaterThan);
//    res = maxElement._Unwrapped()->size();
//    return res;
//}

//std::string CreateTableHead(std::vector<int>, const Table&);
//std::string CreateTableHeadSeperation(std::vector<int>);
//std::vector<std::vector<std::string>> ConvertToTable(const Columns& col);
//std::vector<std::string> CreateContentLines(std::vector<int>, const std::vector<std::vector<std::string>>&);
//Lines AddContentLines(const std::string& , const std::string& , const Lines& );

Lines FormatLines(std::vector<int>, const Table&, std::string);

Lines FormatTable(std::vector<int> maxColumnLeghth, const Table& table)
{
    //auto head = CreateTableHead(max, col);
    //auto sep = CreateTableHeadSeperation(max);
    //auto table = ConvertToTable(col);
    //auto contentLines = (CreateContentLines(max, table));
    //return AddContentLines(head, sep, contentLines);
    return FormatLines(maxColumnLeghth, table, "|");
}

//Lines AddContentLines(const std::string& head, const std::string& sep, const Lines& content )
//{
//    Lines res{};
//    res.push_back(head);
//    res.push_back(sep);
//    for (auto con : content)
//        res.push_back(con);
//    return res;
//}

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

//std::string CreateTableHead(std::vector<int> maxColumnWidth, const Columns& col)
//{
//    std::string res{};
//    size_t index = 0;
//    for (auto head : col)
//    {
//        std::string whiteSpaces{};
//        for (size_t i = 0; i < maxColumnWidth[index] - head.first.size(); i++)
//        {
//            whiteSpaces += ' ';
//        }
//        res += head.first + whiteSpaces + "|";
//        ++index;
//    }
//    return res;
//}

//std::string CreateTableHeadSeperation(std::vector<int> maxColumnWidth)
//{
//    std::string res{};
//    for (size_t i = 0; i < maxColumnWidth.size(); i++)
//    {
//        for (size_t ii = 0; ii < maxColumnWidth[i]; ii++)
//        {
//            res += '-';
//        }
//        res += "+";
//    }
//    return res;
//}

//std::string CreateContentLine(std::vector<int>, const std::vector<std::string>&);
//std::vector<std::vector<std::string>> ConvertToTable(const Columns&);
//
//std::vector<std::string> CreateContentLines(std::vector<int> max, const std::vector<std::vector<std::string>>& lines)
//{
//    std::vector<std::string> res{};
//    for (auto line : lines) 
//        res.push_back(CreateContentLine(max, line));
//    return res;
//}
//
//std::string CreateContentLine(std::vector<int> max, const std::vector<std::string>& line)
//{
//    std::string res{};
//    size_t index = 0;
//    for (auto word : line)
//    {
//        std::string whiteSpaces{};
//        for (size_t i = 0; i < max[index] - word.size(); i++)
//        {
//            whiteSpaces += ' ';
//        }
//        res += word + whiteSpaces + "|";
//        ++index;
//    }
//    return res;
//}
//
//std::vector<std::vector<std::string>> ConvertToTable(const Columns& col)
//{
//    std::vector<std::vector<std::string>> res{};
//    std::vector<std::vector<std::string>> tempRes{};
//    for (auto c : col)
//        tempRes.push_back(c.second);
//    for (size_t i = 0; i < tempRes[0].size(); i++)
//    {
//        res.push_back(std::vector<std::string>());
//        for (size_t ii = 0; ii < tempRes.size(); ii++)
//            res[i].push_back(tempRes[ii][i]);
//    }
//
//    return res;
//}
