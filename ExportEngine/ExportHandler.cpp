#include "ExportHandler.h"

void ExportHandler::Initialize(IVideoExport* pExporter, const std::filesystem::path& target)
{
	pExporter->Initialize(target);
}

inline bool ExportHandler::ExportVideoFrame(IVideoExport* pExporter, VideoFrame* videoframe, size_t& written)
{
	return pExporter->EncodeVideo(videoframe, &written);
}
