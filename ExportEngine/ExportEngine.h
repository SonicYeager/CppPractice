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
	int m_Result = 0;
	IVideoExport* m_pExporter = nullptr;
	IUserInterface* m_pUserInterface = nullptr;
};

void ConfigPath();

void ThrowIfProgressIsNullPtr();

void OpenProgress();

void IsProgressAbort();

void CloseProgress();

void SetProgress(const size_t& totalWritten);
