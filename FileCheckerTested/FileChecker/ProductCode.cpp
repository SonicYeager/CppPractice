#include "ProductCode.h"

bool FileChecker::Check(const std::wstring& path)
{
	std::filesystem::path filePath{path};
	if(IsInvalidPathString(filePath))
		return false;


	struct _stat buf
	{};
	if(::_wstat(filePath.c_str(), &buf) != 0)
		return false;

	CreateReader();
	bool result = false;

	// Check extension first because it is faster
	if(reader->IsExtensionSupported(filePath))
	{
		result = reader->CheckFile(filePath);
	}
	return result;
}

bool HasFileName(const std::filesystem::path& filePath);
bool HasExtension(const std::filesystem::path& filePath);

bool FileChecker::IsInvalidPathString(const std::filesystem::path& filePath) const
{
	return filePath.empty() or not HasExtension(filePath) or not HasFileName(filePath);
}

void FileChecker::CreateReader()
{
	reader = std::make_unique<Reader>();
	reader->SetLib(::LoadLibrary("reader.dll"));
}

bool HasFileName(const std::filesystem::path& filePath)
{
	return not filePath.filename().empty();
}

bool HasExtension(const std::filesystem::path& filePath)
{
	return not filePath.extension().empty();
}

void Reader::SetLib(const HMODULE& lib)
{
	if (not lib)
		throw;
	else
		this->lib = lib;
}

Reader::~Reader()
{
	FreeLibrary(lib);
}

bool Reader::CheckFile(const std::wstring& filePath)
{
	bool result{false};
	using CheckFileFunc = bool (*)(const wchar_t*);
	auto checkFile = reinterpret_cast<CheckFileFunc>(::GetProcAddress(lib, "CheckFile"));
	if (checkFile(filePath.c_str()))
		return true;
	return false;
}

bool Reader::IsExtensionSupported(const std::wstring& filePath)
{
	using IsExtSupported = bool (*)(const wchar_t*);
	auto isExtSupported = reinterpret_cast<IsExtSupported>(::GetProcAddress(lib, "IsExtensionSupported"));
	return isExtSupported(filePath.substr(filePath.find_last_of('.') + 1).c_str());
}
