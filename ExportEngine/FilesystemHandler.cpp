#include "FilesystemHandler.h"
#include "LogHandler.h"

std::filesystem::path GetAlternativeFileName(bool hasFlagRename, const std::filesystem::path& targetFileName)
{
	std::filesystem::path target{targetFileName};
	if(hasFlagRename && std::filesystem::exists(target))
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
			LogPathCreated(path);
		else
			throw std::exception("could not create target directory");
	}
}

std::filesystem::path ConfigDirectory(bool hasFlag, std::filesystem::path target)
{
	CreateDirectoryIfIsNone(target.stem());
	return GetAlternativeFileName(hasFlag, target);
}
