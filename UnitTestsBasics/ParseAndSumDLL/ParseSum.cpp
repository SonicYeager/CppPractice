#include "ParseSum.h"
#include <vector>

 int ParseSum::ParseAndSum(const std::string& str)
{
     int res{};
     std::vector<int> sum;
     std::string estr{str};
     std::string delimiter = ";";

     size_t pos = 0;
     while ((pos = estr.find(delimiter)) != std::string::npos) {
         auto token = estr.substr(0, pos);
         sum.push_back(std::stoi(token));
         estr.erase(0, pos + delimiter.length());
     }
     if (estr != "")
     {
         auto token = estr.substr(0, estr.length());
         sum.push_back(std::stoi(token));
     }

     for (int num : sum)
         res += num;

     return res;
}
