#pragma once
#include "ExportData.h"
#include "ExporterConfig.h"

struct ExportHandler
{
	ExportHandler(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags);
	void Initialize(const std::filesystem::path& target);
	size_t ExportVideoFrame(std::unique_ptr<VideoFrame> videoframe);
	bool CheckBounceIsValid(const ExportConfig& exConfig, const ExportEngineConfig& config);
	ExportConfig GetExportConfig() const;

private:
	std::unique_ptr<IVideoExport> exporter;
};