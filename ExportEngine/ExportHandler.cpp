#include "ExportHandler.h"
#include "ColorSpaceConverter.h"

bool CanExportNextFrame(bool aborted, bool inRange)
{
	return not aborted && inRange;
}

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

bool ExportHandler::CheckBounceIsValid(const ExportEngineConfig& config)
{
	if(config.flagsExport & BOUNCE_IF_VALID and config.pPI)
	{
		return config.pPI->aspectRation == GetExportConfig().aspectRatio and config.pPI->width >= GetExportConfig().width and config.pPI->height >= GetExportConfig().height and not config.targetFileName.empty();
	}
	return false;
}

void ExportHandler::ExportFrames(Progress& progress, int& result, WrappedVideoEngine& wVideoEng, const ExportEngineConfig& config)
{
	while(CanExportNextFrame(progress.IsAborded(result), wVideoEng.IsInRange(config.pPI->rangeStart, config.pPI->rangeEnd)))
	{
		auto exConfig = GetExportConfig();
		auto videoframe = wVideoEng.GetNextFrame();
		ConvertToYUV(videoframe, exConfig.format);
		auto written = ExportVideoFrame(std::move(videoframe));
		progress.AddProgress(written);
	}
}

void ExportHandler::ExportGrayscaleFrames(Progress& progress, int& result, WrappedVideoEngine& wVideoEng, const ExportEngineConfig& config)
{
	while(CanExportNextFrame(progress.IsAborded(result), wVideoEng.IsInRange(config.pPI->rangeStart, config.pPI->rangeEnd)))
	{
		auto exConfig = GetExportConfig();
		auto videoframe = wVideoEng.GetNextFrame();
		ConvertToGrayscale(videoframe);
		auto written = ExportVideoFrame(std::move(videoframe));
		progress.AddProgress(written);
	}
}

ExportConfig ExportHandler::GetExportConfig() const
{
	ExportConfig config{};
	exporter->GetExportInfo(&config);
	return config;
}
