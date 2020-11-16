#include "Exporter.h"
#include "ExportData.h"
#include <string>
#include <fstream>
#include <windows.h>

class Exporter : public IVideoExport
{
public:
	Exporter(ExportColorFormat format)
		: m_format(format)
	{}
	void Initialize(std::filesystem::path targetFilePath) override
	{
		m_targetFilePath = targetFilePath;
	}

	bool EncodeVideo(VideoFrame* videoframe, size_t* written) override
	{
		auto filename = m_targetFilePath.stem();
		filename.concat(std::to_wstring(m_count++));
		filename.replace_extension("bmp");
		std::ofstream file(filename, std::ios::binary);
		if(not file.is_open())
			return false;
		BITMAPFILEHEADER bmFile{};
		BITMAPINFOHEADER bmInfo{};
		bmInfo.biBitCount = 24;
		bmInfo.biSize = sizeof bmInfo;
		bmInfo.biWidth = videoframe->width;
		bmInfo.biHeight = videoframe->height;
		bmInfo.biSizeImage = videoframe->pixels.size() * sizeof Pixel;
		bmInfo.biPlanes = 1;
		bmFile.bfOffBits = sizeof bmFile + sizeof bmInfo;
		bmFile.bfSize = bmFile.bfOffBits + bmInfo.biSizeImage;
		bmFile.bfType = 'MB';
		file.write(reinterpret_cast<const char*>(&bmFile), sizeof bmFile);
		file.write(reinterpret_cast<const char*>(&bmInfo), sizeof bmInfo);
		// Store as bgr because bitmaps will be interpreted so
		for(const Pixel& p : videoframe->pixels)
		{
			file.write(&p.b, 1);
			file.write(&p.g, 1);
			file.write(&p.r, 1);
		}
		*written = videoframe->pixels.size() * sizeof Pixel + sizeof bmFile + sizeof bmInfo;
		return true;
	}

	void GetExportInfo(ExportConfig* config) override
	{
		config->format = m_format;
		config->frameRate = 25.0;
		config->width = 12;
		config->height = 12;
		config->aspectRatio = 1.0;
		config->type = m_format == ExportColorFormat::RGB ? ExportType::DVD : ExportType::MP4;
	}

	std::filesystem::path m_targetFilePath = {};
	ExportColorFormat m_format;
	int m_count = 0;
};

IVideoExport* IVideoExport::Create(ExportColorFormat format)
{
	return new Exporter(format);
}

IVideoExport* IVideoExport::ConfigExporter(const ExportEngineConfig& expConf)
{
	if(expConf.pExporter)
	{
		return expConf.pExporter;
	}
	else
	{
		if(expConf.createExport)
			return expConf.createExport(expConf.flagsExport & RGB_EXPORT ? ExportColorFormat::RGB : ExportColorFormat::YUV);
		else
			throw std::exception("no export available");
	}
}
