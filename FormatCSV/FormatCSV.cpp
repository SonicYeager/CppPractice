#include "FormatCSV.h"

using Lines = std::vector<std::string>;

struct Table
{
    Table() = default;
    Table(const  std::vector<std::string>& head, const  std::vector<std::string>& seperation, const std::vector<std::vector<std::string>>& content) :
        head(head), seperation(seperation), content(content)
    {}

    Table(const  std::vector<std::string>& head, const std::vector<std::vector<std::string>>& content) :
        Table(head, { head.size(), "" }, content)
    {}

    std::vector<std::string> head;
    std::vector<std::string> seperation; //optional
    std::vector<std::vector<std::string>> content;
};

Table ParseCSV(const  Lines&);
Lines FormatTable(const Table&);

Lines TabulateCSV(const Lines& lines)
{
    Table table = ParseCSV(lines);
    auto res = FormatTable(table);
    return res;
}

Table DecomposeLines(Lines);
std::vector<std::string> DecomposeLine(const std::string&);

Table ParseCSV(const Lines& lines)
{
    auto res = DecomposeLines(lines);
    return res;
}

Table DecomposeLines(Lines lines) //seperation extraction is possible to implement!!
{
    Table res{};
    res.head = DecomposeLine(lines.front());
    lines.erase(std::begin(lines));
    for (auto line : lines)
    {
        res.content.push_back(DecomposeLine(line));
    }
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
Lines FormatLines(const std::vector<int>&, const Table&);

Lines FormatTable(const Table& table)
{
    auto maxLengths = GetMaxColumnLengths(table);
    auto res = FormatLines(maxLengths, table);
    return res;
}

std::vector<int> GetMaxColumnLengths(const Table& table)
{
    std::vector<int> res{};
    for (size_t i = 0; i < table.head.size(); i++)
    {
        int last = 0;
        if (table.head[i].size() > last)
            last = table.head[i].size();
        for (auto line : table.content)
        {
            if (line[i].size() > last)
                last = line[i].size();
        }
        res.push_back(last);
    }
    return res;
}

std::string FormatLine(std::vector<int>, const std::vector<std::string>&, std::string, std::string);

Lines FormatLines(const std::vector<int>& maxColumnWidth, const Table& table)
{
    Lines res{};

    res.push_back(FormatLine(maxColumnWidth, table.head, " ", "|"));
    res.push_back(FormatLine(maxColumnWidth, table.seperation, "-", "+"));
    for (auto line : table.content)
    {
        res.push_back(FormatLine(maxColumnWidth, line, " ", "|"));
    }
    return res;
}

std::string FormatLine(const std::vector<int>& maxColumnWidth, const std::vector<std::string>& line, const std::string& spaceFill, const std::string& seperator)
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
