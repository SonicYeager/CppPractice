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

bool ExportHandler::CheckBounceIsValid(const ExportConfig& exConfig, const ExportEngineConfig& config)
{
	if(config.flagsExport & BOUNCE_IF_VALID and config.pPI)
	{
		return config.pPI->aspectRation == exConfig.aspectRatio and config.pPI->width >= exConfig.width and config.pPI->height >= exConfig.height and not config.targetFileName.empty();
	}
	return false;
}

ExportConfig ExportHandler::GetExportConfig() const
{
	ExportConfig config{};
	exporter->GetExportInfo(&config);
	return config;
}
