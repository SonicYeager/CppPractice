#include "ProductCode.h"

bool FileChecker::Check(const std::wstring& filePath)
{
	if(IsInvalidPathString(filePath))
		return false;

	struct _stat buf
	{};
	if(::_wstat(filePath.c_str(), &buf) != 0)
		return false;

	auto lreader = CreateReader();
	bool result{ false };

	if(lreader->IsExtensionSupported(filePath))
	{
		result = lreader->CheckFile(filePath);
	}
	return result;
}

bool HasFileName(const std::wstring& filePath);
bool HasExtension(const std::wstring& filePath);

bool FileChecker::IsInvalidPathString(const std::wstring& filePath) const
{
	return filePath.empty() or not HasExtension(filePath) or not HasFileName(filePath);
}

std::unique_ptr<LegacyReader> FileChecker::CreateReader()
{
	LegacyReader lreader;
	lreader.SetLib("reader.dll");
	return std::make_unique<LegacyReader>(lreader);
}

bool HasFileName(const std::wstring& filePath)
{
	auto posExtBeg = filePath.find_last_of('.') + 1;
	auto posFileNameBeg = filePath.find_last_of('\\') + 1;
	auto ext = filePath.substr(posExtBeg);
	auto fil = filePath.substr(posFileNameBeg, (posExtBeg - 1) - posFileNameBeg);
	auto inv = fil.find_last_of(L".\\/");
	return not fil.empty() and inv == std::wstring::npos;
}

bool HasExtension(const std::wstring& filePath)
{
	auto ext = filePath.substr(filePath.find_last_of('.') + 1);
	auto inv = ext.find_last_of(L".\\/");
	return not ext.empty() and inv == std::wstring::npos;
}

LegacyReader::~LegacyReader()
{
	FreeLibrary(lib);
}

void LegacyReader::SetLib(const std::string& libStr)
{
	HMODULE lib = ::LoadLibrary(libStr.c_str());
	if (not lib)
		throw; //specify exeption!!
	else
		this->lib = lib;
}

bool LegacyReader::CheckFile(const std::wstring& path)
{
	using CheckFileFunc = bool (*)(const wchar_t*);
	auto checkFile = reinterpret_cast<CheckFileFunc>(::GetProcAddress(lib, "CheckFile"));
	if (checkFile(path.c_str()))
	{
		return true;
	}
	return false;
}

bool LegacyReader::IsExtensionSupported(const std::wstring& path)
{
	using IsExtSupported = bool (*)(const wchar_t*);
	auto isExtSupported = reinterpret_cast<IsExtSupported>(::GetProcAddress(lib, "IsExtensionSupported"));
	return isExtSupported(path.substr(path.find_last_of('.') + 1).c_str());
}
