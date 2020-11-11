#include "ProductCode.h"
#include <sys/stat.h>
#include <windows.h>


struct Reader
{
	Reader()
		: lib(::LoadLibrary("reader.dll"))
	{}
	~Reader()
	{
		if(lib)
			FreeLibrary(lib);
	}
	bool CheckFile(const std::wstring& filePath)
	{
		using CheckFileFunc = bool (*)(const wchar_t*);
		auto checkFile = reinterpret_cast<CheckFileFunc>(::GetProcAddress(lib, "CheckFile"));
		return checkFile(filePath.c_str());
	}
	bool IsExtensionSupported(const std::wstring& extension)
	{
		using IsExtSupported = bool (*)(const wchar_t*);
		auto isExtSupported = reinterpret_cast<IsExtSupported>(::GetProcAddress(lib, "IsExtensionSupported"));
		return isExtSupported(extension.c_str());
	}
	bool IsLoaded()
	{
		return lib;
	}
	HMODULE lib;
};

bool FileChecker::Check(const std::wstring& filePath)
{
	if(IsInvalidPathString(filePath))
		return false;

	struct _stat buf
	{};
	if(::_wstat(filePath.c_str(), &buf) != 0)
		return false;

	Reader reader{};
	if (not reader.IsLoaded())
		return false;

	bool result = false;
	// Check extension first because it is faster
	if(reader.IsExtensionSupported(filePath.substr(filePath.find_last_of('.') + 1)))
	{
		if(reader.CheckFile(filePath))
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

