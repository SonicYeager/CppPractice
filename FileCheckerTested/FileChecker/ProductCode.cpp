#include "ProductCode.h"

bool FileChecker::Check(const std::wstring& str)
{
	std::filesystem::path filePath{str};
	if(IsInvalidPathString(filePath))
		return false;

	if (not std::filesystem::exists(filePath))
		return false;

	auto lreader = CreateReader();
	if (not lreader->SetLib("reader.dll"))
		return false;

	bool result{ false };

	if(lreader->IsExtensionSupported(filePath))
	{
		result = lreader->CheckFile(filePath);
	}
	return result;
}

bool HasFileName(const std::filesystem::path& filePath);
bool HasExtension(const std::filesystem::path& filePath);

bool FileChecker::IsInvalidPathString(const std::wstring& filePath) const
{
	return filePath.empty() or not HasExtension(filePath) or not HasFileName(filePath);
}

std::unique_ptr<LegacyReader> FileChecker::CreateReader()
{
	LegacyReader lreader;
	return std::make_unique<LegacyReader>(lreader);
}

bool HasFileName(const std::filesystem::path& filePath)
{
	return not filePath.filename().empty();
}

bool HasExtension(const std::filesystem::path& filePath)
{
	return not filePath.extension().empty();
}

LegacyReader::~LegacyReader()
{
	FreeLibrary(lib);
}

bool LegacyReader::SetLib(const std::string& libStr)
{
	HMODULE lib = ::LoadLibrary(libStr.c_str());
	if (not lib)
		return false;
	else
		this->lib = lib;
	return true;
}

bool LegacyReader::CheckFile(const std::filesystem::path& path)
{
	using CheckFileFunc = bool (*)(const wchar_t*);
	auto checkFile = reinterpret_cast<CheckFileFunc>(::GetProcAddress(lib, "CheckFile"));
	if (checkFile(path.c_str()))
	{
		return true;
	}
	return false;
}

bool LegacyReader::IsExtensionSupported(const std::filesystem::path& path)
{
	using IsExtSupported = bool (*)(const wchar_t*);
	auto isExtSupported = reinterpret_cast<IsExtSupported>(::GetProcAddress(lib, "IsExtensionSupported"));
	return isExtSupported(path.extension().c_str());
}
