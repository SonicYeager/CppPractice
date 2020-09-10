#include "Tools.h"
#include <iostream>
#include <sstream>
#include <string>

void PrintBattlefieldToConsole(const Battlefield& field)
{
	::system("CLS");
	std::ostringstream ostr;
	for(const auto& row : field)
	{
		for(const auto& col : row)
		{
			ostr << col;
		}
		ostr << "\n";
	}
	std::cout << ostr.str() << std::endl;
}

Battlefield ConvertGameData(const Path& path, const Battlefield& field)
{
	Battlefield res{field};
	for(const auto& elem : path)
		res[elem.pos.y][elem.pos.x] = elem.alienCount > 0 ? '*' : '1';
	return res;
}
