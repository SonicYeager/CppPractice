#include "ExportHandler.h"

ExportHandler::ExportHandler(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags)
{
	exporter = ConfigExporter(pExporter, create, flags);
}

void ExportHandler::Initialize(const std::filesystem::path& target)
{
	exporter->Initialize(target);
}

bool ExportHandler::ExportVideoFrame(std::unique_ptr<VideoFrame> videoframe, size_t& written)
{
	return exporter->EncodeVideo(videoframe.get(), &written);
}

ExportConfig ExportHandler::GetExportConfig() const
{
	ExportConfig config{};
	exporter->GetExportInfo(&config);
	return config;
}
