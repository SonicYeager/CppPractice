#pragma once
#include <string>
#include "ExportData.h"


class ExportEngine
{
public:
	bool Bounce(const ExportEngineConfig&);
	bool BounceGrayscale(const ExportEngineConfig&);
};
