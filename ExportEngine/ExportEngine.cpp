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

void OpenProgress(IUserInterface* ui, long long range)
{
	ui->OpenProgress("Export", range);
}

bool ExportEngine::Bounce(const ExportEngineConfig& config)
{
	try
	{
		size_t totalWritten = 0;
		m_Result = -1;
		m_config = config;
		m_pExporter = ConfigExporter(m_config.pExporter, m_config.createExport, static_cast<ExportFlags>(m_config.flagsExport)); //resource leak (no exporter deletion if created :/)
		if(CheckBounceIsValid())
		{
			ThrowIfProtectedFeature(m_pExporter);

			m_pUserInterface = ThrowIfProgressNullPtr(config.pUserInterface);
			OpenProgress(m_pUserInterface, m_config.pPI->rangeEnd - m_config.pPI->rangeStart);

			m_config.targetFileName = ConfigDirectory(static_cast<ExportFlags>(m_config.flagsExport), m_config.targetFileName);
			
			WrappedVideoEngine::Prepare(*m_config.pPI);

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

				auto videoframe = WrappedVideoEngine::GetFrame(i);
				WrappedVideoEngine::ValidateVideoFrame(videoframe);

				auto exConfig = GetExportConfig(m_pExporter);

				ConvertToYUV(videoframe, exConfig.format);

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
	WrappedVideoEngine::ShutDown();
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
		auto exConfig = GetExportConfig(m_pExporter);
		return m_config.pPI->aspectRation == exConfig.aspectRatio
			and m_config.pPI->width >= exConfig.width
			and m_config.pPI->height >= exConfig.height
			and not m_config.targetFileName.empty();
	}
	return false;
}
