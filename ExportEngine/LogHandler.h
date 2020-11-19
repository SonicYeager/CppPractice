#pragma once
#include "ExportData.h"

void LogExportRange(long long rangeStart, long long rangeEnd, const std::string& fileName);
void LogExportTime(double expLen, long long elapsed);
void LogPathCreated(const std::filesystem::path& path);