#include "FilesystemHandler.h"

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
