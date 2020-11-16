#pragma once
#include "ExportData.h"
#include <iostream>

struct Log
{
	void LogFileName(const ExportEngineConfig& config);
	void LogRange(const ExportEngineConfig& config);
};