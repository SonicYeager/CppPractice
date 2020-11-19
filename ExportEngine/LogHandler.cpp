#include "LogHandler.h"
#include <iostream>

void LogExportRange(long long rangeStart, long long rangeEnd, const std::string& fileName)
{
	std::cout << "Export" << fileName;
	if(rangeEnd > rangeStart)
		std::cout << " from " << rangeStart << " to " << rangeEnd << " started.\n";
}

void LogExportTime(double expLen, long long elapsed)
{
	std::cout << "Export " << std::fixed << std::setprecision(1) << expLen
			  << "s finished successful (Duration=" << elapsed << " ms)\n";
}

void LogPathCreated(const std::filesystem::path& path)
{
	std::cout << "path (" << path << ") had not been exist -> created";
}

void LogAbortByUser()
{
	std::cout << "aborted by user";
}
