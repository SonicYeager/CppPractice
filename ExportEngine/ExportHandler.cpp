#include "ExportHandler.h"

ExportHandler::ExportHandler(IVideoExport* pExporter, std::function<IVideoExport*(ExportColorFormat)> create, ExportFlags flags)
{
	exporter = ConfigExporter(pExporter, create, flags);
}

void ExportHandler::Initialize(const std::filesystem::path& target)
{
	exporter->Initialize(target);
}

size_t ExportHandler::ExportVideoFrame(std::unique_ptr<VideoFrame> videoframe)
{
	size_t written;
	if(not exporter->EncodeVideo(videoframe.get(), &written))
		throw std::exception("Encode error");
	return written;
}

ExportConfig ExportHandler::GetExportConfig() const
{
	ExportConfig config{};
	exporter->GetExportInfo(&config);
	return config;
}
