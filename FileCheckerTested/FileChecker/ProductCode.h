#pragma once
#include <string>
#include <sys/stat.h>
#include <windows.h>
#include <memory>

class Reader
{
public:
	~Reader();
	virtual void SetLib(const HMODULE&);
	virtual bool CheckFile(const std::wstring&);
	virtual bool IsExtensionSupported(const std::wstring&);

private:
	HMODULE lib;
};

class FileChecker
{
public:
	FileChecker() = default;
	bool Check(const std::wstring& filePath);

private:
	bool IsInvalidPathString(const std::wstring&) const;

protected:
	virtual void CreateReader();
	std::unique_ptr<Reader> reader;
};