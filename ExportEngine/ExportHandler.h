#pragma once
#include "ExportData.h"
#include "ExporterConfig.h"

struct ExportHandler
{
	ExportHandler(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags);
	void Initialize(const std::filesystem::path& target);
	bool ExportVideoFrame(VideoFrame* videoframe, size_t& written);
	ExportConfig GetExportConfig(IVideoExport* pExporter) const;

private:
	std::unique_ptr<IVideoExport> exporter;
};