#pragma once
#include <string>
#include "ExportData.h"


class ExportEngine
{
public:
	bool Bounce(const ExportEngineConfig&);

private:
	bool CheckBounceIsValid() const;
	void CheckFeatureProtection(IVideoExport*) const;

	ExportEngineConfig m_config = {};
	IVideoExport* m_pExporter = nullptr;
};
