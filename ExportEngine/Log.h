#pragma once
#include "ExportData.h"
#include "Measurement.h"
#include <iostream>

struct Log
{
	void LogFileName(const ExportEngineConfig& config);
	void LogRange(const ExportEngineConfig& config);
	void LogExport(const Measurement& measure, const ExportEngineConfig& config);
};