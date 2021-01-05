#pragma once
#include "VideoEngine.h"
#include <filesystem>
#include <functional>

enum class ExportType
{
	DVD = 0,
	MP4,
	MP3
};

enum class ExportColorFormat
{
	RGB = 0,
	YUV,
	GRAYSCALE
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

struct ExportEngineConfig;
struct ProgressHandler;

class IVideoExport
{
public:
	virtual void Initialize(std::filesystem::path targetFilePath) = 0;
	virtual bool EncodeVideo(VideoFrame*, size_t*) = 0;
	virtual void GetExportInfo(ExportConfig*) = 0;
	virtual ~IVideoExport() = default;
	virtual void WriteFrame(VideoFrame* videoframe, size_t& totalWritten, ProgressHandler& prgHandler) = 0;

	static IVideoExport* Create(ExportColorFormat);
	static IVideoExport* ConfigExporter(const ExportEngineConfig&);
};
