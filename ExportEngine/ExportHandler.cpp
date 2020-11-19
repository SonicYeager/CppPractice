#include "ExportHandler.h"

ExportHandler::ExportHandler(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags)
{
	exporter = ConfigExporter(pExporter, create, flags);
}

void ExportHandler::Initialize(const std::filesystem::path& target)
{
	exporter->Initialize(target);
}

bool ExportHandler::ExportVideoFrame(VideoFrame* videoframe, size_t& written)
{
	return exporter->EncodeVideo(videoframe, &written);
}

ExportConfig ExportHandler::GetExportConfig(IVideoExport* pExporter) const
{
	ExportConfig config{};
	pExporter->GetExportInfo(&config);
	return config;
}
