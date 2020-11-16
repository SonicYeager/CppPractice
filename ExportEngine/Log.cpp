#include "Log.h"

void Log::LogFileName(const ExportEngineConfig& config)
{
	std::cout << "Export" << config.targetFileName;
}
