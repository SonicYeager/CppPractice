#include "ExportEngine.h"
#include "VideoEngine.h"
#include <iostream>
#include <chrono>
#include "ArrangmentData.h"

#include "FeatureProtection.h"
#include "FilesystemHandler.h"
#include "Measurement.h"
#include "LogHandler.h"
#include "ExportHandler.h"

int ExportIfBounceIsValid(const ExportEngineConfig& config)
{
	int result{-1};
	ExportHandler expHandler{config.pExporter, config.createExport, static_cast<ExportFlags>(config.flagsExport)};
	if(expHandler.CheckBounceIsValid(config))
	{
		ThrowIfProtectedFeature(expHandler.GetExportConfig().type);
		Progress progress{config.pUserInterface};
		progress.OpenProgress(config.pPI->rangeEnd - config.pPI->rangeStart);
		auto targetPath = ConfigDirectory(static_cast<ExportFlags>(config.flagsExport) == ExportFlags::RENAME_FILENAME_IF_EXIST, config.targetFileName);
		WrappedVideoEngine wVideoEng;
		wVideoEng.Prepare(*config.pPI);
		expHandler.Initialize(targetPath);
		LogExportRange(config.pPI->rangeStart, config.pPI->rangeEnd, targetPath.string());
		Measurement measurement;
		measurement.Start();
		expHandler.ExportFrames(progress, result, wVideoEng, config);
		measurement.Stop();
		LogExportTime(config.pPI->rangeEnd - config.pPI->rangeStart / config.pPI->frameRate, measurement.GetElapsedTime());
		result = 1;
	}
	return result;
}

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	int result{-1};
	try
	{
		result = ExportIfBounceIsValid(config);
	}
	catch(std::exception ex)
	{
		LogExportError(ex);
	}
	return result == 1;
}

