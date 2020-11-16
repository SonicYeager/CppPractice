#include "ExportEngine.h"
#include "VideoEngine.h"
#include <iostream>
#include <chrono>
#include "ArrangmentData.h"
#include "ColorSpaceConverter.h"

void FindOtherFile(std::filesystem::path& targetFile)
{
	std::wstring newFilename = targetFile.stem();
	newFilename.push_back(L'_');
	newFilename.append(targetFile.extension());
	targetFile.replace_filename(newFilename);
}

IVideoExport* ConfigExporter(const ExportEngineConfig& exporterConfig)
{
	if(exporterConfig.pExporter)
	{
		return exporterConfig.pExporter;
	}
	else
	{
		if(exporterConfig.createExport)
			return exporterConfig.createExport(exporterConfig.flagsExport & RGB_EXPORT ? ExportColorFormat::RGB : ExportColorFormat::YUV);
		else
			throw std::exception("no export available");
	}
}

void ConfigPath(ExportEngineConfig& config)
{
	if(RENAME_FILENAME_IF_EXIST & config.flagsExport && std::filesystem::exists(config.targetFileName))
		FindOtherFile(config.targetFileName);
	auto path = config.targetFileName.stem();
	if(std::filesystem::is_directory(path))
	{
		if(std::filesystem::create_directory(path))
			//{ LOG-Logger
			std::cout << "path (" << path << ") had not been exist -> created";
			//}
		else
			throw std::exception("could not create target directory");
	}
}

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	VideoEngine vidEngine{};
	try
	{
		size_t totalWritten = 0;
		m_config = config;
		m_Result = -1;
		m_pExporter = ConfigExporter(m_config);
		if(CheckBounceIsValid())
		{
			CheckFeatureProtection(m_config.pExporter);
			ConfigPath(m_config);
			//{ CONFIGUI-this
			m_pUserInterface = m_config.pUserInterface;
			if(m_pUserInterface == nullptr)
				//{ THROWNOPRGRESS
				throw std::exception("no progress is set");
				//}
			auto range = m_config.pPI->rangeEnd - m_config.pPI->rangeStart;
			m_pUserInterface->OpenProgress("Export", range);
			//}
			//{ CONFIGVIDEOENGINE-this
			vidEngine.PrepareVideoEngine(*m_config.pPI);
			m_pExporter->Initialize(m_config.targetFileName);
			//{ LOG-Logger
			std::cout << "Export" << m_config.targetFileName;
			//}
			if(m_config.pPI->rangeEnd > m_config.pPI->rangeStart)
				//{ LOG-Logger
				std::cout << " from " << m_config.pPI->rangeStart << " to " << m_config.pPI->rangeEnd << " started.\n";
				//}
			//}
			//{ START-Measurement
			auto start = std::chrono::high_resolution_clock::now();
			//}
			//{ VALIDATEFRAMES-this | CONVERTFRAMES-Converter | WRITEFRAMES-this
			for(__int64 i = m_config.pPI->rangeStart; i < m_config.pPI->rangeEnd;)
			{
				//{ THROWUSERABORT
				if(m_pUserInterface->Aborted())
				{
					m_Result = 1;
					throw 5;
				}
				//} 
				auto videoframe = vidEngine.VideoEngineGetFrame(i);
				if(videoframe == nullptr)
					throw std::exception("GetFrame error");
				ColorSpaceConverter csc{};
				csc.ConvertFrameColorFormat(m_pExporter, videoframe);
				//{ WRITEFRAME-this
				size_t written = 0;
				bool success = m_pExporter->EncodeVideo(videoframe, &written);
				if(success)
				{
					totalWritten += written;
					//{ OnProgress
					m_pUserInterface->SetProgress(totalWritten);
					//}
					i += static_cast<__int64>(m_config.pPI->frameRate); //next iter
					delete videoframe;
				}
				else
				{
					delete videoframe;
					throw std::exception("Encode error");
				}
				//}
			}
			//}
			//{ STOP-Measurement
			auto end = std::chrono::high_resolution_clock::now();
			//}
			//{ LOG-Logger
			const double expLen = m_config.pPI->rangeEnd - m_config.pPI->rangeStart / m_config.pPI->frameRate;
			std::cout << "Export " << std::fixed << std::setprecision(1) << expLen
					  << "s finished successful (Duration=" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms)\n";
			//}
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
	//{ CLEANUP-this
	vidEngine.ShutdownVideoEngine();
	m_pUserInterface->CloseProgress();
	m_pUserInterface = nullptr;
	m_pExporter = nullptr;
	m_config = {};
	//}
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

void ExportEngine::CheckFeatureProtection(IVideoExport* pExporter) const
{
	if(pExporter)
	{
		ExportConfig config{};
		pExporter->GetExportInfo(&config);
		if(not(config.type == ExportType::DVD) or not (config.type == ExportType::MP4))
			throw std::exception("Feature not allowed");
	}
}
