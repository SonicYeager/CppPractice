#include "ExportEngine.h"
#include "VideoEngine.h"
#include <iostream>
#include <chrono>
#include "ArrangmentData.h"

void FindOtherFile(std::filesystem::path& targetFile)
{
	std::wstring newFilename = targetFile.stem();
	newFilename.push_back(L'_');
	newFilename.append(targetFile.extension());
	targetFile.replace_filename(newFilename);
}

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	try
	{
		size_t totalWritten = 0;
		m_config = config;
		m_Result = -1;
		if(m_config.pExporter)
		{
			m_pExporter = m_config.pExporter;
		}
		else
		{
			if(m_config.createExport)
				m_pExporter = m_config.createExport(m_config.flagsExport & RGB_EXPORT ? ExportColorFormat::RGB : ExportColorFormat::YUV);
			else
				throw std::exception("no export available");
		}

		if(CheckBounceIsValid())
		{
			if(m_config.pExporter)
			{
				bool success = CheckFeatureProtection(m_config.pExporter);
				if(not success)
					throw std::exception("Feature not allowed");
			}
			if(RENAME_FILENAME_IF_EXIST & m_config.flagsExport && std::filesystem::exists(m_config.targetFileName))
				FindOtherFile(m_config.targetFileName);
			auto path = m_config.targetFileName.stem();
			if(std::filesystem::is_directory(path))
			{
				if(std::filesystem::create_directory(path))
					std::cout << "path (" << path << ") had not been exist -> created";
				else
					throw std::exception("could not create target directory");
			}
			m_pUserInterface = m_config.pUserInterface;
			if(m_pUserInterface == nullptr)
				throw std::exception("no progress is set");
			auto range = m_config.pPI->rangeEnd - m_config.pPI->rangeStart;
			m_pUserInterface->OpenProgress("Export", range);
			
			PrepareVideoEngine(*m_config.pPI);
			m_pExporter->Initialize(m_config.targetFileName);
			std::cout << "Export" << m_config.targetFileName;
			if(m_config.pPI->rangeEnd > m_config.pPI->rangeStart)
				std::cout << " from " << m_config.pPI->rangeStart << " to " << m_config.pPI->rangeEnd << " started.\n";
			
			auto start = std::chrono::high_resolution_clock::now();
			for(__int64 i = m_config.pPI->rangeStart; i < m_config.pPI->rangeEnd;)
			{
				if(m_pUserInterface->Aborted())
				{
					m_Result = 1;
					throw 5;
				}
				auto videoframe = VideoEngineGetFrame(i);
				if(videoframe == nullptr)
					throw std::exception("GetFrame error");
				ExportConfig exConfig{};
				m_pExporter->GetExportInfo(&exConfig);
				if(static_cast<ExportColorFormat>(videoframe->colorFormat) != exConfig.format)
				{
					if(videoframe->colorFormat == VideoFrameColorFormat::BGR and exConfig.format == ExportColorFormat::YUV)
					{
						for(Pixel& c : videoframe->pixels)
						{
							Pixel bgr = c;
							c.y = static_cast<char>(0.299 * bgr.b + 0.587 * bgr.g + 0.114 * bgr.r);
							c.u = static_cast<char>((bgr.r - c.y) * 0.493);
							c.v = static_cast<char>((bgr.b - c.y) * 0.877);
						}
					}
					else if(videoframe->colorFormat == VideoFrameColorFormat::RGB and exConfig.format == ExportColorFormat::YUV)
					{
						for(Pixel& c : videoframe->pixels)
						{
							Pixel rgb = c;
							c.y = static_cast<char>(0.299 * rgb.r + 0.587 * rgb.g + 0.114 * rgb.b);
							c.u = static_cast<char>((rgb.b - c.y) * 0.493);
							c.v = static_cast<char>((rgb.r - c.y) * 0.877);
						}
					}
				}
				size_t written = 0;
				bool success = m_pExporter->EncodeVideo(videoframe, &written);
				if(success)
				{
					totalWritten += written;
					m_pUserInterface->SetProgress(totalWritten);
					i += static_cast<__int64>(m_config.pPI->frameRate);
					delete videoframe;
				}
				else
				{
					delete videoframe;
					throw std::exception("Encode error");
				}
			}
			auto end = std::chrono::high_resolution_clock::now();
			const double expLen = m_config.pPI->rangeEnd - m_config.pPI->rangeStart / m_config.pPI->frameRate;
			std::cout << "Export " << std::fixed << std::setprecision(1) << expLen
					  << "s finished successful (Duration=" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)\n";
			m_Result = 1;
		}
	}
	catch(std::exception ex)
	{
		std::cerr << "error during export occurred: " << ex.what();
	}
	catch(int)
	{
		std::cout << "aborted by user";
	}
	ShutdownVideoEngine();
	m_pUserInterface->CloseProgress();
	m_pUserInterface = nullptr;
	m_pExporter = nullptr;
	m_config = {};
	return m_Result == 1;
}

bool ExportEngine::CheckBounceIsValid() const
{
	if(m_config.flagsExport & BOUNCE_IF_VALID and m_pExporter and m_config.pPI)
	{
		ExportConfig exConfig{};
		m_pExporter->GetExportInfo(&exConfig);
		return m_config.pPI->aspectRation == exConfig.aspectRatio //
			and m_config.pPI->width >= exConfig.width //
			and m_config.pPI->height >= exConfig.height //
			and not m_config.targetFileName.empty();
	}
	return false;
}

bool ExportEngine::CheckFeatureProtection(IVideoExport* pExporter) const
{
	if(not pExporter)
		return false;
	ExportConfig config{};
	pExporter->GetExportInfo(&config);
	return config.type == ExportType::DVD or config.type == ExportType::MP4;
}
