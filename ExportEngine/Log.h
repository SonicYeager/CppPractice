#pragma once
#include "ExportData.h"
#include "Measurement.h"
#include <iostream>

struct Log
{
	void LogFileName(const ExportEngineConfig& config) const;
	void LogRange(const ExportEngineConfig& config) const;
	void LogExport(const Measurement& measure, const ExportEngineConfig& config) const;
	void LogCreatedDirectory(const std::filesystem::path& path) const;
};