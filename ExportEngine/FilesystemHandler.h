#pragma once
#include "ExportData.h"

std::filesystem::path GetAlternativeFileName(ExportFlags flags, const std::filesystem::path& targetFileName);
void CreateDirectoryIfIsNone(const std::filesystem::path& path);