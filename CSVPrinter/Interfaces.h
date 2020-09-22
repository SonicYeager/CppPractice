#pragma once
#include "InternalTypes.h"
#include <sstream>

class IUI
{
public:
	void virtual Print(const std::ostringstream&) = 0;
	virtual ~IUI() {}
};

class IResource
{
public:
	std::vector<std::string> virtual Read(const std::string&) = 0;
	virtual ~IResource() {}
};

class ILogic
{
public:
	std::vector<std::string> virtual Format(const std::vector<std::string>&) = 0;
	virtual ~ILogic() {}
};