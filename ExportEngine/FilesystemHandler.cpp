#include "FilesystemHandler.h"
#include <iostream>

std::filesystem::path GetAlternativeFileName(ExportFlags flags, const std::filesystem::path& targetFileName)
{
	std::filesystem::path target{targetFileName};
	if(RENAME_FILENAME_IF_EXIST & flags && std::filesystem::exists(target))
	{
		std::wstring newFilename = target.stem();
		newFilename.push_back(L'_');
		newFilename.append(target.extension());
		target.replace_filename(newFilename);
	}
	return target;
}

void CreateDirectoryIfIsNone(const std::filesystem::path& path)
{
	if(not std::filesystem::is_directory(path))
	{
		if(std::filesystem::create_directory(path))
			std::cout << "path (" << path << ") had not been exist -> created";	//Logger
		else
			throw std::exception("could not create target directory");
	}
}

std::filesystem::path ConfigDirectory(ExportFlags flags, std::filesystem::path target)
{
	CreateDirectoryIfIsNone(target.stem());
	return GetAlternativeFileName(flags, target);
}
