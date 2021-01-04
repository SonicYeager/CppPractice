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

Progress GetOpenedProgress(IUserInterface* ui, long long range)
{
	Progress progress{ui};
	progress.OpenProgress(range);
	return progress;
}

WrappedVideoEngine GetPreparedWrappedVideoEngine(const ProjectInfo& pi)
{
	WrappedVideoEngine wVideoEng;
	wVideoEng.Prepare(pi);
	return wVideoEng;
}

Measurement ExportFramesReturnElapsedTime(Progress& progress, int& result, WrappedVideoEngine& wVideoEng, const ExportEngineConfig& config, ExportHandler& expHandler)
{
	Measurement measurement;
	measurement.Start();
	expHandler.ExportFrames(progress, result, wVideoEng, config);
	measurement.Stop();
	return measurement;
}

int ExportIfBounceIsValid(const ExportEngineConfig& config)
{
	int result{-1};
	try
	{
		ExportHandler expHandler{config.pExporter, config.createExport, static_cast<ExportFlags>(config.flagsExport)};
		if(expHandler.CheckBounceIsValid(config))
		{
			ThrowIfProtectedFeature(expHandler.GetExportConfig().type);
			auto progress = GetOpenedProgress(config.pUserInterface, config.pPI->rangeEnd - config.pPI->rangeStart);
			auto targetPath = ConfigDirectory(static_cast<ExportFlags>(config.flagsExport) == ExportFlags::RENAME_FILENAME_IF_EXIST, config.targetFileName);
			auto wVideoEng = GetPreparedWrappedVideoEngine(*config.pPI);
			expHandler.Initialize(targetPath);
			LogExportRange(config.pPI->rangeStart, config.pPI->rangeEnd, targetPath.string());
			auto measurement = ExportFramesReturnElapsedTime(progress, result, wVideoEng, config, expHandler);
			LogExportTime(config.pPI->rangeEnd - config.pPI->rangeStart / config.pPI->frameRate, measurement.GetElapsedTime());
			result = 1;
		}
	}
	catch(std::exception ex)
	{
		LogExportError(ex);
	}
	return result;
}

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	int result = ExportIfBounceIsValid(config);
	return result == 1;
}

