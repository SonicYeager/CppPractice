#pragma once
#include <string>
#include "ExportData.h"


class ExportEngine
{
public:
	bool Bounce(const ExportEngineConfig&);

private:
	bool CheckBounceIsValid(const ExportConfig& exConfig, const ExportEngineConfig& config) const;
};
