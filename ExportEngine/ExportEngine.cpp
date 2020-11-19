#include "ExportEngine.h"
#include "VideoEngine.h"
#include <iostream>
#include <chrono>
#include "ArrangmentData.h"

#include "ColorSpaceConverter.h"
#include "WrappedVideoEngine.h"
#include "ExporterConfig.h"
#include "FeatureProtection.h"
#include "FilesystemHandler.h"
#include "ProgressHandler.h"
#include "Measurement.h"

void LogExportRange(long long rangeStart, long long rangeEnd, const std::string& fileName)
{
	std::cout << "Export" << fileName;
	if(rangeEnd > rangeStart)
		std::cout << " from " << rangeStart << " to " << rangeEnd << " started.\n";
}

void LogExportTime(double expLen, long long elapsed)
{
	std::cout << "Export " << std::fixed << std::setprecision(1) << expLen
			  << "s finished successful (Duration=" << elapsed << " ms)\n";
}

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	try
	{
		m_Result = -1;
		m_config = config;
		m_pExporter = ConfigExporter(m_config.pExporter, m_config.createExport, static_cast<ExportFlags>(m_config.flagsExport)); //resource leak (no exporter deletion if created :/)
		if(CheckBounceIsValid())
		{
			ThrowIfProtectedFeature(m_pExporter);

			Progress progress{config.pUserInterface};
			progress.OpenProgress(m_config.pPI->rangeEnd - m_config.pPI->rangeStart);

			m_config.targetFileName = ConfigDirectory(static_cast<ExportFlags>(m_config.flagsExport) == ExportFlags::RENAME_FILENAME_IF_EXIST, m_config.targetFileName);
			
			WrappedVideoEngine::Prepare(*m_config.pPI);

			m_pExporter->Initialize(m_config.targetFileName);

			LogExportRange(m_config.pPI->rangeStart, m_config.pPI->rangeEnd, m_config.targetFileName.string());
			
			Measurement measurement;
			measurement.Start();

			for(__int64 i = m_config.pPI->rangeStart; i < m_config.pPI->rangeEnd;)
			{
				progress.ThrowIfAbort(m_Result);

				auto videoframe = WrappedVideoEngine::GetFrame(i);
				WrappedVideoEngine::ValidateVideoFrame(videoframe);

				auto exConfig = GetExportConfig(m_pExporter);

				ConvertToYUV(videoframe, exConfig.format);

				size_t written = 0;
				bool success = m_pExporter->EncodeVideo(videoframe, &written);
				if(success)
				{
					progress.AddProgress(written);

					i += static_cast<__int64>(m_config.pPI->frameRate);

					delete videoframe;
				}
				else
				{
					delete videoframe;
					throw std::exception("Encode error");
				}
			}

			measurement.Stop();
			LogExportTime(m_config.pPI->rangeEnd - m_config.pPI->rangeStart / m_config.pPI->frameRate, measurement.GetElapsedTime());

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
	WrappedVideoEngine::ShutDown();
	m_pExporter = nullptr;
	m_config = {};
	return m_Result == 1;
}

bool ExportEngine::CheckBounceIsValid() const
{
	if(m_config.flagsExport & BOUNCE_IF_VALID and m_pExporter and m_config.pPI)
	{
		auto exConfig = GetExportConfig(m_pExporter);
		return m_config.pPI->aspectRation == exConfig.aspectRatio
			and m_config.pPI->width >= exConfig.width
			and m_config.pPI->height >= exConfig.height
			and not m_config.targetFileName.empty();
	}
	return false;
}
