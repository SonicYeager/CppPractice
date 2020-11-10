#pragma once
#include <string>
#include <memory>
#include <filesystem>
#include <windows.h>

class LegacyReader
{
public:
	~LegacyReader();
	virtual void SetLib(const std::string&);
	virtual bool CheckFile(const std::filesystem::path& path);
	virtual bool IsExtensionSupported(const std::filesystem::path& path);
private:
	HMODULE lib{};
};

class FileChecker
{
public:
	bool Check(const std::wstring& filePath);

private:
	bool IsInvalidPathString(const std::wstring&) const;
	virtual std::unique_ptr<LegacyReader> CreateReader();
};
