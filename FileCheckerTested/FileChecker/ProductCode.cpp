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

	if (not std::filesystem::exists(path))
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

bool HasFileName(const std::filesystem::path & filePath);

bool FileChecker::IsInvalidPathString(const std::filesystem::path& filePath) const
{
	return filePath.empty() or not filePath.has_extension() or not HasFileName(filePath);
}

bool HasFileName(const std::filesystem::path & filePath)
{
	auto fname = filePath.filename().string();
	auto posExtBeg = fname.find_last_of('.') + 1;
	auto posFileNameBeg = fname.find_last_of("\\/") + 1;
	fname = fname.substr(posFileNameBeg, (posExtBeg - 1) - posFileNameBeg);
	auto inv = fname.find_last_of(".\\/");;
	return not fname.empty() and inv == std::wstring::npos;
}

