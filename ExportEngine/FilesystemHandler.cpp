#include "FilesystemHandler.h"

void FilesystemHandler::FindOtherFile(ExportEngineConfig& config)
{
	if(RENAME_FILENAME_IF_EXIST & config.flagsExport && std::filesystem::exists(config.targetFileName))
	{
		std::wstring newFilename = config.targetFileName.stem();
		newFilename.push_back(L'_');
		newFilename.append(config.targetFileName.extension());
		config.targetFileName.replace_filename(newFilename);
	}
}

void FilesystemHandler::ConfigPath(ExportEngineConfig& config)
{
	auto path = config.targetFileName.stem();
	if(std::filesystem::is_directory(path))
	{
		if(std::filesystem::create_directory(path))
			//{ LOG-Logger
			std::cout << "path (" << path << ") had not been exist -> created";
			//}
		else
			throw std::exception("could not create target directory");
	}
}