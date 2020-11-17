#pragma once
#include "ExportData.h"

IVideoExport* ConfigExporter(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags);