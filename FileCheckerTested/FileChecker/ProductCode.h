#pragma once
#include <string>

class FileChecker
{
public:
	bool Check(const std::wstring& filePath);

private:
	bool IsInvalidPathString(const std::wstring&) const;
};
