#pragma once
#include <string>
#include "ExportData.h"


class ExportEngine
{
public:
	bool Bounce(const ExportEngineConfig&);

private:
	bool CheckBounceIsValid() const;
	bool CheckFeatureProtection(IVideoExport*) const;

	ExportEngineConfig m_config = {};
	int m_Result = 0;
	IVideoExport* m_pExporter = nullptr;
	IUserInterface* m_pUserInterface = nullptr;
};

void ConvertToYUV(VideoFrame* videoframe);

void VideoEnginePrepare();
