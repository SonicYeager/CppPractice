#pragma once
#include "ExportData.h"

struct ExportHandler
{
	static void Initialize(IVideoExport* pExporter, const std::filesystem::path& target);
	static bool ExportVideoFrame(IVideoExport* pExporter, VideoFrame* videoframe, size_t& written);
};