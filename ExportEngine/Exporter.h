#pragma once
#include "VideoEngine.h"
#include <filesystem>

enum class ExportType
{
	DVD = 0,
	MP4,
	MP3
};

enum class ExportColorFormat
{
	RGB = 0,
	YUV
};

struct ExportConfig
{
	int width = 1920;
	int height = 1080;
	double frameRate = 25.0;
	double aspectRatio = 16.0 / 9.0;
	ExportType type = ExportType::DVD;
	ExportColorFormat format = ExportColorFormat::YUV;
};


class IVideoExport
{
public:
	virtual void Initialize(std::filesystem::path targetFilePath) = 0;
	virtual bool EncodeVideo(VideoFrame*, size_t*) = 0;
	virtual void GetExportInfo(ExportConfig*) = 0;
	virtual ~IVideoExport() = default;

	static IVideoExport* Create(ExportColorFormat);
};
