#pragma once
#include "ExportData.h"
#include <iostream>

struct FilesystemHandler
{
	void ConfigPath(ExportEngineConfig& config);
	void FindOtherFile(ExportEngineConfig& config);
};