#pragma once
#include "ExportData.h"
#include "ExporterConfig.h"
#include "ProgressHandler.h"
#include "WrappedVideoEngine.h"

struct ExportHandler
{
	ExportHandler(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags);
	void Initialize(const std::filesystem::path& target);
	size_t ExportVideoFrame(std::unique_ptr<VideoFrame> videoframe);
	bool CheckBounceIsValid(const ExportEngineConfig& config);
	void ExportFrames(Progress& progress, int& result, WrappedVideoEngine& wVideoEng, const ExportEngineConfig& config);
	void ExportGrayscaleFrames(Progress& progress, int& result, WrappedVideoEngine& wVideoEng, const ExportEngineConfig& config);
	ExportConfig GetExportConfig() const;

private:
	std::unique_ptr<IVideoExport> exporter;
};