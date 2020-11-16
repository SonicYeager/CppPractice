#pragma once
#include "ExportData.h"
#include "Log.h"
#include <iostream>

struct FilesystemHandler
{
	void ConfigPath(ExportEngineConfig& config, const Log& log);
	void FindOtherFile(ExportEngineConfig& config);
};