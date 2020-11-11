#pragma once
#include <string>
#include <memory>
#include <filesystem>

struct IReader
{
	virtual ~IReader() = default;
	virtual bool CheckFile(const std::wstring& filePath) = 0;
	virtual bool IsExtensionSupported(const std::wstring& extension) = 0;
	virtual bool IsLoaded() = 0;
};


class FileChecker
{
public:
	bool Check(const std::filesystem::path & filePath);

private:
	bool IsInvalidPathString(const std::wstring&) const;

protected:
	virtual std::unique_ptr<IReader> CreateReader();
};
