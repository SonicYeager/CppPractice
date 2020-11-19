#pragma once
#include <string>
#include "ExportData.h"


class ExportEngine
{
public:
	bool Bounce(const ExportEngineConfig&);

private:
	bool CheckBounceIsValid(const ExportConfig&) const;

	ExportEngineConfig m_config = {};
	int m_Result = 0;
};
