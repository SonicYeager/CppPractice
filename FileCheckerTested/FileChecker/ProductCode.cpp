#include "ProductCode.h"
#include <windows.h>


struct Reader : public IReader
{
	Reader() 
		: lib(::LoadLibrary("reader.dll"))
	{}
	~Reader() override
	{
		if(lib)
			FreeLibrary(lib);
	}
	bool CheckFile(const std::wstring& filePath) override
	{
		using CheckFileFunc = bool (*)(const wchar_t*);
		auto checkFile = reinterpret_cast<CheckFileFunc>(::GetProcAddress(lib, "CheckFile"));
		return checkFile(filePath.c_str());
	}
	bool IsExtensionSupported(const std::wstring& extension) override
	{
		using IsExtSupported = bool (*)(const wchar_t*);
		auto isExtSupported = reinterpret_cast<IsExtSupported>(::GetProcAddress(lib, "IsExtensionSupported"));
		return isExtSupported(extension.c_str());
	}
	bool IsLoaded()	 override
	{
		return lib;
	}
	HMODULE lib;
};

std::unique_ptr<IReader> FileChecker::CreateReader()
{
	return std::make_unique<Reader>();
}

bool FileChecker::Check(const std::filesystem::path & path)
{
	std::wstring filePath{std::filesystem::absolute(path)};
	if(IsInvalidPathString(filePath))
		return false;

	struct _stat buf
	{};
	if(::_wstat(filePath.c_str(), &buf) != 0)
		return false;

	auto reader = CreateReader();
	if (not reader->IsLoaded())
		return false;

	bool result = false;
	// Check extension first because it is faster
	if(reader->IsExtensionSupported(filePath.substr(filePath.find_last_of('.') + 1)))
	{
		if(reader->CheckFile(filePath))
		{
			result = true;
		}
	}
	return result;
}

bool HasFileName(const std::wstring& filePath);
bool HasExtension(const std::wstring& filePath);

bool FileChecker::IsInvalidPathString(const std::wstring& filePath) const
{
	return filePath.empty() or not HasExtension(filePath) or not HasFileName(filePath);
}

bool HasFileName(const std::wstring& filePath)
{
	auto posExtBeg = filePath.find_last_of('.') + 1;
	auto posFileNameBeg = filePath.find_last_of(L"\\/") + 1;
	auto ext = filePath.substr(posExtBeg);
	auto fil = filePath.substr(posFileNameBeg, (posExtBeg - 1) - posFileNameBeg);
	auto inv = fil.find_last_of(L".\\/");
	return not fil.empty() and inv == std::wstring::npos;
}

bool HasExtension(const std::wstring& filePath)
{
	auto found = filePath.find_last_of('.');
	if (found == std::wstring::npos)
		return false;
	else 
	{
		auto ext = filePath.substr(found + 1);
		auto inv = ext.find_last_of(L".\\/");
		return not ext.empty() and inv == std::wstring::npos;
	}
}

