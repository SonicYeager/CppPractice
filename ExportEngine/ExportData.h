#pragma once
#include <functional>
#include "Exporter.h"
#include "UserInterface.h"

struct ProjectInfo;


enum ExportFlags
{
	BOUNCE_IF_VALID = 1,
	RENAME_FILENAME_IF_EXIST = 2,
	RGB_EXPORT = 4
};


struct ExportEngineConfig
{
	std::filesystem::path targetFileName = L"ExportEngine.bmp";
	ProjectInfo* pPI = nullptr;
	IVideoExport* pExporter = nullptr;
	IUserInterface* pUserInterface = nullptr;
	unsigned long flagsExport = 0;
	std::function<IVideoExport*(ExportColorFormat)> createExport = IVideoExport::Create;
};
