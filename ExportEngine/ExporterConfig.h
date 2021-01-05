#pragma once
#include "ExportData.h"

std::unique_ptr<IVideoExport> ConfigExporter(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags);

